#!/bin/bash

for COMMAND in --latency --throughput
do
	for PACK in -64 64 640 6400 64000
	do
		for REPEAT in 0 1 2 5
		do
			echo ttfn $COMMAND -p $PACK -r $REPEAT localhost
			./ttfn $COMMAND -p $PACK -r $REPEAT localhost
			echo '************Done**********************'
		done	
	done
done
