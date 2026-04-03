#!/bin/bash
sudo apt update && sudo apt upgrade -y --fix-missing
sudo apt install -y --fix-missing tmux curl ssh git vim

curl -fsSL https://get.docker.com -o get-docker.sh
sudo sh get-docker.sh
sudo apt install -y docker-compose
sudo usermod -aG docker $USER
sudo systemctl enable docker

exec su -l $USER
