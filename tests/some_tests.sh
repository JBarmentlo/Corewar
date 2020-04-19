#!/bin/sh
SCRIPT_DIR=`dirname $0`
ASM_BASE_DIR="./"$SCRIPT_DIR"/../ressources/vm_champs/asm"
ASM_MINE_DIR="./"$SCRIPT_DIR"/../asm"

valgrind $ASM_MINE_DIR
read -n1 -r -p "Press any key to continue..." key
valgrind --leak-check=full $ASM_MINE_DIR $SCRIPT_DIR"/valid/bee_gees.s" -o bidule
rm -f bidule
read -n1 -r -p "Press any key to continue..." key

valgrind --leak-check=full $ASM_MINE_DIR $SCRIPT_DIR"/valid/bee_gees.s" $SCRIPT_DIR"/valid/bigzork.s" $SCRIPT_DIR"/valid/fluttershy.s"
rm -f $SCRIPT_DIR"/valid/bee_gees.cor" $SCRIPT_DIR"/valid/bigzork.cor" $SCRIPT_DIR"/valid/fluttershy.cor"

read -n1 -r -p "Press any key to continue..." key
valgrind --leak-check=full $ASM_MINE_DIR /dev/null

read -n1 -r -p "Press any key to continue..." key
valgrind --leak-check=full $ASM_MINE_DIR /dev/zero

read -n1 -r -p "Press any key to continue..." key
valgrind --leak-check=full $ASM_MINE_DIR /dev/random