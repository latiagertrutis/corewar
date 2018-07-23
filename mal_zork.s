.name "zork"
.comment "I'M ALIIIIVE"

ld: 	
		
		ld %-1, r1
		and r2, %0, r3

live:
		live %-1
		zjmp %:live
