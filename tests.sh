#! /bin/bash

# for each matrix file
for test_file in $(ls matrizes/)
do

	total_time_single=0
	total_time_multi=0

	# ten times to have an average
	for((i=0 ;i<10;i++))
	do
		(gtime -f "\n%e" ./build/main < matrizes/matriz250.txt) 2> tmp-$test_file 1> result-$test_file
		total_time_single=$(python -c "print $total_time_single + $(tail -n 1 tmp-$test_file)")

		(gtime -f "\n%e" ./build/main multi < matrizes/matriz250.txt) 2> tmp-$test_file 1> result-$test_file
		total_time_multi=$(python -c "print $total_time_multi + $(tail -n 1 tmp-$test_file)")
	done

	echo $test_file
	echo Average Singlethreaded Time: $(python -c "print \"%.3f\" % ($total_time_single/10)")
	echo Average Multithreaded Time: $(python -c "print \"%.3f\" % ($total_time_multi/10)")
	echo 

	rm tmp-$test_file
done
