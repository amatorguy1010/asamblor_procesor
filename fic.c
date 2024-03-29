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

//verificare param (prea multi, prea putini, corectitudinea de tip)
//cmp prima val pe 5 biti, nu 0 concatenat cu 4 => done

#define X "00"
#define Y "01"
#define ACC "10"

#define X8 "00000000"
#define Y8 "00000001"
#define ACC8 "00000010"

#define X4 "0000"
#define Y4 "0001"
#define ACC4 "0010"

#define X6 "000000"
#define Y6 "000001"
#define ACC6 "000010"

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
char* conversie_val_imm_pe_8_biti(int nr, char* val_imm)
{
    char sir_numar_in_binar[9]="";
            int aux=nr;
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
            //printf("neinversat %s\n", sir_numar_in_binar);
            for(int j=0; j<strlen(sir_numar_in_binar)/2; j++)
            {
                char help=sir_numar_in_binar[j];
                sir_numar_in_binar[j]=sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j];
                sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j]=help;
            }
            //printf("innver %s\n", sir_numar_in_binar);
            strncat(val_imm, "00000000", 8-strlen(sir_numar_in_binar));
            strcat(val_imm, sir_numar_in_binar);
            return val_imm;
}
char* conversie_val_imm_pe_6_biti(int nr, char* val_imm)
{
    char sir_numar_in_binar[7]="";
            int aux=nr;
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
            //printf("neinversat %s\n", sir_numar_in_binar);
            for(int j=0; j<strlen(sir_numar_in_binar)/2; j++)
            {
                char help=sir_numar_in_binar[j];
                sir_numar_in_binar[j]=sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j];
                sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j]=help;
            }
            //printf("innver %s\n", sir_numar_in_binar);
            strncat(val_imm, "000000", 6-strlen(sir_numar_in_binar));
            strcat(val_imm, sir_numar_in_binar);
            return val_imm;
}
char* conversie_val_imm_pe_11_biti(int nr, char* val_imm)
{
    char sir_numar_in_binar[12]="";
            int aux=nr;
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
            //printf("neinversat %s\n", sir_numar_in_binar);
            for(int j=0; j<strlen(sir_numar_in_binar)/2; j++)
            {
                char help=sir_numar_in_binar[j];
                sir_numar_in_binar[j]=sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j];
                sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j]=help;
            }
            //printf("innver %s\n", sir_numar_in_binar);
            strncat(val_imm, "00000000000", 11-strlen(sir_numar_in_binar));
            strcat(val_imm, sir_numar_in_binar);
            return val_imm;
}

char* conversie_val_imm_pe_4_biti(int nr, char* val_imm)
{
    char sir_numar_in_binar[5]="";
            int aux=nr;
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
            //printf("neinversat %s\n", sir_numar_in_binar);
            for(int j=0; j<strlen(sir_numar_in_binar)/2; j++)
            {
                char help=sir_numar_in_binar[j];
                sir_numar_in_binar[j]=sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j];
                sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j]=help;
            }
            //printf("innver %s\n", sir_numar_in_binar);
            strncat(val_imm, "0000", 4-strlen(sir_numar_in_binar));
            strcat(val_imm, sir_numar_in_binar);
            return val_imm;
}

char* conversie_val_imm_pe_5_biti(int nr, char* val_imm)
{
    char sir_numar_in_binar[6]="";
            int aux=nr;
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
            //printf("neinversat %s\n", sir_numar_in_binar);
            for(int j=0; j<strlen(sir_numar_in_binar)/2; j++)
            {
                char help=sir_numar_in_binar[j];
                sir_numar_in_binar[j]=sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j];
                sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j]=help;
            }
            //printf("innver %s\n", sir_numar_in_binar);
            strncat(val_imm, "00000", 5-strlen(sir_numar_in_binar));
            strcat(val_imm, sir_numar_in_binar);
            return val_imm;
}

char* convertire_eticheta(char matrice[100][100], int indice, char* eticheta, char *rezultat)
{

    for(int i=0; i<indice; i++)
    { 
        char copie_linie[100];
        strcpy(copie_linie, matrice[i]);
        char *linie=strtok(copie_linie, " ");
        if(strcasecmp(linie, eticheta)==0)
        {
            char sir_numar_in_binar[12]="";
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
            for(int j=0; j<strlen(sir_numar_in_binar)/2; j++)
            {
                char help=sir_numar_in_binar[j];
                sir_numar_in_binar[j]=sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j];
                sir_numar_in_binar[strlen(sir_numar_in_binar)-1-j]=help;
            }
            //printf("innver %s\n", sir_numar_in_binar);
            strncat(rezultat, "00000000000", 11-strlen(sir_numar_in_binar));
            strcat(rezultat, sir_numar_in_binar);
            return rezultat;
        }
    }
    return 0;
}

