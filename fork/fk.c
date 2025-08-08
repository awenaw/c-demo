#include <unistd.h>  
#include <stdio.h>  
  
int main() {  
    pid_t pid = fork();  
    printf("PID=%d\n", getpid());  
    sleep(30);  
} 