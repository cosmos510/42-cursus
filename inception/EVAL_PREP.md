# Préparation Correction Inception

## Preliminaries

- **Credentials dans le repo git ?** Non, les mots de passe sont dans le dossier `secrets/` qui est dans le `.gitignore`. Le fichier `.env` est aussi ignoré par git.

---

## Activity Overview

### Comment Docker et docker compose fonctionnent ?
Docker est un outil qui permet de créer des containers isolés. Chaque container embarque une application et ses dépendances dans un environnement léger. Docker compose est un outil qui permet de définir et gérer plusieurs containers en même temps via un fichier `docker-compose.yml`. Il orchestre le démarrage, le réseau et les volumes entre les services.

### Différence entre une image Docker avec et sans docker compose ?
Sans docker compose, on lance chaque container manuellement avec `docker run`, on gère les réseaux et volumes à la main. Avec docker compose, tout est déclaré dans un fichier YAML : les services, réseaux, volumes et dépendances sont gérés automatiquement en une seule commande.

### Avantage de Docker par rapport aux VMs ?
- Docker partage le kernel de l'hôte → plus léger (MB vs GB)
- Démarrage en secondes vs minutes pour une VM
- Moins de ressources consommées
- Plus portable (même image = même comportement partout)
- Une VM virtualise un OS complet avec son propre kernel

### Pertinence de la structure de dossiers ?
- `Makefile` à la racine : point d'entrée unique pour build/clean
- `srcs/` : contient tout le code source (docker-compose, .env, requirements)
- `srcs/requirements/` : un dossier par service (nginx, wordpress, mariadb) avec chacun son Dockerfile, conf et tools
- `secrets/` : fichiers de mots de passe, ignorés par git

---

## README check

- README.md présent à la racine
- Première ligne : *This project has been created as part of the 42 curriculum by maxmarti.*
- Sections : Description, Instructions, Resources (avec explication de l'usage de l'IA)

---

## Documentation check

- `USER_DOC.md` : instructions pour démarrer/arrêter, accéder au site, gérer les credentials
- `DEV_DOC.md` : prérequis, setup, commandes Makefile, docker compose, persistance des données

---

## Simple Setup

### NGINX accessible uniquement sur port 443 ?
```bash
docker compose -f srcs/docker-compose.yml ps
# nginx écoute sur 0.0.0.0:443->443/tcp uniquement
```

### Certificat SSL/TLS utilisé ?
Oui, certificat auto-signé généré dans le Dockerfile nginx avec openssl (TLSv1.2 et TLSv1.3).

### WordPress installé et configuré ?
Ouvrir https://maxmarti.42.fr → le site s'affiche directement (pas la page d'installation).
http://maxmarti.42.fr ne fonctionne pas (pas de port 80 exposé).

---

## Docker Basics

### Un Dockerfile par service ?
- `srcs/requirements/nginx/Dockerfile`
- `srcs/requirements/wordpress/Dockerfile`
- `srcs/requirements/mariadb/Dockerfile`

### Images construites soi-même ?
Oui, chaque Dockerfile part de `debian:bullseye` et installe les services manuellement. Aucune image DockerHub prête à l'emploi.

