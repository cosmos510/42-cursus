# User Documentation

## Start / Stop the Stack

```bash
make        # Build and start all containers
make down   # Stop all containers
make re     # Rebuild and restart everything
```

## Access the Website

- Website: https://maxmarti.42.fr
- Admin panel: https://maxmarti.42.fr/wp-admin

> Note: The site uses a self-signed SSL certificate. Your browser will show a security warning — this is expected.

## Credentials

- **Admin**: `maxmarti` / password in `secrets/wp_admin_password.txt`
- **User**: `user` / password in `secrets/wp_user_password.txt`
- **Database**: `wpuser` / password in `secrets/db_password.txt`

## Manage Credentials

Passwords are stored as Docker secrets in the `secrets/` directory:
- `db_root_password.txt` — MariaDB root password
- `db_password.txt` — MariaDB user password
- `wp_admin_password.txt` — WordPress admin password
- `wp_user_password.txt` — WordPress user password

To change a password, edit the corresponding file then rebuild:
```bash
make re
```

## Basic Checks

```bash
# Check container status
docker compose -f srcs/docker-compose.yml ps

# Check logs
docker logs nginx
docker logs wordpress
docker logs mariadb

# Verify HTTPS is working
curl -k https://maxmarti.42.fr

# Verify HTTP is not accessible (port 80 closed)
curl http://maxmarti.42.fr
# Expected: Connection refused

# Verify TLS version
openssl s_client -connect maxmarti.42.fr:443 -tls1_2
openssl s_client -connect maxmarti.42.fr:443 -tls1_3

# Check database connectivity
docker exec -it mariadb mysql -u wpuser -p -e "SHOW DATABASES;"
```
