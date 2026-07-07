# Developer Documentation

## Prerequisites

- Docker and Docker Compose (v2 plugin)
- Make
- Root/sudo access (for /etc/hosts and Docker)

## Setup

1. Clone the repository

2. Create the secrets:
```bash
mkdir -p secrets
echo "your_db_root_password" > secrets/db_root_password.txt
echo "your_db_password" > secrets/db_password.txt
echo "your_wp_admin_password" > secrets/wp_admin_password.txt
echo "your_wp_user_password" > secrets/wp_user_password.txt
```

3. Configure `srcs/.env`:
```
LOGIN=maxmarti
DOMAIN_NAME=maxmarti.42.fr
MYSQL_DATABASE=wordpress
MYSQL_USER=wpuser
WORDPRESS_ADMIN_USER=maxmarti
WORDPRESS_ADMIN_EMAIL=maxmarti@example.com
WORDPRESS_USER=user
WORDPRESS_USER_EMAIL=user@example.com
```

4. Add the domain to `/etc/hosts`:
```bash
echo "127.0.0.1 maxmarti.42.fr" | sudo tee -a /etc/hosts
```

5. Create data directories:
```bash
sudo mkdir -p /home/maxmarti/data/wordpress
sudo mkdir -p /home/maxmarti/data/mariadb
```

## Makefile Usage

| Command | Action |
|---------|--------|
| `make` | Build and start all containers |
| `make down` | Stop containers |
| `make clean` | Stop + remove Docker images and volumes |
| `make fclean` | Full cleanup including persistent data on disk |
| `make re` | Full rebuild (fclean + make) |

## Docker Compose Commands

```bash
# Build and start
docker compose -f srcs/docker-compose.yml up -d --build

# Stop
docker compose -f srcs/docker-compose.yml down

# Status
docker compose -f srcs/docker-compose.yml ps

# Logs (all services)
docker compose -f srcs/docker-compose.yml logs

# Logs (single service)
docker compose -f srcs/docker-compose.yml logs nginx
```

## Architecture

```
Client → nginx (port 443, TLS) → wordpress (port 9000, PHP-FPM) → mariadb (port 3306)
```

All services communicate through a custom Docker bridge network named `inception`.

## Data Persistence

Volumes are bound to the host filesystem:
- WordPress files: `/home/maxmarti/data/wordpress` → `/var/www/html`
- MariaDB data: `/home/maxmarti/data/mariadb` → `/var/lib/mysql`

Data survives:
- Container restarts (`make down` + `make`)
- VM reboots
- Image rebuilds (`make re`)

Data is destroyed only by `make fclean` (which removes the host directories).
