#include <stdio.h>
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
    int arrayhodnot[100000];
    int arrayvstupu[1000000];

    int counter=0;

    while (1){

        ;
        char ch;
        int a,b,c;
        scanf(" %c",&ch);



    if (ch == '+') {
        if (scanf("%d", &a) != 1 || a < 0 || a > 99999|| counter+1>1000000){
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
        if(scanf("%d %d", &b, &c) != 2 || b > c || b < 0 || c >= counter ){
            printf("Nespravny vstup.\n");
            
            return 1;
        }

        int delka = c-b+1;
        int serazenyarray[delka];
        for (int j = 0; j < delka; j++){
            serazenyarray[j] = arrayvstupu[b+j];

        }
        prototypsortu(serazenyarray, delka);
        int unikat = 0;
        int celkovy = 0;
        for (int k = 0; k < delka-1; k++) {
            if (serazenyarray[k] == serazenyarray[k+1]){
                celkovy++;
            }
            else {
                celkovy++;
                unikat++;
            }
        }
        if (serazenyarray[delka-1] == serazenyarray[delka-2])celkovy++;
        else {
            celkovy++;
            unikat++;
        }
        printf("> %d / %d\n",unikat,celkovy);

    }
    else {
        printf("Nespravny vstup.\n");
        return 1;
    }
        if (feof(stdin)) {break;}

}
    return 0;
}
