#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    char *hello = "Hello from server";
    
    // 创建socket文件描述符
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    
    // 设置socket选项，允许地址重用
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, 
                   &opt, sizeof(opt))) {
        perror("setsockopt SO_REUSEADDR");
        exit(EXIT_FAILURE);
    }
    
    // 在Linux上尝试设置SO_REUSEPORT（可选）
    #ifdef SO_REUSEPORT
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEPORT, 
                   &opt, sizeof(opt)) < 0) {
        // 如果SO_REUSEPORT失败，继续执行（不是致命错误）
        printf("Warning: SO_REUSEPORT not supported on this system\n");
    }
    #endif
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // 绑定socket到指定端口
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    // 开始监听连接
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    
    printf("服务器正在监听端口 %d...\n", PORT);
    
    while (1) {
        // 接受客户端连接
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, 
                                   (socklen_t*)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        
        printf("客户端已连接: %s:%d\n", 
               inet_ntoa(address.sin_addr), ntohs(address.sin_port));
        
        // 读取客户端消息
        int valread = read(client_socket, buffer, BUFFER_SIZE);
        printf("收到消息: %s\n", buffer);
        
        // 向客户端发送回复
        send(client_socket, hello, strlen(hello), 0);
        printf("回复消息已发送\n");
        
        // 关闭客户端连接
        close(client_socket);
        
        // 清空缓冲区
        memset(buffer, 0, BUFFER_SIZE);
    }
    
    // 关闭服务器socket
    close(server_fd);
    return 0;
}