#include <stdio.h>

struct album
{
    int codAlbum;
    char titlu[20];
    char data[10];
    char copyWrite[20];
    char format[20];
};

struct instrument
{
    int numarIdentificare;
    char nume[20];
    char cheieMuzicala[10];
};

struct muzician
{
    long long CNP;
    char adresa[50];
    long numarTelefon;
    struct album albm[10];
    struct instrument instr[10];
};
