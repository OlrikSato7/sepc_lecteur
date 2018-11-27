#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <SDL2/SDL.h>
#include <pthread.h>

#include "stream_common.h"
#include "oggstream.h"
#include "synchro.h"


int main(int argc, char *argv[]) {
    int res;

    if (argc != 2) {
	fprintf(stderr, "Usage: %s FILE", argv[0]);
	exit(EXIT_FAILURE);
    }
    assert(argc == 2);


    // Initialisation de la SDL
    res = SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO|SDL_INIT_EVENTS);
    atexit(SDL_Quit);
    assert(res == 0);

    // start the two stream readers
    void *status;
    pthread_t theopid, vorbpid;

    inithashMutex();
    initFenetreMutex();

    pthread_create(&theopid, NULL, theoraStreamReader, argv[1]);
    pthread_create(&vorbpid, NULL, vorbisStreamReader, argv[1]);

    // wait audio thread
    pthread_join(vorbpid, &status);

    // 1 seconde de garde pour le son,
    sleep(1);

    // tuer les deux threads videos si ils sont bloqués
    pthread_cancel(theopid);
    pthread_cancel(theora2sdlthread);

    // attendre les 2 threads videos

    pthread_join(theora2sdlthread, &status);
    pthread_join(theopid, &status);




    destroyFenetreMutex();
    destroyhashMutex();


    exit(EXIT_SUCCESS);
}
