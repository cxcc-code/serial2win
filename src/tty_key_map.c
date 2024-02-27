#include "tty_key_map.h"

#include <stdlib.h>
#include <stdio.h>

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
};

/*
TAB:09
Enter:0D
ESC:1B
backspace:7F

上:1B 5B 41
下:1B 5B 42
右:1B 5B 43
左:1B 5B 44

home:       1B 5B 31 7E
insert:     1B 5B 32 7E
delete:     1B 5B 33 7E
end:        1B 5B 34 7E
pageup:     1B 5B 35 7E
pagedown:   1B 5B 36 7E

F1:1B 5B 31 31 7E
F2:1B 5B 31 32 7E
F3:1B 5B 31 33 7E
F4:1B 5B 31 34 7E
F5:1B 5B 31 35 7E

F6 :1B 5B 31 37 7E
F7 :1B 5B 31 38 7E
F8 :1B 5B 31 39 7E
F9 :1B 5B 32 30 7E
F10:1B 5B 32 31 7E

F11:1B 5B 32 33 7E
F12:1B 5B 32 34 7E
*/
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
		.value = "\x1B\x5B\x31\x7E"
	},
	[TTY_KEY_INSERT] = {
		.len = 4,
		.value = "\x1B\x5B\x32\x7E"
	},
	[TTY_KEY_DELETE] = {
		.len = 4,
		.value = "\x1B\x5B\x33\x7E"
	},
	[TTY_KEY_END] = {
		.len = 4,
		.value = "\x1B\x5B\x34\x7E"
	},
	[TTY_KEY_PAGEUP] = {
		.len = 4,
		.value = "\x1B\x5B\x35\x7E"
	},
	[TTY_KEY_PAGEDOWN] = {
		.len = 4,
		.value = "\x1B\x5B\x36\x7E"
	},

	[TTY_KEY_F1] = {
		.len = 5,
		.value = "\x1B\x5B\x31\x31\x7E"
	},
	[TTY_KEY_F2] = {
		.len = 5,
		.value = "\x1B\x5B\x31\x32\x7E"
	},
	[TTY_KEY_F3] = {
		.len = 5,
		.value = "\x1B\x5B\x31\x33\x7E"
	},
	[TTY_KEY_F4] = {
		.len = 5,
		.value = "\x1B\x5B\x31\x34\x7E"
	},
	[TTY_KEY_F5] = {
		.len = 5,
		.value = "\x1B\x5B\x31\x35\x7E"
	},
	[TTY_KEY_F6] = {
		.len = 5,
		.value = "\x1B\x5B\x31\x37\x7E"
	},
	[TTY_KEY_F7] = {
		.len = 5,
		.value = "\x1B\x5B\x31\x38\x7E"
	},
	[TTY_KEY_F8] = {
		.len = 5,
		.value = "\x1B\x5B\x31\x39\x7E"
	},
	[TTY_KEY_F9] = {
		.len = 5,
		.value = "\x1B\x5B\x32\x30\x7E"
	},
	[TTY_KEY_F10] = {
		.len = 5,
		.value = "\x1B\x5B\x32\x31\x7E"
	},
	[TTY_KEY_F11] = {
		.len = 5,
		.value = "\x1B\x5B\x32\x33\x7E"
	},
	[TTY_KEY_F12] = {
		.len = 5,
		.value = "\x1B\x5B\x32\x34\x7E"
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

void* get_key_map(const char* filename,struct key_value key_map[TTY_KEY_COUNT])
{
    for(int i=0;i<TTY_KEY_COUNT;i++){
        key_map[i] = tty_default_map[i];
    }
	return NULL;
}