#!/bin/bash

for COMMAND in --latency --throughput
do
	for PACK in -2 20 400 64000
	do
		for REPEAT in -1 1 3 10
		do
			echo ttfn $COMMAND -p $PACK -r $REPEAT eniac.seas.upenn.edu
			./ttfn $COMMAND -p $PACK -r $REPEAT eniac.seas.upenn.edu
			echo '********************done***********************'
		done	
	done
done
