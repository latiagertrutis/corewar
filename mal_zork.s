.name "mal zork"
.comment "I'M ALIIIIVE"

ld: 	
		
		ld %-1, r1
		and r2, %0, r3

live:
		ld %45, r2
		and r2, %0, r3
		zjmp %:live
