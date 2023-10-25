#!/bin/bash
# https://net2.com/how-to-share-folders-between-your-ubuntu-virtualbox-and-your-host-machine/
# sudo apt install virtualbox-guest-utils
RED=`tput setaf 1`
GREEN=`tput setaf 2`
YELLOW=`tput setaf 3`
PURPLE=`tput setaf 5`
BLUE=`tput setaf 6`
RESET=`tput sgr0`

if [ $(dpkg -l | grep -c "zsh " ) -eq 0 ]
then
  read -p "${GREEN}Do you want to ${PURPLE}Install zsh?${GREEN}:${YELLOW} [y/N]${RESET}" zsh
  if  [ "$zsh" = 'y' ]
  then
    if [ $(dpkg -l | grep -c "zsh " ) -eq 0 ]
    then
      echo "${GREEN}Installing ${BLUE}zsh${RESET}"
      sudo apt-get update
      sudo apt-get install ca-certificates curl gnupg lsb-release -y
      sudo apt install zsh -y
      sudo apt install git-core curl fonts-powerline -y
      sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)" -y
    else
      # sudo apt-get --purge remove zsh -y
      # sudo chmod 777 ~/.oh-my-zsh/tools/uninstall.sh
      # ~/.oh-my-zsh/tools/uninstall.sh -y
      echo "${BLUE}zsh${RED} already Installed${RESET}"
    fi
  fi
fi

# enter exit after zsh

read -p "${GREEN}Do you want to ${PURPLE}Install all?${GREEN}:${YELLOW} [y/N]${RESET}" all
if [ "$all" = 'N' ] || [ "$all" = 'n' ]
then
  read -p "${GREEN}Do you want to ${PURPLE}Update Your System?${GREEN}:${YELLOW} [y/N]${RESET}" update
  read -p "${GREEN}Do you want to ${PURPLE}Install git?${GREEN}:${YELLOW} [y/N]${RESET}" git
  read -p "${GREEN}Do you want to ${PURPLE}Install vim?${GREEN}:${YELLOW} [y/N]${RESET}" vim
  read -p "${GREEN}Do you want to ${PURPLE}Install FileZilla?${GREEN}:${YELLOW} [y/N]${RESET}" file
  read -p "${GREEN}Do you want to ${PURPLE}Install openssh?${GREEN}:${YELLOW} [y/N]${RESET}" openssh
  read -p "${GREEN}Do you want to ${PURPLE}Install curl?${GREEN}:${YELLOW} [y/N]${RESET}" curl
  read -p "${GREEN}Do you want to ${PURPLE}Install lsb-release?${GREEN}:${YELLOW} [y/N]${RESET}" lsb
  read -p "${GREEN}Do you want to ${PURPLE}Install Docker?${GREEN}:${YELLOW} [y/N]${RESET}" docker
  read -p "${GREEN}Do you want to Make docker run Without ${PURPLE}sudo${GREEN}:${YELLOW} [y/N]${RESET}" dsudo
  read -p "${GREEN}Do you want to ${PURPLE}Install Docker Compose?${GREEN}:${YELLOW} [y/N]${RESET}" dc
  read -p "${GREEN}Do you want to ${PURPLE}Chek docker${GREEN}:${YELLOW} [y/N]${RESET}" check_d
else
  update='y'
  git='y'
  vim='y'
  file='y'
  openssh='y'
  curl='y'
  lsb='y'
  docker='y'
  dsudo='y'
  # dc='y'
  check_d='y'
  fi
echo "${RED}════════════║Thank You, Please wait....║════════════${RESET}"

sleep 2

if [ "$update" = 'y' ]
then
  echo "${RED}Updating The System${RESET}"
  sudo apt-get update -y
  sudo apt-get upgrade -y
fi

if [ "$openssh" = 'y' ]
then
  if [ $(dpkg -l | grep -c openssh ) -eq 0 ];
  then
      echo "${GREEN}Installing ${BLUE}openssh${RESET}"
      sudo apt install ssh -y
      sudo apt install openssh-server -y
  else
    echo "${BLUE}openssh${RED} already Installed${RESET}"
  fi
fi

if [ "$git" = 'y' ]
then
  if ! [ -x "$(command -v git)" ]
  then
    echo "${GREEN}Installing ${BLUE}git${RESET}"
    sudo apt install git -y
  else
    echo "${BLUE}git${RED} already Installed${RESET}"
  fi
fi
if  [ "$vim" = 'y' ]
then
    if [ $(dpkg -l | grep -c "vim " ) -eq 0 ]
  then
    echo "${GREEN}Installing ${BLUE}vim${RESET}"
    sudo apt install vim -y
  else
    echo "${BLUE}vim${RED} already Installed${RESET}"
  fi
fi
if [ "$file" = 'y' ]
then
  if [ $(dpkg -l | grep -c filezilla ) -eq 0 ]
  then
    echo "${GREEN}Installing ${BLUE}FileZilla${RESET}"
    sudo apt install filezilla -y
  else
    echo "${BLUE}FileZilla${RED} already Installed${RESET}"
  fi
