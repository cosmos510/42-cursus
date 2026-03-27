# User Documentation

## Starting and Stopping

```bash
make        # Build and start the infrastructure
make up     # Start without rebuilding
make down   # Stop the infrastructure (data is preserved)
make fclean # Stop and delete all data
```

## Accessing the Website

- Website: `https://login.42.fr`
- Admin panel: `https://login.42.fr/wp-admin`

Replace `login` with the login configured in `srcs/.env`.

A self-signed certificate warning will appear — accept it to proceed.

## Managing Credentials

Passwords are stored as Docker secrets in the `secrets/` directory:
- `secrets/db_root_password.txt` — MariaDB root password
- `secrets/db_password.txt` — WordPress database user password
- `secrets/wp_admin_password.txt` — WordPress admin password
- `secrets/wp_user_password.txt` — WordPress regular user password

To change a password, edit the corresponding file and rebuild:
```bash
make fclean
make
```

## Basic Checks

Check that all containers are running:
```bash
docker compose -f srcs/docker-compose.yml ps
```

Check container logs:
```bash
docker logs nginx
docker logs wordpress
docker logs mariadb
```
