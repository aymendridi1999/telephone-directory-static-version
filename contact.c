#include "contact.h"

#include <stdio.h>
#include <string.h>

extern int IdentifiantG;

static Adr saisir_adresse(void)
{
    Adr a;

    printf("\nIntroduire le numero de la maison: ");
    scanf("%d", &a.num);

    printf("Introduire le code postal: ");
    scanf("%d", &a.code);

    printf("Introduire le nom de la rue: ");
    scanf("%24s", a.rue);

    printf("Introduire le nom de la ville: ");
    scanf("%24s", a.ville);

    return a;
}

Ctc saisir_contact(void)
{
    Ctc c;

    c.Identifiant = -1;

    printf("\nIntroduire le nom: ");
    scanf("%24s", c.Nom);

    printf("Introduire le prenom: ");
    scanf("%24s", c.Prenom);

    printf("Introduire le numero: ");
    scanf("%d", &c.numero);

    printf("Introduire le numero de CIN (8 chiffres): ");
    do
    {
        scanf("%d", &c.CIN);
        if (c.CIN < 10000000 || c.CIN > 99999999)
        {
            printf("CIN invalide. Introduire un numero de 8 chiffres: ");
        }
    }
    while (c.CIN < 10000000 || c.CIN > 99999999);

    c.adresse = saisir_adresse();
    return c;
}

void Saisir_tab_contact(Ctc Tab_contact[], int *N)
{
    char rep[4];

    do
    {
        Ajouter_contact(Tab_contact, N);

        if (*N >= MAX_CONTACTS)
        {
            break;
        }

        printf("\nVoulez-vous ajouter un autre contact ? oui/non: ");
        scanf("%3s", rep);
    }
    while (strcmp(rep, "oui") == 0);
}

void Ajouter_contact(Ctc Tab_contact[], int *N)
{
    Ctc c;

    if (*N >= MAX_CONTACTS)
    {
        printf("\nLe repertoire est plein (%d contacts maximum).\n", MAX_CONTACTS);
        return;
    }

    do
    {
        c = saisir_contact();
        if (Rechercher_numero(Tab_contact, *N, c.numero) != -1)
        {
            printf("\nCe numero existe deja. Veuillez saisir un autre contact.\n");
        }
    }
    while (Rechercher_numero(Tab_contact, *N, c.numero) != -1);

    c.Identifiant = IdentifiantG++;
    Tab_contact[*N] = c;
    (*N)++;
}

void affiche_contact(Ctc c)
{
    printf("\n------------------------------");
    printf("\nIdentifiant : %d", c.Identifiant);
    printf("\nNom         : %s", c.Nom);
    printf("\nPrenom      : %s", c.Prenom);
    printf("\nNumero      : %d", c.numero);
    printf("\nCIN         : %d", c.CIN);
    printf("\nAdresse     : %d %s, %s %d\n",
           c.adresse.num,
           c.adresse.rue,
           c.adresse.ville,
           c.adresse.code);
}

void affiche_tab_contact(const Ctc Tab_contact[], int N)
{
    int i;

    if (N == 0)
    {
        printf("\nAucun contact.\n");
        return;
    }

    for (i = 0; i < N; i++)
    {
        affiche_contact(Tab_contact[i]);
    }
}

int Rechercher_contact_par_id(const Ctc Tab_contact[], int N, int identifiant)
{
    int i;

    for (i = 0; i < N; i++)
    {
        if (Tab_contact[i].Identifiant == identifiant)
        {
            return i;
        }
    }

    return -1;
}

int Rechercher_numero(const Ctc Tab_contact[], int N, int numero)
{
    int i;

    for (i = 0; i < N; i++)
    {
        if (Tab_contact[i].numero == numero)
        {
            return i;
        }
    }

    return -1;
}

void Modifier_contact(Ctc Tab_contact[], int N, int index)
{
    int choix;
    int nouveau_numero;
    int index_existant;

    printf("\n1. Modifier le nom");
    printf("\n2. Modifier le prenom");
    printf("\n3. Modifier le numero");
    printf("\n4. Modifier l'adresse");
    printf("\nIntroduire votre choix: ");
    scanf("%d", &choix);

    switch (choix)
    {
        case 1:
            printf("Introduire le nom: ");
            scanf("%24s", Tab_contact[index].Nom);
            break;

        case 2:
            printf("Introduire le prenom: ");
            scanf("%24s", Tab_contact[index].Prenom);
            break;

        case 3:
            do
            {
                printf("Introduire le numero: ");
                scanf("%d", &nouveau_numero);
                index_existant = Rechercher_numero(Tab_contact, N, nouveau_numero);

                if (index_existant != -1 && index_existant != index)
                {
                    printf("Ce numero appartient deja a un autre contact.\n");
                }
            }
            while (index_existant != -1 && index_existant != index);

            Tab_contact[index].numero = nouveau_numero;
            break;

        case 4:
            Tab_contact[index].adresse = saisir_adresse();
            break;

        default:
            printf("\nChoix invalide.\n");
            break;
    }
}

void Supprimer_contact(Ctc Tab_contact[], int *N, int index)
{
    int i;

    for (i = index; i < *N - 1; i++)
    {
        Tab_contact[i] = Tab_contact[i + 1];
    }

    (*N)--;
}

int tri_nom(const void *a, const void *b)
{
    const Ctc *contact_a = (const Ctc *)a;
    const Ctc *contact_b = (const Ctc *)b;
    int comparaison = strcmp(contact_a->Nom, contact_b->Nom);

    if (comparaison == 0)
    {
        comparaison = strcmp(contact_a->Prenom, contact_b->Prenom);
    }

    return comparaison;
}

int charger_contacts(const char *nom_fichier, Ctc Tab_contact[], int *N)
{
    FILE *fichier;
    Ctc c;
    int lus;

    *N = 0;
    fichier = fopen(nom_fichier, "rt");

    if (fichier == NULL)
    {
        return 0;
    }

    while (*N < MAX_CONTACTS)
    {
        lus = fscanf(
            fichier,
            "%d %d %24s %24s %d %d %24s %24s %d",
            &c.Identifiant,
            &c.CIN,
            c.Nom,
            c.Prenom,
            &c.numero,
            &c.adresse.num,
            c.adresse.rue,
            c.adresse.ville,
            &c.adresse.code
        );

        if (lus != 9)
        {
            break;
        }

        Tab_contact[*N] = c;
        (*N)++;
    }

    fclose(fichier);
    return 1;
}

int sauvegarder_contacts(const char *nom_fichier, const Ctc Tab_contact[], int N)
{
    FILE *fichier;
    int i;

    fichier = fopen(nom_fichier, "wt");
    if (fichier == NULL)
    {
        return 0;
    }

    for (i = 0; i < N; i++)
    {
        fprintf(
            fichier,
            "%d %d %s %s %d %d %s %s %d\n",
            Tab_contact[i].Identifiant,
            Tab_contact[i].CIN,
            Tab_contact[i].Nom,
            Tab_contact[i].Prenom,
            Tab_contact[i].numero,
            Tab_contact[i].adresse.num,
            Tab_contact[i].adresse.rue,
            Tab_contact[i].adresse.ville,
            Tab_contact[i].adresse.code
        );
    }

    fclose(fichier);
    return 1;
}

int prochain_identifiant(const Ctc Tab_contact[], int N)
{
    int i;
    int max_id = -1;

    for (i = 0; i < N; i++)
    {
        if (Tab_contact[i].Identifiant > max_id)
        {
            max_id = Tab_contact[i].Identifiant;
        }
    }

    return max_id + 1;
}
