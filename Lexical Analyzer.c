#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define program 1
#define id 2
#define pt 3
#define pv 4
#define var 5
#define dp 6
#define v 7
#define integer 8
#define chari 9
#define begin 10
#define end 11
#define iff 12
#define whille 13
#define write 14
#define writeln 15
#define read 16
#define readln 17
#define aff 18
#define po 19
#define pf 20
#define opadd 21
#define opmul 22
#define oprel 23
#define nb 24
#define elsee 25
#define then 26
#define doo 27
#define ppe 28
#define dif 29
#define ppq 30
#define ega 31
#define pge 32
#define pgq 33
#define edf 34

typedef struct unilex {
 int ul;
 int att;
} unilex;


int *c = 0;

FILE* fp;

char tab_iden[100][30];
char car;
unilex symbole;
char ch[30]; // mots lu
int z = 0;  // indice de de debut de chaine


int mot_cle[15]={1,10,5,8,9,11,26,12,25,16,17,14,15,27,13};

char tab_mot_cle[20][20] = { "program", "begin", "var",
"integer", "char", "end", "then", "if", "else", "read",
"readln", "write", "writeln", "do", "while" };


void reculer(int k) {
 fseek(fp, -k, SEEK_CUR);
}

char carsuivant() {
 return fgetc(fp);
}

int unilexid() {
     int k = 0;
     int i = 0;
     while (i < 15 && (!k)) {
         if (strcmp(tab_mot_cle[i], ch) == 0) {
             printf("mot cle \t%s\n",tab_mot_cle[i]);
             k = 1;
         } else {
            i++;
         }
     }
     if (k == 1){
         printf("code mot cle %d",mot_cle[i]);
         return mot_cle[i];
     }
     else {
        return id;
     }
}


int rangerid(int k, int* c) {
     int s = 0;
     if (k == id) {
         while ((strcmp(tab_iden[s], ch) != 0) && (s < (*c)))
            s++;
         if (s < *c) {
            return s;
         } else {
            (*c)++;
            strcpy(tab_iden[*c], ch);
            return *c;
         }
    }
     else{
     return 0;
     }
}


unilex analex() {
     int etat = 0;
     int colonne = 0, ligne = 1;
     while (1) {
         switch (etat) {
         case 0:
             car = carsuivant();
             int k;
             scanf("this is the first car %d",&k);
             if (car == ' ') {
                 colonne++;
                 etat = 0;
             } else if (car == '\n') {
                 ligne++;
                 colonne = 0;
                 etat = 0;
             }else if(car=='\t'){
                 colonne+=3;
                 etat=0;
             }
             else if (isalpha(car)){
                 z=0;
                 ch[0]=car;
                 etat=1;
             }
             else if (isdigit(car)) {
                etat = 3;
             } else if (car == '<') {
                etat = 5;
             } else if (car == '>') {
                etat = 10;
             } else if (car == '=') {
                etat = 9;
             } else if (car == '$') {
                 printf("end of file ");
                 scanf("%d",&k);
                 etat = 23;
             }else if(car==';'){
                etat=22;
             }
             else if (car==',')
                etat=21;
             else if (car=='(')
                etat=18;
             else if (car==':')
                etat=13;
             else if (car==')')
                etat=19;
            else if (car=='.')
                etat=20;
            else if (car=='+')
                etat=16;
            else if (car=='*')
                etat=17;
             else {
                etat = 24;
             }
            break;
        case 1:
             car = carsuivant();
             if (isalpha(car) || isdigit(car)) {
                 z++;
                 ch[z] = car;
             } else {
                 etat = 2;
                 ch[z + 1] = '\0';
                 printf("this is the chaine %s",ch);
                 z = 0;
             }
             break;
        case 2:
             reculer(1);
             symbole.ul = unilexid();
             symbole.att = rangerid(symbole.ul, &c);
             return symbole;
        case 3:

             car = carsuivant();
             if (isdigit(car)) {
                 z++;
                 ch[z] = car;
             } else {
                 etat = 4;
                 ch[z + 1] = '\0';
                 z = 0;
             }
             break;
        case 4:
             reculer(1);
             symbole.ul = nb;
             symbole.att = atoi(ch);
             return symbole;
        case 5:
            car = carsuivant();
             switch (car) {
                 case '=':
                    etat = 6;
                    break;
                 case '>':
                    etat = 7;
                    break;
                 default:
                    etat = 8;
                    }
                break;

        case 6:
                 symbole.ul = oprel;
                 symbole.att = ppe;
                 return symbole;
        case 7:
                 symbole.ul = oprel;
                 symbole.att = dif;
                 return symbole;
        case 8:
                 reculer(1);
                 symbole.ul = oprel;
                 symbole.att = ppq;
                 return symbole;
        case 9:
                 symbole.ul = oprel;
                 symbole.att = ega;
                 return symbole;
        case 10:

                 car = carsuivant();
                 if (car == '=') {
                    etat = 11;
                 } else {
                     etat=12;
                 }
        case 11:
                 symbole.ul = oprel;
                 symbole.att = pge;
                 return symbole;

        case 12:
                reculer(1);
                 symbole.ul = oprel;
                 symbole.att = pgq;
                 return symbole;
        case 13:
                 car=carsuivant();
                 if (car=='='){
                        etat=14;
                 } else{
                    etat=15;
                 }
        case 14 :
                     symbole.ul=aff;
                     symbole.att=0;
                     return symbole;

        case 15:
                 reculer(1);
                 symbole.ul=dp;
                 symbole.att=0;
                 return symbole;


        case 16:
                 symbole.ul=opadd;
                 symbole.att=0;
                 return symbole;

        case 17:
                 symbole.ul=opmul;
                 symbole.att=0;
                 return symbole;
        case 18:
                 symbole.ul=po;
                 symbole.att=0;
                 return symbole;

        case 19:
                 symbole.ul=pf;
                 symbole.att=0;
                 return symbole;
        case 20:
                 symbole.ul=pt;
                 symbole.att=0;
                 return symbole;
        case 21:
                 symbole.ul=v;
                 symbole.att=0;
                 return symbole;

        case 22:
                 symbole.ul=pv;
                 symbole.att=0;
                 return symbole;

        case 23:
                 symbole.ul = edf;
                 symbole.att = 0;
                 return symbole;

        case 24:
                 printf("Erreur : caractère inattendu à la ligne %d, colonne %d\n", ligne, colonne);
                 etat=0;
                break;

         }


     }
}


int main() {
    char fichier[50];
     printf("Entrez le nom du fichier source : ");
     scanf("%s", fichier);
     fp = fopen(fichier, "r");
     if (fp == NULL) {
         printf("Impossible d'ouvrir le fichier %s.\n", fichier);
         return 1;
     }
     do {
         symbole = analex();
         printf("\nSymbole : %d, Attribut : %d\n", symbole.ul, symbole.att);
     }
     while (symbole.ul != edf);
     fclose(fp);

    return 0;
}

