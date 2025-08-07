#!/usr/bin/env python3
import socket
import datetime

# python3 udp_server.py

def udp_server():
    # 创建UDP socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    
    # 绑定地址和端口
    host = 'localhost'
    port = 8080
    server_socket.bind((host, port))
    
    print(f"UDP服务端启动，监听 {host}:{port}")
    print("按 Ctrl+C 停止服务")
    
    try:
        while True:
            # 接收数据
            data, client_address = server_socket.recvfrom(1024)
            received_msg = data.decode('utf-8')
            
            # 打印收到的内容
            print(f"收到来自 {client_address} 的消息: {received_msg}")
            
            # 构造回传内容：时间 + 原内容
            current_time = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
            response = f"[{current_time}] {received_msg}"
            
            # 回传给客户端
            server_socket.sendto(response.encode('utf-8'), client_address)
            print(f"已回传: {response}")
            
    except KeyboardInterrupt:
        print("\n服务端停止")
    finally:
        server_socket.close()

if __name__ == "__main__":
    udp_server()
