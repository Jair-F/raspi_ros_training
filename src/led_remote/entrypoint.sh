#!/bin/bash
set -e

# Source ROS 2 environments
source "/opt/ros/jazzy/setup.bash"
source "/workspace/install/setup.bash"

exec "$@"