import rclpy
from rclpy.node import Node
from std_msgs.msg._color_rgba import ColorRGBA
from flask import Flask, render_template, request
import threading

app = Flask(__name__)
selected_color_hex = "#ffffff"

@app.route('/', methods=['GET', 'POST'])
def index():
    global selected_color_hex
    if request.method == 'POST':
        # Get color from the "selected_color" input field
        selected_color_hex = request.form.get('selected_color')
        print(f"Flask received: {selected_color_hex}")
        
    return render_template('index.html', color=selected_color_hex)

class HomeNode(Node):
    def __init__(self):
        super().__init__("home_node")
        self._publisher = self.create_publisher(ColorRGBA, 'cmd_color', 1)
        self._timer = self.create_timer(1, self._send_color_callback)

        self._flask_thread = threading.Thread(target=lambda: app.run('0.0.0.0', port=1234, debug=False, use_reloader=False), daemon=True)
        self._flask_thread.start()
        self.get_logger().info('Started flask thread in background')

    def _send_color_callback(self):
        global selected_color_hex
        h = selected_color_hex.lstrip('#')
        r, g, b = tuple(int(h[i:i+2], 16)/255.0 for i in (0, 2, 4))
        color = ColorRGBA()
        color.r = float(r)
        color.g = float(g)
        color.b = float(b)
        color.a = 1.0
        self.get_logger().info(f"ROS 2 Publishing: R:{r:.2f} G:{g:.2f} B:{b:.2f}")
        self._publisher.publish(color)


def main(args=None):
    rclpy.init(args=args)
    node = HomeNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()
