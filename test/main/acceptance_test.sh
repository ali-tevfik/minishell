# Acceptance test for minishell
# This is a program that tests the outputs of minishell. It takes no arguments.
# Run as: ./acceptance_test.sh

# Configuration parameters
PATH_TO_MINISHELL="/Users/hyilmaz/Desktop/curriculum/minishell"

# Colours
RED="\033[0;31m"
GREEN="\033[0;32m"
NC="\033[0m"

# Create tmp directory
TEST_DIR="/tmp/test_minishell"
mkdir -p $TEST_DIR
if [[ "$?" != 0 ]]; then
	echo "Could not create $TEST_DIR directory..."
	exit 1
fi

# Input file name
file_in_1="$TEST_DIR/file_in_1"

# Input files
cat << EOF > $file_in_1
codamcodingcollege
codam
ahhaha
codamamsterdam
codanmgotcha
EOF

# Program argv check
if [[ "$1" != "" ]]; then
	echo "Run as: ./acceptance_test.sh"
	echo "No arguments needed."
	exit 1
fi

# Check for minishell executable
if [[ ! -f ${PATH_TO_MINISHELL}/minishell ]]; then
	echo "Can't find ./minishell executable in $PATH_TO_MINISHELL."
	exit 1
fi

# Exit statuses for bash and minishell
exit_status_bash=""
exit_status_minishell=""

# Echo the name of the test
test_name () {
	echo "TEST: \"$1\""
}

# Run the command in bash. Only one argument: the command to run.
run_bash () {
	bash -c "$1"
	exit_status_bash="$?"
}

# Run the command in minishell. Only one argument: the command to run.
run_minishell () {
	$PATH_TO_MINISHELL/minishell -c "$1"
	exit_status_minishell="$?"
}

# Compare the output files.
compare_files () {

	diff "$1" "$2" > /dev/null
	if [[ "$?" != "0" ]]; then
		echo "${RED}ERROR${NC}: diff between "$1" and "$2""
		echo "--------------------------------------------------"
		echo "$1:"
		cat "$1"
		echo "--------------------------------------------------"
		echo "$2:"
		cat "$2"
		echo "--------------------------------------------------"
	else
		echo "${GREEN}SUCCES${NC}: "$1" and "$2" files the same"
	fi
}

compare_exit_status () {
	if [[ "$exit_status_bash" != "$exit_status_minishell" ]]; then
		echo "${RED}ERROR${NC}: exit_status_bash=$exit_status_bash" "|" "exit_status_minishell=$exit_status_minishell"
	else
		echo "${GREEN}SUCCES${NC}: exit codes correct."
	fi
}

###############################################################################
#                                                                             #
#                     Testing navigation: cd and pwd                          #
#                                                                             #
###############################################################################

# TEST 1
command="pwd"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 1
command="pwd 0"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 1
command="pwd -"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 1
command="pwd --"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 1
command="pwd -p hahah"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="cd"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="cd -p ahah"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="cd o"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="cd -"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="cd ...."
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

###############################################################################
#                                                                             #
#                     Testing basic commands and pipelines                    #
#                                                                             #
###############################################################################

# TEST 1
command="ls -l"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="ls -l /Users/hyilmaz/Desktop/rutger | grep codam | wc -c"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="cat $file_in_1"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="cat $file_in_1 | grep prpprprprprpr | wc"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="cd .. | echo \$PWD"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="cat /dev/urandom | head -c 10"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

###############################################################################
#                                                                             #
#                 Non existing / not executable commands                      #
#                                                                             #
###############################################################################

# TEST 2
command="caat"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="a b c"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command=""
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="/Users/hyilmaz/Desktop/rutger"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="/Users/hyilmaz/Desktop/rutger | ls -l /Users/hyilmaz/Desktop/"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="ls -l | /Users/hyilmaz/Desktop/rutger"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="ls -l | /Users/hyilmaz/Desktop/rutger | ls -l /Users/hyilmaz/Desktop"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST 2
command="ls -l | ls -l /Users/hyilmaz/Desktop | /Users/hyilmaz/Desktop/rutger"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

