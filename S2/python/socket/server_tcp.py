import socket

server = socket.socket(family=socket.AF_INET, type=socket.SOCK_STREAM)

# AF_INET = famille d'adresses : IPv4
# type : type de serveur TCP

host = socket.gethostname()
port = 444

server.bind((host, port))
server.listen(5)
# 5 connexions autorisées question : comment est gere la liste d attente

print(f"Running TCP server on {host} : {port}")
while True: 
    client, address = server.accept()  # appel bloquant : attend un client et une adresse
    print(f"Received connection from {address}")
    message = "Hello!\r\n"
    client.send(message.encode('ascii'))
    print(f"Sent TCP to {address}")
    client.close()
    print(f"Closed TCP with {address}")

    # 95% du temps, le serveur envoie le premier message, donc le client doit recevoir ce message après la connexion. Ce message est appelé la bannière et contient des informations sur le service auquel on se connecte.

import socket


# Configuration du serveur
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Crée un socket TCP/IP en utilisant l'adresse IPv4 et le protocole TCP
host = socket.gethostname()  # Obtient le nom d'hôte de la machine locale pour lier le serveur à cette adresse
port = 444  # Définit le port sur lequel le serveur écoutera les connexions entrantes
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