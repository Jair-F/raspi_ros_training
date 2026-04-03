from gpiozero import RGBLED
from time import sleep

led = RGBLED(red=17, green=27, blue=22)

if __name__ == "__main__":
    while True:
        led.color = (1, 0, 0) # Red
        sleep(1)
        led.color = (0, 1, 0) # Green
        sleep(1)
        led.color = (0, 0, 1) # Blue
        sleep(1)

        # Mix colors (e.g., Purple)
        led.color = (0.5, 0, 0.5)
        sleep(1)

        led.off()
        sleep(1)
