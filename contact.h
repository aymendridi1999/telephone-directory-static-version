#ifndef CONTACT_H_INCLUDED
#define CONTACT_H_INCLUDED

struct Adresse
{   int num;
    int code;
    char rue[25];
    char ville[25];
} ;
typedef struct Adresse Adr;

struct Contact
{   int Identifiant;
    char Nom[25];
    char Prenom[25];
    int numero;
    int CIN;
    Adr adresse;

} ;
typedef struct Contact Ctc;

Ctc saisir_contact();
void Saisir_tab_contact(Ctc Tab_contact[],int* N);
void Ajouter_contact(Ctc Tab_contact[],int* N);
void affiche_contact(Ctc c);
void affiche_tab_contact(Ctc Tab_contact[],int N);
int Rechercher_contact(Ctc Tab_contact[], int N,int iden );
void Modifier_contact(Ctc  Tab_contact[],int id);
void Supprimer_contact(Ctc  Tab_contact[], int* N,int id);
int tri_nom(char *str1, char *str2);

#endif // CONTACT_H_INCLUDED
