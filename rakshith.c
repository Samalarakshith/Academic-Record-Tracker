#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semester.h"

int g;

int main()
{
    system("COLOR E4");

    printf("\n\n\n\n\t\t\t\t\t* WELCOME ");
    sleep(1);
    printf("TO ");
    sleep(1);
    printf("SEMESTER ");
    sleep(1);
    printf("PORTAL *");

    printf("\n\t\t\t\t\t `` `` `` ````` '");
    sleep(1);

    printf("\n\n\t 1.LOGIN\n\t 2.REGISTER\n\t 3.EXIT OR QUIT\n");
    scanf("%d", &g);

    switch (g)
    {
        case 1:
            login();
            break;
        case 2:
            signin();
            break;
        case 3:
            return 0;
            break;
        default:
            printf("\n option not found...........please enter the valid option........");
    }

    return 0;
}
