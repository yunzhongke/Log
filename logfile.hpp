/*================================================================
*   Copyright (C) 2018 Vertiv Tech Co Ltd. All rights reserved.
*   
*   文件名称：logfile.hpp
*   创 建 者：yunzhongke
*   创建日期：2018年03月28日22时
*   描    述：
*
================================================================*/

// 参考：http://www.cnblogs.com/alexshi/archive/2012/03/09/2388453.html

#ifndef _LOGFILE_H
#define _LOGFILE_H

#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include "codeconvert.hpp"

#define LINE_MAX (128) //一行字符最长是128字节

FILE *g_fp = NULL;

static void get_time(char *out_buf);
static void create_file();
static void version_information(char *in_buf);
// 判断有没有存在换行符
static void judge_line_break();

static char line_in_buf[LINE_MAX];
static char line_out_buf[LINE_MAX];

static int platform_flag  = 1; //当前系统为win32

#define LOG_OUT(format , args...) \
    do{\
       if(!g_fp) \
         create_file(); \
       get_time(NULL); \
        {fprintf(g_fp , "[%s:%s():%d]: " ,  __FILE__ , __func__ , __LINE__);}\
       if (platform_flag){\
            memset(line_in_buf , 0 , LINE_MAX); \
            sprintf(line_in_buf , format , ##args); \
            write_file(line_in_buf);\
        }\
        else {\
            fprintf(g_fp , format , ##args); \
            judge_line_break(); \
        }\
       fflush(g_fp); \
    }while(0);

void write_file(char *in){
    memset(line_out_buf , 0 , LINE_MAX);
    char ch = fgetc(g_fp);
    if(ch != '\n'){
        strcat(in , (char*)"\r\n");
    }
    if(u2g(in , LINE_MAX , line_out_buf , LINE_MAX)){
        printf("ERROR:[%s][%s][%d]utf-8 to gbk fail!\n" , __FILE__ , __func__ , __LINE__);
        throw;
    }
    fwrite(line_out_buf , 1 , strlen(line_out_buf), g_fp);
}

void get_time(char *out_buf)
{
    time_t nowtime;
    struct tm *gm ;
    struct timeval tm_s;
    nowtime = time(NULL);    
    gm = localtime(&nowtime);
    gettimeofday( &tm_s , NULL);
    if(!out_buf ){
        fprintf(g_fp , "[%d-%d-%d:%d-%d-%d-%ld]:" , gm->tm_year + 1900 , gm->tm_mon + 1 , gm->tm_mday , gm->tm_hour
                , gm->tm_min , gm->tm_sec , tm_s.tv_usec % 10000);
    }
    else if(out_buf )
        sprintf(out_buf , "%d-%d-%d-%d-%d-%d.txt" , gm->tm_year + 1900 , gm->tm_mon + 1 , gm->tm_mday , gm->tm_hour
            , gm->tm_min , gm->tm_sec);
}

void create_file()
{
#ifdef __linux__
    platform_flag = 0;
#elif defined(WIN32)
    platform_flag  = 1;
#endif 

    if(!g_fp){
        char buf[120] = {0};
        get_time(buf);
        int len = strlen(buf);
        buf[len] = 0;
        g_fp = fopen(buf , "wb");
        buf[len -4] = 0;//去除后缀.txt 4个字符
        version_information(buf); 
    }
}

void judge_line_break()
{
    char ch = fgetc(g_fp);
    if(ch != '\n' && ch != '\0'){
            fputc('\n' , g_fp);
    }
}

void version_information(char *in_buf)
{
        sprintf(line_in_buf , "==================================================================\n"
            "*   Copyright (C) 2018 Vertiv Tech Co Ltd. All rights reserved.\n"
            "*\n"
            "*   项目名称：My_Project\n"
            "*   创 建 者：yunzhongke\n"
            "*   项目版本: 1.0\n"
            "*   创建日期：%s\n"
            "*   编译日期：%s\n"
            "*   描    述：\n"
            "*\n"
            "==================================================================\n\n" ,
            in_buf , __DATE__
            );
    if(platform_flag){
        int i = 0, j =0;
        char tmp[LINE_MAX] = {0};
        while(i < (int)strlen(line_in_buf)){
            if(line_in_buf[i] == '\n'){
                memset(tmp , 0 , LINE_MAX);
                memset(line_out_buf , 0 , LINE_MAX);
                strncpy(tmp , line_in_buf + j , i - j);
                strcat(tmp , (char*)"\r\n");
                if(u2g(tmp , LINE_MAX , line_out_buf , LINE_MAX)){
                    printf("ERROR:[%s][%s][%d]utf-8 to gbk fail!\n" , __FILE__ , __func__ , __LINE__);
                    throw;
                }
                fwrite(line_out_buf , 1 , strlen(line_out_buf), g_fp);
                j = i + 1;
            }
            ++i;
        }

    }
    else{
        fwrite(line_in_buf , 1 , strlen(line_in_buf), g_fp);
    }
    fflush(g_fp); 
}

#endif //LOGFILE_H
