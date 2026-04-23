
export ROS_DOMAIN_ID=0
export ROS_LOCALHOST_ONLY=0

source /opt/ros/$ROS_DISTRO/setup.sh

source /usr/share/colcon_argcomplete/hook/colcon-argcomplete.bash
eval "$(register-python-argcomplete3 ros2 2>/dev/null || register-python-argcomplete ros2)"
eval "$(register-python-argcomplete3 colcon 2>/dev/null || register-python-argcomplete colcon)"