#/usr/bin/bash

# Reset
Color_Off='\033[0m'       # Text Reset

# Regular Colors
Black='\033[0;30m'        # Black
Red='\033[0;31m'          # Red
Green='\033[0;32m'        # Green
Yellow='\033[0;33m'       # Yellow
Blue='\033[0;34m'         # Blue
Purple='\033[0;35m'       # Purple
Cyan='\033[0;36m'         # Cyan
White='\033[0;37m'        # White

# Bold
BBlack='\033[1;30m'       # Black
BRed='\033[1;31m'         # Red
BGreen='\033[1;32m'       # Green
BYellow='\033[1;33m'      # Yellow
BBlue='\033[1;34m'        # Blue
BPurple='\033[1;35m'      # Purple
BCyan='\033[1;36m'        # Cyan
BWhite='\033[1;37m'       # White

# Underline
UBlack='\033[4;30m'       # Black
URed='\033[4;31m'         # Red
UGreen='\033[4;32m'       # Green
UYellow='\033[4;33m'      # Yellow
UBlue='\033[4;34m'        # Blue
UPurple='\033[4;35m'      # Purple
UCyan='\033[4;36m'        # Cyan
UWhite='\033[4;37m'       # White

# Background
On_Black='\033[40m'       # Black
On_Red='\033[41m'         # Red
On_Green='\033[42m'       # Green
On_Yellow='\033[43m'      # Yellow
On_Blue='\033[44m'        # Blue
On_Purple='\033[45m'      # Purple
On_Cyan='\033[46m'        # Cyan
On_White='\033[47m'       # White

# High Intensity
IBlack='\033[0;90m'       # Black
IRed='\033[0;91m'         # Red
IGreen='\033[0;92m'       # Green
IYellow='\033[0;93m'      # Yellow
IBlue='\033[0;94m'        # Blue
IPurple='\033[0;95m'      # Purple
ICyan='\033[0;96m'        # Cyan
IWhite='\033[0;97m'       # White

# Bold High Intensity
BIBlack='\033[1;90m'      # Black
BIRed='\033[1;91m'        # Red
BIGreen='\033[1;92m'      # Green
BIYellow='\033[1;93m'     # Yellow
BIBlue='\033[1;94m'       # Blue
BIPurple='\033[1;95m'     # Purple
BICyan='\033[1;96m'       # Cyan
BIWhite='\033[1;97m'      # White

# High Intensity backgrounds
On_IBlack='\033[0;100m'   # Black
On_IRed='\033[0;101m'     # Red
On_IGreen='\033[0;102m'   # Green
On_IYellow='\033[0;103m'  # Yellow
On_IBlue='\033[0;104m'    # Blue
On_IPurple='\033[0;105m'  # Purple
On_ICyan='\033[0;106m'    # Cyan
On_IWhite='\033[0;107m'   # White


test_description=""
bash_cmd=""
minishell_cmd=""
test_nb=0
bash_output="out/output_bash"
minishell_output="out/output_minishell"
bash_return_value=""
minishell_return_value=""
errors_minishell="out/errors_minishell"
errors_bash="out/errors_bash"
bash_return_value=""

failed_test=0
succes_test=0

touch	in/input_interdit
chmod -r in/input_interdit

clean_output()
{
	echo "" >$bash_output
	echo "" >$minishell_output
	echo "" >$errors_bash
	echo "" >$errors_minishell
	echo "" > ../valgrind_output
}

summary()
{
	echo "$BBlue Summary"
	echo "$Color_Off $test_nb  tests executed"
	if [ $failed_test -eq 0 ]
	then
	echo "$BGreen $failed_test errors found"
	else
	echo "$BRed $failed_test errors found"
	fi
}


