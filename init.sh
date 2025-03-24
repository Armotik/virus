#!/bin/bash

# Dossier de travail
SANDBOX="./sandbox"
IMGDIR="$SANDBOX"

echo "[*] Initialisation de l'environnement de test dans $SANDBOX..."

# Réinitialisation
rm -rf "$SANDBOX"
mkdir -p "$IMGDIR"
cd "$SANDBOX" || exit 1

# Création de vraies images avec ImageMagick
echo "[*] Génération d'images..."
for i in {1..6}; do
    convert -size 400x300 xc:"rgb($((RANDOM%256)),$((RANDOM%256)),$((RANDOM%256)))" \
        -gravity center -pointsize 30 -annotate 0 "Image $i" \
        "img${i}.jpg"
done

# Création de 5 exécutables factices
echo "[*] Création d'exécutables..."
for i in {1..5}; do
    FILENAME="MonPG$i.c"
    echo "#include <stdio.h>
int main() {
    printf(\"[MonPG$i] Exécutable factice.\\n\");
    return 0;
}" > "$FILENAME"

    gcc "$FILENAME" -o "MonPG$i"
    chmod 775 "MonPG$i"
    rm "$FILENAME"
done

cd ..
echo "[+] Initialisation terminée. Dossier prêt : $SANDBOX"
