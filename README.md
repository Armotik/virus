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
3. Il portera le nom de MediaPlayer.exe et sera compilé
   avec [gcc](https://fr.wikipedia.org/wiki/GNU_Compiler_Collection).
4. Il vous est conseillé de développer graduellement, fonction par fonction, et de visualiser point par point les
   retours de votre programme.

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

Ne pas oublier d'installer les dépendances avant de compiler le projet :

```bash
sudo apt install libgtk-3-dev
sudo apt install imagemagick
```

```bash
cd build
cmake ..
make
```

### Utilisation

Une fois le projet compilé, vous pouvez exécuter le virus avec la commande suivante :

```bash
cd ..
./init.sh
cd build
./MediaPlayer.exe
```

Ce script initialise un dossier de test [sandbox](./sandbox) avec des fichiers de test ainsi que des images, puis la
commande `./MediaPlayer.exe` exécute lance l'application, l'utilisateur devra choisir un dossier source (tout les
programme de ce dossier et de ses sous-dossiers seront infectés). Le programme récupérera toutes les images et vidéos
dans un menu à gauche et l'utilisateur pourra les visionner en cliquant dessus.

### Bibliothèques utilisées

- [stdio.h](https://en.wikipedia.org/wiki/Stdio.h) : Pour les entrées/sorties
- [stdlib.h](https://en.wikipedia.org/wiki/Stdlib.h) : Pour les fonctions de conversion de chaînes, de gestion de la
  mémoire, de recherche, de tri et d'autres fonctions
- [string.h](https://en.wikipedia.org/wiki/String.h) : Pour les fonctions de manipulation de chaînes
- [sys/stat.h](https://en.wikipedia.org/wiki/Sys/stat.h) : Pour les fonctions de manipulation de fichiers
- [unistd.h](https://en.wikipedia.org/wiki/Unistd.h) : Pour les fonctions de gestion des fichiers et des répertoires
- [dirent.h](https://en.wikipedia.org/wiki/Dirent.h) : Pour les fonctions de manipulation de répertoires
- [errno.h](https://en.wikipedia.org/wiki/Errno.h) : Pour les fonctions de gestion des erreurs
- [time.h](https://en.wikipedia.org/wiki/Time.h) : Pour les fonctions de gestion du temps
- [gtk/gtk.h](https://en.wikipedia.org/wiki/GTK) : Pour les fonctions de gestion de l'interface graphique
- [pthread.h](https://en.wikipedia.org/wiki/POSIX_Threads) : Pour les fonctions de gestion des threads
- [limits.h](https://en.wikipedia.org/wiki/Limits.h) : Pour les constantes de limites

### Détails de l'infection

- Une fois le virus lancé et le dossier source choisi, le virus infectera tous les fichiers exécutables du dossier et de
  ses sous-dossiers dans un thread séparé afin de ne pas bloquer l'interface graphique et de permettre à l'utilisateur
  de continuer à naviguer dans les images et vidéos sans qu'il ne se rende compte de l'infection.
- Les programmes infectés seront renommés avec le nom du programme original tandit que le programme original sera renommé avec l'extension `.old`
- Si un programme infecté est exécuté, il executera le code du virus et transmettra l'exécution au programme original
- Si un programme original est exécuté, il executera le code du programme original
- Le virus ne peut pas infecter un programme déjà infecté

### Système de Log

- Le virus écrit des logs dans le fichier `log.txt` dans le dossier d'execution du MediaPlayer.exe

---

## Auteur

- Anthony MUDET
- UE Sécurité
- Licence 3 Informatique - Semestre 6
- La Rochelle Université - 2025