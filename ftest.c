/*
 * @Author: your name
 * @Date: 2020-03-05 23:01:21
 * @LastEditTime: 2020-03-07 03:25:34
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /FATFS_SIMULATOR/ftest.c
 */

#include <stdio.h>

#include "ftest.h"
#include "ff.h"
#include "mydisk.h"
#include "myheap.h"

extern disk_dev flash;
void fat_test(){
	FATFS *userfs;
	FRESULT res;
	FIL fl;
	uint32_t bw;
	uint32_t br;
	uint8_t *buf;
    mem_init();
    buf= (uint8_t *)my_malloc(512);
	userfs=(FATFS *)my_malloc(sizeof(FATFS));
	if(fake_disk_init(&flash)){
        printf("fake_disk_init failed\n");
        return ;
    }
	f_mkfs("0",0,buf,512);

	res= f_mount(userfs,"0",1);
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
	printf("f_open=%d\n",res);

	f_unmount("0");
	my_free(buf);
	my_free(userfs);
}

void dir_test(){
    
}