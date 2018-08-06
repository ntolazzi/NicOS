#include "../header/stdlib.h"

int strlen(char* str)
{
    int len =0;
    while(str[len]!='\0') len++;
    return len;
}

void reverse(char* str)
{
    char c;
    int start =0;
    int stop=strlen(str)-1;
    while(start<stop)
    {
        c = str[start];
        str[start] = str[stop];
        str[stop] = c;
        start++;
        stop--;
    }
    return;
}

void itoa(int num, char* buffer)
{
    int i = 0;
    bool isNeg = false;
    if(num<0) isNeg = true;

    /*Handle special case of 0*/
    if(num==0)
    {
        buffer[i] = '0';
        i++;
        buffer[i] = '\0';
        return;
    }

    /*Repeated devision to get digits of number*/
    while(num !=0)
    {
        int reminder = num % 10;
        buffer[i] = reminder + '0';
        i++;
        num = num/10;
    }
    buffer[i] = '\0'; //Add terminating char
    reverse(buffer);
    return;
}
