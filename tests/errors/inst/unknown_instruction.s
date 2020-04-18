.name "Zork"
.comment "Hello, i'm Zork"          

sti r1,%:live,%1      
bonjjour
ld %0, r16
live:
live %1
zjmp %:live
