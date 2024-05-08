#include <stdio.h>
#include <string.h>

void to_rmb(char *buffer, double money)
{
    char temp[20];
    sprintf(temp, "%.2f", money);

    int temp_len = strlen(temp);

    int buffer_idx = 0;
    int temp_num = temp_len - 4;
    for (int i = 0; i < temp_len; i++)
    {
        
        buffer[buffer_idx++] = temp[i];

        if (temp_num > 0 && temp_num % 3 == 0)
        {
            buffer[buffer_idx++] = ',';
        }
        temp_num--;
    }

    buffer[buffer_idx] = '\0';
}

void to_str(char *buffer, double money)
{
    sprintf(buffer, "%.2f", money);
}