###############################################################################
#                                                                             #
#                     Testing redirections                                    #
#                                                                             #
###############################################################################

# TEST 2
command_bash="ls -l > $TEST_DIR/outfile_bash_1"
command_minishell="ls -l > $TEST_DIR/outfile_minishell_1"
test_name "$command_bash and $command_minishell"
run_bash "$command_bash" > $TEST_DIR/bash_output 2>&1
run_minishell "$command_minishell" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
compare_files "$TEST_DIR/outfile_bash_1" "$TEST_DIR/outfile_minishell_1"
echo ""

# TEST 2: Does not write to outfile_minishell_1
command_bash="ls -l > $TEST_DIR/outfile_bash_1 | cat $file_in_1"
command_minishell="ls -l > $TEST_DIR/outfile_minishell_1 | cat $file_in_1"
test_name "$command_bash and $command_minishell"
run_bash "$command_bash" > $TEST_DIR/bash_output 2>&1
run_minishell "$command_minishell" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
compare_files "$TEST_DIR/outfile_bash_1" "$TEST_DIR/outfile_minishell_1"
echo ""

command_bash="ls -l | grep test > $TEST_DIR/outfile_bash_1 | wc"
command_minishell="ls -l | grep test > $TEST_DIR/outfile_minishell_1 | wc"
test_name "$command_bash and $command_minishell"
run_bash "$command_bash" > $TEST_DIR/bash_output 2>&1
run_minishell "$command_minishell" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
compare_files "$TEST_DIR/outfile_bash_1" "$TEST_DIR/outfile_minishell_1"
echo ""

command_bash="ls -l | grep test | wc > $TEST_DIR/outfile_bash_1"
command_minishell="ls -l | grep test | wc > $TEST_DIR/outfile_minishell_1"
test_name "$command_bash and $command_minishell"
run_bash "$command_bash" > $TEST_DIR/bash_output 2>&1
run_minishell "$command_minishell" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
compare_files "$TEST_DIR/outfile_bash_1" "$TEST_DIR/outfile_minishell_1"
echo ""

# TEST
command_bash="< $file_in_1 cat | wc -l"
command_minishell="< $file_in_1 cat | wc -l"
test_name "$command_bash and $command_minishell"
run_bash "$command_bash" > $TEST_DIR/bash_output 2>&1
run_minishell "$command_minishell" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST
command_bash="ls -l | < $file_in_1 cat"
command_minishell="ls -l | < $file_in_1 cat"
test_name "$command_bash and $command_minishell"
run_bash "$command_bash" > $TEST_DIR/bash_output 2>&1
run_minishell "$command_minishell" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST
command_bash="ls -l | < $file_in_1 cat | wc -l"
command_minishell="ls -l | < $file_in_1 cat | wc -l"
test_name "$command_bash and $command_minishell"
run_bash "$command_bash" > $TEST_DIR/bash_output 2>&1
run_minishell "$command_minishell" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# TEST
command_bash="ls -l | < $file_in_1 cat > $TEST_DIR/outfile_bash_1"
command_minishell="ls -l | < $file_in_1 cat > $TEST_DIR/outfile_minishell_1"
test_name "$command_bash and $command_minishell"
run_bash "$command_bash" > $TEST_DIR/bash_output 2>&1
run_minishell "$command_minishell" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
compare_files "$TEST_DIR/outfile_bash_1" "$TEST_DIR/outfile_minishell_1"
echo ""

