from pythonosc import dispatcher
from pythonosc import osc_server
import argparse

def quat_handler(unused_addr, x, y, z, w):
    print(f"Quat: {x}, {y}, {z}, {w}")

def euler_handler(unused_addr, x, y, z):
    print(f"Euler: {x}, {y}, {z}")

def rpy_handler(unused_addr, r, p, y):
    print(f"RPY: {r}, {p}, {y}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--ip", default="0.0.0.0", help="The IP to listen on")
    parser.add_argument("--port", type=int, default=54445, help="The port to listen on")
    args = parser.parse_args()

    disp = dispatcher.Dispatcher()
    #disp.map("/quat", quat_handler)
    #disp.map("/euler", euler_handler)
    disp.map("/rpy", rpy_handler)

    server = osc_server.ThreadingOSCUDPServer((args.ip, args.port), disp)
    print(f"Serving on {server.server_address}")

    try:
        server.serve_forever()
    except KeyboardInterrupt:
        server.server_close()
