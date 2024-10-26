#ifndef PROJET3_H_INCLUDED
#define PROJET3_H_INCLUDED
#define FALSE 0
#define TRUE 1

typedef struct date{

 int jour,annee,heure,minute;
 char mois[15];

}date;
typedef struct patient{

  char nom[20],prenom[30],CIN[10],email[60],etat_civile[20];
  int tel,age;

}patient;

typedef struct consultation{

 date date_consult;
 patient pat;
 char etat[20];

}consultation;

typedef struct list_consultation{

  consultation consult;
  struct list_consultation *precedent,*suivant;

}list_consult;


typedef struct list_patient{

  patient pat;
  struct list_patient *precedent,*suivant;

}liste_patient;


void gotoxy(int ,int );
int comparer_date(date,date);
int comparer_date_2(date,date);
liste_patient* lire_fichier_patient();
list_consult* lire_fichier_consultation();
patient saisir_patient();
consultation saisir_consultation();
liste_patient* ajouter_patient(liste_patient*,patient );
list_consult* ajouter_consultation(list_consult*,consultation );
liste_patient* supprimer_patient(liste_patient*);
list_consult* supprimer_consultation(list_consult* );
int chercher_patient_nom(liste_patient* );
int chercher_patient_CIN(liste_patient* );
void afficher_consultation_nom_CIN(list_consult* );//par cin ou nom
void afficher_consultation_jour(list_consult* );
void afficher_consultation_annule(list_consult* );
void afficher_patient(liste_patient* );
void sauvegarder_patients(liste_patient* );
void sauvegarder_consultations(list_consult* );



#endif // PROJET3_H_INCLUDED
