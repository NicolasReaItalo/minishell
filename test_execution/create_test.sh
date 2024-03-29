#/usr/bin/bash

file_nb=$(ls -1q ./test_commands | wc -l)
file_nb=$((file_nb + 1))
echo "creating test nb : $file_nb"
echo $1 > test_commands/$file_nb.txt
../minishell "$(cat ./test_commands/$file_nb.txt)" 1> "test_expected_outputs/$file_nb.txt" 2> "test_expected_outputs/$file_nb.txt"
echo $? > test_expected_status/$file_nb.txt
