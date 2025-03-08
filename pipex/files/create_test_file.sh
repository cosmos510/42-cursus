#!/bin/bash

# Couleurs pour le texte
GREEN="\033[32m"
RESET="\033[0m"

# Création de fichiers nécessaires pour les tests

echo "Creating necessary files for the tests..."

# Fichier d'entrée standard
echo "Creating 'infile'..."
echo -e "Line 1: Hello World\nLine 2: This is a test\nLine 3: 42 is the answer\nLine 4: Another test line" > infile

# Fichier vide
echo "Creating 'emptyfile'..."
> emptyfile

# Fichier avec une seule ligne
echo "Creating 'singlelinefile'..."
echo "This is a single line of text." > singlelinefile

# Fichier volumineux (10 000 lignes)
echo "Creating 'bigfile'..."
for i in $(seq 1 10000); do
    echo "This is line $i of the bigfile. 42 is here sometimes." >> bigfile
done

# Fichiers de sortie pour commandes Bash et pipex
echo "Creating output files..."
> outfile_bash
> outfile_pipex

# Fichier temporaire pour les tests avancés
echo "Creating 'temp_outfile'..."
> temp_outfile

echo -e "${GREEN}All necessary files have been created!${RESET}"
