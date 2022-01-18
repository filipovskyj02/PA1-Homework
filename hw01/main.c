#include <stdio.h>
#include <math.h>

int main() {
    printf("Velikost latky:\n");
    double l2, l1, prekryv;
    if (scanf("%lf %lf", &l2, &l1) != 2 || l2 <= 0 || l1 <= 0 ) {
        printf( "Nespravny vstup.\n" );
        return 1;
    }
    double p2, p1;
    printf("Velikost plachty:\n");
    if (scanf("%lf %lf", &p1, &p2)!= 2 || p1 <= 0 || 2 <= 0 ) {
        printf( "Nespravny vstup.\n" );

        return 1;
    }
    if ((l2 >= p1 && l1 >= p2) || (l1 >= p1 && l2 >= p2))
    {printf("Pocet kusu latky: 1\n");return 0;}
    printf("Prekryv:\n");
    if (scanf("%lf", &prekryv) != 1 || prekryv < 0 ) {
        printf( "Nespravny vstup.\n" );
        return 0;
    }
    if (prekryv >= l1 && prekryv >= l2) {printf( "Nelze vyrobit.\n" ); return 0;}


    int a,b;
    if (fmod(p2,l2) != 0){a = floor(p2/l2)+1;}
    else {a = p2/l2;}
    if (fmod(p1,l1) != 0) {b = floor(p1/l1)+1;}
    else {b = p1/l1;}

    int a1,b1;
    if (fmod(p2,l1) != 0) {a1 = floor(p2/l1)+1;}
    else {a1 = p2/l1;}
    if (fmod(p1,l2) != 0) {b1 = floor(p1/l2)+1;}
    else {b1 = p1/l2;}


   while ((((l2 - prekryv) * (a-1)) + l2) < p2-0.00000000001) {a++;}
   while ((((l1 - prekryv) * (b-1)) + l1 )< p1 - 0.00000000001) {b++;}

   while ((((l1 - prekryv) * (a1-1)) + l1 )< p2-0.0000000001) {a1++;}
   while ((((l2 - prekryv) * (b1-1)) + l2 )< p1-0.0000000001) {b1++;}


   int n1 = a*b;
   int m1 = a1*b1;

   int k = (n1 > m1) ? m1:n1;
    printf("Pocet kusu latky: %d\n", k);
    return 0;

    







}
