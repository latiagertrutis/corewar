.name "zork"
.comment "I'M ALIIIIVE"

live:			fork %:live
				live %1
				ld %48, r2
				aff r2;
