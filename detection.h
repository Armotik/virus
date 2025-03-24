//
// Created by armotik on 24/03/25.
//

#ifndef DETECTION_H
#define DETECTION_H

#define MAX_PATH_LEN 1024

// Retourne 1 si le fichier se termine par .old
int a_extension_old(const char *filename);

// Retourne 1 si un fichier <filename>.old existe dans le répertoire courant
int fichier_old_existe(const char *filename);

// Détermine si un fichier est déjà infecté
int est_deja_infecte(const char *filename);

#endif // DETECTION_H
