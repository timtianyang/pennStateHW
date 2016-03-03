#include <getopt.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <time.h>

void print_usage() {
    printf("Usage: --latency|--throughput [- p packagesize] [-r repeats] hostname\n");
}
void ttfn_throughput();
void ttfn_latency();

struct hostent *hp;
int through_put = 0;
int latency = 0;
int repeat = 1;
int packet_size = 1;
char *hostip;
const int PORT = 13547;

int main(int argc, char *argv[]) {
    int opt= 0;
    
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
    if( latency && through_put )
    {
        print_usage();
        exit(EXIT_FAILURE);
    }
    if( packet_size <= 0 || repeat <=0 )
    {
        printf("packet_size, repeats must be greater than 0\n");
        exit(EXIT_FAILURE);
    }
    hp = gethostbyname(argv[argc-1]);
    if( hp == 0)
    {
        printf("fail to resolve this host name\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        struct in_addr **addr_list;
        int i;
        printf("    Host Address to test: ");
        addr_list = (struct in_addr **)hp->h_addr_list;
        for(i = 0; addr_list[i] != NULL; i++) {
            printf("%s ", inet_ntoa(*addr_list[i]));
            hostip = inet_ntoa(*addr_list[i]);
            break;
        }
        printf("\n");
    }
    if( latency )
    {
        printf("measuring latency\n");
        if(packet_size == 1)
            packet_size = 64;
        ttfn_latency();
    }
    else if ( through_put )
    {
        printf("measuring throughput\n");
        if(packet_size == 1)
            packet_size = 512;
        ttfn_throughput();
    }
    return 0;
}

void ttfn_latency(){
    int sock;
    struct sockaddr_in server;
    //int header = 20;
    clock_t start, end;
    double cpu_time_used;
    
    char * buf;
    
    buf = (char*) malloc(packet_size);
    if (buf == NULL) exit (1);
    
    memset(buf,'a',packet_size-1);
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket failed");
        exit(1);
    }
    server.sin_family = AF_INET;
    
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_port = htons(PORT);
    
    if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0){
        perror("Connect failed");
        exit(1);
    }
    ssize_t n = 0;
    long double max = 0;
    long double min = 1000;
    long double sum = 0;
    int count = 0;
    
    int i;
    for ( i = 0; i<repeat; i++){
        start = clock();
        if((n =send(sock, buf, packet_size, 0)) < 0){
            perror("send failed");
            exit(1);
        }
        end = clock();
        cpu_time_used = ((double) (end - start)/CLOCKS_PER_SEC);
        printf("%d bytes from %s(%s): time= %Lf ms\n", (int)n, hp->h_name, hostip, (long double)cpu_time_used*1000);
        fflush(stdout);
        if (cpu_time_used > max) max = cpu_time_used;
        if (cpu_time_used < min) min = cpu_time_used;
        sum += cpu_time_used;
        count++;
        sleep(1);
    }
    long double avg = sum / repeat;
    printf("%d packets transmitted, %d packets received, %.2Lf %% packet loss\n", repeat, count, (long double)(repeat - count)/repeat);
    printf("round-trip max: %Lf ms min: %Lf ms avg: %Lf ms\n", max*1000, min*1000, avg*1000);
    fflush(stdout);
    
    close(sock);
    return;
}

void ttfn_throughput(){
    int sock;
    struct sockaddr_in server;
    //int header = 20;
    clock_t start, end;
    double cpu_time_used;
    
    char * buf;
    
    buf = (char*) malloc(packet_size);
    if (buf == NULL) exit (1);
    
    memset(buf,'a',packet_size-1);
    
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0)
    {
        perror("socket failed");
        exit(1);
    }
    server.sin_family = AF_INET;
    
    memcpy(&server.sin_addr, hp->h_addr, hp->h_length);
    server.sin_port = htons(PORT);
    
    if(connect(sock, (struct sockaddr *) &server, sizeof(server)) < 0){
        perror("Connect failed");
        exit(1);
    }
    ssize_t n = 0;
    long double max = 0;
    long double min = 1000;
    long double sum = 0;
    int i;
    for (i = 0; i<repeat; i++){
        start = clock();
        if((n =send(sock, buf, packet_size, 0)) < 0){
            perror("send failed");
            exit(1);
        }
        end = clock();
        cpu_time_used = ((double) (end - start)/CLOCKS_PER_SEC);
        printf("Sent %d bytes  time %Lf s\n", (int)n, (long double)cpu_time_used);
        fflush(stdout);
        if (cpu_time_used > max) max = cpu_time_used;
        if (cpu_time_used < min) min = cpu_time_used;
        sum += cpu_time_used;
        sleep(1);
    }
    long double avg = sum / repeat;
    long total = n*repeat;
    printf("Total Bytes   Real s    Real-Bytes/s   Msgs Transferred  Packet-Size(bytes)\n");
    printf("%li      %Lf    %.2Lf          %d         %d\n", total, sum, (long double)total/sum, repeat, packet_size);
    fflush(stdout);
    
    close(sock);
    return;
}
