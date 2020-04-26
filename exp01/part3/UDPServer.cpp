/* UDPServer.cpp */

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>
#include "conio.h"
#define	BUFLEN		2000                  // ��������С
#define WSVERS		MAKEWORD(2, 2)        // ָ���汾2.2 
#pragma comment(lib,"ws2_32.lib")         // ����winsock 2.2 Llibrary
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
    WSAStartup(WSVERS, &wsadata);   /* ����winsock library��WSVERSΪ����汾,wsadata����ϵͳʵ��֧�ֵ���߰汾��    */		
    sock = socket(PF_INET, SOCK_DGRAM,IPPROTO_UDP); // ����UDP�׽���, ������������Э���(family)�����ݱ��׽��֣�UDPЭ��ţ� ���أ�Ҫ�����׽��ֵ���������INVALID_SOCKET
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;                     // ��(����)���еĽӿڡ�
	sin.sin_port = htons((u_short)atoi(service));         // ��ָ���ӿڡ�atoi--��asciiת��Ϊint��htons -- ������(host)ת��Ϊ������(network), Ϊshort���͡� 
	bind(sock, (struct sockaddr *)&sin, sizeof(sin));     // �󶨱��ض˿ںţ��ͱ���IP��ַ)

 	while(!_kbhit()){                                    //����Ƿ��а���
	    cc = recvfrom(sock, buf, BUFLEN, 0, (SOCKADDR *)&from, &fromsize);  //���տͻ����ݡ����ؽ����ccΪ���յ��ַ�����from�н������ͻ�IP��ַ�Ͷ˿ںš�
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
		
		(void) time(&now);                                      // ȡ��ϵͳʱ��
	    ptr = ctime(&now);                                      // ��ʱ��ת��Ϊ�ַ���
		printf("the client time is %s\n",ptr); 
		cc = sendto(sock, ptr, 100, 0,(SOCKADDR *)&from, sizeof(from));
		
		
		puts("over"); 
	}
	
	closesocket(sock);
	WSACleanup();       	          /* ж��ĳ�汾��DLL */
	getchar();
	return 0; 
}