fi
if [ "$curl" = 'y' ]
then
  if [ $(dpkg -l | grep -c "curl " ) -eq 0 ]
  then
    echo "${GREEN}Installing ${BLUE}curl${RED}, ${BLUE}ca-certificates${RED} and ${BLUE}gnupg${RESET}"
    sudo apt-get install ca-certificates curl gnupg lsb-release -y
  else
    echo "${BLUE}curl${RED} already Installed${RESET}"
  fi
fi
if  [ "$lsb" = 'y' ]
then
  if ! [ -x "$(command -v lsb_release)" ]
  then
    echo "${GREEN}Installing ${BLUE}lsb-release${RESET}"
    sudo apt-get install lsb-release -y
  else
    echo "${BLUE}lsb_release${RED} already Installed${RESET}"
  fi
fi

if  [ "$docker" = 'y' ]
then
  if [ $(dpkg -l | grep -c docker ) -eq 0 ]
  then
    echo "${GREEN}Adding ${BLUE}Docker${GREEN}’s official ${BLUE}GPG key${RESET}"
    sudo apt-get remove docker docker-engine docker.io containerd runc
    sudo apt-get update
    sudo apt-get install -y \
    ca-certificates \
    curl \
    gnupg \
    lsb-release \
    docker \
    docker-compose
    # curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo gpg --dearmor -o /etc/apt/keyrings/docker.gpg
    #  echo \
    # "deb [arch=$(dpkg --print-architecture) signed-by=/etc/apt/keyrings/docker.gpg] https://download.docker.com/linux/ubuntu \
    # $(lsb_release -cs) stable" | sudo tee /etc/apt/sources.list.d/docker.list > /dev/null
    echo "${GREEN}Installing ${BLUE}docker${RESET}"
    sudo apt-get update
    sudo apt-get install docker-ce docker-ce-cli containerd.io docker-compose-plugin -y
    sudo docker run hello-world
    # echo "${GREEN}Make docker run as${BLUE} root${RESET}"
    # # sudo groupdel docker
    # if grep -q docker /etc/group
    # then
    #   echo "${GREEN}The Group${BLUE} docker${GREEN} Exists${RESET}"
    # else
    #   sudo groupadd docker
    # fi
    # sudo usermod -aG docker $USER
    # sudo newgrp docker
    # dsudo='u'
  else
      echo "${BLUE}docker${RED} already Installed${RESET}"
    fi
fi

if [ "$dsudo" = 'y' ]
then
  if grep -q docker /etc/group
  then
    echo "${GREEN}The Group${BLUE} docker${GREEN} Exists${RESET}"
    dsudo='n'
  else
    echo "${GREEN}Make docker run as${BLUE} root${RESET}"
    sudo groupadd docker
  fi
  sudo usermod -aG docker $USER
  sudo newgrp docker

fi

# if [ "$dc" = 'y' ]
# then
#   DOCKER_CONFIG=${DOCKER_CONFIG:-$HOME/.docker}
#   if ! [ -d $DOCKER_CONFIG ]
#   then
#     echo "${GREEN}Downloading the current stable release of Docker Compose${RESET}"
#     sudo apt-get update
#     mkdir -p $DOCKER_CONFIG/cli-plugins
#     curl -SL https://github.com/docker/compose/releases/download/v2.7.0/docker-compose-linux-x86_64 -o $DOCKER_CONFIG/cli-plugins/docker-compose
#     echo "${GREEN}Apply executable permissions to the binary${RESET}"
#     sudo  chmod +x $DOCKER_CONFIG/cli-plugins/docker-compose
#     sudo curl -L https://github.com/docker/compose/releases/download/1.25.3/docker-compose-`uname -s`-`uname -m` -o /usr/local/bin/docker-compose
#     sudo chmod +x /usr/local/bin/docker-compose
#     https://www.digitalocean.com/community/tutorials/how-to-install-docker-compose-on-debian-10
#     sudo curl -L https://github.com/docker/compose/releases/download/1.25.3/docker-compose-`uname -s`-`uname -m` -o /usr/local/bin/docker-compose
#     sudo chmod +x /usr/local/bin/docker-compose
#   else
#     echo "${BLUE}docker-compose${RED} already Installed${RESET}"
#   fi
# fi

if [ "$check_d" = 'y' ] &&  ! [ "$dsudo" = 'y' ] &&  ! [ "$dsudo" = 'u' ]
then
echo "${BLUE}Checking docker...${RESET}"
  sudo docker run hello-world
  docker run hello-world
fi

echo "${RED}════════════║End║════════════${RESET}"
if [ "$dsudo" = 'y' ] || [ "$dsudo" = 'u' ]
then
  echo "${RED}╔════════════════════════════║reeboot║════════════════════════╗${RESET}"
  sleep 10
  sudo reboot
fi

# mkdir /home/.docker
