.name "zork"
.comment "I'M ALIIIIVE"

cosa:
	ld %0, r4
	zjmp %300
	ld 3, r3
	and r4, r3, r5
	st r5, 300
