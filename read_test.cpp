/*================================================================
 *   Copyright (C) 2018 Vertiv Tech Co Ltd. All rights reserved.
 *   
 *   文件名称：main.cpp
 *   创 建 者：yunzhongke
 *   创建日期：2018年04月14日16时
 *   描    述：读取配置文件demo
 *
 ================================================================*/

#include <iostream>
#include <string>
#include <thread>
#include <fstream>
#include <cstring>
#include <map>
#include <vector>

struct tree
{
    int num;///< 序号
    std::string eng_name; ///< 英文名
    std::string zh_name; ///< 中文名
    bool is_arg; ///< 是否有参数
    int level; ///< 树节点的等级
    int arg_num; ///< 该节点所拥有的子节点个数
    int title_type; ///< 标题的类型
};

// 对应上面的结构体
enum tree_index
{
    NUM = 0, 
    ENG_NAME,
    ZH_NAME,
    IS_ARG,
    LEVEL,
    ARG_NUM,
    TITLE_TYPE
};

/*
 * @brief 处理文件每行的内容
 *
 * @param buf 行的内容 
 * @param sep 分割符
 */
void one_op(char *buf , const char *sep , 
        std::vector<std::vector<std::string>> *tree_node)
{
    tree tmp;
    char *p = strtok(buf , sep);
    std::vector<std::string> vc; 
    std::string tmps;
    int i = 0;
    while(p){
            switch(i){
                case 0:
                    vc.emplace_back(p);
                    ++i;
                    break;
                case 1:
                    vc.emplace_back(p);
                    ++i;
                    break;
                case 2:
                    {
                        // 当前的字符串不等于英文名，且当前的字符串不包含英文名的几个字符，且当前字符串必须于字母开头
                        if (vc[1] != p && strncmp(vc[1].c_str() , p , vc[1].length())  && ((p[0] >= 'a' && p[0] <= 'z') || (p[0] >= 'A' && p[0] <= 'Z'))){
                            tmps += ' ';
                            tmps += p;
                        }
                        else{
                            if (tmps != " ")
                                vc[1] += tmps;
                            vc.emplace_back(p);
                            ++i;
                        }
                    }
                    break;
                default:
                    vc.emplace_back(p);
                    break;
            }
            p = strtok(NULL , sep);
    }
    tree_node->push_back(vc);
#if 0 // 第一种写法
    std::string tmps;
    int i = 0;
    while(p){
            switch(i){
                case 0:
                    tmp.num = atoi(p);
                    ++i;
                    break;
                case 1:
                    tmp.eng_name = p;
                    ++i;
                    break;
                case 2:
                    {
                        // 当前的字符串不等于英文名，且当前的字符串不包含英文名的几个字符，且当前字符串必须于字母开头
                        if (tmp.eng_name != p && strncmp(tmp.eng_name.c_str() , p , tmp.eng_name.length())  && ((p[0] >= 'a' && p[0] <= 'z') || (p[0] >= 'A' && p[0] <= 'Z'))){
                            tmps += ' ';
                            tmps += p;
                        }
                        else{
                            if (tmps != " ")
                                tmp.eng_name += tmps;
                            tmp.zh_name = p;
                            ++i;
                        }
                    }
                    break;
                case 3:
                    tmp.is_arg = atoi(p);        
                    ++i;
                    break;
                case 4:
                    tmp.level = atoi(p);
                    ++i;
                    break;
                case 5:
                    tmp.arg_num = atoi(p);
                    ++i;
                    break;
                case 6:
                    tmp.title_type = atoi(p);
                    break;
                default:
                    fprintf(stdout , "Error: i=%d\n" , i);
                    break;
            }
            p = strtok(NULL , sep);
    }
#endif
    //fprintf(stdout , "num:%d , eng:%s , zh:%s , bool:%d , level:%d , args:%d , titpe:%d \n" , 
            //tmp.num , tmp.eng_name.c_str() , tmp.zh_name.c_str() , tmp.is_arg , tmp.level , tmp.arg_num , tmp.title_type);
}

void there_op(char *buf , const char *sep , 
        std::map<int , std::vector<std::string>> *title)
{
    char *p = strtok(buf , sep);
    std::string tmps;
    int key = 0;
    std::vector<std::string> value;
    std::map<int , std::vector<std::string>> tmp;
    while(p){
        if (p[0] >= '0' && p[0] <= '9'){
            key = atoi(p); 
        }else
            value.emplace_back(p);
        p = strtok(NULL , sep); 
    }
    title->emplace(key , value);
#if 0
    std::cout << "----key:" << key << " ";
    for (auto val : value)
        std::cout << val << " ";
    std::cout << "\n";
    tmp.emplace(key , value);
#endif
}

/*
 * @brief 处理文件每行的内容 
 *
 * @param buf 行的内容
 * @param sep 分割符
 * @param flag 是否有参数处理
 */
