/**
 * main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include "DList.h"

int main(void)
{
    int choose;
    int data;
    int flag = 1;
    pmyNode pnode;
    pmyNode list = CreateList(0);

    while(flag) {
        printfHowUse();
        scanf("%d", &choose);

        switch(choose) {
            case 1:
                printf("Input the data to insert: ");
                scanf("%d", &data);
                list = InsertNode(list, data);
                break;
            case 2:
                printf("Input the data to delete: ");
                scanf("%d", &data);
                DelectNode(list, data);
                break;
            case 3:
                printf("Input the data to find: ");
                scanf("%d", &data);
                pnode = FindNode(list, data);
                if(NULL != pnode)   printf("Find succeed..!!\n");
                else                printf("Find failed..!!\n");
                break;
            case 4:
                printf("The list's length is %d", GetLenght(list));
                break;
            case 5:
                PrintList(list);
                break;
            case 7:
                ClearList(list);
                break;
            case 8:
                printf("The list's max is %d", GetMaxData(list));
                break;
            case 9:
                printf("The list's sum is %d", GetListSum(list));
                break;
            case 0:
                DelectList(list);
                flag = 0;
                break;
            default:
                printf("Please select 0-7 numbers..!!\n");
                break;
        }
        printf("\n\n\n");
    }

    return 0;
}
