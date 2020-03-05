#!/bin/sh
# ./ressources/vm_champs/corewar -d 0 leo.cor | sed '1d' | sed '1d' | cut -c10- | sed 's/.$//'
# ./corewar -dump 1 leo.cor | sed '1d' | sed '$d' | sed '$d'
C=5500
CHAMPS=("./ressources/vm_champs/champs/Gagnant.cor")

while ((C != 100000))
do
	clear
	echo "CYCLE = $C"
	./ressources/vm_champs/corewar -d $C ${CHAMPS[@]} | sed '1d' | grep -v '^* Player' | cut -c10- | sed 's/.$//' > zaz_dump
	./corewar -mute -dump $C ${CHAMPS[@]} | sed '1d' | sed '$d' | sed '$d' > gll_dump
	DIFF=$(diff zaz_dump gll_dump)
	if [ "$DIFF" != "" ] 
	then
		echo "Diff at cycle $C"
		exit 1
	fi
	let "C = $C + 1"
done