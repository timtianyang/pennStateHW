# ttfn part2 implementation

To run the program:
- Go to the directory /ttfn2
- Build both server and clients using command: make
- Run server under /ttfn2 directory using command: ttfn_server [-f filename]
- Run client under /ttfn2 directory using command: ttfn --latency|--throughput [-p packetsize] [-r repeats] hostname

Note:
- The port number is hard coded in server and client code to be 13547. You may change the port number in case there is a conflict.
- The file containing the delay values is delay.txt
- Our test typescripts are saved in directory /ttfn/typescripts. There are six pairs of typescripts, each pair including typescript from server and client. Typescript 1 - 5 are test results of using the delay.txt file. Both latency and throughput have been tested with different packet sizes and repetitions. Typescript 6 is the test result of not adding any delay (default case).
- Both the server and the client are based on UDP. The server returns a short ACK message to the client whenever it received a message from it. On the client side the round-trip delay time is measured by calculating the time difference between sending the message and receiving the ACK.
