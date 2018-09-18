.name "zork"
.comment "just a basic living prog"

l2:	sti	r99,123456789123456,%0
	and r1,%0,r1
live:	live	%1
	zjmp	%:live
