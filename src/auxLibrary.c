// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include "include/auxLibrary.h"

// Reverses a string 'str' of length 'len'
void reverse(char* str, int len)
{
    int i = 0, j = len - 1;
    while (i < j) {
        int temp;
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}
  
// Converts a given integer x to string str[]. 
// d is the number of digits required in the output. 
// If d is more than the number of digits in x, 
// then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;
    while (x) {
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }
  
    // If number of digits required is more, then
    // add 0s at the beginning
    while (i < d)
        str[i++] = '0';
  
    reverse(str, i);
    str[i] = '\0';
    return i;
}

static size_t mypow(size_t base, size_t exponent){
    size_t result = 1;
    for(int i = exponent ; i > 0 ; i--){
        result *= base;
    }
    return result;
}

// Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint)
{
    // Extract integer part
    int ipart = (int)n;
  
    // Extract floating part
    float fpart = n - (float)ipart;
    if(fpart < 0){
        res[0] = '-';
        res++;
    }
  
    // convert integer part to string
    if(ipart < 0){
        ipart *= -1;
    }
    int i = intToStr(ipart, res, 1);
    // int i = numToStr(n, res, 10);

    // check for display option after point
    if (afterpoint != 0) {
        int fpartInt;
        res[i] = '.'; // add dot
  
        // Get the value of fraction part upto given no.
        // of points after dot. The third parameter 
        // is needed to handle cases like 233.007
        fpart *= mypow(10, afterpoint);
        if(fpart < 0){
            fpart *= -1;
        }
        fpartInt = fpart;
        // numToStr((int)fpart, res+i+1, 10);

        intToStr(fpartInt, res + i + 1, afterpoint);
    }
}