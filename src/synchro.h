#ifndef SYNCHRO_H
#define SYNCHRO_H

#include <stdbool.h>
#include "ensitheora.h"

extern bool fini;


/* Les extern des variables pour la synchro ici */

/*definition des variables du moniteur*/
pthread_mutex_t mutexFenetre;
//POURQUOI NE PAS TOUT FAIRE DUN COUP?
pthread_mutex_t mutexTexture;


pthread_cond_t decodeur;
pthread_cond_t afficheur;

pthread_cond_t producteur;
pthread_cond_t consomateur;
int nb_case_pleine;

//A RAJOUTER AU DEBUT DES FCT
bool fenetre_ecrite;
bool fenetre_lu;



/* Fonctions de synchro à implanter */

void envoiTailleFenetre(th_ycbcr_buffer buffer);
void attendreTailleFenetre();

void attendreFenetreTexture();
void signalerFenetreEtTexturePrete();

void debutConsommerTexture();
void finConsommerTexture();

void debutDeposerTexture();
void finDeposerTexture();

void inithashMutex();
void lockhashMutex();
void unlockhashMutex();
void destroyhashMutex();
//mutex Fenetre
void initFenetreMutex();
void destroyFenetreMutex();

void iniConditionDecodeur();
void initConditionAfficheur();
void destroyConditionDecodeur();
void destroyConditionAfficheur();


#endif
