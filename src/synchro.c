#include <pthread.h>

#include "synchro.h"
#include "ensitheora.h"


bool fini;

/* les variables pour la synchro, ici */

pthread_mutex_t hashMutex;


/* l'implantation des fonctions de synchro ici */

/*decodeur utilise cete fonction pour envoyer taille fenetre*/
/*on a que deux thread ?*/
void envoiTailleFenetre(th_ycbcr_buffer buffer) {
// modifier les windows?
//on a que un consom, un poducteur?
pthread_mutex_lock(&mutexFenetre);
windowsx = buffer[0].width;
windowsy = buffer[0].height;
fenetre_ecrite = true;
/*on signal aux afficheur que la fenetre est prete */
pthread_cond_signal(&afficheur);
pthread_mutex_unlock(&mutexFenetre);

}

void attendreTailleFenetre() {
  pthread_mutex_lock(&mutexFenetre);
  //la netre-feu est pas encore la
  if (!fenetre_ecrite){
    pthread_cond_wait(&afficheur, &mutexFenetre);
  }
  pthread_mutex_unlock(&mutexFenetre);

}
//appeler juste apres avoir affiche
void signalerFenetreEtTexturePrete() {
  pthread_mutex_lock(&mutexFenetre);
  //on signal au decodeur que la fenetre est affiche
  fenetre_lu = true;
  pthread_cond_signal(&decodeur);
  pthread_mutex_unlock(&mutexFenetre);


}



void attendreFenetreTexture() {
  //apres avoir envoye la fenetre on attend que la fenetre soit affiche.
  pthread_mutex_lock(&mutexFenetre);
  if (!fenetre_lu){
    pthread_cond_wait(&decodeur, &mutexFenetre);
  }
  //on a affiche la fenetre, on peut en recrire une nouvelle.
  fenetre_lu = false;
  fenetre_ecrite = false;
  //la fenetre texture est affiche, on peut continuer.
  pthread_mutex_unlock(&mutexFenetre);

}





void debutConsommerTexture() {
}

void finConsommerTexture() {
}


void debutDeposerTexture() {
}

void finDeposerTexture() {
}

void inithashMutex()
{
  pthread_mutex_init(&hashMutex, NULL);
}



void initFenetreMutex()
{
  pthread_mutex_init(&mutexFenetre, NULL);
}

void lockhashMutex()
{
  pthread_mutex_lock(&hashMutex);
}

void unlockhashMutex()
{
  pthread_mutex_unlock(&hashMutex);
}

void destroyhashMutex()
{
  pthread_mutex_destroy(&hashMutex);
}

void destroyFenetreMutex()
{
  pthread_mutex_destroy(&mutexFenetre);
}

void initConditionAfficheur(){
  //Creer une structure moniteur = plus propre
  fenetre_ecrite = false;
  fenetre_lu = false;
  pthread_cond_init(&afficheur,NULL);

}

void iniConditionDecodeur(){
  pthread_cond_init(&decodeur,NULL);
}

void destroyConditionDecodeur(){
  pthread_cond_destroy(&decodeur);
}

void destroyConditionAfficheur(){
  pthread_cond_destroy(&afficheur);

}
