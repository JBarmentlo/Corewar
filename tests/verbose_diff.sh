#!/bin/sh

grep_line=20

make
./ressources/vm_champs/corewar -v 31 "$@" | sed '1d' | grep -v '^* Player' | grep -v '^Contestant' | grep -n ' ' > zaz
./corewar -log "$@" | grep -n ' ' > gll
diff zaz gll > diff
CYCLE_LINE=$(diff zaz gll | head -n 2 | sed '1d' | cut -d ' ' -f 2)
LINE=$(echo "$(echo $CYCLE_LINE | cut -d ':' -f 1):")

grep --color -E -C $grep_line "^$LINE" gll > gll_section
grep --color -E -C $grep_line "^$LINE" zaz > zaz_section
diff -y gll_section zaz_section > verbose_log
grep --color -E -C $grep_line "^$LINE.+" verbose_log
echo "\033[0;31mNOTRE								VOTRE\033[0m"

CYCLE=`sed "/$LINE/q" gll | tail -r | sed '/It is now cycle/q' | grep 'now cycle' | cut -d ' ' -f5`
echo "\033[0;31mCycle: $CYCLE\033[0m"
let "CYCLE_CMD=$CYCLE - 2"

rm gll zaz diff
echo "Fait toi plaise lache la commande :"
echo "./corewar $@ -v $CYCLE_CMD"
./ressources/vm_champs/corewar -d $CYCLE "$@" | sed '1d' | grep -v '^* Player' > zaz_dump
./corewar -mute -dump $CYCLE "$@" | sed '1d' | sed '$d' | sed '$d' > gll_dump
diff zaz_dump gll_dump > dump_diff
rm zaz_dump gll_dump
echo "Ou regarde la diff dans dump_diff"