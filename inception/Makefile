all: build

build:
	@mkdir -p /home/$$(grep LOGIN srcs/.env | cut -d'=' -f2)/data/wordpress
	@mkdir -p /home/$$(grep LOGIN srcs/.env | cut -d'=' -f2)/data/mariadb
	docker compose -f srcs/docker-compose.yml up -d --build

up:
	docker compose -f srcs/docker-compose.yml up -d

down:
	docker compose -f srcs/docker-compose.yml down

clean: down
	docker system prune -af
	docker volume prune -f

fclean: clean
	docker volume rm inception_wordpress_data inception_mariadb_data 2>/dev/null || true
	sudo rm -rf /home/maxmarti/data/mariadb/*
	sudo rm -rf /home/maxmarti/data/wordpress/*

re: fclean all

.PHONY: all build up down clean fclean re