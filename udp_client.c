#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    char message[BUFFER_SIZE];
    socklen_t server_len;
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
    server_addr.sin_port = htons(SERVER_PORT);
    
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("无效的服务器地址");
        close(sockfd);
        exit(1);
    }

    printf("UDP客户端启动，连接到 %s:%d\n", SERVER_IP, SERVER_PORT);
    printf("输入消息发送给服务器 (输入 'quit' 退出):\n");

    while (1) {
        printf("> ");
        fflush(stdout);

        // 读取用户输入
        if (fgets(message, sizeof(message), stdin) == NULL) {
            break;
        }

        // 移除换行符
        message[strcspn(message, "\n")] = '\0';

        // 检查退出命令
        if (strcmp(message, "quit") == 0) {
            printf("客户端退出\n");
            break;
        }

        // 发送消息到服务器
        if (sendto(sockfd, message, strlen(message), 0, 
                  (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            perror("sendto失败");
            continue;
        }

        printf("消息已发送: %s\n", message);

        // 接收服务器回复
        server_len = sizeof(server_addr);
        recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE-1, 0, 
                           (struct sockaddr*)&server_addr, &server_len);

        if (recv_len < 0) {
            perror("recvfrom失败");
            continue;
        }

        // 添加字符串结束符
        buffer[recv_len] = '\0';
        printf("服务器回复: %s\n", buffer);
        printf("---\n");
    }

    close(sockfd);
    return 0;
}