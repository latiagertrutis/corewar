.name "zork"
.comment "I'M ALIIIIVE"

cosa:
	ld %201326592, r2
	st r2, 6
	st r1, 200
	fork %200