# TEST
rm -f $TEST_DIR/outfile_bash_1 $TEST_DIR/outfile_minishell_1
echo "hilmiyilmaz" > $TEST_DIR/outfile_bash_1 ; echo "hilmiyilmaz" > $TEST_DIR/outfile_minishell_1
command_bash="ls -la >> $TEST_DIR/outfile_bash_1"
command_minishell="ls -la >> $TEST_DIR/outfile_minishell_1"
test_name "$command_bash and $command_minishell"
run_bash "$command_bash" > $TEST_DIR/bash_output 2>&1
run_minishell "$command_minishell" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
compare_files "$TEST_DIR/outfile_bash_1" "$TEST_DIR/outfile_minishell_1"
echo ""

command_bash="ls -l | grep test >> $TEST_DIR/outfile_bash_1 | < $file_in_1 wc >> $TEST_DIR/outfile_bash_1"
command_minishell="ls -l | grep test >> $TEST_DIR/outfile_minishell_1 | < $file_in_1 wc >> $TEST_DIR/outfile_minishell_1"
test_name "$command_bash and $command_minishell"
run_bash "$command_bash" > $TEST_DIR/bash_output 2>&1
run_minishell "$command_minishell" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
compare_files "$TEST_DIR/outfile_bash_1" "$TEST_DIR/outfile_minishell_1"
echo ""

command_bash="< $file_in_1 cat > $TEST_DIR/output_bash_1 | < $file_in_1 grep codam > $TEST_DIR/output_bash_2 | wc -l < $file_in_1 > $TEST_DIR/output_bash_3"
command_minishell="< $file_in_1 cat > $TEST_DIR/output_minishell_1 | < $file_in_1 grep codam > $TEST_DIR/output_minishell_2 | wc -l < $file_in_1 > $TEST_DIR/output_minishell_3"
test_name "$command_bash and $command_minishell"
run_bash "$command_bash" > $TEST_DIR/bash_output 2>&1
run_minishell "$command_minishell" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
compare_files "$TEST_DIR/output_bash_1" "$TEST_DIR/output_minishell_1"
compare_files "$TEST_DIR/output_bash_2" "$TEST_DIR/output_minishell_2"
compare_files "$TEST_DIR/output_bash_3" "$TEST_DIR/output_minishell_3"
echo ""

###############################################################################
#                                                                             #
#                     Testing expansions                                      #
#                                                                             #
###############################################################################

export hilmi="s -l"
command="l\"\$hilmi\""
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""
unset hilmi

export hilmi="s -l"
command="l\$hilmi"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""
unset hilmi

export hilmi="ls -l"
command="\"\$hilmi\""
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""
unset hilmi

export hilmi="ls -l"
command="\$hilmi"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""
unset hilmi

command="echo \$LOGNAME"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

command="echo \"\$LOGNAME\""
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

command="echo '\$LOGNAME'"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

# command="echo \$?"
# test_name "$command"
# run_bash "$command" > $TEST_DIR/bash_output 2>&1
# run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
# compare_exit_status
# compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
# echo ""

###############################################################################
#                                                                             #
#                     Testing echo                                            #
#                                                                             #
###############################################################################

command="echo hilmi yilmaz"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

command="echo -n hilmi yilmaz"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

command="echo"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

command="echo a"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

command="echo -"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

command="echo --"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

command="echo -n"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

command="echo ."
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

command="echo 9"
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

command="echo asd df ds f dsf ds fds fds fds f dsf dsfds f dsf ds fds er y rth  h t gh "
test_name "$command"
run_bash "$command" > $TEST_DIR/bash_output 2>&1
run_minishell "$command" > $TEST_DIR/minishell_output 2>&1
compare_exit_status
compare_files "$TEST_DIR/bash_output" "$TEST_DIR/minishell_output"
echo ""

###############################################################################
#                                                                             #
#                     Testing exit                                            #
#                                                                             #
###############################################################################

###############################################################################
#                                                                             #
#                     Testing signals (interactive)                           #
#                                                                             #
###############################################################################

###############################################################################
#                                                                             #
#                     Wrong grammer / syntax                                  #
#                                                                             #
###############################################################################



###############################################################################
#                                                                             #
#                    Test with a lot of (d)quotes                             #
#                                                                             #
###############################################################################
