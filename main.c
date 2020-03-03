/*
 * @Author: your name
 * @Date: 2020-03-03 10:03:44
 * @LastEditTime: 2020-03-03 16:32:29
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /FAT_TEST/main.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "mydisk.h"
#include "myheap.h"
#include "ff.h"

extern disk_dev flash;

int main(int argc,char *argv[])
{
	printf("Hello world\n");
	
	mem_init();
	fake_disk_init(&flash);
	FATFS userfs;
	FRESULT res;
	FIL fl;
	uint32_t bw;
	uint32_t br;
	
	uint8_t *buf= (uint8_t *)my_malloc(512);
	f_mkfs("0",0,buf,512);
	res= f_mount(&userfs,"0",0);
	printf("f_mount=%d\n",res);
	res= f_open(&fl,"0:test.txt",FA_CREATE_ALWAYS|FA_WRITE);
	printf("f_open=%d\n",res);
	sprintf(buf,"%s","hello world");
	res=f_write(&fl,buf,20,&bw);
	printf("f_write=%d\n",res);
	res=f_close(&fl);	
	printf("f_close=%d\n",res);


	res= f_open(&fl,"0:test.txt",FA_READ);
	res=f_read(&fl,buf,11,&br);
	printf("f_read=%d\tbuf=%s\n",res,buf);
	res=f_close(&fl);	
	printf("f_close=%d\n",res);
	my_free(buf);
	exit(0);
}

