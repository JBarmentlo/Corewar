.name "ldi tester"
.comment "no comment"

ldi %512,%0,r2
ld %10,r3
ldi %512,r3,r2
st r3, 100
ldi 95,r3,r4
