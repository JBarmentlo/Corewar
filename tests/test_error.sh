#!/bin/sh
SCRIPT_DIR=`dirname $0`
ASM_BASE_DIR="./"$SCRIPT_DIR"/../vm_champs/asm"
ASM_MINE_DIR="./"$SCRIPT_DIR"/../asm"
SEARCH_FOLDER="errors/*"
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
			echo "BASE :"
			$ASM_BASE_DIR $f
			OUTPUT=${f/.s/.cor}
			hexdump -v $OUTPUT > theiroutput
			echo "MINE :"
			$ASM_MINE_DIR $f
			OUTPUT=${f/.s/.cor}
			hexdump -v $OUTPUT > myoutput
			diff theiroutput myoutput
			echo ""
			OUTPUT=${f/.s/.cor}
			rm -f $OUTPUT
			read -n1 -r -p "Press any key to continue..." key
		fi
	done
}
process_folder $SEARCH_FOLDER

