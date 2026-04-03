# 🤖 ROS Pi Learn: C++ Hardware Integration (Docker Edition)

Welcome to the **ROS Pi Learn** repository\! This branch (`develop/add_cpp_node`) provides a containerized sandbox for bridging ROS with Raspberry Pi hardware using high-performance C++.

## 🎯 Why Docker?

By using Docker and Docker Compose, we eliminate the need to manually install ROS, compilers, or hardware libraries on your Raspberry Pi's host OS.

  * **Zero Host Pollution:** Your Pi stays clean; all dependencies live in the container.
  * **Hardware Access:** The configuration handles the complex task of mapping GPIO permissions into the virtual environment.
  * **Consistent Builds:** Ensure the C++ code compiles and runs exactly the same way every time.

## ⚙️ How it Works

The system is orchestrated via `docker-compose.yml`, which manages two primary services:

1.  **ros-master:** Handles the communication backbone.
2.  **led-driver:** The C++ node that subscribes to `/led_color` and translates those values into Hardware PWM signals using the `pigpio` library.

-----

## 🚀 Getting Started

### Prerequisites

  * A Raspberry Pi (3B+ recommended) with **Docker** and **Docker Compose** installed.
  * An RGB LED wired to the GPIO pins (see pinout below).

### 1\. Build and Launch

Navigate to the repository folder and run the following command. This will build the C++ node and start the ROS environment automatically:

```bash
docker-compose up --build
```

### 2\. Control the Hardware

In a new terminal window, use the running container to publish a ROS message. For example, to set the LED to **Purple**:

```bash
docker exec -it ros_pi_learn_led-driver_1 /bin/bash -c \
"source /ros_ws/devel/setup.bash && rostopic pub -1 /led_color std_msgs/ColorRGBA '{r: 1.0, g: 0.0, b: 1.0, a: 1.0}'"
```

-----

## 🛠 Repository Structure

  * **`Dockerfile`**: Defines the ARM-based ROS environment, installs `libpigpio-dev`, and compiles the C++ source.
  * **`docker-compose.yml`**: Configures the network and grants the container `privileged` access to `/dev/gpiomem`.
  * **`src/`**: Contains the C++ source code for the LED driver.

### 📍 Hardware Setup & Pinout

*(Note: Always use current-limiting resistors (e.g., 220Ω) to protect your Pi's GPIO pins\!)*

-----

## 📚 Technical Deep Dive

  * **[pigpio C++ Interface](https://abyz.me.uk/rpi/pigpio/cif.html)**: Used for precise, hardware-timed PWM which prevents flickering compared to software-based PWM.
  * **[Dockerizing ROS Nodes](https://roboticseabass.com/2021/04/21/docker-and-ros/)**: Best practices for running robotics stacks in containers.
  * **[Privileged Containers](https://www.google.com/search?q=https://docs.docker.com/engine/reference/run/%23runtime-privilege-and-linux-capabilities)**: Explains why we use the `privileged: true` flag to interact with physical memory and GPIO.

-----

## 💡 Future Expansion

  * **ROS 2 Humble Migration:** Transitioning to `rclcpp` and using the ROS 2 Docker images.
  * **Industrial UI:** Adding a `rosbridge` container to serve a glassmorphism-style web dashboard for real-time control.
  * **Telemetry Integration:** Linking the LED color to system health or network traffic metrics.