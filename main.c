#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    char CNP[30];
    char nume [50];
    char adresa[50];
    char numarTelefon[20];
    int numarInstrumente;
    struct album albm[20];
    struct instrument instr[10];
    int numarAlbume;
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


    int i=0,n=0,nr;  // n = numarul muzicienilor cititi / i = linia care se citeste
    //char linie[60];  // in linie se stocheaza toate caracterele de pe linia citita
    int ct=0;

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
            muzicieni[n].numarInstrumente=nr+1;
        }
        else if(i>5){


            for (int k=1;k<=nr+1;k++){
                strcpy(muzicieni[n].instr[k].numarIdentificare,linie);
                fgets(linie,sizeof(linie),inM);
                strcpy(muzicieni[n].instr[k].nume,linie);
                fgets(linie,sizeof(linie),inM);
                strcpy(muzicieni[n].instr[k].cheieMuzicala,linie);
                fgets(linie,sizeof(linie),inM);
            }

            //linia corespunzatoare albumelor

            ct=0;
            int nral;
            nral=0;
            while(linie[ct]>='0' && linie[ct]<='9'){
                nral++;
                char codA[10]="",ch;
                while(linie[ct]!=',' && linie[ct]!=NULL){
                    ch=linie[ct];
                    strncat(codA,&ch,1);
                    ct++;
                }
                ct++;
                for(j=1;j<=m;j++)
                    if(strncmp (codA,albume[j].codAlbum,6)==0){
                        muzicieni[n].albm[nral]=albume[j];
                    }

            }
            muzicieni[n].numarAlbume=nral;
            i=-1;
        }

    }
    printf("\n\n\n");
    for (i=1;i<=n;i++){
        printf("Muzician %d :\n",i);
        printf("CNP : %s",muzicieni[i].CNP);
        printf("Adresa :%s",muzicieni[i].adresa);
        printf("Numar telefon :%s",muzicieni[i].numarTelefon);
        printf("Nume :%s",muzicieni[i].nume);
        printf("\nInstrumente folosite de muzician :\n");
        for(j=1;j<=muzicieni[i].numarInstrumente;j++){
            printf("%d.\n",j);
            printf("    Numar identificare instrument :%s",muzicieni[i].instr[j].numarIdentificare);
            printf("    Nume instrument :%s",muzicieni[i].instr[j].nume);
            printf("    Cheie muzicala :%s",muzicieni[i].instr[j].cheieMuzicala);
        }
        printf("\nAlbume scoase de muzician :\n");
        for(j=1;j<=muzicieni[i].numarAlbume;j++){
            printf("%d.\n",j);
            printf("-Cod album : %s",muzicieni[i].albm[j].codAlbum);
            printf("-Titlu : %s",muzicieni[i].albm[j].titlu);
            printf("-Data lansarii : %s",muzicieni[i].albm[j].data);
            printf("-Format : %s",muzicieni[i].albm[j].format);
        }
        printf("-----------------------------------\n");
    }
    fclose(inA);
    fclose(inM);
    return 0;
}

