#!/bin/bash

# Verificăm dacă a fost furnizat un director ca argument
if [ $# -ne 1 ]; then
    echo "Utilizare: $0 <director>"
    exit 1
fi

# Verificăm dacă directorul dat există
if [ ! -d "$1" ]; then
    echo "Eroare: $1 nu este un director valid."
    exit 1
fi

# Folosim find pentru a găsi toate fișierele cu drepturile 755 din directorul dat și subdirectoarele sale
find "$1" -type f -perm 755 | while IFS= read -r file; do
    # Afișăm numele fișierului
    echo "Fișier: $file"
    
    # Cerem confirmarea utilizatorului pentru a schimba drepturile de acces
    read -p "Doriți să modificați drepturile de acces la 744 pentru acest fișier? (Da/Nu): " confirmare
    
    if [[ $confirmare == "Da" || $confirmare == "Yes" ]]; then
        # Modificăm drepturile de acces la 744
        chmod 744 "$file"
        echo "Drepturile de acces au fost modificate cu succes."
    elif [[ $confirmare == "Nu" || $confirmare == "No" ]]; then
        echo "Drepturile de acces nu au fost modificate."
    else
        echo "Opțiune invalidă. Drepturile de acces nu au fost modificate."
    fi
done
