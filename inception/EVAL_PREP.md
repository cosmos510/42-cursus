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

### Explication détaillée des Dockerfiles et scripts

#### NGINX - Dockerfile
```dockerfile
FROM debian:bullseye
# Image de base Debian 11 (avant-dernière stable)

ARG DOMAIN_NAME
# Récupère le nom de domaine passé en argument au build

RUN apt-get update && apt-get install -y nginx openssl gettext-base && rm -rf /var/lib/apt/lists/*
# Installe nginx (serveur web), openssl (pour générer le certificat SSL), gettext-base (pour envsubst qui remplace les variables dans la config)

RUN mkdir -p /etc/nginx/ssl
# Crée le dossier pour stocker le certificat SSL

RUN openssl req -x509 -nodes -days 365 -newkey rsa:2048 -keyout /etc/nginx/ssl/nginx.key -out /etc/nginx/ssl/nginx.crt -subj "/C=FR/ST=Paris/L=Paris/O=42/CN=${DOMAIN_NAME}"
# Génère un certificat SSL auto-signé valide 365 jours, clé RSA 2048 bits, avec le CN = nom de domaine

COPY conf/nginx.conf /etc/nginx/nginx.conf.template
# Copie la config nginx comme template (contient $DOMAIN_NAME à remplacer)

COPY tools/entrypoint.sh /entrypoint.sh
# Copie le script d'entrée

RUN chmod +x /entrypoint.sh
# Rend le script exécutable

EXPOSE 443
# Déclare le port 443 (HTTPS)

CMD ["/entrypoint.sh"]
# Lance le script au démarrage du container
```

#### NGINX - entrypoint.sh
```bash
#!/bin/sh
envsubst '$DOMAIN_NAME' < /etc/nginx/nginx.conf.template > /etc/nginx/nginx.conf
# Remplace $DOMAIN_NAME dans le template par la vraie valeur de la variable d'environnement

exec nginx -g 'daemon off;'
# Lance nginx au premier plan (pas en daemon, sinon le container s'arrête)
```

#### WordPress - Dockerfile
```dockerfile
FROM debian:bullseye
# Image de base Debian 11

RUN apt-get update && apt-get install -y php7.4-fpm php7.4-mysql php7.4-curl php7.4-gd php7.4-xml php7.4-mbstring php7.4-zip wget mariadb-client && rm -rf /var/lib/apt/lists/*
# Installe PHP-FPM 7.4 avec les extensions nécessaires pour WordPress, wget pour télécharger, mariadb-client pour tester la connexion à la DB

RUN mkdir -p /var/www/html && wget https://wordpress.org/latest.tar.gz && tar -xzf latest.tar.gz && mv wordpress/* /var/www/html/ && rm -rf wordpress latest.tar.gz
# Crée le dossier web, télécharge WordPress, l'extrait et le place dans /var/www/html

RUN wget https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar && chmod +x wp-cli.phar && mv wp-cli.phar /usr/local/bin/wp
# Télécharge WP-CLI (outil en ligne de commande pour configurer WordPress sans navigateur)

COPY conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf
# Copie la config PHP-FPM (écoute sur port 9000)

COPY tools/setup.sh /setup.sh
RUN chmod +x /setup.sh
# Copie et rend exécutable le script de setup

WORKDIR /var/www/html
# Définit le répertoire de travail

EXPOSE 9000
# Déclare le port 9000 (PHP-FPM)

CMD ["/setup.sh"]
# Lance le script au démarrage
```

