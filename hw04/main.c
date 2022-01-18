#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MAX_VALUE 1000000



int arrayhodnot[200000];
int arrayvstupu[MAX_VALUE];
int array[MAX_VALUE];

//Zdroj: cpp reference na zaklade discordu
int compare_ints(const void* a, const void* b)
{
    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2) return -1;
    if (arg1 > arg2) return 1;
    return 0;


}





//Zefektivnit sorting algo
void prototypsortu (int serazenyarray[], int delka){
    int temp = 0;
    for (int i = 0; i < delka-1; i++) {
        for (int j = 0; j < delka-i-1; j++) {
            if (serazenyarray[j] > serazenyarray[j+1]) {

                temp = serazenyarray[j];
                serazenyarray[j]  = serazenyarray[j+1];
                serazenyarray[j+1] = temp;
            }
        }
    }


}
int main() {
    printf("Pozadavky:\n");

    int counter=0;
    char ch;
    while(~scanf(" %c",&ch)){



        int a,b,c;




    if (ch == '+') {
        if (scanf(" %d", &a) != 1 || a < 0 || a > 99999|| counter+1>1000000){
            printf("Nespravny vstup.\n");
            return 1;
        }
        arrayhodnot[a]++;
        arrayvstupu[counter] = a;
        counter++;
        if (arrayhodnot[a] == 1)printf("> prvni navsteva\n");
        else printf("> navsteva #%d\n",arrayhodnot[a]);

    }
    else if (ch == '?'){
        if(scanf(" %d %d", &b, &c) != 2 || b > c || b < 0 || c >= counter ){
            printf("Nespravny vstup.\n");


            return 1;
        }
    if (b == 0 && c == 0){
        printf("> 0 / 0 \n");

    }

        int delka = c-b+1;

        for (int j = 0; j < delka; j++){
            array[j] = arrayvstupu[b+j];

        }
        qsort(array, delka, sizeof(int), compare_ints);


        //prototypsortu(serazenyarray, delka);
        int unikat = 1;
        int celkovy = 1;
        for (int k = 0; k < delka-1; k++) {
            if (array[k] == array[k+1])celkovy++;
            else {celkovy++;unikat++;}
        }
        printf("> %d / %d\n",unikat,celkovy);

    }

    else {
        printf("Nespravny vstup.\n");


        return 1;

    }


}
    return 0;
}
