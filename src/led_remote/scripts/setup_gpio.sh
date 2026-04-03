#!/bin/bash
apt install -y python3-lgpio python3-pigpio python3-rpi.gpio
usermod -aG gpio $USER || true
