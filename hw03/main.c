#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */
int zmena[] = {4,5,2,3,3,1,5,4,1,2,4,5,2,3,3,1,5,4,1,2,4,5,2,3,3,1,5,4,1,2,4,5,2,3,3,1,5,4,1,2,4,5,2,3,3,1,5,4,1,2,4,5,2,3,3,1,5,4,1,2}; //60 cisel
int den = 292886;
int hodina = 12200;
int minuta = 200;
int rokn = den * 364;
int rokp = den * 365;
int pocetdnivmesici[] = {31,28,31,31,30,31,30,31,31,30,31,30,31};

int february(int y1){
    if((y1 % 4 == 0 && y1 % 100 != 0 ) || y1 % 400 == 0){
        pocetdnivmesici[1] = 29;
        return 1;
    }else{
        pocetdnivmesici[1] = 28;
        return 0;
    }
}

int jeprestupny(int y1){
    if((y1 % 4 == 0 && y1 % 100 != 0 ) || y1 % 400 == 0){
        return 1;
    }else{
        return 0;
    }
}

int mindiffpod60 (int i1, int i2)
{
    int sum = 0;

    for (int i = i1; i < i2; i++){

        sum += minuta;
        sum += zmena[i];
        if (i % 10 == 0 && i != 0) sum += zmena[(i/10)-1];


    }

    return sum;

}

int mindiff60 (int i1, int i2)
{
    int sum = 0;

    for (int i = i1; i <= i2; i++){

        sum += minuta;
        sum += zmena[i];
        if (i % 10 == 0 && i != 0) sum += zmena[(i/10)-1];

        if (i == i2) sum += 3;

    }
    sum += 3;

    return sum;

}


int hoddiff (int h1, int h2)
{
    int sum = 0;

    for (int i = h1; i < h2; i++){


        sum += hodina;
        sum += zmena[i];
        if (i % 10 == 0 && i != 0) sum += zmena[(i/10)-1];
        if (i == 23) sum += 3;

    }

    return sum;

}


int rozdildni (int y1,int m1, int d1,int y2,int m2, int d2){
    int isnegative = 0;
    int densum = 0;
    if ((d2-d1)<0)isnegative = 1;
    while (d1 != d2){
        february(y1);
        d1++;
        densum++;
        if (d1 == pocetdnivmesici[m1-1]) {d1 = 1;densum++;}
    }
    if (isnegative == 1) {isnegative = 0; m1++;}
    if ((m2-m1<0))isnegative = 1;
    while (m1 != m2){
        february(y1);
        densum += pocetdnivmesici[m1-1];
        m1++;
        if (m1 == 12){m1=1;densum += 31;}

    }
    if (isnegative == 1) {isnegative = 0; y1++;}
    while (y1 != y2){
    if (jeprestupny(y1) == 1) densum += rokp;
    else densum += rokn;
    y1++;

    }

    return densum-2;

}





int twotimesenergy (int h1, int i1, int h2, int i2)
{
    int consumtion = 0;
    if (h1 == h2){
        if (i1==i2) return consumtion;
        consumtion += mindiffpod60(i1, i2);
        return consumtion;
    }

    if (i1 == i2){
        consumtion += hoddiff(h1,h2);
        return consumtion;
    }

    consumtion += mindiff60(i1,59);
    consumtion += hoddiff(h1+1,h2);
    consumtion += mindiffpod60(0,i2);

    return consumtion;

}
int energybetweendays (int h1, int i1, int h2, int i2){
    int sum = 0;
    sum += mindiff60(i1,59);
    sum += hoddiff(h1+1,24);
    sum += hoddiff(0,h2);
    sum += mindiffpod60(0,i2);
    return sum+5;


}



int energyConsumption ( int y1, int m1, int d1, int h1, int i1,
                        int y2, int m2, int d2, int h2, int i2, long long int * consumption )
{

    if (y1 > y2 || m1 > 12 || m2 > 12 || d1 > 31 || d2 > 31 || (y1 == y2 && m1 > m2) || (y1 == y2 && m1 == m2 && d1 > d2) || (y1 == y2 && m1 == m2 && d1 == d2 && h1 > h2) || (y1 == y2 && m1 == m2 && d1 == d2 && h1 == h2 && i1 > i2))
        return 0;

    if ((d1 > 28 && jeprestupny(y1) == 0) ||(d2 > 28 && jeprestupny(y2) == 0) )
        return 0;
    int sum = 0;
    if (y1 == y2 && m1 == m2 && d1 == d2)
    {
         sum += twotimesenergy(h1,i1,h2,i2);
        *consumption = sum;

        return 1;
    }
    if (y1 == y2 && m1 == m2 && d1+1 == d2){
        sum += energybetweendays(h1,i1,h2,i2);
        *consumption = sum;
        return 1;

    }
    sum += energybetweendays(h1, i1, h2, i2);
    sum += (rozdildni(y1, m1, d1, y2, m2, d2)*den);
    *consumption = sum;
    return 1;


}


#ifndef __PROGTEST__
int main ( int argc, char * argv [] ) {
    long long int  consumption;


  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  1, 18, 45, &consumption ) == 1
           && consumption == 67116LL );
  assert ( energyConsumption ( 2021, 10,  1, 13, 15,
                               2021, 10,  2, 11, 20, &consumption ) == 1
           && consumption == 269497LL );
  assert ( energyConsumption ( 2021,  1,  1, 13, 15,
                               2021, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
  assert ( energyConsumption ( 2024,  1,  1, 13, 15,
                               2024, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81398919LL );
  assert ( energyConsumption ( 1900,  1,  1, 13, 15,
                               1900, 10,  5, 11, 20, &consumption ) == 1
           && consumption == 81106033LL );
  assert ( energyConsumption ( 2021, 10,  1,  0,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 146443LL );
  assert ( energyConsumption ( 2021, 10,  1,  0, 15,
                               2021, 10,  1,  0, 25, &consumption ) == 1
           && consumption == 2035LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 1
           && consumption == 0LL );
  assert ( energyConsumption ( 2021, 10,  1, 12,  0,
                               2021, 10,  1, 12,  1, &consumption ) == 1
           && consumption == 204LL );
  assert ( energyConsumption ( 2021, 11,  1, 12,  0,
                               2021, 10,  1, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2021, 10, 32, 12,  0,
                               2021, 11, 10, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2100,  2, 29, 12,  0,
                               2100,  2, 29, 12,  0, &consumption ) == 0 );
  assert ( energyConsumption ( 2400,  2, 29, 12,  0,
                               2400,  2, 29, 12,  0, &consumption ) == 1
           && consumption == 0LL );


  return 0;
}
#endif /* __PROGTEST__ */
