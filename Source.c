#include <stdio.h>

struct album
{
    char codAlbum;
    char titlu[20];
    char data[10];
    char copyWrite[20];
    char format[20];
};

struct instrument
{
    char numarIdentificare;
    char nume[20];
    char cheieMuzicala[10];
};

struct muzician
{
    long long CNP;
    char nume [50];
    char adresa[50];
    char numarTelefon[10];
    struct album albm[10];
    struct instrument instr[10];
    char voce[3];
    char compozitor[3] ;
    char gen_muuzica[50];
};
