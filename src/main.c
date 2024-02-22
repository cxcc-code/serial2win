#include <stdio.h>
#include <Windows.h>
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

    //get console handler
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    //set console mode, enable window and mouse input
    DWORD cNumRead, fdwMode, i;
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    //get input
    DWORD cc;
    INPUT_RECORD irec;
    KEY_EVENT_RECORD* key;
    MOUSE_EVENT_RECORD* mouse;

    if (!SetConsoleMode(h, fdwMode))
        fprintf(stderr, "%s\n", "SetConsoleMode");

    for (; ; )
    {
        ReadConsoleInput(h, &irec, 1, &cc);
        //mouse input
        if (irec.EventType == MOUSE_EVENT)
        {
            mouse = (MOUSE_EVENT_RECORD*)&irec.Event;
            switch (mouse->dwButtonState )
            {
            case FROM_LEFT_1ST_BUTTON_PRESSED:
                printf("mouse left click\n");
                printf("   mouse pos:(%d,%d)\n",mouse->dwMousePosition.X,mouse->dwMousePosition.Y);
                break;
            case RIGHTMOST_BUTTON_PRESSED:
                printf("mouse right click\n");
                printf("   mouse pos:(%d,%d)\n",mouse->dwMousePosition.X,mouse->dwMousePosition.Y);
                break;
            case FROM_LEFT_2ND_BUTTON_PRESSED:
                printf("mouse middle click\n");
                printf("   mouse pos:(%d,%d)\n",mouse->dwMousePosition.X,mouse->dwMousePosition.Y);
                break;
            default:
                break;
            }
 
            switch (mouse->dwEventFlags)
            {
            case DOUBLE_CLICK:
                printf("mouse DOUBLE_CLICK\n");
                break;
            case MOUSE_WHEELED:
                printf("mouse MOUSE_WHEELED: %d\n",HIWORD(mouse->dwButtonState));
                break;
            default:
                break;
            }
        }
        else if (irec.EventType == KEY_EVENT)
        {
            key = (KEY_EVENT_RECORD*)&irec.Event;
            if (key->bKeyDown)
            {
                if (key->wVirtualKeyCode == VK_F1)
                {
                    printf("key: F1\n");
                }
                else if(key->wVirtualKeyCode == VK_ESCAPE){
                    printf("key: %d\tcode: %d[ESC]\n",key->uChar.AsciiChar,key->wVirtualKeyCode);
                    break;
                }
                else
                {
                    printf("key: %c\tcode: %d\n",key->uChar.AsciiChar,key->wVirtualKeyCode);
                }
            }
        }
    }
    
    return 0;
}