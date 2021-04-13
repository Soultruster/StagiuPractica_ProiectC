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
    char titlu[70];
    char data[12];
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

int meniu(){
     int alegere;
     printf("Selectati ce doriti sa afiseze programul :\n");
     printf("1 : Albumele scoase de un anumit muzician\n2 : Numarul albumelor aparute intr-un anumit an\n3 : Albumele inregistrate pe un anumit format\n4 : Toate datele\n5 : Toate albumele inregistrate (ordine cronologica)\n6 : Instrumentele folosite pentru un album\n");
     scanf("%d",&alegere);
     printf("\n");
     return alegere;
}

void cerinta1(struct muzician muzicieni[],int n,FILE *p){
    printf("Alegeti un muzician :\n");
    int alegere;
    for(int i=1;i<=n;i++){
        printf("%d : %s",i,muzicieni[i].nume);
    }
    scanf("%d",&alegere);
    fprintf(p,"\nAlbume scoase de %s\n",muzicieni[alegere].nume);
    for (int j=1;j<=muzicieni[alegere].numarAlbume;j++)
        fprintf(p," - %s",muzicieni[alegere].albm[j].titlu);
        fprintf(p,"\n");
}

void cerinta2(struct album albume[],int m,FILE *p){
    printf("Alegeti un an:\n");
    char alegere[5];
    int nr=0;
    scanf("%s",alegere);
    printf("\n");
    for (int i=1;i<=m;i++){
        if(alegere[0]==albume[i].data[6] &&alegere[1]==albume[i].data[7] && alegere[2]==albume[i].data[8] && alegere[3]==albume[i].data[9] )
            nr++;
    }
    fprintf(p,"In anul %s au iesit %d albume",alegere,nr);
    fprintf(p,"\n");

}
void cerinta3(struct album albume[],int m,FILE *p){
    printf("Alegeti un format (CD/DVD):\n");
    char alegere[10];
    int nr=0;
    scanf("%s",alegere);
    if(strcmp(alegere,"CD")!=0 && strcmp(alegere,"DVD")!=0){
        printf("Nu ati introdus un format valid");
        return;}
    printf("\n");
    for (int i=1;i<=m;i++){
        if (strncmp(albume[i].format,alegere,2)==0)
            fprintf(p,"-%s",albume[i].titlu),nr++;
    }
    if(nr==0)
        printf("Ne pare rau ,nu exista albume inregistrate pe acest format\n");
}
void cerinta5(struct album albume[],int m,FILE *p){
    int ok=0,sw=0;
    struct album aux;
    do{
            ok=0;
        for(int i=1;i<m;i++){
            sw=0;
            if(albume[i].data[8]>albume[i+1].data[8])
                sw=1;
            else   if(albume[i].data[8]==albume[i+1].data[8] )
                if(albume[i].data[9]>albume[i+1].data[9])
                    sw=1;
                else if(albume[i].data[9]==albume[i+1].data[9])
                    if(albume[i].data[3]>albume[i+1].data[3])
                        sw=1;
                    else if(albume[i].data[3]==albume[i+1].data[3])
                        if(albume[i].data[4]>albume[i+1].data[4])
                            sw=1;
                        else if(albume[i].data[4]==albume[i+1].data[4])
                            if(albume[i].data[0]>albume[i+1].data[0])
                                sw=1;
                            else if(albume[i].data[0]==albume[i+1].data[0])
                                if(albume[i].data[1]>albume[i+1].data[1])
                                    sw=1;
            if(sw==1){
                aux=albume[i];
                albume[i]=albume[i+1];
                albume[i+1]=aux;
                ok=1;
            }
        }
    }while(ok!=0);

    for(int i=1;i<=m;i++)
        fprintf(p,"%s\n",albume[i].titlu);

}
void cerinta6(struct muzician muzicieni[],int n,struct album albume[],int m,FILE *p)
{
    printf("Alegeti un album:\n");
    int al;
    char cod[100];
    for(int i=1;i<=m;i++)
        printf("%d.%s",i,albume[i].titlu);
    scanf("%d",&al);
    strcpy(cod,albume[al].codAlbum);
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=muzicieni[i].numarAlbume;j++)
            if(strncmp(muzicieni[i].albm[j].codAlbum,cod,6)==0)
                for(int k=1;k<=muzicieni[i].numarInstrumente;k++)
                    fprintf(p,"%s",muzicieni[i].instr[k].nume);
    }

}
void afisare_date(struct muzician muzicieni[],int n,FILE *p)
{
    printf("\n\n\n");
    for (int i=1;i<=n;i++){
        fprintf(p,"Muzician %d :\n",i);
        fprintf(p,"CNP : %s",muzicieni[i].CNP);
        fprintf(p,"Adresa :%s",muzicieni[i].adresa);
        fprintf(p,"Numar telefon :%s",muzicieni[i].numarTelefon);
        fprintf(p,"Nume :%s",muzicieni[i].nume);
        fprintf(p,"\nInstrumente folosite de muzician :\n");
        for(int j=1;j<=muzicieni[i].numarInstrumente;j++){
            fprintf(p,"%d.\n",j);
            fprintf(p,"    Numar identificare instrument :%s",muzicieni[i].instr[j].numarIdentificare);
            fprintf(p,"    Nume instrument :%s",muzicieni[i].instr[j].nume);
            fprintf(p,"    Cheie muzicala :%s",muzicieni[i].instr[j].cheieMuzicala);
        }
        fprintf(p,"\n");
        fprintf(p,"\nAlbume scoase de muzician :\n");
        for(int j=1;j<=muzicieni[i].numarAlbume;j++){
            fprintf(p,"%d.\n",j);
            fprintf(p,"-Cod album : %s",muzicieni[i].albm[j].codAlbum);
            fprintf(p,"-Titlu : %s",muzicieni[i].albm[j].titlu);
            fprintf(p,"-Data lansarii : %s",muzicieni[i].albm[j].data);
            fprintf(p,"-Format : %s",muzicieni[i].albm[j].format);
        }
        fprintf(p,"-----------------------------------\n");
    }
}

int main()
{
    FILE *inM,*inA;
    inM= fopen("input_muzicieni.txt","r");  // inM = fisierul cu informatii despre artisti semnati si intrumentele la care canta
    inA= fopen("input_albume.txt","r");  // inA = fisierul cu informatii despre albumele din cadrul firmei de inregistrari

    struct muzician muzicieni[200];
    struct album albume[200];

    int j=0,m=0;  // m = numarul albumelor citite / j = linia care se citeste
    char linie[160];  // in linie se stocheaza toate caracterele de pe linia citita

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

    int a1=meniu();
    FILE * fPointer;
    fPointer=fopen("informatii.txt","w");

    if(a1==1)
        {cerinta1(muzicieni,n,fPointer);
         fclose(fPointer);
        }
    else if(a1==2)
       {cerinta2(albume,m,fPointer);
          fclose(fPointer);
       }
    else if(a1==3)
    {
        cerinta3(albume,m,fPointer);
        fclose(fPointer);
    }
    else if(a1==4)
    {
        afisare_date(muzicieni,n,fPointer);
        fclose(fPointer);
    }
    else if(a1==5)
    {
        cerinta5(albume,m,fPointer);
        fclose(fPointer);
    }
    else if(a1==6)
    {
        cerinta6(muzicieni,n,albume,m,fPointer);
        fclose(fPointer);
    }


    fclose(inA);
    fclose(inM);
    return 0;
}
