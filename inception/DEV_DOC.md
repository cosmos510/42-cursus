# Developer Documentation

## Prerequisites

- Docker and Docker Compose
- Make
- A virtual machine running Debian/Ubuntu

## Setup

1. Clone the repository
2. Copy and edit the environment file:
```bash
cp srcs/.env.example srcs/.env
```
3. Create the secrets:
```bash
mkdir -p secrets
echo "your_password" > secrets/db_root_password.txt
echo "your_password" > secrets/db_password.txt
echo "your_password" > secrets/wp_admin_password.txt
echo "your_password" > secrets/wp_user_password.txt
```
4. Add the domain to `/etc/hosts`:
```bash
echo "127.0.0.1 login.42.fr" | sudo tee -a /etc/hosts
```

## Makefile Usage

| Command      | Description                              |
|--------------|------------------------------------------|
| `make`       | Build images and start containers        |
| `make up`    | Start containers without rebuilding      |
| `make down`  | Stop containers                          |
| `make clean` | Stop containers and prune Docker system  |
| `make fclean`| Full cleanup including volumes           |
| `make re`    | Rebuild everything from scratch          |

## Docker Compose Commands

```bash
docker compose -f srcs/docker-compose.yml ps      # List containers
docker compose -f srcs/docker-compose.yml logs -f  # Follow logs
docker compose -f srcs/docker-compose.yml exec mariadb mysql -u wpuser -p wordpress  # Access DB
```

## Data Persistence

Data is stored on the host at `/home/$USER/data/`:
- `/home/$USER/data/wordpress` — WordPress files
- `/home/$USER/data/mariadb` — MariaDB database

These directories are created automatically by `make` and mounted as Docker volumes. Data survives `make down` and `make clean`, but is removed by `make fclean`.

## Project Structure

```
inception/
├── Makefile
├── srcs/
│   ├── .env
│   ├── docker-compose.yml
│   └── requirements/
│       ├── mariadb/
│       │   ├── Dockerfile
│       │   ├── conf/50-server.cnf
│       │   └── tools/setup.sh
│       ├── nginx/
│       │   ├── Dockerfile
│       │   ├── conf/nginx.conf
│       │   └── tools/entrypoint.sh
│       └── wordpress/
│           ├── Dockerfile
│           ├── conf/www.conf
│           └── tools/setup.sh
└── secrets/
```
