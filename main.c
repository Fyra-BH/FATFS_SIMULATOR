/*
 * @Author: your name
 * @Date: 2020-03-03 10:03:44
 * @LastEditTime: 2020-03-07 03:02:26
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /FAT_TEST/main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "mydisk.h"
#include "myheap.h"
#include "ff.h"
#include "ftest.h"

int main(int argc,char *argv[])
{
	fat_test();
	printf("test finish\n");
	return 0;
}

