#! /bin/bash

# for each matrix file
for test_file in $(ls matrizes/)
do

	total_time_single=0
	total_time_multi=0

	# ten times to have an average
	for((i=0 ;i<10;i++))
	do
		(/usr/bin/time -f "\n%e" ./build/main < matrizes/$test_file) 2> tmp-$test_file 1> result-$test_file
		total_time_single=$(python -c "print $total_time_single + $(tail -n 1 tmp-$test_file)")

		(/usr/bin/time -f "\n%e" ./build/main multi < matrizes/$test_file) 2> tmp-$test_file 1> result-$test_file
		total_time_multi=$(python -c "print $total_time_multi + $(tail -n 1 tmp-$test_file)")
	done

	echo $test_file
	echo Average Singlethreaded Time: $(python -c "print \"%.3f\" % ($total_time_single/10)")s
	echo Average Multithreaded Time: $(python -c "print \"%.3f\" % ($total_time_multi/10)")s
	echo 

	rm tmp-$test_file
done
