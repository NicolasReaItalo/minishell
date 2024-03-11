#!/bin/bash

mkdir -p test_outputs
for input_file in test_commands/*.txt; do
	base_name=$(basename "$input_file" .txt)
#	command=$(cat "$input_file")
	./minishell "$(cat $input_file)" > "test_outputs/$base_name.txt"
#	./minishell "$command" > "test_outputs/${base_name}.txt"
	if diff -u "test_expected_outputs/$base_name.txt" "test_outputs/$base_name.txt" > /dev/null; then
		echo "Test $base_name : good."
	else
		echo "Test $base_name : failed. Differences :"
		diff -u "test_expected_outputs/$base_name.txt" "test_outputs/$base_name.txt"
	fi
done