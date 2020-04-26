/* UDPServer.cpp */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include "conio.h"
#define	BUFLEN		2000                  // 缓冲区大小
#define WSVERS		MAKEWORD(2, 2)        // 指明版本2.2 
#pragma comment(lib,"ws2_32.lib")         // 加载winsock 2.2 Llibrary
/*------------------------------------------------------------------------
 * main - TCP client for DAYTIME service
 *------------------------------------------------------------------------
 */
int main()
{
	char   *host = "127.0.0.1";	    /* server IP Address to connect */
	char   *service = "50500";  	    /* server port to connect       */
	struct sockaddr_in sin;	        /* an Internet endpoint address	*/
	struct sockaddr_in from;        /* sender address               */
	int    fromsize = sizeof(from);
	char   buf[BUFLEN+1];   	    /* buffer for one line of text	*/
	SOCKET	sock;		  	        /* socket descriptor	    	*/
	int	cc;			                /* recv character count		    */
	time_t now; 
	char *ptr,IP[100],port[100],str[100]; 
	strcpy(buf,"sdf"); 
	
	WSADATA wsadata;
    WSAStartup(WSVERS, &wsadata);   /* 加载winsock library，WSVERS为请求版本,wsadata返回系统实际支持的最高版本。    */		
    sock = socket(PF_INET, SOCK_DGRAM,IPPROTO_UDP); // 创建UDP套接字, 参数：因特网协议簇(family)，数据报套接字，UDP协议号， 返回：要监听套接字的描述符或INVALID_SOCKET
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;                     // 绑定(监听)所有的接口。
	sin.sin_port = htons((u_short)atoi(service));         // 绑定指定接口。atoi--把ascii转化为int，htons -- 主机序(host)转化为网络序(network), 为short类型。 
	bind(sock, (struct sockaddr *)&sin, sizeof(sin));     // 绑定本地端口号（和本地IP地址)

 	while(!_kbhit()){                                    //检测是否有按键
	    cc = recvfrom(sock, buf, BUFLEN, 0, (SOCKADDR *)&from, &fromsize);  //接收客户数据。返回结果：cc为接收的字符数，from中将包含客户IP地址和端口号。
        if (cc == SOCKET_ERROR){
            printf("recvfrom() failed; %d\n", WSAGetLastError());
            break;
        }
		else{
			buf[cc] = '\0';
			cc = sendto(sock, buf, 100, 0,(SOCKADDR *)&from, sizeof(from));
		}
		in_addr tmp=from.sin_addr; 
//		itoa(tmp.S_un.S_un_b.s_b1, str, 10);
//		strcpy(IP,str); 
//    	itoa(tmp.S_un.S_un_b.s_b2, str, 10);
//    	strcat(IP,"."); strcat(IP,str);
//    	itoa(tmp.S_un.S_un_b.s_b3, str, 10);
//    	strcat(IP,"."); strcat(IP,str);    	
//    	itoa(tmp.S_un.S_un_b.s_b4, str, 10);
//    	strcat(IP,"."); strcat(IP,str);
		
		sprintf(IP,"%d.%d.%d.%d",tmp.S_un.S_un_b.s_b1,tmp.S_un.S_un_b.s_b2,tmp.S_un.S_un_b.s_b3,tmp.S_un.S_un_b.s_b4); 
		printf("the client IP is %s\n",IP); 
		cc = sendto(sock, IP, 100, 0,(SOCKADDR *)&from, sizeof(from));
		
		itoa(from.sin_port, port, 10);
		printf("the client port is %s\n",port); 
	    cc = sendto(sock, port, 100, 0,(SOCKADDR *)&from, sizeof(from));
		
		(void) time(&now);                                      // 取得系统时间
	    ptr = ctime(&now);                                      // 把时间转换为字符串
		printf("the client time is %s\n",ptr); 
		cc = sendto(sock, ptr, 100, 0,(SOCKADDR *)&from, sizeof(from));
		
		
		puts("over"); 
	}
	
	closesocket(sock);
	WSACleanup();       	          /* 卸载某版本的DLL */
	getchar();
	return 0; 
}



