#.name "Zork"
			#.name "Zork"
		#.name ###"Zork"#
 .name "#Zork#"
.comment "Hello#,
#i'm Zork#"#end         

sti r1,%:live,%1           
ld %0, r16
live: #sti r1,%:live,%1           
#live:
live %1
zjmp %:live
