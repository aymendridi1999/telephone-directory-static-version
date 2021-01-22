
#include "contact.h"
#include <stdio.h>
#include <string.h>
extern int IdentifiantG;
extern Ctc Tab_contact;

Adr saisir_adresse()
{
    Adr a;
    printf ("\n Introduire le numero de la maison: ");
    scanf("%d", &a.num);
    printf ("\n Introduire le code postal:");
    scanf ("%d",&a.code);
    printf ("\n Introduire le nom de la rue:");
    scanf ("%s",a.rue);
    printf("\n Introduire le nom de la ville:");
    scanf("%s",a.ville);





return a;
}




Ctc saisir_contact()
{
    Ctc c;

    c.Identifiant=IdentifiantG++;
    printf ("\n Introduire le nom:");
    scanf ("%s",c.Nom);
    printf ("\n Introduire le prenom:");
    scanf ("%s",c.Prenom);
    printf("\n Introduire le numero:");
    scanf("%d",&c.numero);
    printf("\n Introduire le numero de CIN:");
    do
        {scanf("%d",&c.CIN);}
    while (c.CIN<10000000||c.CIN>99999999);

    printf("\n Introduire l'adresse:");
    c.adresse=saisir_adresse();





return c;
}


void Saisir_tab_contact(Ctc Tab_contact[],int* N)
{Ctc c;
int i;
char Rep[3];
i=*N;
do
{do{
    c=saisir_contact();}
    while (Rechercher_contact(Tab_contact, *N, c.numero)==-10);
    Tab_contact[i]=c;
    i++;
  printf("\n voulez vous ajouter un autre contact Oui/Non: ");
  scanf ("%s",Rep);
}while (!strcmp(Rep,"oui"));
*N=i;
}
void Ajouter_contact(Ctc Tab_contact[],int* N)
{Ctc c;
int i;

i=*N;

  c=saisir_contact();
  Tab_contact[i]=c;
  i++;

*N=i;
}
void affiche_adresse(Adr a)
{
printf("\n *******\n Numero de la maison: %d", a.num);
printf ("\n Rue: %s",a.rue);
printf ("\n Ville: %s", a.ville);
printf ("\n Code Postal: %d", a.code);

}
void affiche_contact(Ctc c)
{
printf("\n *******\n Identifiant: %d", c.Identifiant);
printf ("\n Nom: %s",c.Nom);
printf ("\n Prénom: %s", c.Prenom);
printf ("\n Numero: %d", c.numero);
affiche_adresse(c.adresse);

}



void affiche_tab_contact(Ctc Tab_contact[],int N)
{int i;
for (i=0;i<N;i++)
{
    affiche_contact(Tab_contact[i]);
}

}

int Rechercher_contact(Ctc Tab_contact[], int N,int numr )
{   int i;
    for (i=0;i<N;i++)
    {
        if (Tab_contact[i].numero==numr)
            return i;
    }

return -1;
}
int Rechercher_numero(Ctc Tab_contact[], int N,int numr )
{   int i;
    for (i=0;i<N;i++)
    {
        if (Tab_contact[i].numero==numr)
            return 1;
    }

return -1;
}
void Modifier_contact(Ctc Tab_contact[],int iden)
{   int choix;
    printf ("\n 1. Modifier le nom");
    printf ("\n 2. Modifier le prenom");
    printf ("\n 3. Modifier le numero");
    printf("\n Introduire votre Choix: ");
    scanf("%d", &choix);
    switch(choix)
    {   case 1:
        {   printf ("\n introduire le nom: ");
            scanf ("%s",Tab_contact[iden].Nom );
            break;
        }
        case 2:
        {   printf ("\n introduire le prenom: ");
            scanf ("%s",Tab_contact[iden].Prenom);
            break;
        }
        case 3:
        {   printf ("\n introduire le numero: ");
            scanf ("%d",&Tab_contact[iden].numero );
            break;
        }


        default: printf ("\n choix erronée");

    }




}


void Supprimer_contact(Ctc Tab_contact[], int* N,int id)
{   int i;
    int taille=*N;
    for (i=id;i<taille-1;i++)
    {
        Tab_contact[i]=Tab_contact[i+1];
    }
    (*N)--;
}
int tri_nom(char *str1, char *str2)
{
  while(*str1 != '\0')
  {
    str1++;
  }
  while(*str2 != '\0')
  {
    str2++;
  }
if(*str1 == *str2);
return 0 ;

}





