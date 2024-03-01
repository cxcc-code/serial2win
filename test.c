#include <stdio.h>
#include <windows.h>

int select_item(HANDLE hConsole,char* list[],int len,int default_item)
{
	int ret = default_item;
	INPUT_RECORD irec;
	DWORD cc;
	KEY_EVENT_RECORD* key;
	int cur = 0;
	int count = 0;
	for(;;){
		// for(int i=0;i<len;i++){
		// 	if(i!=cur)
		// 		printf("%d. %s\n",i,list[i]);
		// 	else
		// 		printf("\033[7m%d. %s\033[27m\n",i,list[i]);
		// }

		ReadConsoleInput(hConsole, &irec, 1, &cc);

        if (irec.EventType != KEY_EVENT)
            continue;
		key = (KEY_EVENT_RECORD*)&irec.Event;
		printf("key:%d\n",key->wVirtualKeyCode);
		if(VK_ESCAPE==key->wVirtualKeyCode)
			break;
		// switch (key->wVirtualKeyCode)
		// {
		// case VK_RETURN:
		// 	if(count<2){
		// 		count++;
		// 		break;
		// 	}
		// 	ret = cur;
		// case VK_ESCAPE:
		// 	goto end_for;
		// case VK_UP:
		// 	printf("VK_UP\n");
		// 	if(cur>0)
		// 		cur--;
		// 	else
		// 		printf("\b");
		// 	break;
		// case VK_DOWN:
		// 	printf("VK_DOWN\n");
		// 	if(cur<(len-1))
		// 		cur++;
		// 	else
		// 		printf("\b");
		// 	break;
		// default:
		// 	break;
		// }
		// printf("\033c");
	}
end_for:

	return ret;
}

int main()
{
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

	char *comlist[] = {
		"COM3",
		"COM5",
		"COM7",
	};
	int s = select_item(hConsole,comlist,3,1);

	printf("Select item : %d\n",s);

	// 关闭串口
    CloseHandle(hConsole);
	return 0;
}