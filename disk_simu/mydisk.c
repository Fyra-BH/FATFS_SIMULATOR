/*
 * @Author: your name
 * @Date: 2020-03-03 10:12:31
 * @LastEditTime: 2020-03-07 03:27:20
 * @LastEditors: Please set LastEditors
 * @Description: 使用文件来模拟磁盘
 * @FilePath: /FAT_TEST/disk_simu/mydisk.c
 */
#include "mydisk.h"
#include "myheap.h"


// char *name;
// uint32_t sector_size;
// uint32_t block_size;
// uint64_t sector_num;
disk_dev flash=
{
    "FLASH_4M",
    4096,
    1,
    4*1024*1024/4096
};

/**
 * 2M的SD卡可真是小呢
*/
disk_dev sdcard=
{
    "SD_2M",
    512,
    1,
    1*1024*1024/512,
};


/**
 * 函数名   fake_disk_init
 * 描述     强调fake，这不是真正的磁盘，只是用文件模拟的
 * 参数     disk_dev
 * 注       请先调教好disk参数
*/
uint8_t fake_disk_init(disk_dev *disk)
{
    FILE *file;
    uint32_t size;//写文件时用到
    file=fopen(disk->name,"w");
        if(file==NULL)return -1;//失败
    uint8_t *pad=(uint8_t *)my_malloc(disk->sector_size);//填充磁盘用
    my_memset(pad,0xff,disk->sector_size);
    for (int i = 0; i < disk->sector_num; i++){
         size=fwrite(pad,disk->sector_size,1,file);
         if(size!=1)return -1;//写出错      
    }
    fclose(file);
    my_free(pad);
    return 0;
}



/**
 * @name:   read_sector
 * @func:   read sectors
 * @args:     
 *          disk        device
 *          buff        buffer
 *          sector_addr addrss to read
 *          count       number of sectors to read        
*/
uint8_t read_sector(disk_dev *disk,uint8_t *buff,uint32_t sector_addr,uint32_t count)
{
    FILE *file=NULL;
    file=fopen(disk->name,"r");
        if(file==NULL)return -1;//failed
        if(fseek(file,sector_addr*disk->sector_size,SEEK_SET))return -1;//failed
    uint32_t size=fread(buff,disk->sector_size,count,file);
        if(size!=count)return  -1;//failed
        if(fclose(file))return -1;//failed
    return 0;
}


/**
 * @name:   write_sector
 * @func:   write_sectors
 * @args:     
 *          disk        device
 *          buff        buffer
 *          sector_addr addrss to write
 *          count       number of sectors to write        
*/
uint8_t write_sector(disk_dev *disk,uint8_t *buff,uint32_t sector_addr,uint32_t count)
{
    FILE *file=NULL;
    file=fopen(disk->name,"rb+");
        if(file==NULL)return -1;//failed
        if(fseek(file,sector_addr*disk->sector_size,SEEK_SET))return -1;//failed
    uint32_t size=fwrite(buff,disk->sector_size,count,file);
        if(size!=count)return  -1;//failed
        if(fclose(file))return -1;//failed
    return 0;
}
