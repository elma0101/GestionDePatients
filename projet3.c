#include"projet3.h"
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>


void gotoxy(int x,int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
int comparer_date(date date1,date date2)
{
    if(date1.annee>date2.annee || (date1.annee == date2.annee && strcmp(date1.mois,date2.mois)==1) || (date1.annee==date2.annee && strcmp(date1.mois,date2.mois)==0 && date1.jour>date2.jour) || (date1.annee==date2.annee && strcmp(date1.mois,date2.mois)==0 && date1.jour==date2.jour && date1.heure>date2.heure)|| (date1.annee==date2.annee && strcmp(date1.mois,date2.mois)==0 && date1.jour==date2.jour && date1.heure==date2.heure &&date1.minute>date2.minute)==0 )
        return 1;
    else if(date1.annee==date2.annee && strcmp(date1.mois,date2.mois)==0 && date1.jour==date2.jour && date1.heure==date2.heure &&date1.minute==date2.minute)
        return 0;
    return -1;
}
int comparer_date_2(date date1 ,date date2)
{
    if(date1.annee==date2.annee && strcmp(date1.mois,date2.mois)==0 && date1.jour==date2.jour)
        return FALSE;
    return TRUE;
}
liste_patient* lire_fichier_patient() //valide
{
    FILE *fpat;
    liste_patient *lst_pat=NULL,*nv=malloc(sizeof(liste_patient)),*temp;


    fpat=fopen("patients.txt","r");

    while(fscanf(fpat,"%s %s %d %s %s %s %d",nv->pat.nom,nv->pat.prenom,&nv->pat.tel,nv->pat.CIN,nv->pat.email,nv->pat.etat_civile,&nv->pat.age)!=EOF)
    {

        nv->precedent=NULL;
        nv->suivant=lst_pat;
        lst_pat=nv;
        nv=malloc(sizeof(liste_patient));

    }

    fclose(fpat);

    return lst_pat;
}

list_consult* lire_fichier_consultation() //valide
{
    FILE *fcons;
    list_consult *lst_cons=NULL,*nv=malloc(sizeof(list_consult)),*temp;


    fcons=fopen("consultations.txt","r");

    while(fscanf(fcons,"%d %s %d %d %d %s %s %d %s %s %s %d %s",&nv->consult.date_consult.jour,nv->consult.date_consult.mois,&nv->consult.date_consult.annee,&nv->consult.date_consult.heure,&nv->consult.date_consult.minute,nv->consult.pat.nom,nv->consult.pat.prenom,&nv->consult.pat.tel,nv->consult.pat.CIN,nv->consult.pat.email,nv->consult.pat.etat_civile,&nv->consult.pat.age,nv->consult.etat)!=EOF)
    {

        nv->precedent=NULL;
        nv->suivant=lst_cons;
        lst_cons=nv;
        nv=malloc(sizeof(list_consult));

    }

    fclose(fcons);

    return lst_cons;
}

//fonction de saisie

patient saisir_patient() //valide
{
    patient pat1;

    system("cls");
    getchar();
    printf("Nom : ");
    gets(pat1.nom);
    printf("Prenom : ");
    gets(pat1.prenom);
    printf("Telephone : ");
    scanf("%d",&pat1.tel);
    printf("CIN : ");
    getchar();
    gets(pat1.CIN);
    printf("Email : ");
    gets(pat1.email);
    printf("Etat civil : ");
    gets(pat1.etat_civile);
    printf("Age : ");
    scanf("%d",&pat1.age);

    return pat1;
}

consultation saisir_consultation() //valide
{
    consultation cons1;

    system("cls");
    printf("Date (jj/mm/aa hh:mm): ");
    scanf("%d%s%d%d%d",&cons1.date_consult.jour,cons1.date_consult.mois,&cons1.date_consult.annee,&cons1.date_consult.heure,&cons1.date_consult.minute);
    printf("Nom patient : ");
    getchar();
    gets(cons1.pat.nom);
    printf("Prenom patient : ");
    gets(cons1.pat.prenom);
    printf("Telephone  : ");
    scanf("%d",&cons1.pat.tel);
    printf("CIN : ");
    getchar();
    gets(cons1.pat.CIN);
    printf("Email : ");
    gets(cons1.pat.email);
    printf("Etat civil : ");
    gets(cons1.pat.etat_civile);
    printf("Age : ");
    scanf("%d",&cons1.pat.age);
    printf("Etat : ");
    scanf("%s",cons1.etat);

    return cons1;

}

//fonction d ajout

liste_patient* ajouter_patient(liste_patient* lst_pat,patient pat1) //valide
{
    liste_patient *courant=lst_pat,*nv=malloc(sizeof(liste_patient)),*prev=NULL;

    while(courant!=NULL && strcmp(courant->pat.nom,pat1.nom)==-1)
    {
        prev=courant;
        courant=courant->suivant;
    }


    nv->pat=pat1;
    nv->precedent=prev;
    nv->suivant=courant;

    if(prev==NULL)
    {
        lst_pat=nv;
        if(courant!=NULL)
            courant->precedent=nv;
    }
    else
    {

        if(courant!=NULL)
            courant->precedent=nv;

        prev->suivant=nv;

    }



    return lst_pat;

}


list_consult* ajouter_consultation(list_consult* lst_cons,consultation cons1) //valide
{
    list_consult *courant=lst_cons,*nv=malloc(sizeof(list_consult)),*prev=NULL;

    while(courant!=NULL && comparer_date(courant->consult.date_consult,cons1.date_consult)==-1)
    {
        prev=courant;
        courant=courant->suivant;
    }

    nv->consult=cons1;
    nv->precedent=prev;
    nv->suivant=courant;


    if(prev==NULL)
    {
        lst_cons=nv;
        if(courant!=NULL)
            courant->precedent=nv;
    }
    else
    {
        if(courant!=NULL)
            courant->precedent=nv;
        prev->suivant=nv;
    }

    return lst_cons;
}

//fonction de suppression

liste_patient* supprimer_patient(liste_patient* lst_pat)
{
    liste_patient *courant=lst_pat,*aide,*prev=NULL;
    char *CIN=malloc(10*sizeof(char));

    system("cls");

    printf("CIN : ");
    gets(CIN);


    while(courant!=NULL && strcmp(CIN,courant->pat.CIN)!=0)
    {
        prev=courant;
        courant=courant->suivant;
    }

    if(courant==NULL)
        return FALSE;

    aide=courant;
    if(prev==NULL)
    {

        lst_pat=lst_pat->suivant;
        if(courant->suivant!=NULL)
         lst_pat->precedent=NULL;

    }
    else
    {
        prev->suivant=courant->suivant;
        if(courant->suivant!=NULL)
            courant->suivant->precedent=prev;
    }

    free(aide);

    return lst_pat;
}

list_consult* supprimer_consultation(list_consult* lst_cons)
{
    list_consult *courant=lst_cons,*aide,*prev=NULL;
    char *nom=malloc(20*sizeof(char));
    int choix;
    date date_ver;

    system("cls");
    printf("SUPPRIMER PAR : \n");
    printf("1.Nom du patient \n");
    printf("2.Date de consultation \n");
    scanf("%d",&choix);

  switch(choix)
   {
     case 1 :
        system("cls");
        getchar();
        printf("NOM DU PATIENT :  ");
        gets(nom);
        while(courant!=NULL && strcmp(nom,courant->consult.pat.nom)!=0 )
        {
            prev=courant;
            courant=courant->suivant;
        }
        break;
    case 2 :
        system("cls");
        printf("DATE DE CONSULTATION (jj/mm/aa)  :  ");
        scanf("%d%s%d",&date_ver.jour,date_ver.mois,&date_ver.annee);
        while(courant!=NULL && comparer_date_2(courant->consult.date_consult,date_ver)!=0 )
        {
            prev=courant;
            courant=courant->suivant;
        }
        break;
    }

    if(courant==NULL)
        return lst_cons;



    if(prev==NULL)
    {
        aide=lst_cons;
        lst_cons=lst_cons->suivant;
        if(courant->suivant!=NULL)
         lst_cons->precedent=NULL;

    }
    else
    {
        aide=courant;
        prev->suivant=courant->suivant;
        if(courant->suivant!=NULL)
         courant->suivant->precedent=prev;
    }

    free(aide);

    return lst_cons;
}

//fonction de recherche

int chercher_patient_nom(liste_patient* lst_pat)
{
    liste_patient *courant=lst_pat;
    char *nom=malloc(20*sizeof(char));

    system("cls");
    printf("NOM DU PATIENT :  ");
    gets(nom);

    while(courant!=NULL && strcmp(nom,courant->pat.nom)!=0)
        courant=courant->suivant;

    if(courant==NULL)
        return FALSE;

    printf("\n%-10s %-15s 0%-10d %-10s %-30s %-15s %-10d \n\n",courant->pat.nom,courant->pat.prenom,courant->pat.tel,courant->pat.CIN,courant->pat.email,courant->pat.etat_civile,courant->pat.age);
    return TRUE;

}

int chercher_patient_CIN(liste_patient* lst_pat)
{
    liste_patient *courant=lst_pat;
    char *CIN=malloc(10*sizeof(char));

    system("cls");
    printf("CIN DU PATIENT :  ");
    gets(CIN);

    while(courant!=NULL && strcmp(CIN,courant->pat.CIN)!=0)
        courant=courant->suivant;

    if(courant==NULL)
        return FALSE;

    printf("\n%-10s %-15s 0%-10d %-10s %-30s %-15s %-10d \n\n",courant->pat.nom,courant->pat.prenom,courant->pat.tel,courant->pat.CIN,courant->pat.email,courant->pat.etat_civile,courant->pat.age);
    return TRUE;

}

//fonction d'affichage

void afficher_consultation_nom_CIN(list_consult* lst_cons) //valide
{
    list_consult *courant=lst_cons;
    int choix;
    char *CIN=malloc(10*sizeof(char)),*nom=malloc(20*sizeof(char));

    system("cls");
    gotoxy(40,2);
    printf("\xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB Gestion de Patients \xDB\xDB\xDB\xDB\xDB\xDB\xDB\xDB");
    gotoxy(15,5);
    printf("\xDB AFFICHER PAR : \n\n");
    printf("\t\t 1.NOM \n");
    printf("\t\t 2.CIN \n\n\t\t\t votre choix :");
    scanf("%d",&choix);

    switch(choix)
    {
    case 1 :
        system("cls");
        gotoxy(15,7);
        printf("\xDB NOM DU PATIENT :  ");
        getchar();
        gets(nom);
        break;
    case 2 :
        system("cls");
        gotoxy(15,7);
        printf("\xDB CIN du patient :  ");
        scanf("%s",CIN);
        break;
    }


    while(courant!=NULL )
    {
        if(strcmp(courant->consult.pat.nom,nom)==0 || strcmp(courant->consult.pat.CIN,CIN)==0)
        {
           printf("\n\t\tDATE \t\t NOM \t\t PRENOM \t TELEPHONE \t CIN \t\t GMAIL \t\t E.CIVILE \t AGE \t ETAT \n\n");
           printf("\n\t\t%d %s %d  %d:%d %-30s%-20s0%-20d%-20s%-20s%-30s%-20d%-20s \n\n",courant->consult.date_consult.jour,courant->consult.date_consult.mois,courant->consult.date_consult.annee,courant->consult.date_consult.heure,courant->consult.date_consult.minute,courant->consult.pat.nom,courant->consult.pat.prenom,courant->consult.pat.tel,courant->consult.pat.CIN,courant->consult.pat.email,courant->consult.pat.etat_civile,courant->consult.pat.age,courant->consult.etat);
        }

        courant=courant->suivant;
    }


}

void afficher_consultation_jour(list_consult* lst_cons) //valide
{
    list_consult *courant=lst_cons,*lst_cons_jour=NULL,*courant2;
    consultation aide;
    int choix;
    date date_ver;

    system("cls");
    printf("La date (jj/mm/aa) :  ");
    scanf("%d%s%d",&date_ver.jour,date_ver.mois,&date_ver.annee);

    while(courant!=NULL )
    {
        if(strcmp(courant->consult.date_consult.mois,date_ver.mois)==0 && courant->consult.date_consult.jour==date_ver.jour && courant->consult.date_consult.annee==date_ver.annee )
            lst_cons_jour=ajouter_consultation(lst_cons_jour,courant->consult);
        courant=courant->suivant;
    }

    courant=lst_cons_jour;

    while(courant->suivant!=NULL)
    {
        courant2=courant->suivant;
        while(courant2!=NULL)
        {
            if(courant2->consult.date_consult.heure<courant->consult.date_consult.heure || (courant2->consult.date_consult.heure==courant->consult.date_consult.heure && courant2->consult.date_consult.minute<courant->consult.date_consult.minute))
            {
                aide=courant2->consult;
                courant2->consult=courant->consult;
                courant->consult=aide;
            }
            courant2=courant2->suivant;
        }
        courant=courant->suivant;
    }

    courant=lst_cons_jour;

    while(courant!=NULL)
    {
        printf("\n%-2d %-10s %-4d  %-2d:%-2d %-10s %-15s 0%-10d %-10s %-30s %-15s %-10d %-15s \n\n",courant->consult.date_consult.jour,courant->consult.date_consult.mois,courant->consult.date_consult.annee,courant->consult.date_consult.heure,courant->consult.date_consult.minute,courant->consult.pat.nom,courant->consult.pat.prenom,courant->consult.pat.tel,courant->consult.pat.CIN,courant->consult.pat.email,courant->consult.pat.etat_civile,courant->consult.pat.age,courant->consult.etat);
        courant=courant->suivant;
    }


}

void afficher_consultation_annule(list_consult* lst_cons)
{

    list_consult *courant=lst_cons,*lst_cons_annule=NULL,*courant2;
    consultation aide;
    int choix;
    date date_ver;

    system("cls");
    printf("La date (jj/mm/aa) :  ");
    scanf("%d%s%d",&date_ver.jour,date_ver.mois,&date_ver.annee);

    while(courant!=NULL )
    {
        if(strcmp(courant->consult.date_consult.mois,date_ver.mois)==0 && courant->consult.date_consult.jour==date_ver.jour && courant->consult.date_consult.annee==date_ver.annee && strcmp(courant->consult.etat,"annule")==0)
            lst_cons_annule=ajouter_consultation(lst_cons_annule,courant->consult);
        courant=courant->suivant;
    }

    courant=lst_cons_annule;

    while(courant->suivant!=NULL)
    {
        courant2=courant->suivant;
        while(courant2!=NULL)
        {
            if(courant2->consult.date_consult.heure<courant->consult.date_consult.heure || (courant2->consult.date_consult.heure==courant->consult.date_consult.heure && courant2->consult.date_consult.minute<courant->consult.date_consult.minute))
            {
                aide=courant2->consult;
                courant2->consult=courant->consult;
                courant->consult=aide;
            }
            courant2=courant2->suivant;
        }
        courant=courant->suivant;
    }

    courant=lst_cons_annule;

    while(courant!=NULL)
    {
        printf("\n%-2d %-10s %-4d  %-2d:%-2d %-10s %-15s 0%-10d %-10s %-30s %-15s %-10d %-15s \n\n",courant->consult.date_consult.jour,courant->consult.date_consult.mois,courant->consult.date_consult.annee,courant->consult.date_consult.heure,courant->consult.date_consult.minute,courant->consult.pat.nom,courant->consult.pat.prenom,courant->consult.pat.tel,courant->consult.pat.CIN,courant->consult.pat.email,courant->consult.pat.etat_civile,courant->consult.pat.age,courant->consult.etat);
        courant=courant->suivant;
    }
}

void afficher_patient(liste_patient *lst_pat)  //valide
{
    liste_patient *courant=lst_pat;

    system("cls");
    while(courant!=NULL)
    {
        printf("\n%-10s %-15s 0%-10d %-10s %-30s %-15s %-10d \n\n",courant->pat.nom,courant->pat.prenom,courant->pat.tel,courant->pat.CIN,courant->pat.email,courant->pat.etat_civile,courant->pat.age);
        courant=courant->suivant;
    }
}

void afficher_consultation(list_consult* lst_cons) //valide
{
    list_consult *courant=lst_cons;


    system("cls");

    while(courant!=NULL )
    {

        printf("\n%-2d %-10s %-4d  %-2d:%-2d %-10s %-15s 0%-10d %-10s %-30s %-15s %-10d %-15s \n\n",courant->consult.date_consult.jour,courant->consult.date_consult.mois,courant->consult.date_consult.annee,courant->consult.date_consult.heure,courant->consult.date_consult.minute,courant->consult.pat.nom,courant->consult.pat.prenom,courant->consult.pat.tel,courant->consult.pat.CIN,courant->consult.pat.email,courant->consult.pat.etat_civile,courant->consult.pat.age,courant->consult.etat);
        courant=courant->suivant;
    }


}

//fonction de sauvegarde

void sauvegarder_patients(liste_patient *lst_pat)
{
    FILE *fp;
    liste_patient *courant=lst_pat;


    fp=fopen("patients.txt","w");

    while(courant!=NULL)
    {
        fprintf(fp,"%s %s %d %s %s %s %d \n",courant->pat.nom,courant->pat.prenom,courant->pat.tel,courant->pat.CIN,courant->pat.email,courant->pat.etat_civile,courant->pat.age);
        courant=courant->suivant;
    }

    fclose(fp);

}
void sauvegarder_consultations(list_consult *lst_cons)
{
    FILE *fp;
    list_consult *courant=lst_cons;


    fp=fopen("consulations.txt","w");

    while(courant!=NULL)
    {
        fprintf(fp,"%d %s %d %d %d %s %s %d %s %s %s %d %s \n",courant->consult.date_consult.jour,courant->consult.date_consult.mois,courant->consult.date_consult.annee,courant->consult.date_consult.heure,courant->consult.date_consult.minute,courant->consult.pat.nom,courant->consult.pat.prenom,courant->consult.pat.tel,courant->consult.pat.CIN,courant->consult.pat.email,courant->consult.pat.etat_civile,courant->consult.pat.age,courant->consult.etat);
        courant=courant->suivant;
    }

    fclose(fp);

}





