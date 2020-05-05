/* TCPClient.cpp */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <windows.h>
#include <process.h>
#include <math.h>
#define	BUFLEN		2000                  // 缓冲区大小
#define WSVERS		MAKEWORD(2, 0)        // 指明版本2.0 
#pragma comment(lib,"ws2_32.lib")         // 使用winsock 2.0 Llibrary
/*------------------------------------------------------------------------
 * main - TCP client for TIME service
 *------------------------------------------------------------------------
 */
int over=0; 
unsigned __stdcall threaddisp(void *pno){
	char buf[50],inf[100];
	SOCKET psock = *((SOCKET *)pno);
	while(1){
		int cc = recv(psock, buf, 50, 0);
		if(cc <= 0){                        // 出错。其后必须关闭套接字sock
	        printf("Server closed!\n"); over=1; 
			break;  
	    }  else {
	        buf[cc] = '\0';	                       // ensure null-termination
	        printf("\ryou have receive message: %s\n",buf);   // 显示所接收的字符串
	    } 
	    cc = recv(psock, inf, 100, 0);
		if(cc <= 0){    
	        printf("Server closed!\n"); over=1; 
			break;  
	    }  else {
	        inf[cc] = '\0';	                       // ensure null-termination
	        printf("From: %s\n",inf);   // IP and time 
	    } 
	    printf("the message:"); 
	}
	(void) closesocket(psock);
}

int main()
{
	puts("CLIENT");
//	char 	*host = "127.0.0.1"; 
	char	*host = "106.53.78.95";	    /* server IP to connect         */
	char	*service = "50500";  	    /* server port to connect       */
	struct sockaddr_in sin;	            /* an Internet endpoint address	*/
	char	buf[BUFLEN+1];   		    /* buffer for one line of text	*/
	SOCKET	sock;		  	            /* socket descriptor	    	*/
	int	cc;			                    /* recv character count		    */
	char msg[10];
		
	WSADATA wsadata;
	WSAStartup(WSVERS, &wsadata);						  //加载winsock library。WSVERS为请求的版本，wsadata返回系统实际支持的最高版本
  
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	  //创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议
														  //返回：要监听套接字的描述符或INVALID_SOCKET
	
    memset(&sin, 0, sizeof(sin));						  // 从&sin开始的长度为sizeof(sin)的内存清0
    sin.sin_family = AF_INET;							  // 因特网地址簇
    sin.sin_addr.s_addr = inet_addr(host);                // 设置服务器IP地址(32位)
    sin.sin_port = htons((u_short)atoi(service));         // 设置服务器端口号  
    int ret=connect(sock, (struct sockaddr *)&sin, sizeof(sin));  
// 连接到服务器，第二个参数指向存放服务器地址的结构，第三个参数为该结构的大小，返回值为0时表示无错误发生，返回SOCKET_ERROR表示出错，应用程序可通过WSAGetLastError()获取相应错误代码。
	HANDLE hThread; 
	hThread=(HANDLE)_beginthreadex(NULL,0,&threaddisp, (void *)&sock, 0, NULL);
	
	for(int i=1;i<=100000000;i++); //用于给线程延时 
	while(!over){
		printf("the message:"); 
		scanf("%s",msg);
		if(!strcmp(msg,"#Q")) break;
		cc=send(sock, msg, strlen(msg), 0);
		
	}
	printf("you quit the connnect. "); 
    
	closesocket(sock);                             // 关闭监听套接字
    WSACleanup();                                  // 卸载winsock library

    printf("按回车键继续...");
	getchar();										// 等待任意按键
	return 0;  
}
