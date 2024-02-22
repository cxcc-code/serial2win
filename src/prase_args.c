#include "prase_args.h"

#include <string.h>

#define start_with(str,sub) (strstr(str,sub)==str)

int prase_args(
    const struct prase_handle* handle,
    int argc,char*argv[],
    unsigned int *bool_flags,
    const char*string_flags[],
    FILE* err
)
{
    int i,j;
    int sf_p = 0;

    int error_count = 0;

    *bool_flags = 0;
    for(i=0;i<handle->string_max;i++)
        string_flags[i] = NULL;

    for(i=0;i<argc;i++){
        // 无参数
        if(argv[i][0]!='-'){
            for(;string_flags[sf_p]&&sf_p<handle->string_max;sf_p++);
            if(sf_p==handle->string_max){
                err && fprintf(err,"Too many string parameters:<%s>\n",argv[i]);
                error_count++;
                continue;
            }
            string_flags[sf_p] = argv[i];
            continue;
        }
        // 短选项
        if(argv[i][1]!='-'){
            if(handle->bool_name_short){
                for(j=0;j<handle->bool_max;j++){
                    if(!strcmp(argv[i],handle->bool_name_short[j])){
                        *bool_flags |= 0x01 << j;
                        break;
                    }
                }
                if(j!=handle->bool_max)
                    continue;
            }
            if(handle->string_name_short){
                for(j=0;j<handle->string_max;j++){
                    if(!strcmp(argv[i],handle->string_name_short[j])){
                        string_flags[j] = argv[++i];
                        break;
                    }
                }
                if(j!=handle->string_max)
                    continue;
            }
            err && fprintf(err,"Unrecognized parameters:<%s>\n",argv[i]);
            error_count++;
            continue;
        }
        // 长选项
        if(handle->bool_name){
            for(j=0;j<handle->bool_max;j++){
                if(!strcmp(argv[i],handle->bool_name[j])){
                    *bool_flags |= 0x01 << j;
                    break;
                }
            }
            if(j!=handle->bool_max)
                continue;
        }
        if(handle->string_name){
            for(j=0;j<handle->string_max;j++){
                if(start_with(argv[i],handle->string_name[j])){
                    int sublen = strlen(handle->string_name[j]);
                    if(argv[i][sublen]!='=')
                        continue;
                    string_flags[j] = argv[i] + sublen + 1;
                    break;
                }
            }
            if(j!=handle->string_max)
                continue;
        }
        err && fprintf(err,"Unrecognized parameters:<%s>\n",argv[i]);
        error_count++;
        continue;
    }
}