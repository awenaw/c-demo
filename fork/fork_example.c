/*
 * Fork Example Program
 * 
 * Compilation:
 * - macOS:   mkdir -p bin && clang -o bin/fork_example fork_example.c
 * - Linux:   mkdir -p bin && gcc -o bin/fork_example fork_example.c
 * - Ubuntu:  mkdir -p bin && gcc -o bin/fork_example fork_example.c
 * 
 * Usage: ./fork_example <process_count> <alive_seconds>
 * Example: ./fork_example 3 5
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <process_count> <alive_seconds>\n", argv[0]);
        return 1;
    }
    
    int process_count = atoi(argv[1]);
    int alive_seconds = atoi(argv[2]);
    
    if (process_count <= 0 || alive_seconds <= 0) {
        printf("Process count and alive seconds must be positive integers\n");
        return 1;
    }
    
    printf("Creating %d processes, each alive for %d seconds\n", process_count, alive_seconds);
    
    for (int i = 0; i < process_count; i++) {
        pid_t pid = fork();
        
        if (pid < 0) {
            perror("fork failed");
            return 1;
        }
        else if (pid == 0) {
            printf("Child process %d: PID=%d, Parent PID=%d\n", i+1, getpid(), getppid());
            sleep(alive_seconds);
            printf("Child process %d: PID=%d exiting\n", i+1, getpid());
            exit(0);
        }
        else {
            printf("Parent created child %d with PID=%d\n", i+1, pid);
        }
    }
    
    printf("Parent process PID=%d waiting for all children to complete\n", getpid());
    
    for (int i = 0; i < process_count; i++) {
        int status;
        pid_t child_pid = wait(&status);
        printf("Child process PID=%d terminated\n", child_pid);
    }
    
    printf("All child processes completed. Parent exiting.\n");
    return 0;
}