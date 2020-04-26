/* UDPClient.cpp */
#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <string.h>
#include <time.h>

#define	BUFLEN		50                  // ��������С
#define WSVERS		MAKEWORD(2, 2)        // ָ���汾2.2 
#pragma comment(lib,"ws2_32.lib")         // ����winsock 2.2 Llibrary

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
    WSAStartup(WSVERS, &wsadata);       /* ����ĳ�汾Socket��DLL        */	

    sock = socket(PF_INET, SOCK_DGRAM,IPPROTO_UDP);

	memset(&toAddr, 0, sizeof(toAddr));
	toAddr.sin_family = AF_INET;
	toAddr.sin_port = htons((u_short)atoi(service));    //atoi����asciiת��Ϊint. htons��������(host)ת��Ϊ������(network), s--short
	toAddr.sin_addr.s_addr = inet_addr(host);           //���hostΪ��������Ҫ���ú���gethostbyname������ת��ΪIP��ַ
	
	
	printf("input message:"); scanf("%s",buf); 
	puts(""); 
	cc = sendto(sock, buf, BUFLEN, 0,(SOCKADDR *)&toAddr, sizeof(toAddr));
    if (cc == SOCKET_ERROR){
        printf("����ʧ�ܣ�����ţ�%d\n", WSAGetLastError());
    }
	else{
		printf("���ͳɹ�!\r\n");
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
	WSACleanup();       	          /* ж��ĳ�汾��DLL */  
	printf("��������˳�...");
	getchar();
	return 0; 
}
