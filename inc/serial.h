#ifndef __SERIAL_H__
#define __SERIAL_H__

#include <windows.h>

/**
 * @brief 打开串口
 * @param port:串口号
 * @param baud:波特率
 * @param data_bit:数据位长度
 * @param check_bit:校验位长度
 * @param stop_bit:停止位长度
 * 
 * @return 打开失败返回NULL,否则为打开成功
*/
HANDLE serial_open(
    int port,
    unsigned int baud,
    int data_bit,
    int check_bit,
    int stop_bit
);

/**
 * @brief 关闭串口
 * @param hSerial:串口句柄
*/
void serial_close(HANDLE hSerial);

/**
 * @brief 写数据到串口
 * @param hSerial:串口句柄
 * @param data:数据指针
 * @param dataSize:数据的长度
 * 
 * @return 返回实际传输的字节数,异常返回-1
*/
size_t serial_write(HANDLE hSerial,const void* data, size_t dataSize);


/**
 * @brief 从串口读取数据
 * @param hSerial:串口句柄
 * @param buffer:缓冲区指针
 * @param bufferSize:缓冲区大小
 * 
 * @return 返回实际传输的字节数,异常返回0
*/
size_t serial_read(HANDLE hSerial, void* buffer,size_t bufferSize);

/**
 * @brief 获取系统中可用的串口
 * @param available:[OUT]若串口可用,则对应的bit为1
*/
void serial_available(UINT32 available[8]);

#define SERIAL_TEST_AVAILABLE(available,num) (available[num/32]&(0x01<<(num%32)))

#endif //!__SERIAL_H__

