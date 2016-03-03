#!/bin/bash

for COMMAND in --latency --throughput
do
	for PACK in -2 20 400 64000
	do
		for REPEAT in -1 1 3 10
		do
			echo $COMMAND -p $PACK -r $REPEAT eniac.seas.upenn.edu
		done	
	done
done
