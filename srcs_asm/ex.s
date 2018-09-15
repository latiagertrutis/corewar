.name "TheName"
.comment "hola soy un comentario"
		
l2:	sti	r1,%:live,%0
	and	r1,%0,r1
live:	live	%1
	zjmp	%:live
