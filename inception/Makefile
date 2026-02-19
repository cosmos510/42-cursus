all: build

build:
	docker compose -f srcs/docker-compose.yml up -d --build

down:
	docker compose -f srcs/docker-compose.yml down

clean: down
	docker system prune -af
	docker volume prune -f

fclean: clean
	docker volume rm inception_wordpress_data inception_mariadb_data 2>/dev/null || true

re: fclean all

.PHONY: all build down clean fclean re