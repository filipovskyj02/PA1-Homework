#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct ITEM_CLASS {
    int QUANTITY;
    char NAME[100];
};

//Structure comparator function for qsort, inspired by cpp reference and stackoverflow
int COMPARE_QUANTITY(const void* a, const void* b){

    const struct ITEM_CLASS* n1 = (struct ITEM_CLASS *)a;
    const struct ITEM_CLASS* n2 = (struct ITEM_CLASS *)b;
    int STRCOMP;

    if (n1->QUANTITY < n2->QUANTITY) return 1;
    else if (n1->QUANTITY > n2->QUANTITY) return -1;
    STRCOMP = strcmp(n1->NAME, n2->NAME);
    if (STRCOMP < 0) return -1;
    else if (STRCOMP > 0) return +1;

    else return 0;

}
int SAME_QUANTITY (struct ITEM_CLASS ITEM[], int n){

    int i = n;
    int REPEAT = 0;

    while (ITEM[i].QUANTITY == ITEM[i + 1].QUANTITY) {
            REPEAT++;
            i++;

        }

    return REPEAT;


}



int main() {
    int SIZE =5;
    struct ITEM_CLASS *ITEM = (struct ITEM_CLASS*) calloc(SIZE,sizeof(struct ITEM_CLASS));
    int TRACKED_ITEMS;
    char CHARACTER;
    int ITEMS_TOTAL = 0;


    printf("Pocet sledovanych:\n");

    if (scanf(" %d", &TRACKED_ITEMS) != 1 || TRACKED_ITEMS < 1) {
        printf("Nespravny vstup.\n");
        free(ITEM);
        return 1;
    }
    printf("Pozadavky:\n");
    while (~scanf(" %c", &CHARACTER)) {
        int MAX_SOLD = 0;

        if (CHARACTER == '+') {
            char TEMP[100];
            //Using int as a boolean because lazy
            int MATCH = 0;
            scanf("%100s", TEMP);
            //Finding if the array already contains an item with the same name.
            for (int i = 0; i < ITEMS_TOTAL; i++) {

                if (strcmp(ITEM[i].NAME, TEMP) == 0) {
                    ITEM[i].QUANTITY++;
                    MATCH = 1;
                    break;

                }

            }
            if (MATCH == 0) {

                if (ITEMS_TOTAL+1 == SIZE) {
                    SIZE *= 2;
                    ITEM = (struct ITEM_CLASS*) realloc(ITEM, SIZE * sizeof(struct ITEM_CLASS));
                    for (int i = ITEMS_TOTAL+1; i < SIZE; i++){
                        ITEM[i].QUANTITY = 0;
                    }

                }
                strcpy(ITEM[ITEMS_TOTAL].NAME, TEMP);
                ITEM[ITEMS_TOTAL].QUANTITY++;
                ITEMS_TOTAL++;

            }


        } else if (CHARACTER == '?') {
            qsort(ITEM, ITEMS_TOTAL, sizeof(struct ITEM_CLASS), COMPARE_QUANTITY);
            int to = TRACKED_ITEMS;
            if (TRACKED_ITEMS > ITEMS_TOTAL) to = ITEMS_TOTAL;

            for (int i = 0; i < to; i++) {
                MAX_SOLD += ITEM[i].QUANTITY;

                if (i == to - 1) {
                    if (ITEM[i].QUANTITY == ITEM[i + 1].QUANTITY) to++;

                }
            }
            printf("Nejprodavanejsi zbozi: prodano %d kusu\n", MAX_SOLD);

        } else if (CHARACTER == '#') {
            qsort(ITEM, ITEMS_TOTAL, sizeof(struct ITEM_CLASS), COMPARE_QUANTITY);
            int to;
            if (TRACKED_ITEMS > ITEMS_TOTAL) to = ITEMS_TOTAL;
            else to = TRACKED_ITEMS;
            for (int i = 0; i < to; i++) {
                MAX_SOLD += ITEM[i].QUANTITY;
                int REPEAT = SAME_QUANTITY(ITEM, i);

                if (REPEAT == 0) {
                    printf("%d. %s, %dx\n", i + 1, ITEM[i].NAME,ITEM[i].QUANTITY);

                }
                else if (REPEAT != 0){
                    for (int j = 0; j < REPEAT+1; j++){
                        printf("%d.-%d. %s, %dx\n", i + 1, i + 1 + REPEAT, ITEM[i+j].NAME,ITEM[i].QUANTITY);

                    }
                    i += REPEAT;
                    MAX_SOLD += REPEAT*ITEM[i].QUANTITY;
                }


                if (i == to - 1) {
                    if (ITEM[i].QUANTITY == ITEM[i + 1].QUANTITY) to++;

                }


            }
            printf("Nejprodavanejsi zbozi: prodano %d kusu\n", MAX_SOLD);


        }

        else {
            printf("Nespravny vstup.\n");
            free(ITEM);
            return 1;
        }





    }
    free(ITEM);
    return 0;
}
