# Inception - Cheatsheet Évaluation

---

## 1. General Instructions (Vérifications préliminaires)

### Structure du repo
- `srcs/` à la racine → contient `docker-compose.yml`, `.env.example`, et `requirements/` ✅
- `Makefile` à la racine ✅

### Commande de nettoyage (l'évaluateur la lance avant tout)
```bash
docker stop $(docker ps -qa); docker rm $(docker ps -qa); docker rmi -f $(docker images -qa); docker volume rm $(docker volume ls -q); docker network rm $(docker network ls -q) 2>/dev/null
```
Ça supprime tous les containers, images, volumes et networks Docker. C'est normal, on repart de zéro.

### Vérifications dans docker-compose.yml
- Pas de `network: host` → on utilise `driver: bridge` ✅
- Pas de `links:` → on utilise le network Docker pour la communication ✅
- Présence de `networks:` → notre network `inception` est défini ✅

### Vérifications dans le Makefile et scripts
- Pas de `--link` nulle part ✅

### Vérifications dans les Dockerfiles
- Pas de `tail -f` ✅
- Pas de commande en background (`nginx & bash`) ✅
- Pas de `bash` ou `sh` seul comme ENTRYPOINT ✅
- On utilise `CMD ["/setup.sh"]` ou `CMD ["/entrypoint.sh"]` qui lancent des scripts ✅
- Base image : `debian:bullseye` (avant-dernière version stable de Debian) ✅

### Vérifications dans les scripts
- Pas de `sleep infinity`, `tail -f /dev/null`, `tail -f /dev/random` ✅
- `nginx -g 'daemon off;'` → garde nginx au premier plan (pas en background) ✅
- `php-fpm7.4 -F` → garde php-fpm au premier plan ✅
- `mysqld_safe` → garde MariaDB au premier plan ✅

### Lancer le projet
```bash
make
```

---

## 2. Activity Overview (Questions théoriques)

### Comment Docker et Docker Compose fonctionnent ?
- **Docker** : crée des containers isolés à partir d'images. Chaque container est un environnement léger qui partage le kernel de la machine hôte mais a son propre filesystem, réseau et processus.
- **Docker Compose** : outil qui permet de définir et lancer plusieurs containers en même temps via un fichier `docker-compose.yml`. Il gère les dépendances entre services, le réseau commun, les volumes, etc.
- En résumé : Docker = 1 container, Docker Compose = orchestrer plusieurs containers ensemble.

### Différence entre une image Docker avec et sans Docker Compose ?
- **Sans Compose** : tu build et run chaque image manuellement avec `docker build` et `docker run`. Tu dois gérer toi-même le réseau, les volumes, l'ordre de lancement.
- **Avec Compose** : tout est décrit dans le `docker-compose.yml`. Un seul `docker compose up` build toutes les images, crée le réseau, les volumes, et lance les containers dans le bon ordre (grâce à `depends_on`).
- L'image elle-même ne change pas, c'est la gestion qui est simplifiée.

### Avantages de Docker par rapport aux VMs ?
- **VM** : virtualise tout un OS complet (kernel inclus) → lourd (plusieurs Go), lent à démarrer.
- **Docker** : partage le kernel de l'hôte, ne virtualise que l'application → léger (quelques Mo), démarre en secondes.
- Docker est plus rapide, plus portable, et consomme moins de ressources.

### Pertinence de la structure de dossiers du projet ?
```
inception/
├── Makefile              → point d'entrée, lance tout
├── srcs/
│   ├── docker-compose.yml → définit les services
│   ├── .env               → variables d'environnement
│   └── requirements/      → un dossier par service
│       ├── mariadb/       → Dockerfile + config + script
│       ├── nginx/         → Dockerfile + config + script
│       └── wordpress/     → Dockerfile + config + script
└── secrets/               → mots de passe (pas dans git)
```
- Chaque service a son propre dossier avec son Dockerfile, sa config et son script → séparation claire des responsabilités.
- Le `Makefile` à la racine simplifie l'utilisation (`make`, `make down`, etc.).
- Les secrets sont séparés du code pour la sécurité.

---

## 3. README Check

- README.md à la racine ✅
- Première ligne en italique : `*This project has been created as part of the 42 curriculum by maxmarti.*` ✅
- Sections présentes :
  - **Description** ✅
  - **Instructions** ✅
  - **Resources** avec liens documentation + explication de l'utilisation de l'IA ✅

---

## 4. Simple Setup

### Port 443 uniquement
- Notre nginx n'écoute que sur le port 443 (pas de port 80) ✅
- Vérifier : `docker compose -f srcs/docker-compose.yml ps` → seul le port `443` apparaît
- Tester que http ne marche pas : `curl -k http://maxmarti.42.fr` → connexion refusée ✅

