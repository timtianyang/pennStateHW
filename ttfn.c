#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

void print_usage() {
    printf("Usage: --latency|--throughput [- p packagesize] [-r repeats] hostname\n");
}

int main(int argc, char *argv[]) {
    int opt= 0;
    int through_put = 0;
    int latency = 0;
    int repeat = 0;
    int packet_size = 0;

    //Specifying the expected options
    //The two options l and b expect numbers as argument
    static struct option long_options[] = {
        {"latency",      no_argument,       0,  'l' },
        {"throughput", no_argument,       0,  't' },
        {"p", required_argument,       0,  'p' },
        {"r",    required_argument, 0,  'r' },
        {0,           0,                 0,  0   }
    };

    int long_index =0;
    
    
    while ((opt = getopt_long(argc, argv,"ltp:r:", 
                   long_options, &long_index )) != -1) {
        switch (opt) {
             case 'l' : latency = 1;
                 break;
             case 't' : through_put = 1;
                 break;
             case 'r' : repeat = atoi(optarg); 
                 break;
             case 'p' : packet_size = atoi(optarg);
                 break;
             default: print_usage();
                 exit(EXIT_FAILURE);
        }
    }
    if( latency )
    {
        printf("measuring latency\n");
    }
    else if ( through_put )
    {
        printf("measuring throughput\n");
    }
    if( latency && through_put )   
    {
        print_usage();
        exit(EXIT_FAILURE);
    } 
    
    printf("packet size is %d\n",packet_size);
    printf("repeating %d times\n",repeat);
    return 0;
}
