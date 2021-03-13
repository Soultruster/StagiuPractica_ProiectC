#include <stdio.h>
#include <stdlib.h>

struct instrument
{
    char numarIdentificare[20];
    char nume[20];
    char cheieMuzicala[10];
};

struct album
{
    char codAlbum[20];
    char titlu[40];
    char data[10];
    char copyWrite[20];
    char format[20];
};

struct muzician
{
    char CNP[14];
    char nume [50];
    char adresa[50];
    char numarTelefon[10];
    struct album albm[10];
    struct instrument instr[10];
    char voce[3];
    char compozitor[3] ;
    char gen_muuzica[50];
};


int main()
{
    FILE *inM,*inA;
    inM= fopen("input_muzicieni.txt","r");  // inM = fisierul cu informatii despre artisti semnati si intrumentele la care canta
    inA= fopen("input_albume.txt","r");  // inA = fisierul cu informatii despre albumele din cadrul firmei de inregistrari

    struct muzician muzicieni[200];
    struct album albume[200];

    int j=0,m=0;  // m = numarul albumelor citite / j = linia care se citeste
    char linie[60];  // in linie se stocheaza toate caracterele de pe linia citita

    while(fgets(linie,sizeof(linie),inA)){
        j++;
        if (j==1){
            m++;
            strcpy(albume[m].codAlbum,linie);
        }
        else if(j==2){
            strcpy(albume[m].titlu,linie);
        }
        else if(j==3){
            strcpy(albume[m].data,linie);
        }
        else if(j==4){
            strcpy(albume[m].format,linie);
            j=-1;
        }
    }

                   /*for (j=1;j<=m;j++)
                        printf("%s\n%s\n%s\n%s\n",albume[j].codAlbum,albume[j].titlu,albume[j].data,albume[j].format);
                    printf("%s",albume[3].titlu); */

    int i=0,n=0,nr;  // n = numarul muzicienilor cititi / i = linia care se citeste
    //char linie[60];  // in linie se stocheaza toate caracterele de pe linia citita

    while(fgets(linie,sizeof(linie),inM)){
        i++;
        if (i==1){
            n++;
            strcpy(muzicieni[n].CNP,linie);
        }
        else if(i==2){
            strcpy(muzicieni[n].nume,linie);
        }
        else if(i==3){
            strcpy(muzicieni[n].adresa,linie);
        }
        else if(i==4){
            strcpy(muzicieni[n].numarTelefon,linie);
        }
        else if(i==5){
            nr=0;
            for (int k=0;k<strlen(linie);k++){
                if(linie[k]==',')
                    nr++;
            }
        }
        else if(i>5){
            for (int k=1;k<nr;k++){
                strcpy(muzicieni[n].instr[k].numarIdentificare,linie);
                fgets(linie,sizeof(linie),inM);
                strcpy(muzicieni[n].instr[k].nume,linie);
                fgets(linie,sizeof(linie),inM);
                strcpy(muzicieni[n].instr[k].cheieMuzicala,linie);
            }

            fgets(linie,sizeof(linie),inM);  //linia corespunzatoare albumelor


           /* inc=0,sf=0;
            for (int k=0;k<strlen(linie);k++)
                if(k==','){
                    sf
                }
                */


            i=-1;
        }



    }




    fclose(inA);
    fclose(inM);
    return 0;
}