void two_op(char *buf , const char *sep , 
        std::vector<std::vector<std::string>> *node_args , bool flag)
{
    char *p = strtok(buf , sep);
    //@note 将文件中提取的字符串不进行进一步的处理，如：转int型或bool型等，这样方便后期的处理
    std::vector<std::string> vc; 
    std::string tmps;
    int i = 0;
    while(p){
        if(!flag){
            switch(i){
                case 0:
                    vc.emplace_back(p);
                    ++i;
                    break;
                case 1:
                    vc.emplace_back(p);
                    ++i;
                    break;
                case 2:
                    {
                        // 当前的字符串不等于英文名，且当前的字符串不包含英文名的几个字符，且当前字符串必须于字母开头
                        if (vc[1] != p && strncmp(vc[1].c_str() , p , vc[1].length())  && ((p[0] >= 'a' && p[0] <= 'z') || (p[0] >= 'A' && p[0] <= 'Z'))){
                            tmps += ' ';
                            tmps += p;
                        }
                        else{
                            if (tmps != " ")
                                vc[1] += tmps;
                            vc.emplace_back(p);
                            ++i;
                        }
                    }
                    break;
                default:
                    vc.emplace_back(p);
                    break;
            }
        }else if(strcmp(p , "THEEND")){
            node_args->back().push_back(p);
            //vc.emplace_back(p);
        }
        p = strtok(NULL , sep);
    }
    if(!flag){
        node_args->push_back(vc);
    }
#if 0
    for (auto val : vc){
        fprintf(stdout , "|%s|" , val.c_str());
    }
    std::cout << "\n";
#endif
}

/*
 * @brief 读取配置文件
 *
 * @param filename 配置文件名
 * @param clock 所花费的时间 
 */
void readfile2(char *filename , int *clock , std::vector<std::vector<std::string>> *tree_node ,
        std::vector<std::vector<std::string>> *node_args , std::map<int , std::vector<std::string>> *title)
{
    std::chrono::system_clock::time_point start = std::chrono::system_clock::now(); //当前系统时间 
    FILE *fp = fopen(filename , "r");
    char buf[512] = {0};
    const char *sep = " \t\r\n";
    bool flag = false;
    while(fgets(buf , 512 , fp)){
        if(strstr(buf , "***"))
            there_op(&buf[3] , sep , title); 
        else if (strstr(buf , "**")){
            two_op(&buf[2] , sep , node_args , false);
            flag = true;
        }
        else if(strchr(buf , '*')){
            one_op(&buf[1] ,  sep  , tree_node);
            flag = false;
        }
        else if(flag){
            two_op(buf , sep , node_args , flag);
        }
    }
    fclose(fp); 
    std::chrono::system_clock::time_point end = std::chrono::system_clock::now();
    *clock = std::chrono::duration_cast<std::chrono::microseconds>((end - start)).count(); // 相差多少微妙
}

int main(int argc , char *argv[])
{

    if (argc != 2 ){
        printf("Usage:%s <filename>\n" , argv[0]);
        return -1;
    }
    int clock= 0;
    std::vector<std::vector<std::string>> tree_node; ///< 树节点，外面的vector表示文本的行，里面的vector表示行的内容
    std::vector<std::vector<std::string>> node_args; ///< 树节点参数，外：文本行，内：行的内容
    std::map<int , std::vector<std::string>> title;   ///< 标题 ：行号，行的内容
    std::thread t(readfile2 , argv[1] , &clock , &tree_node , &node_args , &title);

    t.join();

#if 0 // 打印树的信息
    for (auto tree : tree_node){
        std::cout << "|";
        for (auto conten : tree)
            std::cout << conten << "|";
        std::cout << "\n";
    }
#endif 

#if 0 // 打印树节点参数信息
    for (auto node : node_args){
        std::cout << "||";
        for (auto args : node)
            std::cout << args << "|";
        std::cout << "\n";
    }
#endif 

#if 0 //打印标题的类型
    for (auto t : title){
        std::cout << "|||" << t.first << "|"; 
        for (auto conten : t.second)
            std::cout << conten << "|";
        std::cout << "\n";
    }
#endif 

    int index = 0; ///< 节点参数索引
    for (auto tree : tree_node){
        std::cout << "@-";
        for (auto conten : tree)
            std::cout << conten << "|";
        auto it = node_args.begin();
        if (stoi(tree[IS_ARG])){
            std::advance(it , index); //移动index个元素
        }
        std::cout << "\n";
#if 1
        for (int i = 0; i < stoi(tree[ARG_NUM]); ++i){
            std::cout << "||--";
            for ( auto arg : *it ){
                std::cout << arg << "|"; 
            }
            std::cout << "\n";
            ++it;
            ++index;
        }
#endif
    }


    printf("t:%d \n" ,  clock);
    return 0;
}