TEST()
{
	clean_output 2> /dev/null
	test_nb=$((test_nb + 1))
	bash_cmd="<in/$infile  $cmd1 | $cmd2 > $bash_output "
	minishell_cmd="../minishell in/$infile \"$cmd1\" \"$cmd2\" $minishell_output"

	echo $Color_Off
	echo "\n                      ${UPurple}TEST n ${test_nb}\n"
	echo "${Color_Off} ${test_description}"
	echo "${Yellow} Bash command : ${Color_Off} $bash_cmd"
	echo "${Cyan} minishell command : ${Color_Off} $minishell_cmd"
	echo "\n"
	echo "${BYellow}Executing Bash command\n"
	echo "Errors output:"
	echo "${Yellow}######################################"
	echo "${Red}"
	echo "$bash_cmd" | $SHELL
	bash_return_value=$?
	echo "${Yellow}"
	echo "######################################"
	echo ""

	echo "${BYellow}$bash_output content :"
	echo "${Yellow}######################################"
	cat $bash_output
	echo "######################################\n"
	echo "${Yellow}Exit code value: [$bash_return_value]\n"

	echo "${BCyan}Executing minishell command\n"
		echo "Errors output:"
	echo "${Cyan}######################################"
	echo "${Red}"
	echo "valgrind  --log-file="../valgrind_output" --trace-children=yes $minishell_cmd" | $SHELL
	minishell_return_value=$?
	echo ${Cyan}
	echo "######################################"
	echo "\n${BCyan}$minishell_output content :"
	echo "${Cyan}######################################"
	cat $minishell_output
	echo "${Cyan}######################################\n"
	echo "${Cyan}Exit code value: [$minishell_return_value]\n"
	echo ""
	echo "${BWhite}Results:\n"


	diff $bash_output $minishell_output 2> /dev/null
	diff_r=$?
	if [ $diff_r -eq 0 ]
	then
		echo "${BGreen}[OK]	$minishell_output and $bash_output are identical"
	else
		echo "${BRed}[KO]	$minishell_output and $bash_output are not identical"
		failed_test=$((failed_test + 1))
	fi

	if [ $minishell_return_value -eq $bash_return_value ]
	then
		echo "${BGreen}[OK]	the exit values are identical"
	else
		echo "${BRed}[KO]	the exit values are not identical"
		failed_test=$((failed_test + 1))
	fi

	echo $BPurple
	read -p "Press any key to proceed or q + enter to quit "  user_input

	if [ $user_input = "q" ]
	then
		exit 0
	else
		clear
	fi
}


echo "\n ${BBlue}
###################################################
#                                                 #
#                   TESTS MINISHELL               #
#                                                 #
###################################################"

echo $BPurple
read -p "Press any key to proceed or q + enter to quit "  user_input

if [ $user_input = "q" ]
then
	exit 0
else
	clear
fi


#TEST 1
test_description="Test simple qui ne doit pas retourner d'erreur\n"
infile="input_ok"
cmd1="ls -l"
cmd2="cat -n"
TEST

#TEST 2
test_description="Test simple qui ne doit pas retourner d'erreur\n"
infile="input_ok"
cmd1="grep volette"
cmd2="cat -n"
TEST

#TEST 3
test_description="le fichier toto n'existe pas une error doit etre soulevee\n"
infile="toto"
cmd1="grep volette"
cmd2="cat -n"
TEST

#TEST 4
test_description="le fichier input est interdit en lecture n'existe pas une error doit etre soulevee\n"
infile="input_interdit"
cmd1="grep volette"
cmd2="cat -n"
TEST

#TEST 5
test_description="le fichier input est un repertoire\n"
infile="dir"
cmd1="grep volette"
cmd2="cat -n"
TEST

#TEST 6
test_description="La cmd1 n'existe pas\n"
infile="input_ok"
cmd1="cmd_bidon"
cmd2="cat -n"
TEST

#TEST 7
test_description="La cmd1 est interdite en execution\n"
infile="input_ok"
cmd1="./cmd_interdite.sh"
cmd2="cat -n"
TEST

#TEST 8
test_description="La cmd2 n'existe pas\n"
infile="input_ok"
cmd1="cat -e"
cmd2="toto"
TEST

#TEST 9
test_description="La cmd2 est interdite\n"
infile="input_ok"
cmd1="cat -e"
cmd2="./cmd_interdite.sh"
TEST

#TEST 10
bash_output="out/output_interdit"
minishell_output="out/output_interdit"

test_description="Le fichier output est interdit en ecriture\n"
infile="input_ok"
cmd1="ls"
cmd2="cat -n"
TEST

#TEST 11
bash_output="out/dir"
minishell_output="out/dir"

test_description="Le fichier output est un repertoire\n"
infile="input_ok"
cmd1="ls"
cmd2="cat -n"
TEST



bash_output="out/output_bash"
minishell_output="out/output_minishell"

#TEST 12
test_description="chemins de commandes absolus\n"
infile="input_ok"
cmd1="/usr/bin/cat -e"
cmd2="/usr/bin/cat -n"
TEST

#TEST 13
test_description="chemins de commandes relatifs\n"
infile="input_ok"
cmd1="./pgm"
cmd2="./pgm"
TEST

#TEST 14
test_description="chemins de commandes relatifs\n"
infile="input_ok"
cmd1="../minishell"
cmd2="../minishell"
TEST

#TEST 15
test_description="chemins de commandes relatifs interdit\n"
infile="input_ok"
cmd1="./pgm_interdit"
cmd2="./pgm_interdit"
TEST


#TEST 16
test_description="test commande single quotes (optionnel)\n"
infile="input_ok"
cmd1="printf 'Hello les amis\n'"
cmd2="cat -e"
TEST


# A FAIRE

# test timeout


description="deux commnades a l suite"
cmd="ls ls"

TEST
{

echo $description

shell "commande"     > result_shell
exit_test
bash  $cmd > result_bash
diff



}


summary



