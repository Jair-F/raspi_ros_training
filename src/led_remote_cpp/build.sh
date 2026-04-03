#!/bin/bash

rosdep install --from-paths src -y --ignore-src
colcon build --symlink-install