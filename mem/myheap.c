/*
 * @Author: fyra
 * @Date: 2020-03-02 19:46:50
 * @LastEditTime: 2020-03-03 15:55:32
 * @LastEditors: Please set LastEditors
 * @Description: 简单内存管理
 * @FilePath: /mem/myheap.c
 */
 #include "myheap.h"

 mem_lut mem_tab[LUT_LEN];//内存管理表
 uint8_t mem_pool[MAX_MEM_SIZE];//内存池


/**
 * 函数名:  my_memset
 * 描述:    填充数组
 * arg      p   要填充的对象
 *          pad 填充内容
 *          num 长度
 * 
*/
void my_memset(void * p,char pad, int num)
{
    uint8_t *ptr=(uint8_t *)p;
    for (int i = 0; i < num; i++){
        *(ptr+i)=pad;        
    } 
}


/**
 * 函数名:  mem_init
 * 描述:    初始化内存查找表
 * 
*/
void mem_init()
{
    mem_tab[0].last=0;//链表头
    mem_tab[0].base_addr=(uint8_t*)mem_pool;
    mem_tab[LUT_LEN-1].next=0;//链表尾
    for (int i = 0; i < LUT_LEN; i++){
        mem_tab[i].is_free=1;//初始空闲
        if(i!=0){
            mem_tab[i].last=&mem_tab[i-1]; 
        }
        if(i!=LUT_LEN-1){
            mem_tab[i].next=&mem_tab[i+1];  
        } 
    }
}

/**
 * 函数名   my_malloc
 * 描述     分配内存
 * 参数     
 *  size   分派大小
 * 返回值   地址
*/
void *my_malloc(uint32_t size)
{
    mem_lut *p=&mem_tab[0];
    while (p->next){            
        if(p->is_free){//空闲可用
            if(p->last==0){//是链表头
                //do nothing
            }else{       
                p->base_addr=p->last->len+p->last->base_addr;//紧接上一个
            }
            /**
             * 关于下面的长条件：
             * 要么下一个表空闲，要么当前表剩余长度够用
             * 才会分配
            */
            if(p->next->is_free||\
                (p->next->is_free==0&&\
                (p->next->base_addr>=\
                p->base_addr+size))){
                    p->len=size;
                    p->is_free=0;//占用标记
#ifdef DEBUG                    
                    printf("malloc\t%d\t@0x%x\n",size,(uint32_t)p->base_addr);
#endif                    
                    return p->base_addr;
                }

        }//else if
        p=p->next;
    }
        /* code */
    return NULL;
}
/**
 * 函数名   my_free
 * 描述    释放
 * 参数     
 * addr   地址
 * 
*/
void my_free(void *addr)
{
 
    mem_lut *p=&mem_tab[LUT_LEN-1];//从后往前找

    for (int i = 0; i < LUT_LEN; i++){
        if((p->base_addr==addr)&&p->is_free==0){
            p->is_free=1;   
#ifdef DEBUG                    
             printf("free\t%d\t@0x%x\n",p->len,(uint32_t)addr);
#endif    
            return;         
        }
        p=p->last;
    }   
}

/**
 * 函数名   mem_test
 * 描述     测试代码
*/
void mem_test(void)
{
    char *p0=(char *)my_malloc(10);
    char *p1=(char *)my_malloc(100);
    my_free(p0);
    p0=(char*)my_malloc(20);
    my_free(p0);
    p0=(char *)my_malloc(10);
    my_free(p0);
    my_free(p1);
}