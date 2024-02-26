#include <stdio.h>
#include <Windows.h>
#include "prase_args.h"
#include "serial.h"
#include "tty_key_map.h"

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

void send_hello_world(HANDLE hSerial) {
    const char* message = "Hello, World!";
    while (1) {
        serial_write(hSerial, message, strlen(message));
        printf("Sent: %s\n", message);
        Sleep(1000); // 每隔1秒发送一次
    }
}

int utf8_to_gb2312(const char* utf8_string, char* gb2312_string, int gb2312_string_size) {
    // 将UTF-8编码的字符串转换为宽字符
    int wchar_count = MultiByteToWideChar(CP_UTF8, 0, utf8_string, -1, NULL, 0);
    if (wchar_count == 0) {
        printf("Error: Failed to get wchar count\n");
        return -1;
    }

    wchar_t* wide_string = malloc(sizeof(wchar_t)*wchar_count);
    MultiByteToWideChar(CP_UTF8, 0, utf8_string, -1, wide_string, wchar_count);

    // 将宽字符转换为GB2312编码的字符串
    int gb2312_length = WideCharToMultiByte(CP_ACP, 0, wide_string, -1, NULL, 0, NULL, NULL);
    if (gb2312_length == 0) {
        printf("Error: Failed to get GB2312 string length\n");
        free(wide_string);
        return -1;
    }

    if (gb2312_string_size < gb2312_length) {
        printf("Error: Output buffer is too small\n");
        free(wide_string);
        return -1;
    }

    WideCharToMultiByte(CP_ACP, 0, wide_string, -1, gb2312_string, gb2312_length, NULL, NULL);
    free(wide_string);

    return gb2312_length - 1; // 返回转换后的字符串长度，不包括末尾的NULL字符
}

int main(int argc,char*args[])
{
    prase_args(&main_args,argc-1,args+1,&bool_flags,args_string,stdout);

    //get console handler
    HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
    //set console mode, enable window and mouse input
    DWORD cNumRead, fdwMode, i;
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT ;
    //get input
    DWORD cc;
    INPUT_RECORD irec;
    KEY_EVENT_RECORD* key;
    MOUSE_EVENT_RECORD* mouse;

    int flag = 0;
    char buffer[5] = {0,0,0,0,0};

    if (!SetConsoleMode(h, fdwMode))
        fprintf(stderr, "%s\n", "SetConsoleMode");
    char buf[1024];
    for (; ; )
    {
        ReadConsoleInput(h, &irec, 1, &cc);
        if (irec.EventType == KEY_EVENT)
        {
            key = (KEY_EVENT_RECORD*)&irec.Event;
            if(key->wVirtualKeyCode==0){
                
                buffer[flag++]=key->uChar.AsciiChar;
                // printf("falg:%d\tkey: 0x%02x\tcode: %d[ESC]\n",flag,key->uChar.AsciiChar,key->wVirtualKeyCode);
                if(flag==3){
                    buffer[2]=0;
                    puts(buffer);
                }
                else if(flag==4){
                    flag = 0;
                }
            }
            else if (key->bKeyDown)
            {
                int tty_key = -1;
                switch (key->wVirtualKeyCode)
                {
                case VK_TAB:tty_key=TTY_KEY_TAB;break;
                case VK_RETURN:tty_key=TTY_KEY_ENTER;break;
                case VK_ESCAPE:tty_key=TTY_KEY_ESC;break;
                case VK_BACK:tty_key=TTY_KEY_BACKSPACE;break;
                
                case VK_LEFT:tty_key=TTY_KEY_LEFT;break;
                case VK_UP:tty_key=TTY_KEY_UP;break;
                case VK_RIGHT:tty_key=TTY_KEY_RIGHT;break;
                case VK_DOWN:tty_key=TTY_KEY_DOWN;break;
                
                case VK_PRIOR:tty_key=TTY_KEY_PAGEUP;break;
                case VK_NEXT:tty_key=TTY_KEY_PAGEDOWN;break;
                case VK_END:tty_key=TTY_KEY_END;break;
                case VK_HOME:tty_key=TTY_KEY_HOME;break;
                case VK_INSERT:tty_key=TTY_KEY_INSERT;break;
                case VK_DELETE:tty_key=TTY_KEY_DELETE;break;
                default:
                    break;
                }
                if(key->wVirtualKeyCode>=VK_F1&&key->wVirtualKeyCode<=VK_F12)
                    tty_key = TTY_KEY_F1 + (key->wVirtualKeyCode - VK_F1);
                if(tty_key!=-1)
                    printf("tty key:%s\n",tty_key_name[tty_key]);
                else
                    printf("key: %c\tcode: 0x%02x\n",key->uChar.AsciiChar,key->wVirtualKeyCode);
                flag = 0;
                if(tty_key==TTY_KEY_ESC)
                    break;
            }
            else
                flag = 0;
        }
    }
    // char buffer_read[1024];
    // size_t size;
    // // 打开串口
    // HANDLE hSerial = serial_open(5, 115200, 8, NOPARITY, ONESTOPBIT);
    // if (hSerial != NULL) {
    //     // 调用函数发送 "Hello, World!"
    //     // send_hello_world(hSerial);
    //     while (1)
    //     {
    //         size = serial_read(hSerial,buffer_read,1024);
    //         buffer_read[size] = 0;
    //         char gb2312_buffer[1024];
    //         utf8_to_gb2312(buffer_read,gb2312_buffer,1024);
    //         if(!strcmp(gb2312_buffer,"exit"))
    //             break;
    //         for(size_t i=0;i<size;i++){
    //             putchar(gb2312_buffer[i]);
    //             if(gb2312_buffer[i]=='\r')
    //                 putchar('\n');
    //         }
    //         // printf("%s",buffer_read);
    //     }
        

    //     // 关闭串口
    //     serial_close(hSerial);
    // }


    
    return 0;
}