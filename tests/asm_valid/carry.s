.name "carry tester"
.comment "no comment"

zjmp %0
add r3,r3,r3
zjmp %3
add r3,r1,r3
zjmp %3
ld %0,r4
zjmp %3
ld %2,r6
zjmp %3
sub r1,r4,r4
zjmp %3
sub r4,r1,r3
zjmp %3
and %8,%4,r3
zjmp %3
and %8,%12,r3
zjmp %3
