# FROM osrf/ros:jazzy-desktop-full
FROM osrf/ros:humble-desktop-full
RUN apt update && apt upgrade -y

RUN apt install -y ssh git
# GUI - on host: sudo xhost +local:docker
ENV DISPLAY=$DISPLAY
ENV XAUTHORITY=/tmp/.docker.xauth

RUN apt install -y bash-completion python3-pip python3-argcomplete python3-colcon-argcomplete

RUN apt install -y ros-jazzy-turtlesim ros-jazzy-rqt ros-jazzy-rqt-gui python3-colcon-core python3-colcon-common-extensions
RUN apt install -y ros-jazzy-fluent-rviz

WORKDIR /workspace
# ADD requirements.txt .
# RUN pip install -r requirements.txt