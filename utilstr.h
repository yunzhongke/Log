/*================================================================
*   Copyright (C) 2018 Vertiv Tech Co Ltd. All rights reserved.
*   
*   文件名称：utilstr.h
*   创 建 者：yunzhongke
*   创建日期：2018年06月27日09时
*   描    述：
*
================================================================*/


#ifndef _UTILSTR_H
#define _UTILSTR_H

#include <string.h>
#include <math.h>

/**
 *
 * @brief 计算数字的位数
 *
 * @param data 输入的数字位
 *
 * @note 只能计算数字前面没有零的数字,且计算的最大的位数是10
 * @return 结果位数
 */
static int count_int(int data);

/**
 * @brief 将字符串逆转
 *
 * @param input 输入的字符串
 *
 * @return 逆转后的字符串
 */
static char* reversion_str(char *input);

/**
 * @brief 查找字符串中子串所在的位置 
 *
 * @param str 输入的字符串
 * @param sub 子串
 *
 * @return 查找到后返回子串在字符串中开始出现的位置，没找到返回 -1
 */
static int find_substr(char *str , const char *sub);

/** 
 * @brief 查找字符串中子串最后出现的位置
 * 
 * @param str 输入的字符串
 * @param sub 子串
 *
 * @return 查找到后返回子串在字符串中最后出现的位置，没找到返回 -1
 */
static int find_last_substr(char *str , const char *sub);

/** 
 * @brief 查找字符串中子串出现的个数
 * @param str 输入的字符串
 * @param sub 输入的子串
 *
 * @return 找到返回子串出现的个数，否则返回0
 */
static int substr_num(char *str , const char* sub);

static int insert(char *str , const int pos , const char *sub);

/**
 * @brief 返回指定位置且指定字符个数的子串
 *
 * @param str 输入的字符串
 * @param start_pos 开始的位置
 * @param count 截取的字符个数 
 *
 * @return 截取成功返回非空指针，否则返回NULL
 */
static char* substr(char *str , int start_pos , int count);


/** 
 * @brief 将数字转为字符串
 *
 * @param data 输入的数字
 *
 * @return 返回转换后的字符串
 */
static char* int_to_str(int data);

/**
 * @brief 将含有整数的字符串转为整数
 *
 * @param input 输入的字符串
 * @param digit 要转换的字符位数
 *
 * @return 返回转换后的整数 
 */
static unsigned int decstr_to_int(char *input , int digit);

/**
 * @brief 将浮点数转字符串
 *
 * @param data 输入的浮点数 
 * @param out 输出的字符串
 *
 * @return 返回输出字符串的长度 
 */
static int float_to_str(float data , char *out);

/**
 * @brief 将字符串转为浮点数
 *
 * @param data 输入的字符串
 *
 * @return 返回转换后的浮点数
 */
static float str_to_float(char *input);


#endif //UTILSTR_H
