#include <time.h>
#include <string.h>
#include "timeutil.h"
#include "stringformatutil.h"

void initLastYears(char strArray[][MAX_YEAR_STR_LENGTH], int yearRange)
{
    time_t current_time;
    struct tm *current_tm;

    current_time = time(NULL);
    current_tm = localtime(&current_time);
    int year = current_tm->tm_year;

    char buf[MAX_YEAR_STR_LENGTH];
    for (int i = 0; i < yearRange; i++)
    {
        to_str_int(buf, 1900 + year - i);
        strncpy(strArray[i], buf, MAX_YEAR_STR_LENGTH - 1);
        strArray[i][MAX_YEAR_STR_LENGTH - 1] = '\0';
    }
}

void initMonths(char strArray[][MAX_MONTH_STR_LENGTH])
{
    char buf[MAX_MONTH_STR_LENGTH];
    for (int i = 0; i < MAX_MONTH_LENGTH; i++)
    {
        to_str_int(buf, i + 1);
        strncpy(strArray[i], buf, MAX_MONTH_STR_LENGTH - 1);
        strArray[i][MAX_MONTH_STR_LENGTH - 1] = '\0';
    }
}