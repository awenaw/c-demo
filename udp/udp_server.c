#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];
    socklen_t client_len;
    ssize_t recv_len;

    // 1. 创建UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket创建失败");
        exit(1);
    }

    // 2. 设置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // 监听所有接口
    server_addr.sin_port = htons(PORT);

    // 3. 绑定socket到地址
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind失败");
        close(sockfd);
        exit(1);
    }

    printf("UDP服务器启动，监听端口 %d...\n", PORT);
    printf("等待客户端消息...\n");

    // 4. 接收和处理消息
    while (1) {
        client_len = sizeof(client_addr);
        
        // 接收数据
        recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE-1, 0, 
                           (struct sockaddr*)&client_addr, &client_len);
        
        if (recv_len < 0) {
            perror("recvfrom失败");
            continue;
        }

        // 添加字符串结束符
        buffer[recv_len] = '\0';

        // 显示收到的消息
        printf("收到来自 %s:%d 的消息: %s\n", 
               inet_ntoa(client_addr.sin_addr), 
               ntohs(client_addr.sin_port), 
               buffer);

        // 构造回复消息
        char reply[BUFFER_SIZE];
        snprintf(reply, sizeof(reply), "服务器收到: %s", buffer);

        // 发送回复
        if (sendto(sockfd, reply, strlen(reply), 0, 
                  (struct sockaddr*)&client_addr, client_len) < 0) {
            perror("sendto失败");
        } else {
            printf("已回复客户端\n");
        }

        printf("---\n");
    }

    close(sockfd);
    return 0;
}