void verificare_registru_corect(char *cuvant)
{
    if ((strcasecmp(cuvant, "X") != 0) && (strcasecmp(cuvant, "Y") != 0) && (strcasecmp(cuvant, "ACC") != 0))
    {
        perror("Argumentul trebuie sa fie un registru (X, Y, ACC)");
        exit(7);
    }
}
void verificare_argument_existent(char *cuvant)
{
    if(cuvant==NULL)
    {
        perror("Prea putine argumente!");
        exit(7);
    }
}
void argument_nu_trebuie_sa_fie_registru(char *cuvant)
{
    if ((strcasecmp(cuvant, "X") == 0) || (strcasecmp(cuvant, "Y") == 0) || (strcasecmp(cuvant, "ACC") == 0))
    {
        perror("Argumentul la branch nu trebuie sa fie registru");
        exit(7);
    }
}
int verificare_atoi(char *sir)
{
    if(atoi(sir)!=0)
    {
        return atoi(sir);
    }
    else
    {
        if(sir[0]=='0' && strlen(sir)==1)
        {
            return 0;
        }
        return -1;
    }
}

void verificare_linie_existenta(char *cuvant, int indice)
{
    if (verificare_atoi(cuvant) > indice)
    {
        perror("Sare la o adresa inexistenta!");
        exit(7);
    }
}
void verificare_capacitate_valoare_imm(char *cuvant, int maxim)
{
    if (verificare_atoi(cuvant) >= maxim )
    {
        perror("Numarul este prea mare!");
        exit(7);
    }
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
    char *pointer_pt_linie=NULL;
    pointer_pt_linie=strtok(buffer_fisier, "\n");
    //printf("%s\n", pointer_pt_linie);
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
        //printf("%s\n\n", pointer_pt_linie);
        strcat(matrice[indice], pointer_pt_linie);
        strcat(matrice_copie[indice], pointer_pt_linie);
        indice++;

        pointer_pt_linie=strtok(NULL, "\n");

    }
    for(int i=0; i<indice; i++)
    {
        char buffer_linie[17]="";
        char rezultat[12]="";
        char rezultat8[9]="";
        char *linie=NULL;
        //printf("Linie matrice: %s\n", matrice[i]);
        linie=strtok(matrice[i], " ");  //am primul cuv din line =instr
        if (linie != NULL)
        {
            //printf("%s ", linie);
            if(
                (strcasecmp(linie, "LDR")!=0 ) &&
                (strcasecmp(linie, "STR")!=0 ) &&
                (strcasecmp(linie, "BRZ")!=0 ) &&
                (strcasecmp(linie, "BRC")!=0 ) &&
                (strcasecmp(linie, "BRO")!=0 ) &&
                (strcasecmp(linie, "BRN")!=0 ) &&
                (strcasecmp(linie, "BRA")!=0 ) &&
                (strcasecmp(linie, "JMP")!=0 ) &&
                (strcasecmp(linie, "RET")!=0 ) &&
                (strcasecmp(linie, "ADD")!=0 ) &&
                (strcasecmp(linie, "SUB")!=0 ) &&
                (strcasecmp(linie, "LSR")!=0 ) &&
                (strcasecmp(linie, "LSL")!=0 ) &&
                (strcasecmp(linie, "RSR")!=0 ) &&
                (strcasecmp(linie, "RSL")!=0 ) &&
                (strcasecmp(linie, "MUL")!=0 ) &&
                (strcasecmp(linie, "DIV")!=0 ) &&
                (strcasecmp(linie, "MOD")!=0 ) &&
                (strcasecmp(linie, "AND")!=0 ) &&
                (strcasecmp(linie, "OR")!=0 ) &&
                (strcasecmp(linie, "XOR")!=0 ) &&
                (strcasecmp(linie, "MOV")!=0 ) &&
                (strcasecmp(linie, "NOT")!=0 ) &&
                (strcasecmp(linie, "INC")!=0 ) &&
                (strcasecmp(linie, "DEC")!=0 ) &&
                (strcasecmp(linie, "CMP")!=0 )
            )
            {
                linie=strtok(NULL, " ");
                
            }

            if (strcasecmp(linie, "LDR") == 0)
            { 
                char buffer_linie[17]="";
                strcat(buffer_linie, LDR);
                char *cuv1, *cuv2;
                cuv1 = strtok(NULL, " ");
                cuv2 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                verificare_argument_existent(cuv2);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la LDR!");
                    exit(7);
                }

                if(verificare_atoi(cuv1)!=-1)
                {
                    perror("Primul argument nu e registru la LDR!");
                    exit(7);
                }
                verificare_registru_corect(cuv1);
                if(verificare_atoi(cuv2)!=-1)   //avem de lucru cu o valoare imm
                {
                    verificare_capacitate_valoare_imm(cuv2, 256);
                    strcat(buffer_linie, "1");  //M=1
                }
                else 
                {
                    strcat(buffer_linie, "0");
                }

                if(strcasecmp(cuv1, "X")==0)
                {
                    strcat(buffer_linie, X);
                }
                if (strcasecmp(cuv1, "Y") == 0)
                {
                    strcat(buffer_linie, Y);
                }
                if (strcasecmp(cuv1, "ACC") == 0)
                {
                    strcat(buffer_linie, ACC);
                }
                if(verificare_atoi(cuv2)!=-1) 
                {
                    char rezultat8[9]="";
                    conversie_val_imm_pe_8_biti(verificare_atoi(cuv2), rezultat8);
                    strcat(buffer_linie, rezultat8);
                }
                else
                {
                    verificare_registru_corect(cuv2);
                    if (strcasecmp(cuv2, "X") == 0)
                    {
                        strcat(buffer_linie, X8);
                    }
                    if (strcasecmp(cuv2, "Y") == 0)
                    {
                        strcat(buffer_linie, Y8);
                    }
                    if (strcasecmp(cuv2, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC8);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if (strcasecmp(linie, "STR") == 0)
            { 
                char buffer_linie[17]="";
                strcat(buffer_linie, STR);
                char *cuv1, *cuv2;
                cuv1 = strtok(NULL, " ");
                cuv2 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                verificare_argument_existent(cuv2);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la STR!");
                    exit(7);
                }

                if(verificare_atoi(cuv2)!=-1)
                {
                    perror("Al doilea argument nu e registru!");
                    exit(7);
                }
                if(verificare_atoi(cuv1)!=-1)
                {
                    verificare_capacitate_valoare_imm(cuv1, 256);
                    strcat(buffer_linie, "1");  //M=1
                }
                else 
                {
                    strcat(buffer_linie, "0");
                }
                
                if(verificare_atoi(cuv1)!=-1)
                {
                    char rezultat8[9]="";
                    conversie_val_imm_pe_8_biti(verificare_atoi(cuv1), rezultat8);
                    strcat(buffer_linie, rezultat8);
                }
                else //daca primul arg e registru
                {
                    verificare_registru_corect(cuv1);
                    if (strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X8);
                    }
                    if (strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y8);
                    }
                    if (strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC8);
                    }
                }
                verificare_registru_corect(cuv2);
                if(strcasecmp(cuv2, "X")==0)
                {
                    strcat(buffer_linie, X);
                }
                if (strcasecmp(cuv2, "Y") == 0)
                {
                    strcat(buffer_linie, Y);
                }
                if (strcasecmp(cuv2, "ACC") == 0)
                {
                    strcat(buffer_linie, ACC);
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
               
            }
            if (strcasecmp(linie, "BRZ") == 0)
            {
                char buffer_linie[17]="";
                strcat(buffer_linie, BRZ);
                linie = strtok(NULL, " ");
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la BRZ!");
                    exit(7);
                }
                verificare_argument_existent(linie);
                argument_nu_trebuie_sa_fie_registru(linie);
                char rezultat[12]="";
                if(verificare_atoi(linie)==-1) //eticheta
                {
                    strcat(buffer_linie, convertire_eticheta(matrice_copie,indice, linie, rezultat));
                }
                else  
                {
                    verificare_linie_existenta(linie, indice);
                    strcat(buffer_linie, conversie_val_imm_pe_11_biti(verificare_atoi(linie), rezultat));
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
                
            }
            if (strcasecmp(linie, "BRN") == 0)
            {
                char buffer_linie[17]="";
                strcat(buffer_linie, BRN);
                linie = strtok(NULL, " ");
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la BRN!");
                    exit(7);
                }
                verificare_argument_existent(linie);
                argument_nu_trebuie_sa_fie_registru(linie);
                char rezultat[12]="";
                if(verificare_atoi(linie)==-1) //eticheta
                {
                    strcat(buffer_linie, convertire_eticheta(matrice_copie,indice, linie, rezultat));
                }
                else  
                {
                    verificare_linie_existenta(linie, indice);
                    strcat(buffer_linie, conversie_val_imm_pe_11_biti(verificare_atoi(linie), rezultat));
                }
                
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
                
            }
            if (strcasecmp(linie, "BRC") == 0)
            {
                char buffer_linie[17]="";
                strcat(buffer_linie, BRC);
                linie = strtok(NULL, " ");
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la BRC!");
                    exit(7);
                }
                verificare_argument_existent(linie);
                argument_nu_trebuie_sa_fie_registru(linie);
                char rezultat[12]="";
                if(verificare_atoi(linie)==-1) //eticheta
                {
                    strcat(buffer_linie, convertire_eticheta(matrice_copie,indice, linie, rezultat));
                }
                else  
                {
                    verificare_linie_existenta(linie, indice);
                    strcat(buffer_linie, conversie_val_imm_pe_11_biti(verificare_atoi(linie), rezultat));
                }
                
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
                
            }
             if (strcasecmp(linie, "BRO") == 0)
            {
                char buffer_linie[17]="";
                strcat(buffer_linie, BRO);
                linie = strtok(NULL, " ");
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la BRO!");
                    exit(7);
                }
                verificare_argument_existent(linie);
                argument_nu_trebuie_sa_fie_registru(linie);
                char rezultat[12]="";
                if(verificare_atoi(linie)==-1) //eticheta
                {
                    strcat(buffer_linie, convertire_eticheta(matrice_copie,indice, linie, rezultat));
                }
                else  
                {
                    verificare_linie_existenta(linie, indice);
                    strcat(buffer_linie, conversie_val_imm_pe_11_biti(verificare_atoi(linie), rezultat));
                }
                
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
                
            }
            if (strcasecmp(linie, "BRA") == 0)
            {
                char buffer_linie[17]="";
                strcat(buffer_linie, BRA);
                linie = strtok(NULL, " ");
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la BRA!");
                    exit(7);
                }
                verificare_argument_existent(linie);
                argument_nu_trebuie_sa_fie_registru(linie);
                char rezultat[12]="";
                if(verificare_atoi(linie)==-1) //eticheta
                {
                    strcat(buffer_linie, convertire_eticheta(matrice_copie,indice, linie, rezultat));
                }
                else  
                {
                    verificare_linie_existenta(linie, indice);
                    strcat(buffer_linie, conversie_val_imm_pe_11_biti(verificare_atoi(linie), rezultat));
                }
                
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
                
            }
            if (strcasecmp(linie, "JMP") == 0)
            {
                char buffer_linie[17]="";
                strcat(buffer_linie, JMP);
                linie = strtok(NULL, " ");
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la JMP!");
                    exit(7);
                }
                verificare_argument_existent(linie);
                argument_nu_trebuie_sa_fie_registru(linie);
                char rezultat[12]="";
                if(verificare_atoi(linie)==-1) //eticheta
                {
                    strcat(buffer_linie, convertire_eticheta(matrice_copie,indice, linie, rezultat));
                }
                else  
                {
                    verificare_linie_existenta(linie, indice);
                    strcat(buffer_linie, conversie_val_imm_pe_11_biti(verificare_atoi(linie), rezultat));
                }
                
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if (strcasecmp(linie, "RET") == 0)
            {
                char buffer_linie[17]="";
                strcat(buffer_linie, RET);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la RET!");
                    exit(7);
                }
                strcat(buffer_linie, "00000000000\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "ADD") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, ADD);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la ADD!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[7] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "SUB") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, SUB);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
               verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la SUB!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "LSR") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, LSR);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la LSR!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "LSL") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, LSL);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la LSL!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "RSR") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, RSR);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la RSR!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "RSL") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, RSL);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la RSL!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "MUL") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, MUL);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la MUL!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "DIV") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, DIV);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la DIV!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "MOD") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, MOD);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la MOD!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "AND") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, AND);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la AND!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "OR") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, OR);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la OR!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "XOR") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, XOR);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la XOR!");
                    exit(7);
                }
                if(verificare_atoi(cuv1) != -1)     
                {
                    verificare_capacitate_valoare_imm(cuv1, 64);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    verificare_registru_corect(cuv1);
                    strcat(buffer_linie, "0");
                }
                strcat(buffer_linie,ACC);
                strcat(buffer_linie,ACC);
                if(verificare_atoi(cuv1) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_6_biti(verificare_atoi(cuv1), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    if(strcasecmp(cuv1, "X") == 0)
                    {
                        strcat(buffer_linie, X6);
                    }
                    if(strcasecmp(cuv1, "Y") == 0)
                    {
                        strcat(buffer_linie, Y6);
                    }
                    if(strcasecmp(cuv1, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC6);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }

            if(strcasecmp(linie, "MOV") == 0)
            {
                char buffer_linie[17]= "";
                strcat(buffer_linie, MOV);
                char *cuv1, *cuv2;
                cuv1 = strtok(NULL, " ");
                cuv2 = strtok(NULL, " ");
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la MOV!");
                    exit(7);
                }
                verificare_argument_existent(cuv2);
                verificare_argument_existent(cuv1);
                if(verificare_atoi(cuv1)!=-1)
                {
                    perror("Primul argument trebuie sa fie registru");
                    exit(7);
                }
                verificare_registru_corect(cuv1);
                
                
                if(verificare_atoi(cuv2) != -1)
                {
                    verificare_capacitate_valoare_imm(cuv2, 256);
                    strcat(buffer_linie, "1");
                }
                else
                {
                    strcat(buffer_linie, "0");
                }
               
                if(strcasecmp(cuv1, "X") == 0)
                {
                    strcat(buffer_linie, X);
                }
                if(strcasecmp(cuv1, "Y") == 0)
                {
                    strcat(buffer_linie, Y);
                }
                if(strcasecmp(cuv1, "ACC") == 0)
                {
                    strcat(buffer_linie, ACC);
                }
                if(verificare_atoi(cuv2) != -1)
                {
                    char valoare[9] = "";
                    conversie_val_imm_pe_8_biti(verificare_atoi(cuv2), valoare);
                    strcat(buffer_linie, valoare);
                }
                else
                {
                    verificare_registru_corect(cuv2);
                    if(strcasecmp(cuv2, "X") == 0)
                    {
                        strcat(buffer_linie, X8);
                    }
                    if(strcasecmp(cuv2, "Y") == 0)
                    {
                        strcat(buffer_linie, Y8);
                    }
                    if(strcasecmp(cuv2, "ACC") == 0)
                    {
                        strcat(buffer_linie, ACC8);
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "NOT") == 0) //nu are arg , neaga implicit ACC
            {
                char buffer_linie[17] = "";
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la NOT!");
                    exit(7);
                }
                strcat(buffer_linie, NOT);
                strcat(buffer_linie, "000000000");
                strcat(buffer_linie, ACC);
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "INC") == 0)
            {
                char buffer_linie[17] = "";
                strcat(buffer_linie, INC);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la INC!");
                    exit(7);
                }
                if(verificare_atoi(cuv1)!=-1 )
                {
                    perror("Argumentul trebuie sa fie registru!");
                    exit(7);
                }
                verificare_registru_corect(cuv1);
                if(strcasecmp(cuv1, "X") == 0)
                {
                    strcat(buffer_linie, "000000000");
                    strcat(buffer_linie, X);
                }
                if(strcasecmp(cuv1, "Y") == 0)
                {
                    strcat(buffer_linie, "000000000");
                    strcat(buffer_linie, Y);
                }
                if(strcasecmp(cuv1, "ACC") == 0)
                {
                    strcat(buffer_linie, "000000000");
                    strcat(buffer_linie, ACC);
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "DEC") == 0)
            {
                char buffer_linie[17] = "";
                strcat(buffer_linie, DEC);
                char *cuv1;
                cuv1 = strtok(NULL, " ");
                verificare_argument_existent(cuv1);
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
              
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la DEC!");
                    exit(7);
                }
                if(verificare_atoi(cuv1)!=-1 )
                {
                    perror("Argumentele trebuie sa fie registre!");
                    exit(7);
                }
                verificare_registru_corect(cuv1);
                if(strcasecmp(cuv1, "X") == 0)
                {
                    strcat(buffer_linie, "000000000");
                    strcat(buffer_linie, X);
                }
                if(strcasecmp(cuv1, "Y") == 0)
                {
                    strcat(buffer_linie, "000000000");
                    strcat(buffer_linie, Y);
                }
                if(strcasecmp(cuv1, "ACC") == 0)
                {
                    strcat(buffer_linie, "000000000");
                    strcat(buffer_linie, ACC);
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
            if(strcasecmp(linie, "CMP") == 0)
            {
                char buffer_linie[17] = "";
                strcat(buffer_linie, CMP);
                char *cuv1, *cuv2;
                cuv1 = strtok(NULL, " ");
                cuv2 = strtok(NULL, " ");
                char *gresit=NULL;
                gresit=strtok(NULL, " ");
                if(gresit!=NULL)
                {
                    perror("Sunt prea multe argumente la CMP!");
                    exit(7);
                }
                verificare_argument_existent(cuv1);
                verificare_argument_existent(cuv2);
                if(verificare_atoi(cuv1) != -1)
                {
                    if(verificare_atoi(cuv2) != -1)
                    {
                        verificare_capacitate_valoare_imm(cuv1, 32);
                        verificare_capacitate_valoare_imm(cuv2, 16);
                        strcat(buffer_linie, "11");
                        char valoare1[6] = "";
                        conversie_val_imm_pe_5_biti(verificare_atoi(cuv1), valoare1);
                        strcat(buffer_linie, valoare1);
                        char valoare2[5] = "";
                        conversie_val_imm_pe_4_biti(verificare_atoi(cuv2), valoare2);
                        strcat(buffer_linie, valoare2);
                    }
                    else
                    {
                        verificare_capacitate_valoare_imm(cuv1, 32);
                        strcat(buffer_linie, "01");
                        char valoare[6] = "";
                        conversie_val_imm_pe_5_biti(verificare_atoi(cuv1), valoare);
                        strcat(buffer_linie, valoare);
                        verificare_registru_corect(cuv2);
                        if(strcasecmp(cuv2, "X") == 0)
                        {
                            strcat(buffer_linie, X4);
                        }
                        if(strcasecmp(cuv2, "Y") == 0)
                        {
                            strcat(buffer_linie, Y4);
                        }
                        if(strcasecmp(cuv2, "ACC") == 0)
                        {
                            strcat(buffer_linie, ACC4);
                        }
                    }
                }
                else
                {
                    if(verificare_atoi(cuv2) != -1)
                    {
                        verificare_capacitate_valoare_imm(cuv2, 16);
                        strcat(buffer_linie, "10");
                        verificare_registru_corect(cuv1);
                        if(strcasecmp(cuv1, "X") == 0)
                        {
                            strcat(buffer_linie, "0");
                            strcat(buffer_linie, X4);
                        }
                        if(strcasecmp(cuv1, "Y") == 0)
                        {
                            strcat(buffer_linie, "0");
                            strcat(buffer_linie, Y4);
                        }
                        if(strcasecmp(cuv1, "ACC") == 0)
                        {
                            strcat(buffer_linie, "0");
                            strcat(buffer_linie, ACC4);
                        }
                        char valoare[5] = "";
                        conversie_val_imm_pe_4_biti(verificare_atoi(cuv2), valoare);
                        strcat(buffer_linie, valoare);
                    }
                    else
                    {
                        strcat(buffer_linie, "00");
                        verificare_registru_corect(cuv1);
                        verificare_registru_corect(cuv2);
                        if(strcasecmp(cuv1, "X") == 0)
                        {
                            strcat(buffer_linie, "0");
                            strcat(buffer_linie, X4);
                        }
                        if(strcasecmp(cuv1, "Y") == 0)
                        {
                            strcat(buffer_linie, "0");
                            strcat(buffer_linie, Y4);
                        }
                        if(strcasecmp(cuv1, "ACC") == 0)
                        {
                            strcat(buffer_linie, "0");
                            strcat(buffer_linie, ACC4);
                        }
                        if(strcasecmp(cuv2, "X") == 0)
                        {
                            strcat(buffer_linie, X4);
                        }
                        if(strcasecmp(cuv2, "Y") == 0)
                        {
                            strcat(buffer_linie, Y4);
                        }
                        if(strcasecmp(cuv2, "ACC") == 0)
                        {
                            strcat(buffer_linie, ACC4);
                        }
                    }
                }
                strcat(buffer_linie, "\n");
                if ((write(descr_out, buffer_linie, strlen(buffer_linie))) < 0)
                {
                    perror("Nu s-a putut scrie in fisier!");
                    exit(7);
                }
            }
        }
    }     

    close(descr_in);
    close(descr_out);
    return 0;
}