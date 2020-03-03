/*
 * @Author: your name
 * @Date: 2020-03-02 19:46:51
 * @LastEditTime: 2020-03-03 15:36:37
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: /mem/heap.h
 */
#ifndef HEAP__H
#define HEAP__H

#include <stdint.h>
#include <stdio.h>

//可申请的内存块数目
#define LUT_LEN 16
//内存池大小
#define MAX_MEM_SIZE    (1024*1024*16)

/**
 * 查找表结构体
*/
typedef struct mem_lut_t
{
    struct mem_lut_t *last;//前向指针
    uint8_t *base_addr;//分配的基地址(默认字节地址，请自行转换)
    uint32_t len;//分配的长度,单位字节
    struct mem_lut_t *next;//后向指针
    uint8_t is_free;//空闲标志

}mem_lut;


void mem_init(void);
void mem_test(void);
void *my_malloc(uint32_t size);
void my_free(void *addr);
void my_memset(void * p,char pad, int num);
#endif  
 