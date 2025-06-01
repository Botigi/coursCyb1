
import socket


# Configuration du serveur
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Crée un socket TCP/IP en utilisant l'adresse IPv4 et le protocole TCP
host = socket.gethostname()  # Obtient le nom d'hôte de la machine locale pour lier le serveur à cette adresse
port = 4444  # Définit le port sur lequel le serveur écoutera les connexions entrantes
server.bind((host, port))  # Lie le socket à l'adresse et au port spécifiés
server.listen(5)  # Met le serveur en mode écoute, avec une file d'attente maximale de 5 connexions


print(f"Serveur TCP en cours d'exécution sur {host}:{port}")


# Boucle d'attente des connexions entrantes

while True:  
    client, address = server.accept()  # Accepte une nouvelle connexion entrante
    print(f"Connexion reçue de {client} {address}")
    message = "Hello!\r\n"  # Message à envoyer au client
    client.send(message.encode('ascii'))  # Envoie le message encodé en ASCII au client
    print(f"Message TCP envoyé à {client} {address}")
    client.close()  # Ferme la connexion avec le client
    print(f"Connexion TCP fermée avec {client} {address}")