FROM ros:jazzy-ros-base AS builder
WORKDIR /workspace
COPY . .

RUN colcon build

FROM ros:jazzy-ros-core
WORKDIR /workspace
ENV PIP_NO_CACHE_DIR=1
RUN apt update && apt upgrade -y
RUN apt install -y python3-pip

COPY . .
COPY --from=builder /workspace/install ./install

RUN scripts/setup_gpio.sh

RUN python3 -m pip install --break-system-packages -r requirements.txt

RUN echo ". /opt/ros/jazzy/setup.bash" >> ~/.bashrc && \
    echo ". install/setup.bash" >> ~/.bashrc

ENTRYPOINT ["./entrypoint.sh"]
CMD ["ros2", "launch", "launch/remote.launch.py"]