### Certificat SSL/TLS
- Certificat auto-signé généré dans le Dockerfile nginx avec `openssl` ✅
- TLSv1.2 et TLSv1.3 configurés dans `nginx.conf` ✅
- Vérifier : dans le navigateur, cliquer sur le cadenas → certificat auto-signé visible

### WordPress installé et configuré
- Ouvrir `https://maxmarti.42.fr` → le site WordPress s'affiche (pas la page d'installation) ✅
- Le setup est fait automatiquement par `wp core install` dans le script `setup.sh`
- Si la page d'installation apparaît → vérifier `docker logs wordpress`

### Commandes utiles
```bash
docker compose -f srcs/docker-compose.yml ps
curl -k http://maxmarti.42.fr     # doit échouer
curl -k https://maxmarti.42.fr    # doit marcher
```

---

## 5. Docker Basics

### Un Dockerfile par service
- `srcs/requirements/mariadb/Dockerfile` ✅
- `srcs/requirements/nginx/Dockerfile` ✅
- `srcs/requirements/wordpress/Dockerfile` ✅
- Aucun n'est vide ✅

### Pas d'images préfaites (DockerHub interdit)
- On build nos propres images à partir de `debian:bullseye` ✅
- On n'utilise pas `FROM wordpress`, `FROM nginx`, `FROM mariadb` ✅
- Tout est installé manuellement via `apt-get` dans les Dockerfiles ✅

### Base image : avant-dernière version stable
- Les 3 Dockerfiles commencent par `FROM debian:bullseye` ✅
- Bullseye = Debian 11, c'est l'avant-dernière version stable (la dernière est Bookworm = Debian 12)

### Nom des images = nom des services
- Dans `docker-compose.yml`, chaque service a `image: <nom>` qui correspond au service :
  - service `mariadb` → `image: mariadb` ✅
  - service `wordpress` → `image: wordpress` ✅
  - service `nginx` → `image: nginx` ✅
- Vérifier : `docker images` → les 3 images apparaissent avec ces noms

### Makefile lance tout via docker compose
- `make` appelle `docker compose -f srcs/docker-compose.yml up -d --build` ✅
- Vérifier que les 3 containers tournent : `docker compose -f srcs/docker-compose.yml ps`

---

## 6. Docker Network

### Vérification dans docker-compose.yml
- Le network `inception` est défini avec `driver: bridge` ✅
- Les 3 services sont connectés au network `inception` ✅

### Commande de vérification
```bash
docker network ls
# Le network "inception" doit apparaître dans la liste
```

### Explication de docker-network
- Un docker-network est un réseau virtuel isolé qui permet aux containers de communiquer entre eux.
- On utilise un network de type `bridge` : chaque container a sa propre IP dans ce réseau privé.
- Les containers se trouvent entre eux par leur nom de service (ex: `wordpress` peut contacter `mariadb` juste avec le hostname `mariadb`).
- Les containers sont isolés du réseau de l'hôte → plus sécurisé que `network: host`.
- Seul nginx expose le port 443 vers l'extérieur, les autres services ne sont accessibles que depuis le network interne.

---

## 7. NGINX avec SSL/TLS

### Dockerfile
- `srcs/requirements/nginx/Dockerfile` existe et n'est pas vide ✅

### Container actif
```bash
docker compose -f srcs/docker-compose.yml ps
# Le container "nginx" doit apparaître avec le status "Up"
```

### Port 80 inaccessible
```bash
curl -k http://maxmarti.42.fr
# Doit échouer (connexion refusée) car nginx n'écoute que sur 443
```
- Dans `docker-compose.yml`, seul le port `443:443` est exposé ✅
- Dans `nginx.conf`, on a `listen 443 ssl;` uniquement (pas de `listen 80`) ✅

### Site WordPress accessible en HTTPS
- Ouvrir `https://maxmarti.42.fr` → le site s'affiche (pas la page d'installation) ✅

### Certificat TLS v1.2/v1.3
- Généré avec `openssl` dans le Dockerfile nginx ✅
- Configuré dans `nginx.conf` : `ssl_protocols TLSv1.2 TLSv1.3;` ✅
- C'est un certificat auto-signé → un avertissement dans le navigateur est normal
- Pour prouver le TLS, montrer la config nginx ou vérifier avec :
```bash
# Depuis la VM
curl -vk https://maxmarti.42.fr 2>&1 | grep -i tls
# Doit afficher la version TLS utilisée (TLSv1.2 ou TLSv1.3)
```

---

## 8. WordPress avec php-fpm et son volume

