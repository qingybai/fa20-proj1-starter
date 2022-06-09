#include <stdlib.h>
#include <stdio.h>
typedef struct bag {int** num;} BAG;

BAG * createbag (void)
{
    BAG* b;
    b = malloc (sizeof(BAG));
    b->num = malloc (sizeof (int *)*10);
    for(int i =0;i<10;i++)
    {
        b->num[i]= malloc (sizeof(int)*10);
    }
    free(b->num[0]);
    return b;
}

int main (void)
{
    printf("%3dhello",1);
    BAG * c;
    c = createbag();
    //opens an array of 10*10

    return 0;
}