#include <stdio.h>
int power (int k)
{
    int i = 1;
    for (int m = 0; m < k; m++)
    {
        i *= 10;
    }
    return i;
}

void pocticko (int arr[],int k, int r, int sp)
{
    int rada = power(k);
    int i = 1;
    while (arr[0] < rada)
    {
        sp ++;
        if (i == k) {arr[0]++; i = 1;}
        else i++;
        if (sp == r) {
            arr[1] = i;
            return;
        }
    }
    k++;
    pocticko(arr,k,r,sp);
}
int main() {
    printf("Pozice a soustava:\n");
    int p, xd;
    lol:
    while (scanf("%d %d", &p,&xd) == 2 ) {
        if ( xd != 10 || p < 0) printf("Nespravny vstup.\n");

        if (p == 0) {
            printf("0\n");
            printf("^\n");
            goto lol;


        }
        int k = 1;
        int r = p;
        int sp = 0;

        int arr[2];
        arr[0] = 0;
        arr[1] = 0;
        pocticko(arr, k, r, sp);
        printf("%d\n", arr[0]);
        for (int i = 0; i < arr[1] - 1; i++) printf(" ");
        printf("^\n");
    }
    return 0;
}