### Dockerfile
- `srcs/requirements/wordpress/Dockerfile` existe et n'est pas vide ✅
- Pas de NGINX dans ce Dockerfile (c'est php-fpm qui tourne, pas nginx) ✅

### Container actif
```bash
docker compose -f srcs/docker-compose.yml ps
# Le container "wordpress" doit apparaître avec le status "Up"
```

### Volume
```bash
docker volume ls
# Doit afficher "inception_wordpress_data"

docker volume inspect inception_wordpress_data
# Doit contenir le chemin "/home/maxmarti/data/wordpress" dans le résultat
```

### Ajouter un commentaire
- Aller sur `https://maxmarti.42.fr`
- Ouvrir un article (ex: "Hello world!")
- Ajouter un commentaire avec le user WordPress (pas l'admin)
- Le commentaire doit apparaître sur la page

### Connexion admin
- Aller sur `https://maxmarti.42.fr/wp-admin`
- Se connecter avec le compte admin : `maxmarti` ✅
- Le username ne contient pas "admin" ou "Admin" ✅
- **ATTENTION** : si ton admin s'appelle `admin`, `administrator`, `Admin-xxx` → c'échec immédiat

### Modifier une page depuis le dashboard
- Dans le dashboard admin, aller dans Pages
- Modifier une page (ex: "Sample Page")
- Vérifier que la modification apparaît sur le site

---

## 9. MariaDB et son volume

### Dockerfile
- `srcs/requirements/mariadb/Dockerfile` existe et n'est pas vide ✅
- Pas de NGINX dans ce Dockerfile ✅

### Container actif
```bash
docker compose -f srcs/docker-compose.yml ps
# Le container "mariadb" doit apparaître avec le status "Up"
```

### Volume
```bash
docker volume ls
# Doit afficher "inception_mariadb_data"

docker volume inspect inception_mariadb_data
# Doit contenir le chemin "/home/maxmarti/data/mariadb" dans le résultat
```

### Se connecter à la base de données
```bash
# Entrer dans le container mariadb
docker exec -it mariadb mysql -u wpuser -p wordpress
# Entrer le mot de passe du fichier secrets/db_password.txt

# Vérifier que la base n'est pas vide
SHOW TABLES;
# Doit afficher les tables WordPress (wp_posts, wp_users, wp_comments, etc.)

# Vérifier les utilisateurs WordPress
SELECT user_login FROM wp_users;
# Doit afficher "maxmarti" et "user"

# Quitter
exit
```

---

## 10. Persistence

### Procédure
1. Rebooter la VM
2. Relancer le projet :
```bash
cd ~/inception
make up
```
3. Vérifier que tout fonctionne :
   - `https://maxmarti.42.fr` → le site s'affiche
   - Le commentaire ajouté précédemment est toujours là
   - La page modifiée est toujours modifiée
   - La base MariaDB contient toujours les données

### Pourquoi ça marche ?
- Les volumes stockent les données dans `/home/maxmarti/data/` sur la VM
- `make down` ou un reboot ne supprime pas les volumes
- Seul `make fclean` supprime les données

### Si ça ne marche pas après reboot
```bash
# Vérifier que les containers tournent
docker compose -f srcs/docker-compose.yml ps

# Vérifier les logs
docker logs wordpress
docker logs mariadb
```

---

## 11. Configuration Modification

L'évaluateur va te demander de changer la config d'un service (ex: changer un port). Voici les cas possibles :

### Changer le port HTTPS de nginx (ex: 443 → 4443)
1. Dans `srcs/docker-compose.yml`, modifier :
```yaml
ports:
  - "4443:443"
```
2. Rebuild et relancer :
```bash
make re
```
3. Accéder au site : `https://maxmarti.42.fr:4443`

### Changer le port php-fpm de WordPress (ex: 9000 → 9001)
1. Dans `srcs/requirements/wordpress/conf/www.conf`, modifier :
```
listen = 9001
```
2. Dans `srcs/requirements/nginx/conf/nginx.conf`, modifier :
```
fastcgi_pass wordpress:9001;
```
3. Rebuild :
```bash
make re
```

### Changer le port MariaDB (ex: 3306 → 3307)
1. Dans `srcs/requirements/mariadb/conf/50-server.cnf`, ajouter :
```
port = 3307
```
2. Dans `srcs/docker-compose.yml`, modifier l'env de WordPress :
```yaml
WORDPRESS_DB_HOST: mariadb:3307
```
3. Rebuild :
```bash
make re
```

### Règle générale
- Modifier la config du service concerné
- Si un autre service dépend de ce port, le mettre à jour aussi
- Toujours `make re` pour rebuild
- Vérifier que le site fonctionne après le changement