### Penultimate stable version ?
`FROM debian:bullseye` (Debian 11, l'avant-dernière version stable).

### Images nommées comme les services ?
Dans docker-compose.yml : `image: mariadb`, `image: wordpress`, `image: nginx`.

### Makefile lance docker compose ?
```bash
make  # exécute docker compose -f srcs/docker-compose.yml up -d --build
```

---

## Docker Network

### docker-network utilisé ?
Oui, dans docker-compose.yml :
```yaml
networks:
  inception:
    driver: bridge
```
Chaque service est connecté au réseau `inception`.

### Vérification :
```bash
docker network ls
# Le réseau "inception" apparaît
```

### Explication docker-network :
Un réseau Docker bridge crée un réseau isolé où les containers communiquent entre eux par leur nom de service (DNS interne). Les containers sont isolés du réseau hôte et ne peuvent communiquer qu'entre eux via ce réseau.

---

## NGINX avec SSL/TLS

### Dockerfile présent ?
`srcs/requirements/nginx/Dockerfile`

### Container créé ?
```bash
docker compose -f srcs/docker-compose.yml ps
# nginx est Up
```

### Port 80 inaccessible ?
```bash
curl http://maxmarti.42.fr
# Connection refused - seul le port 443 est exposé
```

### TLS v1.2/v1.3 ?
```bash
# Vérifier le certificat :
openssl s_client -connect maxmarti.42.fr:443 -tls1_2
openssl s_client -connect maxmarti.42.fr:443 -tls1_3
# Les deux fonctionnent
```

Config nginx : `ssl_protocols TLSv1.2 TLSv1.3;`

---

## WordPress avec php-fpm et son volume

### Dockerfile présent, sans NGINX ?
`srcs/requirements/wordpress/Dockerfile` — contient uniquement php-fpm, wp-cli, pas de nginx.

### Container créé ?
```bash
docker compose -f srcs/docker-compose.yml ps
# wordpress est Up
```

### Volume présent ?
```bash
docker volume ls
docker volume inspect inception_wordpress_data
# "device": "/home/maxmarti/data/wordpress"
```

### Ajouter un commentaire ?
Se connecter avec l'utilisateur `user` / `userpass123` et poster un commentaire sur un article.

### Admin sans "admin" dans le nom ?
Login admin : `maxmarti` (pas de "admin" dedans).

### Modifier une page depuis le dashboard ?
Se connecter sur https://maxmarti.42.fr/wp-admin avec `maxmarti` / `adminpass123`, modifier une page, vérifier que le changement apparaît sur le site.

---

## MariaDB et son volume

### Dockerfile présent, sans NGINX ?
`srcs/requirements/mariadb/Dockerfile` — contient uniquement mariadb-server.

### Container créé ?
```bash
docker compose -f srcs/docker-compose.yml ps
# mariadb est Up
```

### Volume présent ?
```bash
docker volume ls
docker volume inspect inception_mariadb_data
# "device": "/home/maxmarti/data/mariadb"
```

### Se connecter à la base de données ?
```bash
docker exec -it mariadb mysql -u wpuser -p
# Entrer le mot de passe depuis secrets/db_password.txt
SHOW DATABASES;
USE wordpress;
SHOW TABLES;
# Les tables WordPress sont présentes (wp_posts, wp_users, etc.)
```

---

## Persistence

### Après reboot de la VM :
```bash
make  # ou docker compose -f srcs/docker-compose.yml up -d
```
- Les données WordPress sont toujours là (articles, commentaires, pages modifiées)
- La base MariaDB est intacte (les volumes persistent sur le disque dans `/home/maxmarti/data/`)

---

## Configuration modification

### Exemple 1 : changer le port NGINX de 443 à 8443

1. Modifier `srcs/docker-compose.yml` :
```yaml
ports:
  - "8443:443"
```

2. Rebuild :
```bash
make re
```

3. Accéder via https://maxmarti.42.fr:8443

### Exemple 2 : changer le port WordPress (PHP-FPM) de 9000 à 9001

1. Modifier `srcs/requirements/wordpress/conf/www.conf` :
```
listen = 9001
```

2. Modifier `srcs/requirements/nginx/conf/nginx.conf` :
```
fastcgi_pass wordpress:9001;
```

3. Rebuild :
```bash
make re
```

4. Attendre ~20 secondes, le site fonctionne sur https://maxmarti.42.fr

### Exemple 3 : changer le port MariaDB de 3306 à 3307

1. Ajouter le port dans `srcs/requirements/mariadb/conf/50-server.cnf` (sous `bind-address`) :
```
port = 3307
```

2. Modifier `srcs/docker-compose.yml` :
```yaml
WORDPRESS_DB_HOST: mariadb:3307
```

3. Modifier `srcs/requirements/wordpress/tools/setup.sh` (la ligne mysql) :
```bash
while ! mysql -h mariadb -P 3307 -u $WORDPRESS_DB_USER ...
```

4. Rebuild :
```bash
make re
```

5. Le site fonctionne toujours sur https://maxmarti.42.fr

---

Dans tous les cas, le service reste accessible et fonctionnel après rebuild.
