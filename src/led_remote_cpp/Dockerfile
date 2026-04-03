FROM ros:jazzy-ros-base AS builder
WORKDIR /workspace
COPY . .

RUN apt update
RUN scripts/setup_env.sh
RUN ./build.sh


FROM ros:jazzy-ros-core
WORKDIR /workspace
ENV PIP_NO_CACHE_DIR=1

COPY . .
COPY --from=builder /workspace/install ./install

RUN apt update && apt upgrade -y
RUN scripts/setup_env.sh

RUN echo ". /opt/ros/jazzy/setup.bash" >> ~/.bashrc && \
    echo ". install/setup.bash" >> ~/.bashrc

ENTRYPOINT ["./entrypoint.sh"]
CMD ["ros2", "launch", "launch/remote.launch.py"]