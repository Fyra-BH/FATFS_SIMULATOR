/*
 * @Author: your name
 * @Date: 2020-03-03 10:12:32
 * @LastEditTime: 2020-03-03 15:09:16
 * @LastEditors: Please set LastEditors
 * @Description: 使用文件来模拟磁盘
 * @FilePath: /FAT_TEST/disk_simu/mydisk.h
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

// DSTATUS disk_initialize (BYTE pdrv);
// DSTATUS disk_status (BYTE pdrv);
// DRESULT disk_read (BYTE pdrv, BYTE* buff, LBA_t sector, UINT count);
// DRESULT disk_write (BYTE pdrv, const BYTE* buff, LBA_t sector, UINT count);
// DRESULT disk_ioctl (BYTE pdrv, BYTE cmd, void* buff);
// DWORD get_fattime ();


typedef struct disk_dev_t
{
    char *name;
    uint32_t sector_size;
    uint32_t block_size;
    uint64_t sector_num;
}disk_dev;

uint8_t fake_disk_init(disk_dev *disk);
uint8_t read_sector(disk_dev *disk,uint8_t *buff,uint32_t sector_addr,uint32_t count);
uint8_t write_sector(disk_dev *disk,uint8_t *buff,uint32_t sector_addr,uint32_t count);