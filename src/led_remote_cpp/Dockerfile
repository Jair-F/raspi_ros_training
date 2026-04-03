FROM ros:jazzy-ros-base AS builder
WORKDIR /workspace
COPY . .

RUN echo ". /opt/ros/jazzy/setup.bash" >> /root/.bashrc
SHELL ["/bin/bash", "-c"]

RUN apt update
RUN scripts/setup_env.sh
RUN source /opt/ros/jazzy/setup.bash && \
    rosdep install --from-paths src -y --ignore-src && \
    colcon build


FROM ros:jazzy-ros-core
WORKDIR /workspace
SHELL ["/bin/bash", "-c"]

COPY . .
COPY --from=builder /workspace/install ./install

RUN apt update && apt upgrade -y
RUN scripts/setup_env.sh

RUN echo "source /opt/ros/jazzy/setup.bash" >> ~/.bashrc && \
    echo "source install/setup.bash" >> ~/.bashrc

ENTRYPOINT ["./entrypoint.sh"]
CMD ["ros2", "launch", "launch/remote.launch.py"]