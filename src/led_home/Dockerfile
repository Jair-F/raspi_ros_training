FROM ros:jazzy-ros-base AS builder
WORKDIR /workspace
COPY . .

RUN colcon build

FROM ros:jazzy-ros-core
WORKDIR /workspace
ENV PIP_NO_CACHE_DIR=1

COPY . .
COPY --from=builder /workspace/install ./install


RUN apt update && apt upgrade -y
RUN apt install -y python3-pip

RUN python3 -m pip install --break-system-packages -r requirements.txt

RUN echo ". /opt/ros/jazzy/setup.bash" >> ~/.bashrc && \
    echo ". install/setup.bash" >> ~/.bashrc

EXPOSE 1234/tcp

ENTRYPOINT ["./entrypoint.sh"]
CMD ["ros2", "launch", "launch/home.launch.py"]