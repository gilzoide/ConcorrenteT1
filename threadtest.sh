#! /bin/bash

test_file=$1

for((j=1;j<=20;j+=1))
do

	total_time_multi=0

	for((i=0;i<2;i++))
	do

		(/usr/bin/time -f "\n%e" ./build/main --multi --nthreads $j < matrizes/$test_file) 2> tmp-$test_file 1> result-$test_file
		total_time_multi=$(python -c "print $total_time_multi + $(tail -n 1 tmp-$test_file)")
	done

	echo Threads: $j
	echo $test_file
	echo Average Multithreaded Time: $(python -c "print \"%.3f\" % ($total_time_multi/2)")s
	echo 

	rm tmp-$test_file

done

for((j=20;j<=200;j+=20))
do

        total_time_multi=0

        for((i=0;i<2;i++))
        do

                (/usr/bin/time -f "\n%e" ./build/main --multi --nthreads $j < matrizes/$test_file) 2> tmp-$test_file 1> result-$test_file
                total_time_multi=$(python -c "print $total_time_multi + $(tail -n 1 tmp-$test_file)")
        done

        echo Threads: $j
        echo $test_file
        echo Average Multithreaded Time: $(python -c "print \"%.3f\" % ($total_time_multi/2)")s
        echo

        rm tmp-$test_file

done
