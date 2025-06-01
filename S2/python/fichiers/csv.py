# Lecture/Ecriture d'un fichier CSV
import csv

# Ouvrir le fichier en mode csv pour lecture
# newline="" permet d'éviter les lignes vides supplémentaires sur Windows
with open("data.csv", newline='', encoding="utf-8") as csvfile:
    # retourne chaque une liste de dict à partir de chaque ligne du fichier. le dict est sous la forme dict nom_colonne: valeur_colonne
    reader = csv.DictReader(csvfile)
    for row in reader:
        print(row["name"], row["age"], row["city"])
        rendered_html = template.render(**row)

# Données à écrire : une liste de dictionnaires
donnee = {"Nom": "Alice", "Age": 30, "Ville": "New York"}

# Ouvrir le fichier en mode csv pour écriture - "w": ecrase le fichier existant, "a": ajoute au fichier existant
# newline="" permet d'éviter les lignes vides supplémentaires sur Windows
with open("data.csv", "w", newline="") as csvfile:
    # Définition de l’ordre des colonnes - Doit correspondre aux en-têtes existants en mode "a"
    noms_colonnes = ["Nom", "Age", "Ville"] 
    # Création de l'objet writer pour écrire des dictionnaires
    writer = csv.DictWriter(csvfile, fieldnames=noms_colonnes)

    # Écriture de la ligne d'en-tête - en mode "a" il ne faut pas l'utiliser
    writer.writeheader()

    # Écriture de la nouvelle ligne (sans répéter l'en-tête) - writerows permet d'écrire plusieurs ligne en une seule fois. prend une liste de dict en parametre
    writer.writerow(donnee)

