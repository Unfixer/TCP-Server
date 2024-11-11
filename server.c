// server.c
#include<netinet/in.h>
#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

#define PORT 8090


int main()
{
    int s, c; // one socket file descriptor for server and other for client
    socklen_t addrlen; // for accept function
    struct sockaddr_in srv,  cli;
    char buf[512];
    char *data;

    addrlen = 0;
    memset(&srv, 0, sizeof(srv));
    memset(&cli, 0, sizeof(cli));
    s = socket(AF_INET, SOCK_STREAM, 0); // initialize the server socket
    if(s < 0)
    {
        printf("socket()\n");
        return -1;
    }

    
    srv.sin_family = AF_INET;   // structure the server
    srv.sin_addr.s_addr = 0;
    srv.sin_port = htons(PORT);

    if (bind(s, (struct sockaddr *)&srv, sizeof(srv)))  // bind the entire server
    {
     printf("bind()\n");
     close(s); 
     return -1;
    }

     if (listen(s, 5))  // queue is 5 here
     {
        printf("listen()\n");
        return -1;
     }
     printf("Listening on 0.0.0.0:%d\n", PORT);

     c = accept(s, (struct sockaddr *)&srv, &addrlen) ; // same syntax as bind
     if (c < 0)
     {
        printf("accept()\n");
        close(s);
        return -1;
     }

     printf("Client Connected\n");
     read(c, buf, 511);
     data = "httpd v1.0\n";
     write(c, data, strlen(data));

     close(c);
     close(s);

     return 0;


}