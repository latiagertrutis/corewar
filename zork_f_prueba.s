.name "zork"
.comment "I'M ALIIIIVE"

cosa:
	ld %2, r4
	ld -1, r3
	add r4, r3, r5
	sub r3, r4, r6
	st r5, 200
	st r6, 300
