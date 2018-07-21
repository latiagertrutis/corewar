.name "zork"
.comment "I'M ALIIIIVE"

ld: 	
		and r2, %0, r3

live:
		live %1
		zjmp %:live
