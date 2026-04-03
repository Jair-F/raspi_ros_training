import rclpy
from rclpy.node import Node
from std_msgs.msg._color_rgba import ColorRGBA

class HomeNode(Node):
    def __init__(self):
        super().__init__("home_node")
        self._publisher = self.create_publisher(ColorRGBA, 'cmd_color', 1)

        self._timer = self.create_timer(1, self._send_color_callback)
    
    def _send_color_callback(self):
        self.get_logger().info(F"sending color command to LED")
        color = ColorRGBA(r=1., g=1., b=1., a=1.)
        self._publisher.publish(color)


def main(args=None):
    rclpy.init(args=args)
    node = HomeNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
