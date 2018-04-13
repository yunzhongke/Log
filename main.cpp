/*================================================================
*   Copyright (C) 2018 Vertiv Tech Co Ltd. All rights reserved.
*   
*   文件名称：main.cpp
*   创 建 者：yunzhongke
*   创建日期：2018年03月18日16时
*   描    述：
*
================================================================*/

#include <iostream>
#include <unistd.h>
#include "logfile.hpp"

struct Cfg
{
    char name[20];
    int age;
    float height;
    char aihao[214];
};

void fun()
{
    LOG_OUT("helo is my %s\n" , __FILE__);
}

void test(char *args , ...){
    printf("%s\n" , args);
}

int parse_line(char *in , Cfg *out)
{
    LOG_OUT("解析文件行\n");
    int i = 0;
    bool flag = false;
    while(in[i] != '\0' && in[i] != '\n')
    {
        LOG_OUT("1111");
        if(in[i] == ' ')
            in[i] = '\t';
        ++i;
    }
    i = 0;
    int j = 0;
    int last = 0;
    while(in[i] != '\0'){
        if((in[i] ==  '\t' | in[i] == '\n') && in[i -1] != '\t' ){
            char tmp[80] ={0};
            strncpy(tmp , in + last , i - last);
            LOG_OUT("%d:%s" , i , tmp);
            if(j == 0)
                strcpy(out->name , tmp);            
            if(j == 1)
                out->age = atoi(tmp);
            if(j == 2)
                out->height = atof(tmp);
            if(j == 3)
                strcpy(out->aihao , tmp);
            
            last += i - last;
            flag = false;
            j++;
        }
        else if(in[i] != '\t' && !flag){
            last = i;
            flag = true;
        }
        ++i;
    }
    return i;
}



int main(int argc, char *argv[])
{
    int n = 5.5f;
    auto func = [&](int n) {return n < 5;};
    int i = 0;
    while(i < 10){
        LOG_OUT("---main--- %d" , i);
        fun();
        i++;
    }
    

    FILE *fp = fopen("../config.txt" , "r"); 
   char buf[512] = {0};
   i = 0;
   bool flag = false;
   Cfg cfg[2];
   LOG_OUT("buf is size:%d" , (int)sizeof(buf));
   do{
       fgets(buf , 512 , fp);
       if(strchr(buf , '*')){
            flag = true;
            //parse_line(&buf[1], cfg[i]);
            continue;
       }
       parse_line(buf , &cfg[i]);
       memset(buf , 0 , 512);
       i++;
   }while(!feof(fp) && flag && i < 2);
   fclose(fp);

   LOG_OUT("写入cfg!");

   for( i = 0; i < 2; ++i ){
       LOG_OUT("name:%s , age:%d , height:%f , aihao:%s" , 
               cfg[i].name , cfg[i].age , cfg[i].height , cfg[i].aihao);
   }

    fclose(g_fp); 
    return 0;
}
