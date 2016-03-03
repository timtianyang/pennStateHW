#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
    /* Variables */
    int sock;
    struct sockaddr_in server;
    int mysock;
    const int BUFSIZE = 65536;
    const int PORT = 13547;
    char buff[BUFSIZE];
    ssize_t rval = 0;
    
    
    /* Create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0) {
        perror("Failed to create socket");
        exit(1);
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    
    /* Call bind */
    if(bind(sock, (struct sockaddr *)&server, sizeof(server)))
    {
        perror("bind failed");
        exit(1);
    }
    
    /* Listen */
    listen(sock, 5);
    
    /* Accept */
    do {
        mysock = accept(sock, (struct sockaddr *) 0, 0);
        if(mysock == -1) perror("accept failed");
        else
        {
            while (1){
                memset(buff, 0, sizeof(buff));
                if((rval = read(mysock, buff, BUFSIZE)) < 0){
                    perror("reading stream message error");
                }
                clock_t end = clock();
                if (rval == 0) break;
                printf("Got the message (rval = %d) (time = %Lf)\n", (int)rval, (long double)end/CLOCKS_PER_SEC);
                fflush(stdout);
                
            }
            
        }
        close(mysock);
    }while(1);
    
    return 0;
}