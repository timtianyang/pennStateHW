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
    int no_delay = 0;
    int* delays;
    int size = 0;
    size_t len = 0;
    int i;

    FILE * fp;
    char * line = NULL;

    if ( argc != 2 )
    {
	printf("You didn't specify a file name so the delay will be zero\n");
	no_delay = 1;
    }
    else
    {
	printf("reading from file %s\n", argv[1]);
	fp = fopen(argv[1], "r");
	if (fp == NULL)
	{
	    no_delay = 1;
	    printf("the file is not found, use zero delay\n");
	}
	else
	{
	    while (getline(&line, &len, fp) != -1) {
		//printf("%s\n", line);
		size++;
	    }
	
	    printf("there are %d lines in the file\n",size);
	    //fclose(fp);
	    if ( size == 0 )
	    {
		printf("use no delay\n");
		no_delay = 1;
	    }
	    else
	    {
		delays = malloc(sizeof(int) * size);
		if ( delays == NULL )
		{
		    printf("not enough mem!\n");
		    return -1;
		}

		rewind(fp);
		i = 0;
		while (getline(&line, &len, fp) != -1) {
		    delays[i++] = atoi(line);
		}
		for (i=0;i<size;i++)
		    printf("%d\n",delays[i]);
		fclose(fp);
	    }
	}    

    }
    
    
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
