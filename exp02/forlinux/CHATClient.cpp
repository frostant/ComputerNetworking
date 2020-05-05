/* TCPClient.cpp */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <windows.h>
#include <process.h>
#include <math.h>
#define	BUFLEN		2000                  // ��������С
#define WSVERS		MAKEWORD(2, 0)        // ָ���汾2.0 
#pragma comment(lib,"ws2_32.lib")         // ʹ��winsock 2.0 Llibrary
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
		if(cc <= 0){                        // ����������ر��׽���sock
	        printf("Server closed!\n"); over=1; 
			break;  
	    }  else {
	        buf[cc] = '\0';	                       // ensure null-termination
	        printf("\ryou have receive message: %s\n",buf);   // ��ʾ�����յ��ַ���
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
	WSAStartup(WSVERS, &wsadata);						  //����winsock library��WSVERSΪ����İ汾��wsadata����ϵͳʵ��֧�ֵ���߰汾
  
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);	  //�����׽��֣�������������Э���(family)�����׽��֣�TCPЭ��
														  //���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET
	
    memset(&sin, 0, sizeof(sin));						  // ��&sin��ʼ�ĳ���Ϊsizeof(sin)���ڴ���0
    sin.sin_family = AF_INET;							  // ��������ַ��
    sin.sin_addr.s_addr = inet_addr(host);                // ���÷�����IP��ַ(32λ)
    sin.sin_port = htons((u_short)atoi(service));         // ���÷������˿ں�  
    int ret=connect(sock, (struct sockaddr *)&sin, sizeof(sin));  
// ���ӵ����������ڶ�������ָ���ŷ�������ַ�Ľṹ������������Ϊ�ýṹ�Ĵ�С������ֵΪ0ʱ��ʾ�޴�����������SOCKET_ERROR��ʾ����Ӧ�ó����ͨ��WSAGetLastError()��ȡ��Ӧ������롣
	HANDLE hThread; 
	hThread=(HANDLE)_beginthreadex(NULL,0,&threaddisp, (void *)&sock, 0, NULL);
	
	for(int i=1;i<=100000000;i++); //���ڸ��߳���ʱ 
	while(!over){
		printf("the message:"); 
		scanf("%s",msg);
		if(!strcmp(msg,"#Q")) break;
		cc=send(sock, msg, strlen(msg), 0);
		
	}
	printf("you quit the connnect. "); 
    
	closesocket(sock);                             // �رռ����׽���
    WSACleanup();                                  // ж��winsock library

    printf("���س�������...");
	getchar();										// �ȴ����ⰴ��
	return 0;  
}
