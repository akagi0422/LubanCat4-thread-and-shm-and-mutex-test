#include <unistd.h>
#include <fcntl.h> // open&close
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // 字符处理比较头文件
#include <pthread.h> // 线程头文件
#include <sys/types.h> // pid_t定义在这里
#include <sys/shm.h> // 共享内存头文件
#include <semaphore.h> // POSIX信号量头文件
#include <sys/wait.h>
#include <sys/ipc.h> // 进程间通信头文件
#include <sys/stat.h> // 获取文件属性头文件
#include <errno.h>

char str[20]; // 一行能放16字母,在这里扫描20个
pthread_mutex_t mutex; // 互斥锁
int shmid; // 共享内存ID