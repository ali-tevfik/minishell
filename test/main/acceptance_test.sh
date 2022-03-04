# Acceptance test for minishell
# This is a program that tests the outputs of minishell. It takes no arguments.

# Configuration parameters
PATH_TO_MINISHELL="$HOME/Desktop/curriculum/minishell"

# Create tmp directory
TEST_DIR="/tmp/test_minishell"
mkdir -p $TEST_DIR
if [[ "$?" != 0 ]]; then
	echo "Could not create $TEST_DIR directory..."
	exit 1
fi

# Run as: ./acceptance_test.sh

if [[ "$1" != "" ]]; then
	echo "Run as: ./acceptance_test.sh"
	echo "No arguments needed."
	exit 1
fi

# Run the command in bash. Only one argument: the command to run.
run_bash () {
	bash -c $1
}

# Run the command in minishell. Only one argument: the command to run.
run_minishell () {
	echo $1 | $PATH_TO_MINISHELL/minishell
}

# Compare the output files.
compare_files () {

	# Loop over the arguments
	echo "Number of arguments: $#"
	for (( i=1; i<=$#; i++))
	{
		eval val='$'$i
		echo "Arg $i: $val"
	}
}

# The way to run test.
run_bash "ls -l"
run_minishell "ls -l"

compare_files "bash_output" "minishell_output"
compare_exit_status "bash_exit_status" "minishell_exit_status"
