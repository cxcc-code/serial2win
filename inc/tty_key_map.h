#ifndef __TTY_KEY_MAP_H__
#define __TTY_KEY_MAP_H__

enum tty_key {
    TTY_KEY_TAB,
    TTY_KEY_ENTER,
    TTY_KEY_ESC,
    TTY_KEY_BACKSPACE,

    TTY_KEY_UP,
    TTY_KEY_DOWN,
    TTY_KEY_RIGHT,
    TTY_KEY_LEFT,

    TTY_KEY_HOME,
    TTY_KEY_INSERT,
    TTY_KEY_DELETE,
    TTY_KEY_END,
    TTY_KEY_PAGEUP,
    TTY_KEY_PAGEDOWN,
    TTY_KEY_F1,
    TTY_KEY_F2,
    TTY_KEY_F3,
    TTY_KEY_F4,
    TTY_KEY_F5,
    TTY_KEY_F6,
    TTY_KEY_F7,
    TTY_KEY_F8,
    TTY_KEY_F9,
    TTY_KEY_F10,
    TTY_KEY_F11,
    TTY_KEY_F12,

    TTY_KEY_COUNT
};

struct key_value {
    short len;
    const char* value;
};

extern const char* const tty_key_name[TTY_KEY_COUNT];
extern const struct key_value tty_default_map[TTY_KEY_COUNT];

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

/**
 * 鼠标事件：
 *  鼠标左键
 *  鼠标右键
 *  鼠标中键
 *  鼠标双击
 *  鼠标滚轮
 * 键盘事件：
 *  ASCII输入
 *  中文输入
 *  Fn输入
 *  方向键
 * 
*/

void* get_key_map(const char* filename,struct key_value key_map[TTY_KEY_COUNT]);

#endif //!__TTY_KEY_MAP_H__
