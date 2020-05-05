/* 简单变量带入。创建两个独立的子线程进行求和(1+2+...+n),然后分别用一个数组元素返回结果。
   全局变量sumall保存所有线程的加数之和 */
/* TCPServer.cpp - main */
#include <stdlib.h>
#include <stdio.h>
//#include <winsock2.h>
#include <time.h>
//#include "conio.h"
//#include <windows.h>
//#include <process.h>
#include <math.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define	WSVERS	MAKEWORD(2, 0)

#pragma comment(lib,"ws2_32.lib")  //使用winsock 2.2 library

int msock, ssock[30];  
//SOCKET	msock, ssock[30];		    /* master & slave sockets	      */
char IPs[30][30];
int ports[30];

struct socketinf{
	int sock_;
	sockaddr_in fsin_;
	socketinf(int sock,sockaddr_in fsin){
		sock_=sock, fsin_=fsin; 
	}
};

//unsigned __stdcall threadrecv(void *pno){
void *threadrecv(void *pno){
	char	buf[50],*pts, inf[50];
	time_t now;
	socketinf inform = *((socketinf *)pno);
	int psock = inform.sock_;
	sockaddr_in ff = inform.fsin_; 
	while(1){
		strcpy(buf,"lyttest"); 
		int cc = recv(psock, buf, 50, 0);
		if(cc <= 0){    
	        printf("Server closed!\n"); 
			break;  
	    }  else {
	        buf[cc] = '\0';
	        printf("you have receive message: %s\n",buf);
	        for(int i=0;i<30;i++){
				if(ssock[i]!=NULL){
					send(ssock[i], buf, strlen(buf),0);
					printf("you chat the message: %s\n", buf);
					(void) time(&now); 
					pts = ctime(&now);
					sprintf(inf,"IP: %s:%d time: %s",inet_ntoa(ff.sin_addr),ff.sin_port,pts);
					send(ssock[i], inf, strlen(inf),0);
					printf("the inf is: #%s\n", inf);
					printf("$$%d, %s",i,buf); 
				}
			}
	    } 
		
	}
	(void) time(&now); strcpy(buf,"leave");
	pts = ctime(&now);
	for(int i=0;i<30;i++) if(ssock[i]!=NULL){
		if(ssock[i]!=NULL){
			send(ssock[i], buf, strlen(buf),0);
			printf("you chat the message: %s\n", buf);
			sprintf(inf,"IP: %s:%d time: %s",inet_ntoa(ff.sin_addr),ff.sin_port,pts);
			send(ssock[i], inf, strlen(inf),0);
			printf("the inf is: #%s\n", inf);
		}
	}
	while(1); 
	close(psock);
}
int main(int argc, char *argv[]) 
/* argc: 命令行参数个数， 例如：C:\> TCPServer 8080 
                     argc=2 argv[0]="TCPServer",argv[1]="8080" */
{
	puts("SERVER"); 
	struct	sockaddr_in fsin;	    /* the from address of a client	  */
//	WSADATA wsadata; 
	char	*service = "50500";
	char	buf[50],*pts, inf[50];
	struct  sockaddr_in sin;	    /* an Internet endpoint address		*/
    socklen_t    alen;
	int  idx;		        /* from-address length		        */
	time_t	now;			        /* current time			            */
	int count=1; 
	
	for(int i=0;i<30;i++) ssock[i]=NULL; 
//	WSAStartup(WSVERS, &wsadata);						// 加载winsock library。WSVERS指明请求使用的版本。wsadata返回系统实际支持的最高版本
	msock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	// 创建套接字，参数：因特网协议簇(family)，流套接字，TCP协议
														// 返回：要监听套接字的描述符或INVALID_SOCKET
	memset(&sin, 0, sizeof(sin));						// 从&sin开始的长度为sizeof(sin)的内存清0
	sin.sin_family = AF_INET;							// 因特网地址簇(INET-Internet)
	sin.sin_addr.s_addr = INADDR_ANY;					// 监听所有(接口的)IP地址。
	sin.sin_port = htons((u_short)atoi(service));		// 监听的端口号。atoi--把ascii转化为int，htons--主机序到网络序(host to network，s-short 16位)
	bind(msock, (struct sockaddr *)&sin, sizeof(sin));  // 绑定监听的IP地址和端口号
	
//	HANDLE hThread; //
	
	listen(msock, 5);                                   // 建立长度为5的连接请求队列，并把到来的连接请求加入队列等待处理。
	while(1){ 		                                   // 检测是否有按键,如果没有则进入循环体执行
		alen = sizeof(struct sockaddr);                         // 取到地址结构的长度
		for(int i=0;i<30;i++){
			if(ssock[i]==NULL){
				ssock[i] = accept(msock, (sockaddr *)&fsin, &alen);
				printf("The %d chat interaction.\nENTER\n",count++);
//				(void) time(&now); strcpy(buf,"ENTER"); 
//				pts = ctime(&now);
//				sprintf(inf,"IP: %s:%d time: %s",inet_ntoa(fsin.sin_addr),fsin.sin_port,pts);
//				printf("the inf is: #%s\n", inf);
//				for(int i=0;i<30;i++) if(ssock[i]!=NULL){
//					send(ssock[i], buf, strlen(buf),0);
//					send(ssock[i], inf, strlen(inf),0);
//				}
				idx=i; break;  
			}
			if(i==29) puts(" the socket is fully."); 
		}
		socketinf t=socketinf(ssock[idx],fsin);
//		hThread = (HANDLE)_beginthreadex(NULL,0,&threadrecv, (void *)&t, 0, NULL); 
		int hThread; pthread_t a_thread; 
		hThread = pthread_create(&a_thread, NULL, threadrecv, (void *)&t );
//		ssock = accept(msock, (struct sockaddr *)&fsin, &alen); 
	}
    close(msock);                                 // 关闭监听套接字
//	WSACleanup();                                             // 卸载winsock library
	printf("按任意键结束...");
	getchar();										// 等待任意按键
	return 0; 

}

