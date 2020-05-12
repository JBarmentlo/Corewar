.name "Zork"
.comment "Hello, i'm Zork"          

sti r1,%:live,1        
ld %0, r16
live:
live r1
zjmp %:live
