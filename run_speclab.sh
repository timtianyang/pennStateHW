#!/bin/bash

for COMMAND in --latency --throughput
do
	for PACK in -65536 512 2048 54321
	do
		for REPEAT in 1 10 100
		do
			echo ttfn $COMMAND -p $PACK -r $REPEAT spec07.seas.upenn.edu
			./ttfn $COMMAND -p $PACK -r $REPEAT spec07.seas.upenn.edu
			echo '************Done***************'
		done	
	done
done
