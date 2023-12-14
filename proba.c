#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define LDR "00000"
#define STR "00001"
#define BRZ "00010"
#define BRN "00011"
#define BRC "00100"
#define BRO "00101"
#define BRA "00110"
#define JMP "00111"
#define RET "01000"
#define ADD "01001"
#define SUB "01010"
#define LSR "01011"
#define LSL "01100"
#define RSR "01101"
#define RSL "01110"
#define MUL "01111"
#define DIV "10000"
#define MOD "10001"
#define AND "10010"
#define OR  "10011"
#define XOR "10100"
#define MOV "10101"
#define NOT "10110"
#define INC "10111"
#define DEC "11000"
#define CMP "11001"

//PC pe 10

#define X "00"
#define Y "01"
#define ACC "10"

void nr_corect_de_parametrii(int argc, int x)
{
    if (argc != x)
    {
        perror("Nr de argumente nu este bun!");
        exit(2);
    }
}
void deschidere_fisier_pentru_citire(int *fis, char *nume)
{
    if ((*fis = open(nume, O_RDONLY)) < 0)
    {
        perror("Eroare la deschiderea fisierului pentru citire!");
        exit(7);
    }
}
void deschidere_fisier_pentru_scriere(int *fis, char *nume)
{
    if ((*fis = open(nume, O_WRONLY)) < 0)
    {
        perror("Eroare la deschiderea fisierului pentru scriere!");
        exit(7);
    }
}
char* dec_to_bin(int x, char rezultat[11])
{
    int array[10];
    for(int j=0; j<10; j++)
    {
        array[j]=0;
    }
    int i=9;
    while(x>10 && i>=0)
    {
        array[i]=x%2;
        x=x/2;
        i--;
    }
   
    for(int j=0; j<11; j++)
    {
        printf("%d", array[j]);
    }
    // for (int i=0; i<10; i++)
    // {
    //     rezultat[i]=array[i]+'0';
    // }
    rezultat[11]='\0';
    // for(int j=0; j<11; j++)
    // {
    //     printf("%c", rezultat[j]);
    // }
    return rezultat;
}
char* convertire_eticheta(char matrice[100][100], int indice, char* eticheta, char *rezultat)
{

    for(int i=0; i<indice; i++)
    {
        if(strcmp(matrice[i], eticheta)>0)
        {
            char sir_numar_in_binar[11]="";
            int aux=i;
            while(aux!=0)
            {
                if(aux%2==0)
                {
                    strcat(sir_numar_in_binar, "0");
                }
                else
                {
                    strcat(sir_numar_in_binar, "1");
                }
                aux=aux/2;
            }
            //printf("%s", sir_numar_in_binar);
            for(int j=0; j<strlen(sir_numar_in_binar)-1; j++)
            {
                char help=sir_numar_in_binar[j];
                sir_numar_in_binar[j]=sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j];
                sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j]=help;
            }
            //printf("innver %s\n", sir_numar_in_binar);
            strncat(rezultat, "0000000000", 10-strlen(sir_numar_in_binar));
            strcat(rezultat, sir_numar_in_binar);
            return rezultat;
        }
    }
    return 0;
}

int main(int argc, char *argv[])
{
    int descr_in, descr_out;
    nr_corect_de_parametrii(argc, 3);
    deschidere_fisier_pentru_citire(&descr_in, argv[1]);
    deschidere_fisier_pentru_scriere(&descr_out, argv[2]);

    struct stat var;
    if ((stat(argv[1],  &var)) != 0)
    {
        perror("Eroare la parcurgerea fisierului");
        exit(7);
    }
    char buffer_fisier[var.st_size];
    char buffer_fisier_copie[var.st_size];
    if(read(descr_in, buffer_fisier, var.st_size)<0)
    {
        perror("Nu s-a putut citi tot fisierul!");
        exit(7);
    }
    strcpy(buffer_fisier_copie, buffer_fisier); //aceasta copie o folosim cand avem instr de branch
    char *pointer_pt_linie;
    pointer_pt_linie=strtok(buffer_fisier, "\n");
    char matrice[100][100];
    char matrice_copie[100][100];
    int indice=0;
    while(pointer_pt_linie!=NULL)   ///ne extragem linile
    {
        char hlt[4];
        strncpy(hlt,pointer_pt_linie, 3);
        if(strcasecmp(hlt, "HLT")==0) 
        {
           break;
        }
        strcat(matrice[indice], pointer_pt_linie);
        strcat(matrice_copie[indice], pointer_pt_linie);
        indice++;

        pointer_pt_linie=strtok(NULL, "\n");

    }
    char buffer_linie[17]="";
    for(int i=0; i<indice; i++)
    {
        char *linie=NULL;
        linie=strtok(matrice[i], " ");  //am primul cuv din line =instr
        while (linie != NULL)
        {
            if (strcasecmp(linie, "BRZ") == 0)
            {
                strcat(buffer_linie, BRZ);
                linie = strtok(NULL, " ");
                char rezultat[11];
                strcat(buffer_linie, convertire_eticheta(matrice_copie,indice, linie, rezultat));
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
                strcpy(buffer_linie, "");
                break;
            }
            if (strcasecmp(linie, "BRN") == 0)
            {
                strcat(buffer_linie, BRN);
                linie = strtok(NULL, " ");
                char rezultat[11];
                strcat(buffer_linie, convertire_eticheta(matrice_copie,indice, linie, rezultat));
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
                strcpy(buffer_linie, "");
                break;
            }
            break;
        }
   
    }

    

    close(descr_in);
    close(descr_out);
    
    return 0;
}