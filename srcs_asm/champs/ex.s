.name "zork"
.comment "just a basic living prog"

l2:	sti	r99,12345678912345,%12345678912345
	and r1,%0,r1
live:	live	%1
	zjmp	%:live
