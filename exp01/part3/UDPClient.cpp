/* UDPClient.cpp */
#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>

#define	BUFLEN		50                  // 缓冲区大小
#define WSVERS		MAKEWORD(2, 2)        // 指明版本2.2 
#pragma comment(lib,"ws2_32.lib")         // 加载winsock 2.2 Llibrary

int main()
{
	char	*host = "127.0.0.1";	    /* server IP to connect         */
	char	*service = "50500";  	    /* server port to connect       */
	struct sockaddr_in toAddr;	        /* an Internet endpoint address	*/
	char	buf[BUFLEN+1];   		    /* buffer for one line of text	*/
	SOCKET	sock;		  	            /* socket descriptor	    	*/
	int	cc;			                    /* recv character count		    */
	char	*pts;			            /* pointer to time string	    */
	time_t	now;			            /* current time			        */

	WSADATA wsadata;
    WSAStartup(WSVERS, &wsadata);       /* 启动某版本Socket的DLL        */	

    sock = socket(PF_INET, SOCK_DGRAM,IPPROTO_UDP);

	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons((u_short)atoi(service));    //atoi：把ascii转化为int. htons：主机序(host)转化为网络序(network), s--short
	toAddr.sin_addr.s_addr = inet_addr(host);           //如果host为域名，需要先用函数gethostbyname把域名转化为IP地址
	
	
	printf("input message:"); scanf("%s",buf); 
	puts(""); 
	cc = sendto(sock, buf, BUFLEN, 0,(SOCKADDR *)&toAddr, sizeof(toAddr));
    if (cc == SOCKET_ERROR){
        printf("发送失败，错误号：%d\n", WSAGetLastError());
    }
	else{
		printf("发送成功!\r\n");
	}
	int    toAddrsize = sizeof(toAddr);
	
	cc = recvfrom(sock, buf, 1000, 0, (SOCKADDR *)&toAddr, &toAddrsize);
	if (cc == SOCKET_ERROR){
        printf("recvfrom() failed; %d\n", WSAGetLastError());
    }
	else{
		buf[cc] = '\0';
		printf("the echo message %s\n", buf);
	}
	cc = recvfrom(sock, buf, 1000, 0, (SOCKADDR *)&toAddr, &toAddrsize);
	if (cc == SOCKET_ERROR){
        printf("recvfrom() failed; %d\n", WSAGetLastError());
    }
	else{
		buf[cc] = '\0';
		printf("the client IP %s\n", buf);
	}
	cc = recvfrom(sock, buf, 1000, 0, (SOCKADDR *)&toAddr, &toAddrsize);
	if (cc == SOCKET_ERROR){
        printf("recvfrom() failed; %d\n", WSAGetLastError());
    }
	else{
		buf[cc] = '\0';
		printf("the client port %s\n", buf);
	}
	cc = recvfrom(sock, buf, 1000, 0, (SOCKADDR *)&toAddr, &toAddrsize);
	if (cc == SOCKET_ERROR){
        printf("recvfrom() failed; %d\n", WSAGetLastError());
    }
	else{
		buf[cc] = '\0';
		printf("the client time %s\n", buf);
	}
	
	closesocket(sock);
	WSACleanup();       	          /* 卸载某版本的DLL */  
	printf("按任意键退出...");
	getchar();
	return 0; 
}
