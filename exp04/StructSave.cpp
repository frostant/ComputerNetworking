/*
  本文件把三个结构变量值写入文件，然后再从该文件中读出这些值并显示出来
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string> 
#include <cstring> 
#define NAME_LEN 30
struct people{
	char name[NAME_LEN];
	int age;
};

int main()
{
	FILE * pFile;
	int i;
	people per[3];
	strcpy(per[0].name, "li");
	per[0].age = 20;
	strcpy(per[1].name, "wang");
	per[1].age = 18;
	strcpy(per[2].name, "zhang");
	per[2].age = 21;

	// 打开要写的二进制文件(w-write b-binary)，没有则创建，有则覆盖
	if ((pFile=fopen("D:\\temp\\aaa.bin", "wb")) == NULL) {
		printf("cant open the file!\n");
		getchar();
		exit(0);
	}
	puts("S");
	for (i = 0; i < 3; i++) {
		//fwrite的参数：数据的起始地址，每个数据的所占字节数，要写入的数据个数，文件句柄
		//      返回值：实际写入的数据个数
		if (fwrite(&per[i], sizeof(people), 1, pFile) != 1) {
			printf("file write error!\n");
		}
	}
	fclose(pFile);
	


	FILE * fp;
	people perBuf;
	if ((fp=fopen("D:\\temp\\aaa.bin", "rb")) == NULL) {
		// getchar();
		printf("can't open the file!\n");
		exit(0);
	}
	// fread的参数：缓冲区起始地址，每个数据的字节数，可缓存的数据个数，文件句柄
	//      返回值：实际读出的数据个数
	while (fread(&perBuf, sizeof(people), 1, fp) == 1) {
		printf("%d %s\r\n", perBuf.age, perBuf.name);
	}
	printf("struct copy finished!\n");
	return 0;
}
