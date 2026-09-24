#!/bin/bash
# ==============================================================================
#   minishell_tester.sh
#
#   For each test case:
#     1. Runs the command(s) through REAL bash          -> reference output
#     2. Runs the same command(s) through ./minishell    -> candidate output
#     3. Compares stdout + exit status
#     4. Runs ./minishell once more under valgrind        -> leak check
#   Prints a final "PASS / TOTAL" summary.
#
#   Usage:
#       ./minishell_tester.sh              # full run (bash diff + valgrind)
#       ./minishell_tester.sh --fast       # skip valgrind (much faster)
#       ./minishell_tester.sh --strict-leaks   # also fail on "still reachable"
#
#   IMPORTANT: adjust PROMPT below so it EXACTLY matches the prompt string
#   your main() passes to readline() / get_input(), otherwise the prompt
#   text will leak into the captured output and break the diff.
# ==============================================================================

MINISHELL="./minishell"
PROMPT="minishell$ "

SKIP_VALGRIND=0
STRICT_LEAKS=0
for arg in "$@"; do
	case "$arg" in
		--fast) SKIP_VALGRIND=1 ;;
		--strict-leaks) STRICT_LEAKS=1 ;;
		-h|--help)
			echo "Usage: $0 [--fast] [--strict-leaks]"
			exit 0
			;;
	esac
done

# ------------------------------------------------------------------ colors --
GREEN="\033[1;32m"
RED="\033[1;31m"
YELLOW="\033[1;33m"
CYAN="\033[1;36m"
BLUE="\033[1;34m"
BOLD="\033[1m"
RESET="\033[0m"

# ------------------------------------------------------------ sanity checks --
if [ ! -x "$MINISHELL" ]; then
	echo -e "${RED}Erreur: $MINISHELL introuvable ou non executable (fais 'make').${RESET}"
	exit 1
fi

if ! command -v bash >/dev/null 2>&1; then
	echo -e "${RED}Erreur: bash introuvable, impossible de comparer.${RESET}"
	exit 1
fi

if [ "$SKIP_VALGRIND" = "0" ] && ! command -v valgrind >/dev/null 2>&1; then
	echo -e "${YELLOW}valgrind introuvable, les checks de leaks seront ignores.${RESET}"
	SKIP_VALGRIND=1
fi

# --------------------------------------------------------------- temp files --
TMPD=$(mktemp -d /tmp/minishell_tester.XXXXXX)
SUPP_FILE="$TMPD/readline_ignore.supp"
VG_LOG="$TMPD/vg.log"
ERR_BASH="$TMPD/bash.err"
ERR_MS="$TMPD/ms.err"

cleanup() {
	rm -rf "$TMPD"
}
trap cleanup EXIT

