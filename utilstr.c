/*================================================================
*   Copyright (C) 2018 Vertiv Tech Co Ltd. All rights reserved.
*   
*   文件名称：utilstr.c
*   创 建 者：yunzhongke
*   创建日期：2018年06月27日09时
*   描    述：
*
================================================================*/

#include "utilstr.h"
#include <stdio.h>
#include <stdlib.h>
#include <alloca.h>

char* substr(char* str , int start_pos , int count)
{
   char *ret = (char*)alloca(count + 1); 
   int src_len = strlen(str);
   if (src_len - start_pos < count || start_pos < 0)
       return NULL;

   memcpy(ret , str + start_pos , count);
   ret[count] = 0;
   return  ret;
}

int find_substr(char *str , const char *sub)
{
    if (!str || !sub)
        return -1;

    int ret_pos = -1 ;
    for (int pos = 0; str[pos] != 0 ; ++pos){
        int flag = 1; // 找到子元素的标记位

        if (str[pos] == *sub){
            int i = 1;
            ret_pos = pos;
            while(i < strlen(sub) ){
                if ( str[++pos] != sub[i++] ){
                    ret_pos = -1;
                    flag = 0;
                    break;
                }
            }

            if (flag){
                return ret_pos;
            }
        }
    }
    return ret_pos;
}

int find_last_substr(char *str , const char *sub)
{
    int ret_pos = -1 , len_sub = strlen(sub);

    for (int str_pos = strlen(str) - 1 , sub_pos = len_sub - 1; str_pos >= 0 ; --str_pos){
        int flag = 1; // 找到子元素的标记位

        if (str[str_pos] == sub[sub_pos]){
            int i = sub_pos ; 
            ret_pos = str_pos;
            while(i > 0){
                if ( str[--str_pos] != sub[--i] ){
                    ret_pos = -1;
                    flag = 0;
                    break;
                }
            }
            if ( flag )
                return ret_pos - len_sub + 1; // sub多减了一个1
        }
    }
    return ret_pos;
}

int substr_num(char *str , const char* sub)
{
    int ret = 0 , pos = 0 , num = 0;
    while(str[pos] != 0){
        ret = find_substr(str + pos , sub);
        if (ret == -1 || pos > strlen(str))
            break;
        else {
            ++num;
        }
        pos += ret + strlen(sub);
    }
    return num;
}

int insert(char *str , const int pos , const char *sub)
{
    int len = strlen(str); 
    if (pos > len || pos < 0 || strlen(sub) + pos > len)
        return -1;
    
}

int count_int(int data)
{
   int ret = 0;
   if (data < 10) 
       return ++ret;
   else{
       ++ret;
       return ret + count_int(data / 10);
   }
}

char* int_to_str(int data)
{
    char buf[128] = {0};
    for (int i = 0; ; ++i){
        if (data < 10){
            buf[i] = data + '0';
            break;
        }
        else if (data % 10 < 10){
            buf[i] = data % 10 + '0';
        }
        data /= 10;
    }
    
    return reversion_str(buf);    
}

char* reversion_str(char *input)
{
    if (!input)
        return NULL;

    int len = strlen(input);
    char *ret = (char*)alloca(len + 1);
    int start = 0 , end = len - 1;
    while(start < len){
       char tmp = input[end];
       ret[start++] = input[end];
       input[end--] = tmp; 
    }
    ret[start] = 0;

    return ret;
}

unsigned int decstr_to_int(char *input , int digit)
{
    unsigned int ret = 0;

    while(digit-- > 0){
        ret += pow(10 , digit) * (*input++ - '0');
    }
    return ret;
}

int float_to_str(float data , char *out)
{
    sprintf(out , "%.3f" , data);
    return strlen(out);  
}

float str_to_float(char *input)
{
    float ret = 0;
    sscanf(input , "%f" , &ret);
    return ret;
}

int main(int argc , char **argv)
{
    if (argc != 2){
        printf("Usage:%s <num>\n" , argv[0]);
        return -1;
    }

    /*printf("num:%s\n" , int_to_str(atoi(argv[1])));*/
    /*printf("num:%u\n" , decstr_to_int(argv[1] , 2));*/

#if 0
    char buf[32] = {0};
    float_to_str(atof(argv[1]) , buf);
    printf("bef num:%s\n" , buf);

    printf("aft num:%.3f\n" , str_to_float(buf));
#endif

    char buf[] ="ueyunzhongkezhongtI";
    const char *ptr = "eyuk";
    /*printf("find:%d\n" , find_substr(buf , ptr));*/
    /*printf("find_last:%d\n" , find_last_substr(buf , ptr));*/
    printf("find count:%d\n" , substr_num(buf , ptr));

    /*char *sub = substr(buf , -1 , 9);*/

    /*printf("sub:%s\n" , sub);*/
    return 0;
}
