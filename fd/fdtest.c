#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    // 打开文件，返回文件描述符
    int fd1 = open("test.txt", O_RDONLY);
    int fd2 = open("test2.txt", O_WRONLY | O_CREAT, 0644);
    
    printf("文件1的fd: %d\n", fd1);  // 通常是 3
    printf("文件2的fd: %d\n", fd2);  // 通常是 4
    
    // 标准的fd
    printf("stdin fd: %d\n", STDIN_FILENO);   // 0
    printf("stdout fd: %d\n", STDOUT_FILENO); // 1
    printf("stderr fd: %d\n", STDERR_FILENO); // 2
    
    // 对fd进行读写操作
    char buffer[100];
    read(fd1, buffer, sizeof(buffer));   // 从fd1读数据
    write(fd2, "hello", 5);              // 向fd2写数据
    
    close(fd1);
    close(fd2);
    return 0;
}