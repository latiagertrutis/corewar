.name "zork"
.comment "I'M ALIIIIVE"

ld: 	sti r1, %:live, %1
		and r2, %0, r3

live:
		live %1
		zjmp %:live
