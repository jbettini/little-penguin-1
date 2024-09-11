#!/bin/bash

# Ouvre le fichier en lecture
#exec 3< /dev/fortytwo

# Première lecture
read -n 7 first /dev/fortytwo

# Deuxième lecture
read -n 8 second /dev/fortytwo

# Affiche les résultats
echo "Première lecture : $first"
echo "Deuxième lecture : $second"

# Ferme le descripteur de fichier
#exec 3<&-
