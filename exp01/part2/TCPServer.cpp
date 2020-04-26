/* TCPServer.cpp - main */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <time.h>
#include "conio.h"

#define	WSVERS	MAKEWORD(2, 0)

#pragma comment(lib,"ws2_32.lib")  //ʹ��winsock 2.2 library
/*------------------------------------------------------------------------
 * main - Iterative TCP server for TIME service
 *------------------------------------------------------------------------
 */

int main(int argc, char *argv[]) 
/* argc: �����в��������� ���磺C:\> TCPServer 8080 
                     argc=2 argv[0]="TCPServer",argv[1]="8080" */
{
	puts("Server Active"); 
	struct	sockaddr_in fsin;	    /* the from address of a client	  */
	SOCKET	msock, ssock;		    /* master & slave sockets	      */
	WSADATA wsadata; 
	char	*service = "50500";
	struct  sockaddr_in sin;	    /* an Internet endpoint address		*/
    int	    alen;			        /* from-address length		        */
	char	*pts;			        /* pointer to time string	        */
	time_t	now;			        /* current time			            */
	int count=1; 
	char	buf[10];
	char str[25],IP[100],port[100];
	WSAStartup(WSVERS, &wsadata);						// ����winsock library��WSVERSָ������ʹ�õİ汾��wsadata����ϵͳʵ��֧�ֵ���߰汾
		
	msock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	// �����׽��֣�������������Э���(family)�����׽��֣�TCPЭ��
														// ���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET

	memset(&sin, 0, sizeof(sin));						// ��&sin��ʼ�ĳ���Ϊsizeof(sin)���ڴ���0
	
	sin.sin_family = AF_INET;							// ��������ַ��(INET-Internet)
	sin.sin_addr.s_addr = INADDR_ANY;					// ��������(�ӿڵ�)IP��ַ��
	sin.sin_port = htons((u_short)atoi(service));		// �����Ķ˿ںš�atoi--��asciiת��Ϊint��htons--������������(host to network��s-short 16λ)
	bind(msock, (struct sockaddr *)&sin, sizeof(sin));  // �󶨼�����IP��ַ�Ͷ˿ں�

	listen(msock, 5);                                   // ��������Ϊ5������������У����ѵ������������������еȴ�����
	while(!_kbhit()){ 		                                   // ����Ƿ��а���,���û�������ѭ����ִ��
		
		printf("######### action: %d\n",count++); 
		
		
		alen = sizeof(struct sockaddr);                         // ȡ����ַ�ṹ�ĳ���
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen); // ����������������������������������������󲢽������ӣ����ظ����ӵ��׽��֣����򣬱���䱻����ֱ�����зǿա�fsin�����ͻ���IP��ַ�Ͷ˿ں�
		in_addr tmp=fsin.sin_addr; 

//		int cc = send(ssock, message, strlen(message), 0);              
// �ڶ�������ָ���ͻ�����������������ΪҪ���͵��ֽ��������ĸ�����һ����0������ֵ��>=0 ʵ�ʷ��͵��ֽ�����0 �Է������رգ�SOCKET_ERROR ����
//		printf("you sent the message: %s\n", message);
		int cc = recv(ssock, buf, 9, 0);
		if(cc == SOCKET_ERROR)                          // ����������ر��׽���sock
	        printf("Error: %d.\n",GetLastError());
	    else if(cc == 0) {                             // �Է������ر�
	        printf("Server closed!",buf);  
	    }  else if(cc > 0) {
	        buf[cc] = '\0';	                       // ensure null-termination
	        printf("you have receive message: %s\n",buf);                         // ��ʾ�����յ��ַ���
	    } 
		(void) time(&now);                                      // ȡ��ϵͳʱ��
		pts = ctime(&now);                                      // ��ʱ��ת��Ϊ�ַ���
		cc = send(ssock, pts, strlen(pts), 0);   
		printf("you sent the time: %s", pts);  
		cc = send(ssock, buf, strlen(buf), 0);   
		printf("you echo the message: %s\n", buf);                               // ��ʾ���͵��ַ���
    	
    	itoa(tmp.S_un.S_un_b.s_b1, str, 10);
		strcpy(IP,str); 
    	itoa(tmp.S_un.S_un_b.s_b2, str, 10);
    	strcat(IP,"."); strcat(IP,str);
    	itoa(tmp.S_un.S_un_b.s_b3, str, 10);
    	strcat(IP,"."); strcat(IP,str);    	
    	itoa(tmp.S_un.S_un_b.s_b4, str, 10);
    	strcat(IP,"."); strcat(IP,str);
    	cc = send(ssock, IP, strlen(IP), 0);
		printf("the client IP is %s\n",IP); 
		
//		printf("$%d.%d.%d.%d\n",tmp.S_un.S_un_b.s_b1,tmp.S_un.S_un_b.s_b2,tmp.S_un.S_un_b.s_b3,tmp.S_un.S_un_b.s_b4); 
		itoa(fsin.sin_port, port, 10);
		cc = send(ssock, port, strlen(port), 0);
		printf("the client port is %s\n",port); 
		
		
		(void) closesocket(ssock);                              // �ر������׽���
	}
    (void) closesocket(msock);                                 // �رռ����׽���
	WSACleanup();                                             // ж��winsock library
	printf("���س�������...");
	getchar();										// �ȴ����ⰴ��
	getchar();
	return 0; 

}

