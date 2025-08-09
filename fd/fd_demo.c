/*
=== 编译说明 ===

## macOS 系统编译步骤
1. 安装开发工具（如果未安装）:
   xcode-select --install

2. 使用 clang 编译（推荐）:
   clang -o fd_demo fd_demo.c

3. 或使用 gcc（如果已安装）:
   gcc -o fd_demo fd_demo.c

4. 运行程序:
   ./fd_demo

## Ubuntu 系统编译步骤
1. 安装编译工具（如果未安装）:
   sudo apt update
   sudo apt install build-essential

2. 使用 gcc 编译:
   gcc -o fd_demo fd_demo.c

3. 或使用 clang（需先安装）:
   sudo apt install clang
   clang -o fd_demo fd_demo.c

4. 运行程序:
   ./fd_demo

## 编译选项（可选）
- 启用所有警告:
  gcc -Wall -Wextra -o fd_demo fd_demo.c

- 调试版本:
  gcc -g -o fd_demo fd_demo.c

- 优化版本:
  gcc -O2 -o fd_demo fd_demo.c

## 运行前准备
创建测试文件:
echo "这是测试内容" > test.txt

## 注意事项
- 程序会创建 test2.txt 文件
- 如果 test.txt 不存在，fd1 将返回 -1
- 记得检查文件操作的返回值以处理错误情况
*/

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