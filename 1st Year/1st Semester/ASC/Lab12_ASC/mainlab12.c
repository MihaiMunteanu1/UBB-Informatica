#include <stdio.h>
#include <string.h>
int convert_to_dec(char str[]);

int main()
{
    char numar[10];
    scanf("%s",numar);
    while (strcmp(numar,"0")!=0)
    {
        int dec_str = convert_to_dec(numar);
        printf("%d ", dec_str);
        //printf("%s ",numar);
        scanf("%s",numar);
    }
    
    return 0;
}