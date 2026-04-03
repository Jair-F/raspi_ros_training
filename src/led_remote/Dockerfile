# FROM mcr.microsoft.com/vscode/devcontainers/base:ubuntu-24.04
FROM ros:jazzy-ros-base AS builder
WORKDIR /workspace
COPY . .

# RUN apt update && apt upgrade -y
# RUN apt update && apt install -y python3-rpi.gpio
RUN ls -la
RUN colcon build

FROM ros:jazzy-ros-core
# USER vscode
WORKDIR /workspace
COPY . .
COPY --from=builder /workspace/install ./install


# RUN apt update && apt upgrade -y
RUN apt update && apt install -y python3-pip python3-rpi.gpio
RUN usermod -aG gpio $USER || true

RUN python3 -m pip install --break-system-packages -r requirements.txt

RUN echo ". /opt/ros/jazzy/setup.bash" >> ~/.bashrc && \
    echo ". install/setup.bash" >> ~/.bashrc

ENTRYPOINT ["./entrypoint.sh"]
CMD ["ros2", "launch", "launch/remote.launch.py"]