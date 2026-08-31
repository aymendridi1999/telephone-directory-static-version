#ifndef CONTACT_H_INCLUDED
#define CONTACT_H_INCLUDED

#define MAX_CONTACTS 100
#define TEXT_SIZE 25

typedef struct Adresse
{
    int num;
    int code;
    char rue[TEXT_SIZE];
    char ville[TEXT_SIZE];
} Adr;

typedef struct Contact
{
    int Identifiant;
    char Nom[TEXT_SIZE];
    char Prenom[TEXT_SIZE];
    int numero;
    int CIN;
    Adr adresse;
} Ctc;

Ctc saisir_contact(void);
void Saisir_tab_contact(Ctc Tab_contact[], int *N);
void Ajouter_contact(Ctc Tab_contact[], int *N);
void affiche_contact(Ctc c);
void affiche_tab_contact(const Ctc Tab_contact[], int N);
int Rechercher_contact_par_id(const Ctc Tab_contact[], int N, int identifiant);
int Rechercher_numero(const Ctc Tab_contact[], int N, int numero);
void Modifier_contact(Ctc Tab_contact[], int N, int index);
void Supprimer_contact(Ctc Tab_contact[], int *N, int index);
int tri_nom(const void *a, const void *b);
int charger_contacts(const char *nom_fichier, Ctc Tab_contact[], int *N);
int sauvegarder_contacts(const char *nom_fichier, const Ctc Tab_contact[], int N);
int prochain_identifiant(const Ctc Tab_contact[], int N);

#endif
