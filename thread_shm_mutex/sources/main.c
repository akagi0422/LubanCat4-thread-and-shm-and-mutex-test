// 双线程
// 指向第一个线程标识符的指针为thread[0],线程运行时执行的函数代码为scan_str
// 指向第二个线程标识符的指针为thread[1],线程运行时执行的函数代码为oled_show_str
// 先试一个show_str

#include <main.h>
#include <test_app.h>

int main()
{
    pthread_t thread[2]; // 创建两个线程标识符指针 两个就是[2],分别为[0]和[1]
    int thread_0 = 0; // 线程0传入参数
    int thread_1 = 1; // 线程1传入参数
    int res;

    printf("start to creat lock\n"); // 建立互斥锁
    pthread_mutex_init(&mutex, NULL);

    shmid = shmget((key_t)0001, 4096, 0644 | IPC_CREAT); // 建立共享内存
    if(shmid == -1)
    {
        printf("shmget failed\n");
        exit(EXIT_FAILURE);
    }

    printf("start to creat thread\n"); // 建立两个线程
    res = pthread_create(&thread[0], NULL, scan_str, (void*)(unsigned long long)(thread_0)); // (线程0, NULL, 线程所跑函数名, 传入参数固定格式)
    if(res != 0)
    {
        printf("Create thread %d failed\n", thread_0);
        exit(res);
    }

    res = pthread_create(&thread[1], NULL, show_str, (void*)(unsigned long long)(thread_1));
    if(res != 0)
    {
        printf("Create thread %d failed\n", thread_1);
        exit(res);
    }

    // printf("create thread finish\n");
    // printf("waiting for threads to finish...\n");

    // pthread_join(thread[0], NULL); // 等待线程结束
    // printf("threads_0 exit\n");
    // pthread_join(thread[1], NULL);
    // printf("threads_1 exit\n");

    // pthread_mutex_destroy(&mutex); // 销毁互斥锁
    // printf("mutex destroy\n");
    
    while(1) // 这里希望两个线程一直运行所以注释了线程、互斥锁回收部分,增加死循环
    {
        sleep(10);
    }

    return 0;
}
