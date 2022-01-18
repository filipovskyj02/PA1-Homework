#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct TEmployee
{
    struct TEmployee         * m_Next;
    struct TEmployee         * m_Bak;
    char                     * m_Name;
} TEMPLOYEE;

#endif /* __PROGTEST__ */

TEMPLOYEE        * newEmployee  ( const char      * name,
                                  TEMPLOYEE       * next )
{

    TEMPLOYEE * Novy = NULL;
    Novy = (TEMPLOYEE*)calloc(1,sizeof (TEMPLOYEE));
    Novy->m_Name = (char *)malloc(sizeof (char ) * strlen(name)+1);
    strcpy(Novy->m_Name,name);
    Novy->m_Next = next;
    return Novy;
}
TEMPLOYEE        * cloneList    ( TEMPLOYEE       * src )
{
    TEMPLOYEE * HashMap[2][100];
    TEMPLOYEE * Head = NULL;
    TEMPLOYEE * Previous = NULL;
    //Counter to store the head
    int Counter = 0;
    while (src != NULL){
        TEMPLOYEE * Novy = (TEMPLOYEE*)malloc(sizeof (TEMPLOYEE));
        HashMap[0][Counter] = src;
        HashMap[1][Counter] = Novy;
        //Storing head
        if (Counter == 0) Head = Novy;
        //Links previous.next to current if current isnt the first
        if (Counter != 0) {
            Previous->m_Next = Novy;
        }
        Previous = Novy;
        Counter++;


        //Copying each element

        Novy->m_Name = (char *)malloc(sizeof (char ) * strlen(src->m_Name)+1);
        strcpy(Novy->m_Name,src->m_Name);



        //End of the list
        if (src->m_Next == NULL) {
            Novy->m_Next = NULL;
            src = src->m_Next;

        }
            //Normal pass of the list
        else {
            src = src->m_Next;
        }

    }
    //Second pass
    Counter = 0;
    src = HashMap[0][0];
    while (src != NULL){
        if (src->m_Bak == NULL){
            HashMap[1][Counter]->m_Bak = NULL;
        }
        else if (src->m_Bak == src){
            HashMap[1][Counter]->m_Bak = HashMap[1][Counter];
        }
        else {
            TEMPLOYEE * Temp = src->m_Bak;
            int i = 0;
            while (HashMap[0][i] != Temp){
                i++;
            }
            HashMap[1][Counter]->m_Bak = HashMap[1][i];


        }
        src= src->m_Next;
        Counter++;

    }
    return Head;
}
void               freeList     ( TEMPLOYEE       * src ) {
    TEMPLOYEE *Temp;
    while (src != NULL) {
        Temp = src;
        src = src->m_Next;
        free(Temp->m_Name);
        free(Temp);
    }
}
#ifndef __PROGTEST__
    int                main         ( int               argc,
                                      char            * argv [] )
    {
        TEMPLOYEE * a, *b;
        char tmp[100];

        assert ( sizeof ( TEMPLOYEE ) == 3 * sizeof ( void * ) );
        a = NULL;
        a = newEmployee ( "Peter", a );
        a = newEmployee ( "John", a );
        a = newEmployee ( "Joe", a );
        a = newEmployee ( "Maria", a );
        a -> m_Bak = a -> m_Next;
        a -> m_Next -> m_Next -> m_Bak = a -> m_Next -> m_Next -> m_Next;
        a -> m_Next -> m_Next -> m_Next -> m_Bak = a -> m_Next;
        assert ( a
                 && ! strcmp ( a -> m_Name, "Maria" )
                 && a -> m_Bak == a -> m_Next );
        assert ( a -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
                 && a -> m_Next -> m_Bak == NULL );
        assert ( a -> m_Next -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
                 && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
        assert ( a -> m_Next -> m_Next -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
                 && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next );
        assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
        b = cloneList ( a );
        strncpy ( tmp, "Moe", sizeof ( tmp ) );
        a = newEmployee ( tmp, a );
        strncpy ( tmp, "Victoria", sizeof ( tmp ) );
        a = newEmployee ( tmp, a );
        strncpy ( tmp, "Peter", sizeof ( tmp ) );
        a = newEmployee ( tmp, a );
        b -> m_Next -> m_Next -> m_Next -> m_Bak = b -> m_Next -> m_Next;
        assert ( a
                 && ! strcmp ( a -> m_Name, "Peter" )
                 && a -> m_Bak == NULL );
        assert ( a -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Name, "Victoria" )
                 && a -> m_Next -> m_Bak == NULL );
        assert ( a -> m_Next -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "Moe" )
                 && a -> m_Next -> m_Next -> m_Bak == NULL );
        assert ( a -> m_Next -> m_Next -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Maria" )
                 && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
        assert ( a -> m_Next -> m_Next -> m_Next -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Joe" )
                 && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == NULL );
        assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "John" )
                 && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next );
        assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
                 && a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next -> m_Next );
        assert ( a -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
        assert ( b
                 && ! strcmp ( b -> m_Name, "Maria" )
                 && b -> m_Bak == b -> m_Next );
        assert ( b -> m_Next
                 && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
                 && b -> m_Next -> m_Bak == NULL );
        assert ( b -> m_Next -> m_Next
                 && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
                 && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
        assert ( b -> m_Next -> m_Next -> m_Next
                 && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
                 && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
        assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
        freeList ( a );
        b -> m_Next -> m_Bak = b -> m_Next;
        a = cloneList ( b );
        assert ( a
                 && ! strcmp ( a -> m_Name, "Maria" )
                 && a -> m_Bak == a -> m_Next );
        assert ( a -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Name, "Joe" )
                 && a -> m_Next -> m_Bak == a -> m_Next );
        assert ( a -> m_Next -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Next -> m_Name, "John" )
                 && a -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next -> m_Next );
        assert ( a -> m_Next -> m_Next -> m_Next
                 && ! strcmp ( a -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
                 && a -> m_Next -> m_Next -> m_Next -> m_Bak == a -> m_Next -> m_Next );
        assert ( a -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
        assert ( b
                 && ! strcmp ( b -> m_Name, "Maria" )
                 && b -> m_Bak == b -> m_Next );
        assert ( b -> m_Next
                 && ! strcmp ( b -> m_Next -> m_Name, "Joe" )
                 && b -> m_Next -> m_Bak == b -> m_Next );
        assert ( b -> m_Next -> m_Next
                 && ! strcmp ( b -> m_Next -> m_Next -> m_Name, "John" )
                 && b -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next -> m_Next );
        assert ( b -> m_Next -> m_Next -> m_Next
                 && ! strcmp ( b -> m_Next -> m_Next -> m_Next -> m_Name, "Peter" )
                 && b -> m_Next -> m_Next -> m_Next -> m_Bak == b -> m_Next -> m_Next );
        assert ( b -> m_Next -> m_Next -> m_Next -> m_Next == NULL );
        freeList ( b );
        freeList ( a );
        return 0;
    }
#endif /* __PROGTEST__ */