#### WordPress - setup.sh
```bash
#!/bin/bash
WORDPRESS_DB_PASSWORD=$(cat $WORDPRESS_DB_PASSWORD_FILE)
WORDPRESS_ADMIN_PASSWORD=$(cat $WORDPRESS_ADMIN_PASSWORD_FILE)
WORDPRESS_USER_PASSWORD=$(cat $WORDPRESS_USER_PASSWORD_FILE)
# Lit les mots de passe depuis les Docker secrets (fichiers montés dans /run/secrets/)

mkdir -p /run/php
# Crée le dossier pour le PID de PHP-FPM

sleep 15
# Attend que MariaDB soit prêt

while ! mysql -h mariadb -u $WORDPRESS_DB_USER -p$WORDPRESS_DB_PASSWORD -e "SELECT 1" >/dev/null 2>&1; do
    echo "Waiting for MariaDB..."
    sleep 2
done
# Boucle qui attend que MariaDB accepte les connexions avant de continuer

if [ ! -f /var/www/html/wp-config.php ]; then
    wp config create --dbname=$WORDPRESS_DB_NAME --dbuser=$WORDPRESS_DB_USER --dbpass=$WORDPRESS_DB_PASSWORD --dbhost=$WORDPRESS_DB_HOST --allow-root
    # Crée wp-config.php avec les infos de connexion à la base

    wp core install --url="https://${DOMAIN_NAME}" --title="Inception" --admin_user=$WORDPRESS_ADMIN_USER --admin_password=$WORDPRESS_ADMIN_PASSWORD --admin_email=$WORDPRESS_ADMIN_EMAIL --allow-root
    # Installe WordPress (crée les tables, l'admin)

    wp user create $WORDPRESS_USER $WORDPRESS_USER_EMAIL --user_pass=$WORDPRESS_USER_PASSWORD --allow-root
    # Crée le deuxième utilisateur (non-admin)

    wp option update home "https://${DOMAIN_NAME}" --allow-root
    wp option update siteurl "https://${DOMAIN_NAME}" --allow-root
    # Configure les URLs du site en HTTPS
fi

chown -R www-data:www-data /var/www/html
# Donne les droits au user www-data (utilisé par PHP-FPM)

php-fpm7.4 -F
# Lance PHP-FPM au premier plan (-F = foreground)
```

#### MariaDB - Dockerfile
```dockerfile
FROM debian:bullseye
# Image de base Debian 11

RUN apt-get update && apt-get install -y mariadb-server && rm -rf /var/lib/apt/lists/*
# Installe le serveur MariaDB

COPY conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
# Copie la config MariaDB (bind-address 0.0.0.0 pour accepter les connexions réseau)

COPY tools/setup.sh /setup.sh
RUN chmod +x /setup.sh
# Copie et rend exécutable le script de setup

EXPOSE 3306
# Déclare le port 3306 (MySQL/MariaDB)

CMD ["/setup.sh"]
# Lance le script au démarrage
```

#### MariaDB - setup.sh
```bash
#!/bin/bash
MYSQL_ROOT_PASSWORD=$(cat $MYSQL_ROOT_PASSWORD_FILE)
MYSQL_PASSWORD=$(cat $MYSQL_PASSWORD_FILE)
# Lit les mots de passe depuis les Docker secrets

if [ ! -d "/var/lib/mysql/$MYSQL_DATABASE" ]; then
    # Si la base n'existe pas encore (premier lancement)

    mysql_install_db --user=mysql --datadir=/var/lib/mysql
    # Initialise les fichiers système de MariaDB

    mysqld_safe --datadir=/var/lib/mysql &
    sleep 10
    # Lance MariaDB temporairement en background pour créer la base et les users

    mysql -e "CREATE DATABASE IF NOT EXISTS $MYSQL_DATABASE;"
    # Crée la base de données WordPress

    mysql -e "CREATE USER IF NOT EXISTS '$MYSQL_USER'@'%' IDENTIFIED BY '$MYSQL_PASSWORD';"
    # Crée l'utilisateur WordPress accessible depuis n'importe quel host (%)

    mysql -e "GRANT ALL PRIVILEGES ON $MYSQL_DATABASE.* TO '$MYSQL_USER'@'%';"
    # Donne tous les droits sur la base WordPress à cet utilisateur

    mysql -e "ALTER USER 'root'@'localhost' IDENTIFIED BY '$MYSQL_ROOT_PASSWORD';"
    # Change le mot de passe root

    mysql -e "FLUSH PRIVILEGES;"
    # Applique les changements de privilèges

    mysqladmin -u root -p$MYSQL_ROOT_PASSWORD shutdown
    # Arrête MariaDB proprement
fi

mysqld_safe --datadir=/var/lib/mysql
# Relance MariaDB au premier plan (le processus principal du container)
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
