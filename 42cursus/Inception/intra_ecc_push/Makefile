# Define the name of your Docker Compose file
DOCKER_COMPOSE_FILE = srcs/docker-compose.yml

build:
	docker-compose -f $(DOCKER_COMPOSE_FILE) build

clean:
	docker-compose -f $(DOCKER_COMPOSE_FILE) down --volumes --remove-orphans
	docker container prune --filter "until=$(shell date -u -d '1 minute ago' '+%Y-%m-%dT%H:%M:%SZ')" -f

cleanall: clean
	docker system prune --all --volumes --force

up: resolve
	@if [ ! -d /home/ecoli/data/mariadb_data ]; then \
		mkdir -p /home/ecoli/data/mariadb_data; \
	fi
	@if [ ! -d /home/ecoli/data/wordpress_data ]; then \
		mkdir -p /home/ecoli/data/wordpress_data; \
	fi
	docker-compose -f $(DOCKER_COMPOSE_FILE) up -d --build

down:

	docker-compose -f $(DOCKER_COMPOSE_FILE) down

logs:
	docker-compose -f $(DOCKER_COMPOSE_FILE) logs -f

status:
	docker ps -a

resolve:
	@grep -q "127.0.0.1 ecoli.42.fr" /etc/hosts; \
	if [ $$? -ne 0 ]; then \
		echo "127.0.0.1 ecoli.42.fr" | sudo tee -a /etc/hosts; \
	fi
	@grep -q "127.0.0.1 www.ecoli.42.fr" /etc/hosts; \
	if [ $$? -ne 0 ]; then \
		echo "127.0.0.1 www.ecoli.42.fr" | sudo tee -a /etc/hosts; \
	fi

# Define a help target to display available Makefile targets
help:
	@echo "Check if file .env is present or if it was ignored by git"
	@echo ""
	@echo "Available Makefile targets:"
	@echo "  build    : Build Docker images using Docker Compose"
	@echo "  clean    : Clean up containers and their networks and volumes"
	@echo "  cleanall : Clean up containers and remove unused images"
	@echo "  up       : Run containers using Docker Compose in the background"
	@echo "  down     : Stop and remove containers defined in the Docker Compose file"
	@echo "  logs     : View logs of running containers"
	@echo "  status   : List the status of all containers"
	@echo "  resolve  : Setup in /etc/hosts the servar name resolution"
	@echo "  help     : Display this help message"
	@echo
	@echo "If needed, use 'docker exec -it <name_container> sh' to enter the container"
	@echo "Otherwise you can enter in an alpine container using 'docker run -it --rm alpine:3.14 /bin/sh'"

# Set the default target when 'make' is called without any arguments
.DEFAULT_GOAL := help
