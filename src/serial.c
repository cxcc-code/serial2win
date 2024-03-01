#include "serial.h"

#include <stdio.h>

HANDLE serial_open(
    int port, // 串口号
    unsigned int baud, // 波特率
    int data_bit, // 数据位
    int check_bit, // 校验位
    int stop_bit // 停止位
)
{
    char port_name[20];
    DCB dcbSerialParams = { 0 };
    COMMTIMEOUTS timeouts = { 0 };
    snprintf(port_name,20,"\\\\.\\COM%d",port);

    HANDLE hSerial = CreateFile(
        port_name,
        GENERIC_READ | GENERIC_WRITE,
        0,//共享模式，独占模式,
        NULL,//指向安全属性的指针,不使用，传NULL
        OPEN_EXISTING,//如何创建,在串口中必须设置为OPEN_EXISTING。表示不能创建新端口只能打开已有的端口
        0,//FILE_ATTRIBUTE_NORMAL,//文件属性,使用默认属性FILE_ATTRIBUTE_NORMAL
        NULL//用于复制文件句柄,通常这个参数设置为NULL，为空表示不使用模板
        );
    if (hSerial == INVALID_HANDLE_VALUE) {
        // printf("Error: Unable to open COM port\n");
        return NULL;
    }

    // 配置串口参数
    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Error: Unable to get serial port state\n");
        CloseHandle(hSerial);
        return NULL;
    }
    dcbSerialParams.BaudRate = baud;
    dcbSerialParams.ByteSize = data_bit;
    dcbSerialParams.Parity = check_bit;
    dcbSerialParams.StopBits = stop_bit;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Error: Unable to set serial port state\n");
        CloseHandle(hSerial);
        return NULL;
    }

    // 设置超时
    timeouts.ReadIntervalTimeout = 5;
    timeouts.ReadTotalTimeoutConstant = 1;
    timeouts.ReadTotalTimeoutMultiplier = 0;
    timeouts.WriteTotalTimeoutConstant = 10;
    timeouts.WriteTotalTimeoutMultiplier = 0;
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        printf("Error: Unable to set serial port timeouts\n");
        CloseHandle(hSerial);
        return NULL;
    }

    return hSerial;
}

void serial_close(HANDLE hSerial) {
    CloseHandle(hSerial);
}

size_t serial_write(HANDLE hSerial,const void* data, size_t dataSize)
{
    DWORD bytesWritten;
    if (!WriteFile(hSerial, data, dataSize, &bytesWritten, NULL)) {
        printf("Error: Unable to write to serial port\n");
        return -1;
    }
    return bytesWritten;
}

size_t serial_read(HANDLE hSerial, void* buffer,size_t bufferSize)
{
    DWORD bytesRead;
    if (!ReadFile(hSerial, buffer, bufferSize, &bytesRead, NULL))
        return 0;
    return bytesRead;
}

void serial_available(UINT32 available[8])
{
    char lpTargetPath[512];
    DWORD test;
    int i = 0;
    char port_name[20];
    for(i=0;i<8;i++)
        available[i] = 0;
    // 枚举所有的设备名称
    for (i = 0; i < 255; i++) {
        snprintf(port_name,20,"COM%d", i);
        test = QueryDosDevice(port_name, lpTargetPath, 512);

        if (test != 0){
            // printf("COM%d\n",i);
            available[i/32] |= (0x01<<(i%32));
        }
    }
}
