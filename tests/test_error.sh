#!/bin/sh
SCRIPT_DIR=`dirname $0`
ASM_BASE_DIR="./"$SCRIPT_DIR"/../vm-champs-linux/asm"
ASM_MINE_DIR="./"$SCRIPT_DIR"/../asm"
SEARCH_FOLDER="asm_errors/*"
process_folder()
{
	for f in $@
	do
		if [ -d "$f" ]
		then
			process_folder $f/*
		elif [[ $f == *.s ]]
		then
			echo ""
			echo "************"
			echo -e "Processing\e[36m `dirname $f`\e[0m"
			echo ""
			echo -e "\e[32mBASE :\e[0m"
			$ASM_BASE_DIR $f
			OUTPUT=${f/.s/.cor}
			if test -f "$OUTPUT"; then
				hexdump -v $OUTPUT > theiroutput
			fi
			echo ""
			echo -e "\e[95mMINE :\e[0m"
			$ASM_MINE_DIR $f
			OUTPUT=${f/.s/.cor}
			if test -f "$OUTPUT"; then
				hexdump -v $OUTPUT > myoutput
			fi
			ls -la | grep 'output' &> /dev/null
			if [ $? -eq 0 ]; then
				diff theiroutput myoutput
			fi
			echo ""
			OUTPUT=${f/.s/.cor}
			rm -f $OUTPUT
			rm -f theiroutput myoutput
			read -n1 -r -p "Press any key to continue..." key
		fi
	done
}
process_folder $SEARCH_FOLDER

