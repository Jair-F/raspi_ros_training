import rclpy
from rclpy.node import Node
from std_msgs.msg._color_rgba import ColorRGBA
from gpiozero import RGBLED

class RemoteNode(Node):
    def __init__(self):
        super().__init__("remote_node")
        self._subscriber = self.create_subscription(ColorRGBA, 'cmd_color', self._set_color_callback, 1)
        self._led = RGBLED(red=17, green=27, blue=22)

    def _set_color_callback(self, msg:ColorRGBA):
        self._led.color = (msg.r, msg.g, msg.b)

def main(args:list[str] | None = None):
    rclpy.init(args=args)
    node = RemoteNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()
