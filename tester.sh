make;

while getopts "fd" opt;
do
	case $opt in
		f)
			read -e -p "Enter files: " dir
			printf "\033[1;32mEvaluating %s\033[0m\n" $(basename $dir);
			./prueba $dir -i > our.txt;
#			ex=$?; if [[ $ex != 0 ]]; then exit $ex; fi
			./corewar $dir -v 4 > real.txt;
#			ex=$?; if [[ $ex != 0 ]]; then exit $ex; fi
			diff our.txt real.txt > diff.txt;
			if [ -s diff.txt ]
			then
				printf "\033[31mDiferences of:\n%s\nStored in diff.txt\033[0m\n" $(basename $dir);
			else
				printf "\033[32mOK\033[0m\n"
			fi
			;;
		d)
			read -e -p "Directory to evaluate (Default /resources/bin/): " dir
			dir=${dir:-resources/bin}
			declare -a arr=("")
			for i in "$dir"/*;
			do
				arr+=($i)
			done
			for f1 in "${arr[@]}";
			do
				for f2 in "${arr[@]}";
				do
					for f3 in "${arr[@]}";
					do
						for f4 in "${arr[@]}";
						do
							if [[ ( -z $f1 && -z $f2 && -z $f3 && -z $f4 ) ]]
							then

								continue
							fi
							printf "\033[32mEvaluating %s %s %s %s\033[0m\n" $f1 $f2 $f3 $f4;
							./prueba  $f1 $f2 $f3 $f4 -i > our.txt;
							./corewar  $f1 $f2 $f3 $f4 -v 4 > real.txt;
							diff our.txt real.txt > diff.txt;
							if [ -s diff.txt ]
							then
								printf "\033[31mDiferences of:\n%s %s %s %s\nStored in diff.txt\033[0m\n"  $f1 $f2 $f3 $f4;
								exit 2
							else
								printf "\033[32mOK\033[0m\n"
							fi
						done
					done
				done
			done
			;;
		\?)
			echo "\033[31mInvalid option: -$OPTARG\033[0m" >&2
			exit 1
			;;
		:)
			echo "\033[31mOption: -$OPTARG requires argument\033[0m" >&2
			exit 1
			;;
	esac
done
