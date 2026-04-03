#include <cstdio>
#include <rclcpp/rclcpp.hpp>
#include <wiringPi.h>
#include <softPwm.h>
#include <unistd.h>

class RemoteNode : public rclcpp::Node {
public:
    RemoteNode() : Node("remote_node") {
        _init_gpio();
    }

    ~RemoteNode() {
        softPwmWrite(led_pin_, 0);
        digitalWrite(led_pin_, LOW);
        RCLCPP_INFO(this->get_logger(), "GPIO cleaned up.");
    }

private:
    const int led_pin_ = 17; // GPIO 17 (BCM numbering)

    void _init_gpio() {
        if (wiringPiSetupGpio() == -1) {
            RCLCPP_ERROR(this->get_logger(), "WiringPi initialization failed");
            throw std::runtime_error("GPIO Init Failed");
        }

        // 2. Setup PWM
        // WiringPi's hardware PWM is limited to specific pins (like 18).
        // For Pin 17, we use softPwm which works on any GPIO.
        // softPwmCreate(pin, initial_value, range) -> range 0-100
        if (softPwmCreate(led_pin_, 0, 100) != 0) {
            RCLCPP_ERROR(this->get_logger(), "SoftPWM creation failed");
            throw std::runtime_error("PWM Init Failed");
        }

        // Set to "half power" (50 out of 100)
        softPwmWrite(led_pin_, 50);

        RCLCPP_INFO(this->get_logger(), "WiringPi initialized. LED on Pin %d at 50%% power.", led_pin_);
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
