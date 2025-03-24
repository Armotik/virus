//
// Created by armotik on 24/03/25.
//

#ifndef TRANSFERT_H
#define TRANSFERT_H

#define MAX_PATH_LEN 1024

// Si le programme lancé n’est pas MediaPlayer, exécute automatiquement <nom>.old
void transferer_execution_si_necessaire(const char *argv0, char **argv);

#endif // TRANSFERT_H
