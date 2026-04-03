#include <cstdio>
#include <rclcpp/rclcpp.hpp>
#include "std_msgs/msg/color_rgba.hpp"
#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

class RemoteNode : public rclcpp::Node {
public:
    RemoteNode() : Node("remote_node") {
        this->_init_gpio();
        // this->create_subscription<>("cmd_color")
    }

    ~RemoteNode() {
        this->_free_gpios();
    }

private:
    const int _led_red_pin = 17; // GPIO 17 (BCM numbering)
    const int _led_green_pin = 18;
    const int _led_blue_pin = 19;

    void _free_single_gpio(const int _pin) {
        softPwmWrite(_pin, 0);
        digitalWrite(_pin, LOW);
    }

    void _free_gpios() {
        this->_free_single_gpio(this->_led_red_pin);
        this->_free_single_gpio(this->_led_green_pin);
        this->_free_single_gpio(this->_led_blue_pin);

        RCLCPP_INFO(this->get_logger(), "GPIO cleaned up.");
    }

    void _init_gpio() {
        if (wiringPiSetupGpio() == -1) {
            RCLCPP_ERROR(this->get_logger(), "WiringPi initialization failed");
            throw std::runtime_error("GPIO Init Failed");
        }

        // 2. Setup PWM
        // WiringPi's hardware PWM is limited to specific pins (like 18).
        // For Pin 17, we use softPwm which works on any GPIO.
        // softPwmCreate(pin, initial_value, range) -> range 0-100
        if ((softPwmCreate(this->_led_red_pin, 0, 1000 ==
             softPwmCreate(this->_led_blue_pin, 0, 1000)) == 
             (softPwmCreate(this->_led_green_pin, 0, 1000))) != 0) {
            RCLCPP_ERROR(this->get_logger(), "SoftPWM creation failed");
            throw std::runtime_error("PWM Init Failed");
        }
    }

    void _set_led_color(float red, float blue, float green) {
        softPwmWrite(this->_led_red_pin, red * 1000.0);
        softPwmWrite(this->_led_green_pin, green * 1000.0);
        softPwmWrite(this->_led_blue_pin, blue * 1000.0);

        RCLCPP_INFO(this->get_logger(), "WiringPi initialized. LED on Pin %d at 50%% power.", _led_red_pin);
    }
};

int main(int argc, char ** argv)
{
    rclcpp::init(argc, argv);
    
    try {
        auto node = std::make_shared<RemoteNode>();
        rclcpp::spin(node);
    } catch (const std::runtime_error& e) {
        fprintf(stderr, "Node failed: %s\n", e.what());
    }

    rclcpp::shutdown();
    return 0;
}
