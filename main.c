#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "contact.h"

int IdentifiantG = 0;

static Ctc Tab_contact[MAX_CONTACTS];
static Ctc Tab_favoris[MAX_CONTACTS];
static Ctc Tab_blacklist[MAX_CONTACTS];

static void afficher_date_heure(void)
{
    time_t secondes;
    struct tm *instant;

    time(&secondes);
    instant = localtime(&secondes);

    if (instant != NULL)
    {
        printf(
            "%02d/%02d/%04d ; %02d:%02d:%02d\n",
            instant->tm_mday,
            instant->tm_mon + 1,
            instant->tm_year + 1900,
            instant->tm_hour,
            instant->tm_min,
            instant->tm_sec
        );
    }
}

static int contient_id(const Ctc liste[], int taille, int identifiant)
{
    return Rechercher_contact_par_id(liste, taille, identifiant) != -1;
}

static void ajouter_contact_existant(
    const Ctc repertoire[],
    int taille_repertoire,
    Ctc liste[],
    int *taille_liste,
    const char *nom_liste
)
{
    int identifiant;
    int index;

    if (*taille_liste >= MAX_CONTACTS)
    {
        printf("\nLa liste %s est pleine.\n", nom_liste);
        return;
    }

    printf("\nIntroduire l'identifiant du contact: ");
    scanf("%d", &identifiant);

    index = Rechercher_contact_par_id(repertoire, taille_repertoire, identifiant);
    if (index == -1)
    {
        printf("\nContact inexistant.\n");
        return;
    }

    if (contient_id(liste, *taille_liste, identifiant))
    {
        printf("\nCe contact existe deja dans la liste %s.\n", nom_liste);
        return;
    }

    liste[*taille_liste] = repertoire[index];
    (*taille_liste)++;
    printf("\nContact ajoute a la liste %s.\n", nom_liste);
}

static void supprimer_de_liste(Ctc liste[], int *taille, const char *nom_liste)
{
    int identifiant;
    int index;
    char rep[4];

    printf("\nIntroduire l'identifiant du contact a supprimer: ");
    scanf("%d", &identifiant);

    index = Rechercher_contact_par_id(liste, *taille, identifiant);
    if (index == -1)
    {
        printf("\nContact inexistant dans la liste %s.\n", nom_liste);
        return;
    }

    affiche_contact(liste[index]);
    printf("\nConfirmer la suppression ? oui/non: ");
    scanf("%3s", rep);

    if (strcmp(rep, "oui") == 0)
    {
        Supprimer_contact(liste, taille, index);
        printf("\nContact supprime de la liste %s.\n", nom_liste);
    }
}

static void menu_liste(
    const Ctc repertoire[],
    int taille_repertoire,
    Ctc liste[],
    int *taille_liste,
    const char *nom_liste,
    const char *nom_fichier
)
{
    int choix;

    do
    {
        printf("\n***********************************");
        printf("\n Liste %s", nom_liste);
        printf("\n 1. Ajouter un contact existant");
        printf("\n 2. Afficher la liste");
        printf("\n 3. Supprimer un contact de la liste");
        printf("\n 0. Retour");
        printf("\n***********************************");
        printf("\nIntroduire votre choix: ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                ajouter_contact_existant(
                    repertoire,
                    taille_repertoire,
                    liste,
                    taille_liste,
                    nom_liste
                );
                break;

            case 2:
                affiche_tab_contact(liste, *taille_liste);
                break;

            case 3:
                supprimer_de_liste(liste, taille_liste, nom_liste);
                break;

            case 0:
                if (!sauvegarder_contacts(nom_fichier, liste, *taille_liste))
                {
                    printf("\nErreur lors de la sauvegarde de %s.\n", nom_fichier);
                }
                break;

            default:
                printf("\nChoix invalide.\n");
                break;
        }
    }
    while (choix != 0);
}

static int calculer_prochain_id(
    const Ctc contacts[], int nb_contacts,
    const Ctc favoris[], int nb_favoris,
    const Ctc blacklist[], int nb_blacklist
)
{
    int prochain = prochain_identifiant(contacts, nb_contacts);
    int valeur = prochain_identifiant(favoris, nb_favoris);

    if (valeur > prochain)
    {
        prochain = valeur;
    }

    valeur = prochain_identifiant(blacklist, nb_blacklist);
    if (valeur > prochain)
    {
        prochain = valeur;
    }

    return prochain;
}

