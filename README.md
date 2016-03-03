# ttfn implementation

To run the program:
- Go to the directory /ttfn
- Build both server and clients using command: make
- Run server under /ttfn directory using command: ttfn_server
- Run client under /ttfn directory using command: ttfn --latency|--throughput [-p packetsize] [-r repeats] hostname

Note:
- The port number is hard coded in server and client code to be 13547. You may change the port number in case there's a conflict
- Our test typescripts are saved in directory /ttfn/typescripts
- We use the package size specified by the command line argument as the total size of each package
- We used bash scripts run_[name].sh to automate the testings.
   run the script on the client side using ./run_[name].sh
