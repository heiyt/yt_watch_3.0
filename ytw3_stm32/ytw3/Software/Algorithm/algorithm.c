//
// Created by heiyt_R9000P on 2024/2/26.
//

#include "algorithm.h"

void swap(uint32_t *a,uint32_t *b) {
    uint32_t temp = *a;
    *a = *b;
    *b = temp;
}

void BubbleSort(uint32_t list[],uint16_t n)//冒泡排序
{
    static int i,j;static int temp;bool flag;
    flag = true;
    for(i = 1;flag && i<n-1;i++){
        flag = false;
        for(j = 0;j<n-i;j++){
            if(list[j]>list[j+1]){
                flag = true;
                swap(&list[j],&list[j+1]);
            }
        }
    }
}