int main(void)
{
    int Taille_Tab = 0;
    int N1 = 0;
    int N2 = 0;
    int choix;
    int identifiant;
    int index;
    char rep[4];

    charger_contacts("repertoire.txt", Tab_contact, &Taille_Tab);
    charger_contacts("favoris.txt", Tab_favoris, &N1);
    charger_contacts("blacklist.txt", Tab_blacklist, &N2);

    IdentifiantG = calculer_prochain_id(
        Tab_contact,
        Taille_Tab,
        Tab_favoris,
        N1,
        Tab_blacklist,
        N2
    );

    afficher_date_heure();

    do
    {
        printf("\n***********************************");
        printf("\n 1. Saisir plusieurs contacts");
        printf("\n 2. Ajouter un contact");
        printf("\n 3. Rechercher un contact");
        printf("\n 4. Modifier un contact");
        printf("\n 5. Supprimer un contact");
        printf("\n 6. Afficher les contacts");
        printf("\n 7. Liste des contacts favoris");
        printf("\n 8. Liste des contacts bloques");
        printf("\n 0. Quitter");
        printf("\n***********************************");
        printf("\nIntroduire votre choix: ");
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                Saisir_tab_contact(Tab_contact, &Taille_Tab);
                break;

            case 2:
                Ajouter_contact(Tab_contact, &Taille_Tab);
                break;

            case 3:
                printf("\nIntroduire l'identifiant du contact a rechercher: ");
                scanf("%d", &identifiant);

                index = Rechercher_contact_par_id(Tab_contact, Taille_Tab, identifiant);
                if (index == -1)
                {
                    printf("\nContact inexistant.\n");
                }
                else
                {
                    affiche_contact(Tab_contact[index]);
                }
                break;

            case 4:
                printf("\nIntroduire l'identifiant du contact a modifier: ");
                scanf("%d", &identifiant);

                index = Rechercher_contact_par_id(Tab_contact, Taille_Tab, identifiant);
                if (index == -1)
                {
                    printf("\nContact inexistant.\n");
                }
                else
                {
                    affiche_contact(Tab_contact[index]);
                    printf("\nConfirmer la modification ? oui/non: ");
                    scanf("%3s", rep);

                    if (strcmp(rep, "oui") == 0)
                    {
                        Modifier_contact(Tab_contact, Taille_Tab, index);
                    }
                }
                break;

            case 5:
                printf("\nIntroduire l'identifiant du contact a supprimer: ");
                scanf("%d", &identifiant);

                index = Rechercher_contact_par_id(Tab_contact, Taille_Tab, identifiant);
                if (index == -1)
                {
                    printf("\nContact inexistant.\n");
                }
                else
                {
                    affiche_contact(Tab_contact[index]);
                    printf("\nConfirmer la suppression ? oui/non: ");
                    scanf("%3s", rep);

                    if (strcmp(rep, "oui") == 0)
                    {
                        Supprimer_contact(Tab_contact, &Taille_Tab, index);
                    }
                }
                break;

            case 6:
                qsort(Tab_contact, Taille_Tab, sizeof(Ctc), tri_nom);
                affiche_tab_contact(Tab_contact, Taille_Tab);
                break;

            case 7:
                menu_liste(
                    Tab_contact,
                    Taille_Tab,
                    Tab_favoris,
                    &N1,
                    "favoris",
                    "favoris.txt"
                );
                break;

            case 8:
                menu_liste(
                    Tab_contact,
                    Taille_Tab,
                    Tab_blacklist,
                    &N2,
                    "contacts bloques",
                    "blacklist.txt"
                );
                break;

            case 0:
                break;

            default:
                printf("\nChoix invalide.\n");
                break;
        }
    }
    while (choix != 0);

    if (!sauvegarder_contacts("repertoire.txt", Tab_contact, Taille_Tab))
    {
        printf("\nErreur lors de la sauvegarde du repertoire.\n");
    }

    if (!sauvegarder_contacts("favoris.txt", Tab_favoris, N1))
    {
        printf("\nErreur lors de la sauvegarde des favoris.\n");
    }

    if (!sauvegarder_contacts("blacklist.txt", Tab_blacklist, N2))
    {
        printf("\nErreur lors de la sauvegarde de la blacklist.\n");
    }

    return 0;
}
