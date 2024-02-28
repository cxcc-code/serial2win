#include "tty_key_map.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

const char* const tty_key_name[TTY_KEY_COUNT] = {
	"TTY_KEY_TAB",
    "TTY_KEY_ENTER",
    "TTY_KEY_ESC",
    "TTY_KEY_BACKSPACE",

    "TTY_KEY_UP",
    "TTY_KEY_DOWN",
    "TTY_KEY_RIGHT",
    "TTY_KEY_LEFT",

    "TTY_KEY_HOME",
    "TTY_KEY_INSERT",
    "TTY_KEY_DELETE",
    "TTY_KEY_END",
    "TTY_KEY_PAGEUP",
    "TTY_KEY_PAGEDOWN",
    "TTY_KEY_F1",
    "TTY_KEY_F2",
    "TTY_KEY_F3",
    "TTY_KEY_F4",
    "TTY_KEY_F5",
    "TTY_KEY_F6",
    "TTY_KEY_F7",
    "TTY_KEY_F8",
    "TTY_KEY_F9",
    "TTY_KEY_F10",
    "TTY_KEY_F11",
    "TTY_KEY_F12",

    "TTY_KEY_CTRL_A",
    "TTY_KEY_CTRL_B",
    "TTY_KEY_CTRL_C",
    "TTY_KEY_CTRL_D",
    "TTY_KEY_CTRL_E",
    "TTY_KEY_CTRL_F",
    "TTY_KEY_CTRL_G",
    "TTY_KEY_CTRL_H",
    "TTY_KEY_CTRL_I",
    "TTY_KEY_CTRL_J",
    "TTY_KEY_CTRL_K",
    "TTY_KEY_CTRL_L",
    "TTY_KEY_CTRL_M",
    "TTY_KEY_CTRL_N",
    "TTY_KEY_CTRL_O",
    "TTY_KEY_CTRL_P",
    "TTY_KEY_CTRL_Q",
    "TTY_KEY_CTRL_R",
    "TTY_KEY_CTRL_S",
    "TTY_KEY_CTRL_T",
    "TTY_KEY_CTRL_U",
    "TTY_KEY_CTRL_V",
    "TTY_KEY_CTRL_W",
    "TTY_KEY_CTRL_X",
    "TTY_KEY_CTRL_Y",
    "TTY_KEY_CTRL_Z",
};

const struct key_value tty_default_map[TTY_KEY_COUNT] = {
    [TTY_KEY_TAB] = {
		.len = 1,
		.value = "\x09"
	},
	[TTY_KEY_ENTER] = {
		.len = 1,
		.value = "\x0D"
	},
	[TTY_KEY_ESC] = {
		.len = 1,
		.value = "\x1B"
	},
	[TTY_KEY_BACKSPACE] = {
		.len = 1,
		.value = "\x7F"
	},

	[TTY_KEY_UP] = {
		.len = 3,
		.value = "\033[A"
	},
	[TTY_KEY_DOWN] = {
		.len = 3,
		.value = "\033[B"
	},
	[TTY_KEY_RIGHT] = {
		.len = 3,
		.value = "\033[C"
	},
	[TTY_KEY_LEFT] = {
		.len = 3,
		.value = "\033[D"
	},

	[TTY_KEY_HOME] = {
		.len = 4,
		.value = "\033[1~"
	},
	[TTY_KEY_INSERT] = {
		.len = 4,
		.value = "\033[2~"
	},
	[TTY_KEY_DELETE] = {
		.len = 4,
		.value = "\033[3~"
	},
	[TTY_KEY_END] = {
		.len = 4,
		.value = "\033[4~"
	},
	[TTY_KEY_PAGEUP] = {
		.len = 4,
		.value = "\033[5~"
	},
	[TTY_KEY_PAGEDOWN] = {
		.len = 4,
		.value = "\033[6~"
	},

	[TTY_KEY_F1] = {
		.len = 5,
		.value = "\033[11~"
	},
	[TTY_KEY_F2] = {
		.len = 5,
		.value = "\033[12~"
	},
	[TTY_KEY_F3] = {
		.len = 5,
		.value = "\033[13~"
	},
	[TTY_KEY_F4] = {
		.len = 5,
		.value = "\033[14~"
	},
	[TTY_KEY_F5] = {
		.len = 5,
		.value = "\033[15~"
	},
	[TTY_KEY_F6] = {
		.len = 5,
		.value = "\033[17~"
	},
	[TTY_KEY_F7] = {
		.len = 5,
		.value = "\033[18~"
	},
	[TTY_KEY_F8] = {
		.len = 5,
		.value = "\033[19~"
	},
	[TTY_KEY_F9] = {
		.len = 5,
		.value = "\033[20~"
	},
	[TTY_KEY_F10] = {
		.len = 5,
		.value = "\033[21~"
	},
	[TTY_KEY_F11] = {
		.len = 5,
		.value = "\033[23~"
	},
	[TTY_KEY_F12] = {
		.len = 5,
		.value = "\033[24~"
	},

	[TTY_KEY_CTRL_A] = {
		.len = 1,
		.value = "\x01"
	},
    [TTY_KEY_CTRL_B] = {
		.len = 1,
		.value = "\x02"
	},
    [TTY_KEY_CTRL_C] = {
		.len = 1,
		.value = "\x03"
	},
    [TTY_KEY_CTRL_D] = {
		.len = 1,
		.value = "\x04"
	},
    [TTY_KEY_CTRL_E] = {
		.len = 1,
		.value = "\x05"
	},
    [TTY_KEY_CTRL_F] = {
		.len = 1,
		.value = "\x06"
	},
    [TTY_KEY_CTRL_G] = {
		.len = 1,
		.value = "\x07"
	},
    [TTY_KEY_CTRL_H] = {
		.len = 1,
		.value = "\x08"
	},
    [TTY_KEY_CTRL_I] = {
		.len = 1,
		.value = "\x09"
	},
    [TTY_KEY_CTRL_J] = {
		.len = 1,
		.value = "\x0A"
	},
    [TTY_KEY_CTRL_K] = {
		.len = 1,
		.value = "\x0B"
	},
    [TTY_KEY_CTRL_L] = {
		.len = 1,
		.value = "\x0C"
	},
    [TTY_KEY_CTRL_M] = {
		.len = 1,
		.value = "\x0D"
	},
    [TTY_KEY_CTRL_N] = {
		.len = 1,
		.value = "\x0E"
	},
    [TTY_KEY_CTRL_O] = {
		.len = 1,
		.value = "\x0F"
	},
    [TTY_KEY_CTRL_P] = {
		.len = 1,
		.value = "\x10"
	},
    [TTY_KEY_CTRL_Q] = {
		.len = 1,
		.value = "\x11"
	},
    [TTY_KEY_CTRL_R] = {
		.len = 1,
		.value = "\x12"
	},
    [TTY_KEY_CTRL_S] = {
		.len = 1,
		.value = "\x13"
	},
    [TTY_KEY_CTRL_T] = {
		.len = 1,
		.value = "\x14"
	},
    [TTY_KEY_CTRL_U] = {
		.len = 1,
		.value = "\x15"
	},
    [TTY_KEY_CTRL_V] = {
		.len = 1,
		.value = "\x16"
	},
    [TTY_KEY_CTRL_W] = {
		.len = 1,
		.value = "\x17"
	},
    [TTY_KEY_CTRL_X] = {
		.len = 1,
		.value = "\x18"
	},
    [TTY_KEY_CTRL_Y] = {
		.len = 1,
		.value = "\x19"
	},
    [TTY_KEY_CTRL_Z] = {
		.len = 1,
		.value = "\x1A"
	},
};

