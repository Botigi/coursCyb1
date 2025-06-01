import os

CURDIR = os.path.dirname(os.path.realpath(__file__))

# Définir le chemin de sauvegarde dans ./test_dec
rel_path = os.path.relpath(file_path, f'{CURDIR}/test')
dec_file_path = os.path.join(f'{CURDIR}/test_dec', rel_path[:-4])

# Créer les répertoires si nécessaires
os.makedirs(os.path.dirname(dec_file_path), exist_ok=True)

# Fonction pour parcourir un répertoire et chiffrer chaque fichier
def search_dir(directory):
    directory = f"{CURDIR}/{directory}"
    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            #enc_file(file_path)
            
            