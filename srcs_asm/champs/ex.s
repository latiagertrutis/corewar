.name "zork"
.comment "just a basic living prog"

l2: sti r99,r12,%0
	and r1,%0,r1
live:	live	%1
l3:
	zjmp	%:live
l4:
l5:
