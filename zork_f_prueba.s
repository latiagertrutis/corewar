.name "zork"
.comment "I'M ALIIIIVE"

l2:	st		r2, 200
	st		r2, 200
	fork	%:l2
	ld		%10, r2
	st		r2, 200
