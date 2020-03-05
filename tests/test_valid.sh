#!/bin/sh
SCRIPT_DIR=`dirname $0`
ASM_BASE_DIR="./"$SCRIPT_DIR"/../ressources/vm_champs/asm"
ASM_MINE_DIR="./"$SCRIPT_DIR"/../asm"

SEARCH_FOLDER=$SCRIPT_DIR"/valid/*"

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
			$ASM_BASE_DIR $f
			OUTPUT=${f/.s/.cor}
			REF=${OUTPUT/.cor/.ref.cor}
			mv $OUTPUT $REF
			$ASM_MINE_DIR $f
			printf "\e[0;31m"
			diff $OUTPUT $REF
			printf "\e[0m"
			rm -f $OUTPUT
			rm -f $REF
			#read -n1 -r -p "Press any key to continue..." key
		fi
	done
}
process_folder $SEARCH_FOLDER