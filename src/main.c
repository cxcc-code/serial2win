#include <stdio.h>
#include "prase_args.h"

enum args_string{
    ARGS_PORT,
    ARGS_BAUD,

    ARGS_STRING_NUM
};

static const char* args_string_name[] = {
    [ARGS_PORT]="--port",
    [ARGS_BAUD]="--baud"
};
static const char* args_string_short[] = {
    [ARGS_PORT]="-p",
    [ARGS_BAUD]="-b"
};

static struct prase_handle main_args = {
    .bool_max = 0,
    .bool_name = NULL,
    .bool_name_short = NULL,
    .string_max = ARGS_STRING_NUM,
    .string_name = args_string_name,
    .string_name_short = args_string_short
};

static unsigned int bool_flags;
static const char* args_string[ARGS_STRING_NUM];

int main(int argc,char*args[])
{
    prase_args(&main_args,argc-1,args+1,&bool_flags,args_string,stdout);
    if(args_string[ARGS_PORT])
        printf("port:%s\n",args_string[ARGS_PORT]);
    else
        printf("port is not set\n");
    
    if(args_string[ARGS_BAUD])
        printf("baud:%s\n",args_string[ARGS_BAUD]);
    else
        printf("baud is not set\n");
    return 0;
}