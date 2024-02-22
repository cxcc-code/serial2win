#ifndef __PRASE_ARGS_H__
#define __PRASE_ARGS_H__

#include <stdio.h>
/**
 * @brief 结构体用于描述可解析的参数
 * @param bool_max:可识别的bool类型参数的个数
 * @param bool_name:bool类型参数的名字
 * @param bool_name_short:bool类型短参数
 * @param string_max:可识别的string类型参数的个数
 * @param string_name:string类型参数的名字
 * @param string_name_short:string类型短参数
*/
struct prase_handle {
    int bool_max;
    const char** bool_name;
    const char** bool_name_short;
    int string_max;
    const char** string_name;
    const char** string_name_short;
};

/**
 * @brief 判断flag是否使能
 * @param flags:解析输出的flags
 * @param flag:需要判断的flag
 * 
 * @return 若flag存在则为真
*/
#define FLAG_ENABLE(flags,flag) (flags&(0x01<<flag))

/**
 * @brief 解析命令行参数
 * @param handle:参数描述结构体
 * @param argc:待解析的参数个数,即args数组的长度
 * @param args:待解析的参数列表
 * @param bool_flags:[OUT]bool类型参数解析输出
 * @param string_flags:string类型参数解析输出
 * @param err:错误输出(可以为NULL)
*/
int prase_args(
    const struct prase_handle* handle,
    int argc,char*args[],
    unsigned int *bool_flags,
    const char*string_flags[],
    FILE* err
);

#endif //!__PRASE_ARGS_H__