cat > "$SUPP_FILE" << 'EOF'
{
   ignore_libreadline_leaks
   Memcheck:Leak
   ...
   obj:*/libreadline.so.*
}
{
   ignore_bin_leaks
   Memcheck:Leak
   ...
   obj:/bin/*
}
{
   ignore_usr_bin_leaks
   Memcheck:Leak
   ...
   obj:/usr/bin/*
}
EOF

escape_sed() {
	printf '%s' "$1" | sed -e 's/[]\/$*.^[]/\\&/g'
}
PROMPT_ESCAPED=$(escape_sed "$PROMPT")

# ------------------------------------------------------------------ state ---
TOTAL=0
PASS=0
FAILED_TESTS=()

print_header() {
	echo -e "\n${BLUE}==============================================================${RESET}"
	echo -e "${BLUE}  $1${RESET}"
	echo -e "${BLUE}==============================================================${RESET}"
}

sum_bytes() {
	# sums every "<label>: N,NNN bytes" occurrence in $VG_LOG for a given label
	grep -o "$1: [0-9,]* bytes" "$VG_LOG" 2>/dev/null \
		| grep -o "[0-9,]*" | tr -d ',' | awk '{s+=$1} END{print s+0}'
}

leak_check() {
	# fills global leak_ok / leak_info / crashed by running minishell under valgrind
	leak_ok=1
	leak_info=""
	crashed=0
	[ "$SKIP_VALGRIND" = "1" ] && return
	: > "$VG_LOG"
	printf '%b\n' "$1" | valgrind --leak-check=full --show-leak-kinds=all \
		--suppressions="$SUPP_FILE" --log-file="$VG_LOG" "$MINISHELL" > /dev/null 2>&1
	local def ind reach
	def=$(sum_bytes "definitely lost")
	ind=$(sum_bytes "indirectly lost")
	if [ "$def" != "0" ] || [ "$ind" != "0" ]; then
		leak_ok=0
		leak_info="definitely=${def}B indirectly=${ind}B"
	fi
	if [ "$STRICT_LEAKS" = "1" ]; then
		reach=$(sum_bytes "still reachable")
		if [ "$reach" != "0" ]; then
			leak_ok=0
			leak_info="$leak_info still_reachable=${reach}B"
		fi
	fi
	if grep -q "Process terminating with default action of signal" "$VG_LOG"; then
		crashed=1
	fi
}

# ==============================================================================
#  run_test: compares minishell against real bash (stdout + exit status)
#            AND checks for leaks
# ==============================================================================
run_test() {
	local category="$1"
	local desc="$2"
	local cmd="$3"

	TOTAL=$((TOTAL + 1))
	local ok=1
	local why=""

	: > "$ERR_BASH"
	local bash_out bash_status
	bash_out=$(printf '%b\n' "$cmd" | bash 2>"$ERR_BASH")
	bash_status=$?

	: > "$ERR_MS"
	local ms_raw ms_status ms_out
	ms_raw=$(printf '%b\n' "$cmd" | "$MINISHELL" 2>"$ERR_MS")
	ms_status=$?
	ms_out=$(printf '%s' "$ms_raw" | sed "s/$PROMPT_ESCAPED//g")

	if [ "$bash_out" != "$ms_out" ]; then
		ok=0
		why="stdout differs"
	fi
	if [ "$bash_status" != "$ms_status" ]; then
		ok=0
		why="$why exit_status(bash=$bash_status,minishell=$ms_status)"
	fi

	local leak_ok leak_info crashed
	leak_check "$cmd"

	if [ "$ok" = "1" ] && [ "$leak_ok" = "1" ] && [ "$crashed" = "0" ]; then
		PASS=$((PASS + 1))
		echo -e "  [${GREEN}OK${RESET}] $desc"
	else
		FAILED_TESTS+=("[$category] $desc")
		echo -e "  [${RED}KO${RESET}] $desc"
		echo -e "     ${YELLOW}cmd:${RESET} $(printf '%b' "$cmd" | tr '\n' ';')"
		[ -n "$why" ] && echo -e "     ${YELLOW}raison:${RESET}$why"
		if [ "$bash_out" != "$ms_out" ]; then
			echo -e "     ${CYAN}bash     [$bash_status]:${RESET} $(printf '%s' "$bash_out" | head -3 | tr '\n' '|')"
			echo -e "     ${CYAN}minishell[$ms_status]:${RESET} $(printf '%s' "$ms_out" | head -3 | tr '\n' '|')"
		fi
		[ "$crashed" = "1" ] && echo -e "     ${RED}CRASH DETECTED (valgrind)${RESET}"
		[ "$leak_ok" = "0" ] && echo -e "     ${RED}LEAK: $leak_info${RESET}"
	fi
}

# ==============================================================================
#  run_leak_only_test: for cases where minishell is NOT expected to match bash
#  (syntax-error edge cases, unterminated quotes across a single line, etc,
#  which the 42 subject explicitly does not require to behave like bash).
#  Only checks: no crash + no leak.
# ==============================================================================
run_leak_only_test() {
	local category="$1"
	local desc="$2"
	local cmd="$3"

	TOTAL=$((TOTAL + 1))
	local leak_ok leak_info crashed
	leak_check "$cmd"

	if [ "$leak_ok" = "1" ] && [ "$crashed" = "0" ]; then
		PASS=$((PASS + 1))
		echo -e "  [${GREEN}OK${RESET}] $desc ${YELLOW}(pas de diff bash - divergence attendue)${RESET}"
	else
		FAILED_TESTS+=("[$category] $desc")
		echo -e "  [${RED}KO${RESET}] $desc"
		echo -e "     ${YELLOW}cmd:${RESET} $(printf '%b' "$cmd" | tr '\n' ';')"
		[ "$crashed" = "1" ] && echo -e "     ${RED}CRASH DETECTED (valgrind)${RESET}"
		[ "$leak_ok" = "0" ] && echo -e "     ${RED}LEAK: $leak_info${RESET}"
	fi
}

# ==============================================================================
#                              BATTERIE DE TESTS
# ==============================================================================

print_header "1. COMMANDES SIMPLES & ESPACES"
run_test "BASICS" "Ligne vide" ''
run_test "BASICS" "Espaces uniquement" '   '
run_test "BASICS" "Commande simple" 'ls'
run_test "BASICS" "Commande avec arguments" 'ls -la'
run_test "BASICS" "Chemin absolu" '/bin/ls'
run_test "BASICS" "Point comme argument" 'ls .'

print_header "2. COMMANDES INTROUVABLES / ERREURS"
run_test "ERRORS" "Commande introuvable" 'commande_qui_nexiste_pas_xyz'
run_test "ERRORS" "Dossier comme commande" '/bin'
run_test "ERRORS" "Chemin absolu inexistant" '/nonexistent/path/xyz'
run_test "ERRORS" "Chemin relatif inexistant" './doesnotexist_xyz'
run_test "ERRORS" "Point seul" '.'
run_test "ERRORS" "Deux points seuls" '..'

print_header "3. BUILTINS"
run_test "BUILTINS" "echo sans argument" 'echo'
run_test "BUILTINS" "echo avec arguments" 'echo hello world'
run_test "BUILTINS" "echo -n" 'echo -n pas de retour a la ligne'
run_test "BUILTINS" "echo -n -n -n (cumul)" 'echo -n -n -n toujours pas de retour'
run_test "BUILTINS" "echo -x (flag invalide = argument normal)" 'echo -x test'
run_test "BUILTINS" "pwd" 'pwd'
run_test "BUILTINS" "cd sans argument (HOME)" 'cd\npwd'
run_test "BUILTINS" "cd .." 'cd ..\npwd'
run_test "BUILTINS" "cd dossier inexistant" 'cd dossier_fantome_xyz_123'
run_test "BUILTINS" "export nouvelle variable" 'export TESTER_VAR=hello\necho $TESTER_VAR'
run_test "BUILTINS" "export puis env" 'export TESTER_VAR2=world\nenv | grep TESTER_VAR2'
run_test "BUILTINS" "export identifiant invalide" 'export 1INVALID=x'
run_test "BUILTINS" "unset variable existante" 'export TESTER_VAR3=1\nunset TESTER_VAR3\nenv | grep TESTER_VAR3'
run_test "BUILTINS" "unset sans argument" 'unset'
run_test "BUILTINS" "unset variable inexistante" 'unset VAR_FANTOME_XYZ'
run_test "BUILTINS" "exit avec code" 'exit 42'
run_test "BUILTINS" "exit code > 255 (modulo 256)" 'exit 300'
run_test "BUILTINS" "exit code negatif" 'exit -1'
run_test "BUILTINS" "exit argument non numerique" 'exit abc'
run_test "BUILTINS" "exit trop d arguments" 'exit 1 2 3'

print_header "4. QUOTES & EXPANSION"
run_test "EXPAND" "Simple quotes (pas d expansion)" "echo '\$HOME'"
run_test "EXPAND" "Double quotes (expansion)" 'echo "$HOME"'
run_test "EXPAND" "Variable dans double quotes" 'echo "valeur: $USER"'
run_test "EXPAND" "Variable inexistante" 'echo $VARIABLE_INEXISTANTE_XYZ_123'
run_test "EXPAND" "Exit status \$?" 'echo $?'
run_test "EXPAND" "Exit status apres erreur" 'commande_bidon_xyz\necho $?'
run_test "EXPAND" "Concatenation quotes" "echo abc'def'ghi"
run_test "EXPAND" "Quotes vides" "echo \"\" ''"
run_test "EXPAND" "Quotes imbriquees" "echo \"'\$USER'\""

print_header "5. REDIRECTIONS (<, >, >>)"
run_test "REDIR" "Redirection sortie simple (>)" "echo contenu_test > $TMPD/out1.txt\ncat $TMPD/out1.txt"
run_test "REDIR" "Redirection append (>>)" "echo ligne1 > $TMPD/out2.txt\necho ligne2 >> $TMPD/out2.txt\ncat $TMPD/out2.txt"
run_test "REDIR" "Redirection entree (<)" "cat < $TMPD/out1.txt"
run_test "REDIR" "Fichier source inexistant" "cat < $TMPD/fichier_fantome_xyz.txt"
run_test "REDIR" "Redirections multiples (dernier gagne)" "echo multi > $TMPD/a.txt > $TMPD/b.txt > $TMPD/c.txt\ncat $TMPD/c.txt"

print_header "6. HEREDOC (<<)"
run_test "HEREDOC" "Heredoc simple" 'cat << EOF\nligne1\nligne2\nEOF'
run_test "HEREDOC" "Heredoc avec expansion" 'export HDVAR=monde\ncat << EOF\nbonjour $HDVAR\nEOF'

print_header "7. PIPELINE (|)"
run_test "PIPES" "Pipe simple" 'echo hello | cat'
run_test "PIPES" "Pipe multiple (3 commandes)" 'echo hello | cat | cat | wc -l'
run_test "PIPES" "Cmd introuvable au debut (exit status du dernier)" 'commande_bidon_xyz | ls > /dev/null\necho $?'
run_test "PIPES" "Cmd introuvable a la fin" 'ls > /dev/null | commande_bidon_xyz\necho $?'
run_test "PIPES" "Pipe + redirections combinees" "cat < $TMPD/out1.txt | tr a-z A-Z > $TMPD/upper.txt\ncat $TMPD/upper.txt"

print_header "8. ENVIRONNEMENT / PATH"
run_test "ENV" "PATH vide -> commande introuvable" 'export PATH=\nls'
run_test "ENV" "PATH restaure -> fonctionne a nouveau" 'export PATH=\nexport PATH=/bin:/usr/bin\nls > /dev/null\necho $?'

print_header "9. ERREURS DE SYNTAXE (divergence bash attendue - leak/crash only)"
run_leak_only_test "SYNTAX" "Pipe au debut" '| ls'
run_leak_only_test "SYNTAX" "Pipe a la fin" 'ls |'
run_leak_only_test "SYNTAX" "Pipes consecutifs" 'ls || echo hi'
run_leak_only_test "SYNTAX" "Redirection sans cible" 'cat <'
run_leak_only_test "SYNTAX" "Redirections doublees" 'echo > > file'
run_leak_only_test "SYNTAX" "Guillemet simple non ferme" "echo 'test"
run_leak_only_test "SYNTAX" "Guillemet double non ferme" 'echo "test'

# ------------------------------------------------------------------ summary --
print_header "RESUME"

echo -e "${YELLOW}NB:${RESET} les signaux (Ctrl-C, Ctrl-D, Ctrl-\\\\) ne peuvent pas etre"
echo -e "automatises simplement dans un script shell classique (il faut un"
echo -e "outil type 'expect' pilotant un pseudo-terminal). Ils doivent etre"
echo -e "verifies manuellement :"
echo -e "  - Ctrl-C sur le prompt vide  -> nouvelle ligne, prompt redessine, \$? = 130"
echo -e "  - Ctrl-C pendant un heredoc  -> heredoc annule, retour au prompt"
echo -e "  - Ctrl-D sur le prompt vide  -> quitte le shell (comme exit)"
echo -e "  - Ctrl-\\\\ (SIGQUIT)          -> ignore au prompt"

echo ""
if [ ${#FAILED_TESTS[@]} -gt 0 ]; then
	echo -e "${RED}Tests en echec :${RESET}"
	for t in "${FAILED_TESTS[@]}"; do
		echo -e "  - $t"
	done
	echo ""
fi

PERCENT=0
if [ "$TOTAL" -gt 0 ]; then
	PERCENT=$((PASS * 100 / TOTAL))
fi

echo -e "${BOLD}=============================================${RESET}"
if [ "$PASS" -eq "$TOTAL" ]; then
	echo -e "${GREEN}${BOLD}  SCORE: $PASS / $TOTAL  ($PERCENT%)${RESET}"
else
	echo -e "${YELLOW}${BOLD}  SCORE: $PASS / $TOTAL  ($PERCENT%)${RESET}"
fi
echo -e "${BOLD}=============================================${RESET}"

[ "$PASS" -eq "$TOTAL" ]
exit $?