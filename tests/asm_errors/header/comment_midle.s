.name "Kroz"

l2:	sti	r1, %:live,%1
	and	r1, %0,r1

.comment "Hello, i'm Kroz"

live: live %1
	  zjmp %:live
