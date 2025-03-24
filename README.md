# Sécurite - Virologie

## Projet de création d'un virus de type compagnon

## Objectif

Dans ce projet, nous concevrons pas à pas un virus de type compagnon (Vu en TD)

1. __Le contexte :__

On vous fournit un cd ROM rempli d'image et de vidéos accompagné d'un programme s'intitulant MediaPlayer.exe (le virus)
censé n'afficher qu'une image/ ou procéder à la lecture d'une vidéo (mais en réalité plus que cela ...).

Ici, la proximité d'un "Player" à côté de multiples images (ou vidéos) qui permet de susciter le click de l'utilisateur
et donc la diffusion.

## Travail demandé

1. Vous devez concevoir un programme virus de type compagnon en langage C.
2. Il sera écrit avec l'éditeur de texte de votre choix.
3. Il portera le nom de MediaPlayer.exe et sera compilé avec [gcc](https://fr.wikipedia.org/wiki/GNU_Compiler_Collection).
4. Il vous est conseillé de développer graduellement, fonction par fonction, et de visualiser point par point les retours de votre programme.

## Développement

### Environnement de développement

- Utilisation de l'IDE [CLion](https://www.jetbrains.com/fr-fr/clion/) pour le développement
- Utilisation de [gcc](https://fr.wikipedia.org/wiki/GNU_Compiler_Collection) pour la compilation
- Utilisation de [CMake](https://fr.wikipedia.org/wiki/CMake) pour la gestion des dépendances

### Structure du projet

```
.
├── build
├── sandbox
├── CMakeLists.txt
├── detection.c
├── detection.h
├── infection.c
├── infection.h
├── init.sh
├── mediaplayer.c
├── mediaplayer.h
├── README.md
├── scanner.c
├── scanner.h
├── transfert.c
└── transfert.h
```

- [build](./build) : Dossier de compilation
- [sandbox](./sandbox) : Dossier de test
- [CMakeLists.txt](./CMakeLists.txt) : Fichier de configuration de CMake
- [detection.c](./detection.c) : Fichier source de la détection -> Fonctions de détection de l'infection
- [detection.h](./detection.h) : Fichier d'en-tête de la détection
- [infection.c](./infection.c) : Fichier source de l'infection -> Fonctions d'infection des fichiers
- [infection.h](./infection.h) : Fichier d'en-tête de l'infection
- [init.sh](./init.sh) : Script d'initialisation de la sandbox
- [mediaplayer.c](./mediaplayer.c) : Fichier source du virus
- [mediaplayer.h](./mediaplayer.h) : Fichier d'en-tête du virus
- [README.md](./README.md) : Fichier README
- [scanner.c](./scanner.c) : Fichier source du scanner -> Fonctions de scan des fichiers
- [scanner.h](./scanner.h) : Fichier d'en-tête du scanner
- [transfert.c](./transfert.c) : Fichier source du transfert -> Fonctions de transfert de l'exécution du virus
- [transfert.h](./transfert.h) : Fichier d'en-tête du transfert

### Compilation

```bash
cd build
cmake ..
make
```

### Utilisation de l'IA

J'ai effectivement utilisé l'IA pour m'aider dans ce projet, mais uniquement pour :
- Le fichier [init.sh](./init.sh) : Car je ne savais pas comment créer un script bash pour créer un dossier et y mettre des fichiers et cela n'a rien à voir avec le virus
- Resolution des erreurs liées à la compilation avec [CMakeLists.txt](./CMakeLists.txt) : Car je ne savais pas comment configurer CMake pour compiler les fichiers sources

Pour tout le reste du projet, j'ai tout fait moi-même.

## Détails des fichiers sources

### [scanner.c](./scanner.c)

