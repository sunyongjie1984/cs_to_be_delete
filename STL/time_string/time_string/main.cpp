#include <iostream>
#include "time.h"
// 时间 时间转换为字符串
#define BUFFER_SIZE 512

int main()
{
    time_t t;
    char tmp[64];
    t = time(0); 
    strftime(tmp, sizeof(tmp), "%Y%m%d\_%H%M%S\_", localtime(&t));

    char buffer[BUFFER_SIZE];
    memset(buffer, 97, BUFFER_SIZE * sizeof(char));
    memcpy(buffer, tmp, 16);
    buffer[406] = '\r';
    buffer[407] = '\n';
}