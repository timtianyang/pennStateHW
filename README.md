# pennStateHW

To run the program:
1. Go to the directory /ttfn
2. Build both server and clients by command: make
3. Run server under /ttfn directory by command: ttfn_server
4. Run client under /ttfn directory with command: ttfn --latency|--throughput [-p packetsize] [-r repeats] hostname

Note:
1. The port number is hard coded in server and client code to be 13547. You may change the port number in case there's a conflict
2. Our test typescripts are saved in directory /ttfn/typescripts
