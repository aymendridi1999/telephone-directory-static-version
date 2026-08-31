#include "contact.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int IdentifiantG = 0;

static Ctc creer_contact(int id, const char *nom, const char *prenom, int numero)
{
    Ctc c;

    c.Identifiant = id;
    strcpy(c.Nom, nom);
    strcpy(c.Prenom, prenom);
    c.numero = numero;
    c.CIN = 12345678 + id;
    c.adresse.num = id + 1;
    c.adresse.code = 1000 + id;
    strcpy(c.adresse.rue, "RueTest");
    strcpy(c.adresse.ville, "Tunis");

    return c;
}

static void test_recherche(void)
{
    Ctc contacts[3];

    contacts[0] = creer_contact(2, "Zied", "Ali", 1111);
    contacts[1] = creer_contact(5, "Amine", "Sami", 2222);
    contacts[2] = creer_contact(9, "Leila", "Nour", 3333);

    assert(Rechercher_contact_par_id(contacts, 3, 5) == 1);
    assert(Rechercher_contact_par_id(contacts, 3, 99) == -1);
    assert(Rechercher_numero(contacts, 3, 3333) == 2);
    assert(Rechercher_numero(contacts, 3, 9999) == -1);
}

static void test_tri(void)
{
    Ctc contacts[3];

    contacts[0] = creer_contact(1, "Zied", "Ali", 1111);
    contacts[1] = creer_contact(2, "Amine", "Sami", 2222);
    contacts[2] = creer_contact(3, "Amine", "Ahmed", 3333);

    qsort(contacts, 3, sizeof(Ctc), tri_nom);

    assert(strcmp(contacts[0].Nom, "Amine") == 0);
    assert(strcmp(contacts[0].Prenom, "Ahmed") == 0);
    assert(strcmp(contacts[1].Nom, "Amine") == 0);
    assert(strcmp(contacts[1].Prenom, "Sami") == 0);
    assert(strcmp(contacts[2].Nom, "Zied") == 0);
}

static void test_suppression(void)
{
    Ctc contacts[3];
    int taille = 3;

    contacts[0] = creer_contact(1, "A", "A", 1111);
    contacts[1] = creer_contact(2, "B", "B", 2222);
    contacts[2] = creer_contact(3, "C", "C", 3333);

    Supprimer_contact(contacts, &taille, 1);

    assert(taille == 2);
    assert(contacts[0].Identifiant == 1);
    assert(contacts[1].Identifiant == 3);
}

static void test_prochain_identifiant(void)
{
    Ctc contacts[3];

    contacts[0] = creer_contact(4, "A", "A", 1111);
    contacts[1] = creer_contact(12, "B", "B", 2222);
    contacts[2] = creer_contact(7, "C", "C", 3333);

    assert(prochain_identifiant(contacts, 3) == 13);
    assert(prochain_identifiant(contacts, 0) == 0);
}

static void test_persistence(void)
{
    const char *fichier = "test_contacts.txt";
    Ctc origine[2];
    Ctc charges[MAX_CONTACTS];
    int taille = 0;

    origine[0] = creer_contact(3, "Amine", "Sami", 1111);
    origine[1] = creer_contact(8, "Leila", "Nour", 2222);

    assert(sauvegarder_contacts(fichier, origine, 2) == 1);
    assert(charger_contacts(fichier, charges, &taille) == 1);
    assert(taille == 2);

    assert(charges[0].Identifiant == origine[0].Identifiant);
    assert(strcmp(charges[0].Nom, origine[0].Nom) == 0);
    assert(charges[0].numero == origine[0].numero);

    assert(charges[1].Identifiant == origine[1].Identifiant);
    assert(strcmp(charges[1].Prenom, origine[1].Prenom) == 0);
    assert(charges[1].adresse.code == origine[1].adresse.code);

    remove(fichier);
}

int main(void)
{
    test_recherche();
    test_tri();
    test_suppression();
    test_prochain_identifiant();
    test_persistence();

    printf("Tous les tests sont passes.\n");
    return 0;
}
