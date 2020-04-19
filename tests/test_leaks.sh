#!/bin/sh
SCRIPT_DIR=`dirname $0`
ASM_BASE_DIR="./"$SCRIPT_DIR"/../ressources/vm_champs/asm"
ASM_MINE_DIR="./"$SCRIPT_DIR"/../asm"

VALID_FOLDER=$SCRIPT_DIR"/valid/*"
ERROR_FOLDER=$SCRIPT_DIR"/errors/*"

process_folder()
{
	for f in $@
	do
		if [ -d "$f" ]
		then
			process_folder $f/*
		elif [[ $f == *.s ]]
		then
			echo "Processing `basename $f`"
			OUTPUT=${f/.s/.cor}
			valgrind $ASM_MINE_DIR $f
			rm -f $OUTPUT
			read -n1 -r -p "Press any key to continue..." key
		fi
	done
}

printf "\033[0;32m"
echo "#############################################################################"
echo "################################ VALID FILES ################################"
echo "#############################################################################"
printf "\e[0m"

process_folder $VALID_FOLDER

printf "\033[0;32m"
echo "#############################################################################"
echo "################################ ERROR FILES ################################"
echo "#############################################################################"
printf "\e[0m"

process_folder $ERROR_FOLDER