#!/bin/bash

#Colors
RED="\e[1;31m"
GREEN="\e[1;32m"
YELLOW="\e[1;33m"
BLUE="\e[1;34m"
DEFAULT="\e[0m"

echo -e "${YELLOW}Do you want to Update the system?: [Y/n]${DEFAULT}"
read -r confirmation
if [[ ! "$confirmation" =~ ^[Nn]|[Nn][Oo]$ ]]; then
	sudo apt-get update -y
	sudo apt-get upgrade -y
fi

echo -e "${YELLOW}Do you want to Install openssh?: [y/N]${DEFAULT}"
read -r confirmation
if [[ "$confirmation" =~ ^[Yy]|[Yy][Ee][Ss]$ ]]; then
	if [ $(dpkg -l | grep -c "openssh " ) -eq 0 ]; then
		echo "Installing openssh"
		sudo apt install -y \
			ssh \
			openssh-server
		echo -e "${GREEN}  \"openssh Installed\"${DEFAULT}"
	else
		echo -e "${GREEN}  \"openssh already Installed\"${DEFAULT}"
	fi
fi

echo -e "${YELLOW}Do you want to Install docker?: [Y/n]${DEFAULT}"
read -r confirmation
if [[ ! "$confirmation" =~ ^[Yy]|[Yy][Ee][Ss]$ ]]; then
	if [ $(dpkg -l | grep -c "docker " ) -eq 0 ]; then

		echo -e "${BLUE}Do a complete Cleanup${DEFAULT}"
			sudo apt remove docker-desktop
			rm -r $HOME/.docker/desktop
			sudo rm /usr/local/bin/com.docker.cli
			sudo apt purge docker-desktop

			sudo apt-get install -y \
				ca-certificates \
				curl \
				gnupg \
				make

		echo -e "${BLUE}Adding Docker's official GPG key${DEFAULT}"
			sudo mkdir -m 0755 -p /etc/apt/keyrings
			curl -fsSL  https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
			
			echo \
			"deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
			$(. /etc/os-release && echo $VERSION_CODENAME) stable" | \
			sudo tee /etc/apt/sources.list.d/docker.list > /dev/null

			sudo apt-get update
			sudo apt-get install -y \
				docker-ce \
				docker-ce-cli \
				containerd.io \
				docker-buildx-plugin \
				docker-compose-plugin \
				docker-compose

		echo -e "${BLUE}Test Docker installation${DEFAULT}"
			sudo docker run hello-world

		echo -e "${BLUE}Make Docker run as root${DEFAULT}"
			sudo groupadd docker
			sudo usermod -aG docker $USER
			newgrp docker

		echo -e "${BLUE}Test Docker installation without sudo${DEFAULT}"
			docker run hello-world
			if [ $? -ne 0 ]; then
				echo -e "${RED}  \"Something went wrong with docker Installation\"${DEFAULT}"
			else
				echo -e "${GREEN}  \"All docker dependencies Installed\"${DEFAULT}"
			fi
	else
		echo -e "${GREEN}  \"docker already Installed\"${DEFAULT}"
	fi
fi

exit 0