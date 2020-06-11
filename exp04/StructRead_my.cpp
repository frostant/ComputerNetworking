/*
  本文件把三个结构变量值写入文件，然后再从该文件中读出这些值并显示出来
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctime>
#include <iostream>
#define EMAIL_LEN 30
#define USER_NAME_LEN 30
using namespace std;
// typedef struct {
// 	char name[NAME_LEN];
// 	int age;
// } people;

// Person的信息表示：
struct Person {
   char username[USER_NAME_LEN];      // 员工名
   int level;                         // 工资级别
   char email[EMAIL_LEN];             // email地址
   time_t sendtime;                    // 发送时间
   time_t regtime;                    // 注册时间
}; 

int main()
{


	FILE * fp;
	Person perBuf;
	if ((fp=fopen("D:\\temp\\bbb.stru", "rb")) == NULL) {
		printf("can't open the file!\n");
		exit(0);
	}
    
    // fread(&perBuf, sizeof(Person), 1, fp); 
    // cout<<" size:"<<sizeof(Person)<<endl;
    // printf("%s %d %s %s\n", perBuf.username, perBuf.level, perBuf.email, ctime(&perBuf.regtime));
    // puts("s");

	// fread的参数：缓冲区起始地址，每个数据的字节数，可缓存的数据个数，文件句柄
	//      返回值：实际读出的数据个数
    puts("\nThe Person Information:");
	while (fread(&perBuf, sizeof(Person), 1, fp) == 1) 
		printf("NAME:%s\nLEVEL:%d\nEmail:%s\nRegtime:%sSendtime:%s\n", 
            perBuf.username, perBuf.level, perBuf.email, ctime(&perBuf.regtime), ctime(&perBuf.sendtime));
	
	printf("struct save finished!\n");
	return 0;
}
/*

hello
123
hello@**.com
Network
18309043
lianyuteng@Win.com
exit
*/



