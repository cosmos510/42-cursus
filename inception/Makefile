all: build

build:
	mkdir -p $(HOME)/data/wordpress
	mkdir -p $(HOME)/data/mariadb
	docker compose -f srcs/docker-compose.yml up -d --build

down:
	docker compose -f srcs/docker-compose.yml down

clean: down
	docker system prune -af
	docker volume prune -f

fclean: clean
	rm -rf $(HOME)/data

re: fclean all

.PHONY: all build down clean fclean re