#include "prase_ini.h"

#include <stdio.h>
#include <stdlib.h>

struct ini_info {
    size_t buffer_size;
    unsigned int section_num;
    unsigned int parameter_num;
};

static int 
prase_ini(
    struct ini_info*ini_info,
    const char*filename,int flag_create)
{
    int flag_comments = 0;
    char ch;
    
    struct ini* ini = NULL;
    struct ini_section* section = NULL;
    struct ini_parameter* parameter = NULL;
    char* null_str = NULL;
    char* buffer = NULL;

    if(flag_create){
        ini = (struct ini*)malloc(
                sizeof(struct ini)+
                sizeof(struct ini_section)*ini_info->section_num+
                sizeof(struct ini_parameter)*ini_info->parameter_num+
                ini_info->buffer_size+
                1);
        section = (struct ini_section*)&ini[1];
        parameter = (struct ini_parameter*)&section[ini_info->section_num];
        ini->st = (char*)&parameter[ini_info->parameter_num];
        null_str = ini->st;
        null_str[0] = '\0';
        buffer = null_str + 1;
    }
    ini_info->buffer_size = 0;
    ini_info->parameter_num = 0;
    ini_info->section_num = 0;
    
    FILE* file = fopen(filename,"r");
    if(file==NULL)
        return -1;
    
    enum {
        FLAG_BEGIN,
        FLAG_COMMENT,
        FLAG_MATCH_SEC,
        FLAG_MATCHED,
    };

    int flag = FLAG_BEGIN;

    do {
        ch = fgetc(file);
        if(ch==EOF)
            break;
        else if(ch=='['){
            section->name = buffer;
            section->next = NULL;
            section->parameters = NULL;
            while ((ch=fgetc(file))!=EOF&&ch!='\n'&&ch!=']')
            {
                ini_info->buffer_size++;
                
            }
            if(ch=='\n'||ch==EOF)
                return 
        }
        else if(ch==)
            
        while ((ch=fgetc(file))!=EOF&&ch!='\n')
        {
            
        }
        
    }while(ch!=EOF);
    
    while ((ch=fgetc(file))!=EOF)
    {
        
    }
    

    fclose(file);
    return 0;
} 

struct ini* ini_read(const char* filename)
{
    struct ini_info
}
int prase_write(struct ini* ini,const char* filename);
int prase_free(struct ini* ini)
{
    free(ini);
}