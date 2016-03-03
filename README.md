# ttfn implementation

To run the program:
1. Go to the directory /ttfn
2. Build both server and clients using command: make
3. Run server under /ttfn directory using command: ttfn_server
4. Run client under /ttfn directory using command: ttfn --latency|--throughput [-p packetsize] [-r repeats] hostname

Note:
1. The port number is hard coded in server and client code to be 13547. You may change the port number in case there's a conflict
2. Our test typescripts are saved in directory /ttfn/typescripts
3. We use the package size specified by the command line argument as the total size of each package
