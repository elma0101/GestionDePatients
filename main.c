#include"projet3.h"
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>



int menu()
{
    int choix;

    system("cls");
    gotoxy(40,2);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB Gestion de Patients \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(25,6);
    printf("-----------------------------------------------------------");
    gotoxy(25,7);
    printf("\xDB 1-  Afficher la liste des patients                       \xDB");
    gotoxy(25,8);
    printf("\xDB 2-  Afficher les consultations d'un patient(par CIN/nom) \xDB");
    gotoxy(25,9);
    printf("\xDB 3-  Afficher les consultations d'un patient(par jour)    \xDB");
    gotoxy(25,10);
    printf("\xDB 4-  Afficher les consultations annulees (par jour)       \xDB");
    gotoxy(25,11);
    printf("-----------------------------------------------------------");
    gotoxy(25,12);
    printf("\xDB 5-  Ajouter un patient                                   \xDB");
    gotoxy(25,13);
    printf("\xDB 6-  Ajouter une consultation                             \xDB");
    gotoxy(25,14);
    printf("-----------------------------------------------------------");
    gotoxy(25,15);
    printf("\xDB 7-  Supprimer un patient                                 \xDB");
    gotoxy(25,16);
    printf("\xDB 8-  Supprimer une consultation                           \xDB");
    gotoxy(25,17);
    printf("-----------------------------------------------------------");
    gotoxy(25,18);
    printf("\xDB 9-  Chercher un patient par nom                          \xDB");
    gotoxy(25,19);
    printf("\xDB 10- Chercher un patient par CIN                          \xDB");
    gotoxy(25,20);
    printf("-----------------------------------------------------------");
    gotoxy(25,21);
    printf("\xDB 0- Quitter                                               \xDB");
    gotoxy(25,22);
    printf("-----------------------------------------------------------");
    gotoxy(45,25);
    printf("votre choix  :  ");
    scanf("%d",&choix);

    return choix;
}
int main()
{
    liste_patient *lst_pat=NULL;
    list_consult *lst_cons=NULL;
    int choix;
    patient pat;
    consultation cons;

    lst_pat=lire_fichier_patient();
    lst_cons=lire_fichier_consultation();



    do{

      choix=menu();

      switch(choix)
      {
        case 1 :
              afficher_patient(lst_pat);
              system("pause");
              break;
        case 2 :
              afficher_consultation(lst_cons);
              system("pause");
              break;
        case 3 :
              afficher_consultation_jour(lst_cons);
              system("pause");
              break;
        case 4 :
              afficher_consultation_annule(lst_cons);
              system("pause");
              break;
        case 5 :
              pat=saisir_patient();
              lst_pat=ajouter_patient(lst_pat,pat);
              break;
        case 6 :
              cons=saisir_consultation();
              lst_cons=ajouter_consultation(lst_cons,cons);
              break;
        case 7 :
              getchar();
              lst_pat=supprimer_patient(lst_pat);
              break;
        case 8 :
              lst_cons=supprimer_consultation(lst_cons);
              break;
        case 9 :
              getchar();
              chercher_patient_nom(lst_pat);
              system("pause");
              break;
        case 10 :
              getchar();
              chercher_patient_CIN(lst_pat);
              system("pause");
              break;

      }

    }while(choix!=0);

    sauvegarder_patients( lst_pat);
    sauvegarder_consultations( lst_cons);

    return 0;
}
