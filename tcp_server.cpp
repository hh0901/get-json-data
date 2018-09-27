#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
#include<afxmt.h>
#define QUEUE 20


void main()
{

        int PORT = 8911;

        char *recStr;
        fd_set rfds;
        struct timeval tv;
        int retval, maxfd;


        //创建用于监听的套接字
        int ss = socket(AF_INET, SOCK_STREAM, 0);   //AF_INET   IPV4   ;SOCK_STREAM   TCP
            struct sockaddr_in server_sockaddr;
            server_sockaddr.sin_family = AF_INET;
            server_sockaddr.sin_port = htons(PORT);
            server_sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);

            /*bind*/
            if(bind(ss, (struct sockaddr* ) &server_sockaddr, sizeof(server_sockaddr))==-1) {
                perror("bind");
                exit(1);
            }
            /*listen*/
            if(listen(ss, QUEUE) == -1) {
                perror("listen");
                exit(1);
            }


        while(1)
        {
                //等待客户请求到来
            /*connect*/
            struct sockaddr_in client_addr;
            socklen_t length = sizeof(client_addr);
            ///成功返回非负描述字，出错返回-1
            int conn = accept(ss, (struct sockaddr*)&client_addr, &length);   //目测需要客户端部分的addr
            if( conn < 0 ) {
                perror("connect");
                exit(1);
            }

            printf("Accept client IP:[%s]\n", inet_ntoa(client_addr.sin_addr));



// 		//接收数据
            recv(conn, recStr, 200, 0);
            printf("%s\n", recStr);

            close(conn);
        }

        close(ss);
}
