#include <pthread.h>

#include "synchro.h"
#include "ensitheora.h"


bool fini;

/* les variables pour la synchro, ici */

pthread_mutex_t hashmutex;


/* l'implantation des fonctions de synchro ici */
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
}

void attendreTailleFenetre() {
}

void signalerFenetreEtTexturePrete() {
}

void attendreFenetreTexture() {
}

void debutConsommerTexture() {
}

void finConsommerTexture() {
}


void debutDeposerTexture() {
}

void finDeposerTexture() {
}

void inithashmutex()
{
  pthread_mutex_init(&hashmutex, NULL);
}

void lockhashmutex()
{
  pthread_mutex_lock(&hashmutex);
}

void unlockhashmutex()
{
  pthread_mutex_unlock(&hashmutex);
}

void destroyhashmutex()
{
  pthread_mutex_destroy(&hashmutex);
}
