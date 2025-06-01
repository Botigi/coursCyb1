import socket

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Crée un socket TCP/IP en utilisant l'adresse IPv4 et le protocole TCP

host = socket.gethostname()  # Obtient le nom d'hôte de la machine locale pour se connecter au serveur
port = 4444  # Définit le port sur lequel le client se connectera

print(f"Connexion au serveur TCP sur {host}:{port}...")
client.connect((host, port))  # Établit une connexion avec le serveur

while True:
    message = input("Entrez le message à envoyer au serveur (ou 'exit' pour quitter): ")
    if message.lower() == 'exit':
        print("Fermeture de la connexion...")
        break
    client.sendall(message.encode('utf-8'))  # Envoie le message au serveur

    data = client.recv(1024)  # Reçoit la réponse du serveur
    print(f"Réponse du serveur: {data.decode('utf-8')}")

client.close()  # Ferme la connexion


import socket 
client=socket.socket(socket.AF_INET, socket.SOCK_STREAM)
host=socket.gethostname()
port = 444

client.connect((host,port))
while True :
    message=input('blalble :')
    if message.lower()== 'exit' :
        print("Fermeture de la connexion...")
        break
    client.sendall(message.encode('utf-8'))
    data = client.recv(1024)
    print(data.decode('utf-8'))
