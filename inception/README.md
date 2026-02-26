# Inception

*This project has been created as part of the 42 curriculum by maxmarti.*

## Description

Inception is a system administration project that involves setting up a small infrastructure using Docker and Docker Compose. The goal is to virtualize several Docker images by creating them in a personal virtual machine, implementing a multi-container application with NGINX, WordPress, and MariaDB.

## Instructions

### Prerequisites
- Docker and Docker Compose installed
- Make

### Setup
1. Clone the repository
2. Create the `.env` file:
```bash
cp srcs/.env.example srcs/.env
# Edit srcs/.env with your login
```

3. Create secrets:
```bash
mkdir -p secrets
echo "your_password" > secrets/db_root_password.txt
echo "your_password" > secrets/db_password.txt
echo "your_password" > secrets/wp_admin_password.txt
echo "your_password" > secrets/wp_user_password.txt
```

4. Add domain to `/etc/hosts`:
```bash
echo "127.0.0.1 login.42.fr" | sudo tee -a /etc/hosts
```

### Build and Run
```bash
make        # Build and start containers
make down   # Stop containers
make clean  # Stop and clean system
make fclean # Full cleanup including volumes
make re     # Rebuild everything
```

### Access
- Website: `https://login.42.fr`
- WordPress Admin: `https://login.42.fr/wp-admin`

## Project Architecture

### Services
- **NGINX**: Web server with TLS v1.2/v1.3 (port 443 only)
- **WordPress**: CMS with PHP-FPM 7.4
- **MariaDB**: Database server

### Docker Network
All services communicate through a custom bridge network (`inception`), ensuring isolation and secure inter-container communication.

### Volumes
- `wordpress_data`: Persistent WordPress files
- `mariadb_data`: Persistent database data

## Design Choices

### Virtual Machines vs Docker
- **VMs**: Full OS virtualization, heavy resource usage, slower startup
- **Docker**: Container-based, lightweight, shares host kernel, faster deployment
- **Choice**: Docker for efficiency and portability

### Secrets vs Environment Variables
- **Environment Variables**: Visible in container inspect, less secure
- **Docker Secrets**: Encrypted at rest, mounted as files in `/run/secrets/`
- **Choice**: Docker secrets for sensitive data (passwords)

### Docker Network vs Host Network
- **Host Network**: Container shares host network stack, no isolation
- **Docker Network**: Isolated bridge network, containers communicate by service name
- **Choice**: Custom bridge network for security and service discovery

### Docker Volumes vs Bind Mounts
- **Bind Mounts**: Direct host path mapping, OS-dependent
- **Docker Volumes**: Managed by Docker, portable, better performance
- **Choice**: Named volumes for data persistence and portability

## Resources

### Documentation
- [Docker Documentation](https://docs.docker.com/)
- [Docker Compose Reference](https://docs.docker.com/compose/)
- [NGINX Documentation](https://nginx.org/en/docs/)
- [WordPress Documentation](https://wordpress.org/documentation/)
- [MariaDB Documentation](https://mariadb.com/kb/en/)

