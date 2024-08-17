#include <unistd.h>
#include <stdio.h>
#include <errno.h>

#define NORD_TEXTURE 0b00000001
#define SOUTH_TEXTURE 0b00000010
#define ID_COMPLETE   0b00000011


int main(void)
{
    int c = 0b10000001;
    int i = 0b00000001;
    
    if ((c ^ i) == 0)
        printf("1");
    else
        printf("0");
    return (0);
}