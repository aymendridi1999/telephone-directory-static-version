#include <stdio.h>
#include <stdlib.h>
#include "contact.h"
#include <string.h>
#include <time.h>

int IdentifiantG=0;
Ctc Tab_contact [100];
Ctc Tab_favoris [100];
Ctc Tab_blacklist [100];
int main()
{   Ctc Tab_contact [100];
    int Taille_Tab=0;
    int id=-1;
    int i;
    int N1=0;
    int N2=0;
    int rech=-1;
    int choix;
    int choix2;
    int choix3;
    char rep[3];
    FILE* fichier;
    FILE* fichier2;
    FILE* fichier3;
    fichier=fopen("répertoire.txt","rt");
    if (fichier==NULL)
    {
        printf("\n fichier inexistant!!!");

    }
    else
    {i=Taille_Tab;
    while(!feof(fichier))
    {
        fscanf(fichier,"%d %d %s %s %d %d %s %s %d\n",&Tab_contact[i].Identifiant, &Tab_contact[i].CIN, Tab_contact[i].Nom,Tab_contact[i].Prenom,&Tab_contact[i].numero,&Tab_contact[i].adresse.num, Tab_contact[i].adresse.rue, Tab_contact[i].adresse.ville, &Tab_contact[i].adresse.code);
    i++;
    }
    Taille_Tab=i;
    fclose(fichier);
    }


   fichier2=fopen("favoris.txt","rt");
    if (fichier2==NULL)
    {
        printf("\n fichier inexistant!!!");

    }
    else
    {i=N1;
    while(!feof(fichier2))
    {
    fscanf(fichier2,"%d %d %s %s %d %d %s %s %d\n",&Tab_favoris[i].Identifiant, &Tab_favoris[i].CIN, Tab_favoris[i].Nom,Tab_favoris[i].Prenom,&Tab_favoris[i].numero,&Tab_favoris[i].adresse.num, Tab_favoris[i].adresse.rue, Tab_favoris[i].adresse.ville, &Tab_favoris[i].adresse.code);

    i++;
    }
    N1=i;
    fclose(fichier2);
    }


    fichier3=fopen("blacklist.txt","rt");
    if (fichier3==NULL)
    {
        printf("\n fichier inexistant!!!");

    }
    else
    {i=N2;
    while(!feof(fichier3))
    {
    fscanf(fichier3,"%d %d %s %s %d %d %s %s %d\n",&Tab_blacklist[i].Identifiant, &Tab_blacklist[i].CIN, Tab_blacklist[i].Nom,Tab_blacklist[i].Prenom,&Tab_blacklist[i].numero,&Tab_blacklist[i].adresse.num, Tab_blacklist[i].adresse.rue, Tab_blacklist[i].adresse.ville, &Tab_blacklist[i].adresse.code);

    i++;
    }
    N2=i;
    fclose(fichier3);
    }

     time_t secondes;
    struct tm instant;

    time(&secondes);
    instant=*localtime(&secondes);



    printf("%d/%d ; %d:%d:%d\n", instant.tm_mday+1, instant.tm_mon+1, instant.tm_hour, instant.tm_min, instant.tm_sec);
    while(1)
    {
        printf("\n***********************************");
        printf("\n 1. Saisir un tableau de contact");
        printf("\n 2. Ajouter un contact");
        printf("\n 3. Rechercher un contact");
        printf("\n 4. Modifier un contact");
        printf("\n 5. Supprimer un contact");
        printf("\n 6. Afficher tableau de contact");
        printf("\n 7. Liste des contacts favoris");
        printf("\n 8. Liste des contacts bloques");
        printf("\n 0. Quitter");
        printf("\n***********************************");
        printf("\n Introduire votre choix: ");
        scanf ("%d",&choix);
      switch(choix)
      {
        case 1:
        {   Saisir_tab_contact(Tab_contact,&Taille_Tab);
            break;
        }
        case 2:
        {   Ajouter_contact(Tab_contact,&Taille_Tab);
            break;
        }
        case 3:
        {   printf ("\n introduire l'identifiant du contact à rechercher: ");
            scanf ("%d", &id);
            rech=Rechercher_contact(Tab_contact,Taille_Tab,id);
            if (rech ==-1)
                printf ("\n contact inexistant");
            else
                affiche_contact(Tab_contact[rech]);
            break;
        }
        case 4:
        {   printf ("\n introduire l'identifiant du contact à modifier: ");
            scanf ("%d", &id);
            rech=Rechercher_contact(Tab_contact,Taille_Tab,id);
            if (rech ==-1)
                printf ("\n etudiant inexistant");
            else
                {
                    affiche_contact(Tab_contact[rech]);
                    printf("\n vous êtes sûre de vouloir modifier ce contact? oui/non: ");
                    scanf ("%s", rep);
                    if (strcmp(rep,"oui")==0)
                    {
                        Modifier_contact(Tab_contact,rech);
                    }


                }
            break;
        }
        case 5:
        { printf ("\n introduire l'identifiant du contact à supprimer: ");
            scanf ("%d", &id);
            rech=Rechercher_contact(Tab_contact,Taille_Tab,id);
            if (rech ==-1)
                printf ("\n contact inexistant");
            else
                {
                    affiche_contact(Tab_contact[rech]);
                    printf("\n vous êtes sûre de vouloir supprimer ce contact? oui/non: ");
                    scanf ("%s", rep);
                    if (strcmp(rep,"oui")==0)
                    {
                    Supprimer_contact(Tab_contact,&Taille_Tab,rech);
                    }


                }
            break;
        }
        case 6:
        {   qsort(Tab_contact,Taille_Tab, sizeof(Ctc), tri_nom);
            affiche_tab_contact(Tab_contact,Taille_Tab);
            break;
        }
        case 7:
            {


    while(1)
    {
        printf("\n***********************************");
        printf("\n 1. ajouter à la liste des favoris");
        printf("\n 2. afficher la liste des favoris");
        printf("\n 3. Supprimer un contact de la liste des favoris");
        printf("\n 0. Quitter");
        printf("\n***********************************");
        printf("\n Introduire votre choix: ");
        scanf ("%d",&choix2);
        switch(choix2)
        {

         case 1:
        {Ctc c;
             int i;

             i=N1;

               c=saisir_contact();
               Tab_favoris[i]=c;
                i++;


                 N1=i;
                 break;
        }
         case 2:
            {
                affiche_tab_contact(Tab_favoris,N1);
                break;

            }
         case 3:
            {
               printf ("\n introduire l'identifiant du contact à supprimer: ");
            scanf ("%d", &id);
            rech=Rechercher_contact(Tab_favoris,N1,id);
            if (rech ==-1)
                printf ("\n contact inexistant");
            else
                {
                    affiche_contact(Tab_favoris[rech]);
                    printf("\n vous êtes sûre de vouloir supprimer ce contact? oui/non: ");
                    scanf ("%s", rep);
                    if (strcmp(rep,"oui")==0)
                    {
                    Supprimer_contact(Tab_favoris,&N1,rech);

                    }


                }
            break;
            }
         case 0:
            {


                  fichier2=fopen("favoris.txt","wt");
        if (fichier2==NULL)

           {

            printf("erreur de creation de fichier !!!");
           }
        else
        {
            for(i=0;i<N1;i++)
             {

               fprintf(fichier,"%d %d %s %s %d %d %s %s %d\n",Tab_favoris[i].Identifiant, Tab_favoris[i].CIN, Tab_favoris[i].Nom,Tab_favoris[i].Prenom,Tab_favoris[i].numero,Tab_favoris[i].adresse.num, Tab_favoris[i].adresse.rue, Tab_favoris[i].adresse.ville, Tab_favoris[i].adresse.code);

             }
            fclose(fichier2);
        }
            exit(0);
        }
        default: printf("\n Choix erronée");
      }

            }


            }
         case 8:
             {



    while(1)
    {
        printf("\n***********************************");
        printf("\n 1. ajouter à la liste des contact bloques");
        printf("\n 2. afficher la liste des contacts bloques");
        printf("\n 0. Quitter");
        printf("\n***********************************");
        printf("\n Introduire votre choix: ");
        scanf ("%d",&choix3);
        switch(choix3)
        {
        case 1:
        {
            Ctc c;
            int i;

             i=N2;

             c=saisir_contact();
              Tab_blacklist[i]=c;
              i++;

                N2=i;
               break;}

        case 2:
            {
               affiche_tab_contact(Tab_blacklist,N2) ;
               break;
            }
        case 0:
             {fichier3=fopen("blacklist.txt","wt");
        if (fichier3==NULL)

           {

            printf("erreur de creation de fichier !!!");
           }
        else
        {
            for(i=0;i<N2;i++)
             {

               fprintf(fichier,"%d %d %s %s %d %d %s %s %d\n",Tab_blacklist[i].Identifiant, Tab_blacklist[i].CIN, Tab_blacklist[i].Nom,Tab_blacklist[i].Prenom,Tab_blacklist[i].numero,Tab_blacklist[i].adresse.num, Tab_blacklist[i].adresse.rue, Tab_blacklist[i].adresse.ville, Tab_blacklist[i].adresse.code);

             }
            fclose(fichier3);
        }
            exit(0);
        }
        default: printf("\n Choix erronée");
      }

            }





    case 0:
        {   fichier=fopen("répertoire.txt","wt");
        if (fichier==NULL)
           {
            printf("erreur de creation de fichier !!!");
           }
        else
        {
            for(i=0;i<Taille_Tab;i++)
             {

               fprintf(fichier,"%d %d %s %s %d %d %s %s %d\n",Tab_contact[i].Identifiant, Tab_contact[i].CIN, Tab_contact[i].Nom,Tab_contact[i].Prenom,Tab_contact[i].numero,Tab_contact[i].adresse.num, Tab_contact[i].adresse.rue, Tab_contact[i].adresse.ville, Tab_contact[i].adresse.code);

             }
            fclose(fichier);
        }
            exit(0);
        }
        default: printf("\n Choix erronée");
      }



    }
    }

    return 0;

}
