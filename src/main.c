#include <stdio.h>
#include <Windows.h>
#include "prase_args.h"
#include "serial.h"
#include "tty_key_map.h"

enum args_bool{
    ARGS_LIST,

    ARGS_BOOL_NUM
};

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
static const char* args_bool_name[] = {
    [ARGS_LIST]="--list",
};
static const char* args_bool_short[] = {
    [ARGS_PORT]="-l",
};

static struct prase_handle main_args = {
    .bool_max = ARGS_BOOL_NUM,
    .bool_name = args_bool_name,
    .bool_name_short = args_bool_short,
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

static HANDLE hCom = NULL;
static HANDLE hConsole = NULL;
static HANDLE hThread_read = NULL;
static DWORD hThread_readId;
static int running = 1;

DWORD WINAPI tty_read(LPVOID lpParam) {
    char buffer[1024];
    size_t size;

    if(hCom==NULL)
        return 0;
    char ch; // 不使用缓冲，每次读取一个字节
    while (1)
    {
        size = serial_read(hCom,buffer,1024);
        if(size==0){
            Sleep(10);// 读取阻塞时无法写入，使用超时的方式，每次休眠的间隙可以进行写入
            // printf("c");
            continue;
        }
        buffer[size] = 0;
        for(size_t i=0;i<size;i++)
            putchar(buffer[i]);
    }
    printf("tty_read end\n");
    return 0;
}

int main(int argc,char*args[])
{
    UINT32 available[8];
    prase_args(&main_args,argc-1,args+1,&bool_flags,args_string,stdout);

    if(FLAG_ENABLE(bool_flags,ARGS_LIST)){
        serial_available(available);
        int count = 0;
        for(int i=0;i<255;i++){
            if(SERIAL_TEST_AVAILABLE(available,i))
                printf("%d:COM%d\n",count++,i);
        }
        return 0;
    }

    int com_num = 0;
    unsigned int baud = 0;
    sscanf(args_string[ARGS_PORT],"COM%d",&com_num);
    sscanf(args_string[ARGS_BAUD],"%u",&baud);

    // 打开串口
    hCom = serial_open(com_num, baud, 8, NOPARITY, ONESTOPBIT);
    if(hCom==NULL){
        printf("serial open faild: COM%d\n",com_num);
        return 0;
    }

    // 创建读串口线程
    hThread_read = CreateThread(
        NULL,                   // 默认安全属性
        0,                      // 默认线程堆栈大小
        tty_read,               // 线程函数
        NULL,                   // 传递给线程函数的参数
        0,                      // 默认创建标志
        &hThread_readId         // 用于接收线程 ID 的变量
    );

    if (hThread_read == NULL) {
        printf("Thread creation failed\n");
        return 0;
    }

    //get console handler
    HANDLE hConsole = GetStdHandle(STD_INPUT_HANDLE);
    //set console mode, enable window and mouse input
    DWORD cNumRead, fdwMode, i;
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT ;
    //get input
    DWORD cc;
    INPUT_RECORD irec;
    KEY_EVENT_RECORD* key;
    MOUSE_EVENT_RECORD* mouse;

    if (!SetConsoleMode(hConsole, fdwMode))
        fprintf(stderr, "%s\n", "SetConsoleMode");
    
    char buffer[4];
    int wchar_flags = 0;
    for ( ; ; )
    {
        ReadConsoleInput(hConsole, &irec, 1, &cc);
        if (irec.EventType != KEY_EVENT)
            continue;

        key = (KEY_EVENT_RECORD*)&irec.Event;
        // 处理中文输入
        if(key->wVirtualKeyCode == 0){ 
            buffer[wchar_flags++] = key->uChar.AsciiChar;
            // printf("key: 0x%02x\tUnicodeChar: %c\tcode: %d\n",key->uChar.AsciiChar,key->uChar.UnicodeChar,key->wVirtualKeyCode);
            if(wchar_flags==2){
                buffer[2]=0;
                buffer[3]=0;
                puts(buffer);
                wchar_flags = 0;
            }
            else if(wchar_flags==4){
                wchar_flags = 0;
            }
        }
        else if (key->bKeyDown)
        {
            int tty_key = -1;
            // TTY 按键识别
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
            if( key->dwControlKeyState&LEFT_CTRL_PRESSED &&
                key->wVirtualKeyCode>='A' &&
                key->wVirtualKeyCode<='Z') {
                
                tty_key = key->wVirtualKeyCode - 'A' + TTY_KEY_CTRL_A;
            }

            // alt + q 退出
            if(key->dwControlKeyState&LEFT_ALT_PRESSED && key->wVirtualKeyCode=='Q')
                break;
            
            if(tty_key!=-1){
                serial_write(hCom,tty_default_map[tty_key].value,tty_default_map[tty_key].len);
                // printf("[DEBUG]:%s\n",tty_key_name[tty_key]);
            }
            else if(key->uChar.AsciiChar>=' '&&key->uChar.AsciiChar<='~'){
                char ch = key->uChar.AsciiChar;
                serial_write(hCom,&ch,1);
            }
            else{
                // printf("key: %c\tcode: 0x%02x\tctrl:%d\n",key->uChar.AsciiChar,key->wVirtualKeyCode,key->dwControlKeyState);
            }
            
        }
    }

    // 关闭串口
    serial_close(hConsole);
    // 终止读取进程
    TerminateThread(hThread_read, 0);
    CloseHandle(hCom);
    CloseHandle(hThread_read);
    return 0;
}
