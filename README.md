# 🤖 ROS Pi Learn: C++ Hardware Integration

Welcome to the **ROS Pi Learn** repository\! This specific branch (`develop/add_cpp_node`) serves as a practical sandbox for bridging the Robot Operating System (ROS) with low-level physical hardware using C++.

## 🎯 Why does this repo exist?

When developing robotics systems, the leap from software simulation to physical hardware is often a major hurdle. This repository acts as a foundational template for systems-level hardware control. It demonstrates how to move beyond standard data nodes and interact directly with the real world—specifically, the GPIO pins of a Raspberry Pi—using high-performance C++.

## ⚙️ What it does & How it works

This package introduces a custom C++ ROS node designed to act as a hardware driver for an RGB LED.

**The Core Workflow:**

1.  **Listen:** The node subscribes to a ROS topic expecting a standardized color message.
2.  **Translate:** It extracts the Red, Green, Blue, and Alpha (intensity) float values.
3.  **Execute:** Using a C++ hardware library, it maps these numerical values to Hardware PWM (Pulse Width Modulation) signals.
4.  **Output:** The signals are routed directly to the Raspberry Pi's GPIO pins, mixing the channels to change the physical LED color in real-time.

### 📍 Hardware Setup & Pinout

To run this project, you will need to wire an RGB LED to your Raspberry Pi 3B+. Below is the GPIO diagram for reference when mapping your pins in the C++ code:

*(Note: Always ensure you use appropriate current-limiting resistors for your LED to protect the Pi's GPIO pins\!)*

-----

## 🚀 Getting Started

### Prerequisites

  * A Raspberry Pi (3B+ recommended) running a compatible Linux distribution.
  * ROS Workspace configured.
  * A C++ GPIO library installed on the Pi (e.g., `pigpio` or `wiringPi`).

### Building the Package

Navigate to your workspace and build the package using the standard C++ compilation pipeline:

```bash
cd ~/catkin_ws
catkin_make
source devel/setup.bash
```

### Running the Example

1.  **Start the ROS Master:**
    ```bash
    roscore
    ```
2.  **Run the Hardware Node:**
    ```bash
    rosrun ros_pi_learn cpp_led_node
    ```
3.  **Publish a Color Command:**
    Open a new terminal and publish a message to light the LED up in **Purple** (100% Red, 100% Blue):
    ```bash
    rostopic pub /led_color std_msgs/ColorRGBA "{r: 1.0, g: 0.0, b: 1.0, a: 1.0}"
    ```

-----

## 📚 Deep Dive Resources

Ready to look under the hood? Explore these resources to understand the underlying mechanics of this implementation:

  * **[ROS std\_msgs/ColorRGBA API](https://docs.ros.org/en/noetic/api/std_msgs/html/msg/ColorRGBA.html)** - Understand the exact structure and float boundaries of the message driving this node.
  * **[pigpio C++ Library](https://abyz.me.uk/rpi/pigpio/cif.html)** - Excellent documentation for precise C/C++ hardware control and hardware-timed PWM on the Raspberry Pi.
  * **[Writing a Publisher and Subscriber (C++)](http://wiki.ros.org/ROS/Tutorials/WritingPublisherSubscriber%28c%2B%2B%29)** - The foundational ROS tutorial for the C++ architecture utilized in this project.
  * **[Understanding Pulse Width Modulation](https://learn.sparkfun.com/tutorials/pulse-width-modulation/all)** - A visual guide to how digital pins simulate analog voltages to mix physical colors.

-----

## 💡 Ideas for Expansion

Looking to take this codebase to the next level? Here are a few architectural upgrades to consider for future branches:

  * **Containerized Deployment:** Wrap the ROS environment in a Docker `devcontainer`. This allows you to keep the host Pi OS completely clean, automate the C++ dependency installation, and ensure your build environment is perfectly reproducible.
  * **Web Telemetry Dashboard:** Build a responsive, industrial-style web interface using HTML and CSS. By integrating `rosbridge_suite`, you could create precise numeric input controls or a glassmorphism UI to drive the LED color directly from a browser or mobile device.
  * **ROS 2 Humble Migration:** Upgrade the architecture and rewrite the node utilizing `rclcpp`. This modernizes the stack and provides a great opportunity to explore how DDS middleware performs on embedded hardware compared to traditional ROS 1 TCP connections.
  * **System State Visualization:** Instead of manual color commands, link the node to a telemetry stream (like a MAVLink parser). Use the LED as a physical status indicator—for instance, pulsing green for a nominal state, and solid red if a network spoofing attempt or process error is detected.


![Raspberry Pi 3b+ pinout](https://s3.amazonaws.com/youngwonks/Blogs/GPIO_diagram.jpg)