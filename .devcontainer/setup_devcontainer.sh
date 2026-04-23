#!/bin/bash

sudo apt install -y tmux

git config --global --add safe.directory "$(pwd)"

echo "source $(pwd)/ros_settings.sh" >> ~/.bashrc
echo "source /usr/share/colcon_cd/function/colcon_cd.sh" >> ~/.bashrc
echo "export _colcon_cd_root=/opt/ros/$ROS_DISTRO/" >> ~/.bashrc

# pip install -r requirements.txt
# pre-commit install
# pre-commit run

source ~/.bashrc
# cd src && rm -rf build install log && colcon build --symlink-install && cd -
# source src/install/setup.bash

echo -e "\n"
echo "run \"sudo xhost +local:docker\" on host"