// size_t prase_ini(const char* filename,void* buffer)
// {
//     size_t size = 0;
//     const char section[]="[key_map]";
//     char ch;
//     FILE* file = fopen(filename,"r");
//     if(file==NULL)
//         return 0;

//     enum {
//         FLAG_BEGIN,
//         FLAG_MATCH_SEC,
//         FLAG_MATCHED,
//     };
    
//     int flag = FLAG_BEGIN;
//     int sec_match_count = 0;

    
//     while ((ch=fgetc(file))!=EOF)
//     {
//         switch (flag)
//         {
//         case FLAG_BEGIN:
//             if(ch==section[0]){
//                 flag = FLAG_MATCH_SEC;
//                 sec_match_count = 1;
//             }
//             continue;
//         case FLAG_MATCH_SEC:
//             if(ch==section[sec_match_count]){
//                 sec_match_count++;
//                 if(sec_match_count==sizeof(section)){
//                     flag = FLAG_MATCHED;
//                 }
//             }
//             else
//                 flag = FLAG_BEGIN;
//             continue;
//         default:
//             break;
//         }

//     }
    

//     flcose(file);
//     return size;
// }

#define start_with(str,prefix)  (strstr(str,prefix)==str)

int key_map_read(const char* filename,struct key_value key_map[TTY_KEY_COUNT])
{
    char buffer[1024];
	int len;
	struct key_value* cur = NULL;
	int end_flag = 0;

	for(int i=0;i<TTY_KEY_COUNT;i++)
		key_map[i] = tty_default_map[i];
	
	if(filename==NULL)
		return 0;
	FILE* fp = fopen(filename,"r");
	if(fp==NULL)
		return 0;
	do
	{
		cur = NULL;

		for (len=0;(buffer[len]=fgetc(fp))!=EOF&&buffer[len]!='='&&buffer[len]!='\n';len++);
		if(buffer[len]==EOF)
			break;
		else if(buffer[len]=='\n')
			continue;
		
		buffer[len] = '\0';
		if(!start_with(buffer,"TTY_KEY_"))
			continue;
		
		for(int i=0;i<TTY_KEY_COUNT;i++){
			if(strcmp(buffer+9,tty_key_name[i]+9))
				continue;
			cur = &key_map[i];
			break;
		}

		if(cur == NULL)
			continue;
		
		for (len=0;(buffer[len]=fgetc(fp))!=EOF&&buffer[len]!='\n';len++){
			if(buffer[len]!='\\')
				continue;
			
		}
		if(buffer[len]==EOF)
			end_flag = 1;
		
		cur->len = len;
		cur->value = (char*)malloc(len);
		memcpy((char*)cur->value,buffer,len);

	}while(!end_flag);
	
	fclose(fp);

	return 0;
}

int key_map_free(struct key_value key_map[TTY_KEY_COUNT])
{
	for(int i=0;i<TTY_KEY_COUNT;i++)
		if(key_map[i].value!=tty_default_map[i].value)
			free((char*)tty_default_map[i].value);
}