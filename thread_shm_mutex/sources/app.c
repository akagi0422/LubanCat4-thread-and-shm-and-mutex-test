#include <main.h>
#include <app.h>

/*
int scan_str()
{
    printf("Enter some text\n");
    fgets(str, 18, stdin); 
    // 想显示16个字母应读取18个,只读16个则只能显示14个字母,之后就会开始下一次循环,剩下的字母会在下个循环中显示
    // fgets会读回车(\n)进去,但用gets时如果输入的字符数目大于数组的长度,gets无法检测到这个问题,就会发生内存越界,所以编程时建议使用fgets()

    char *find = strchr(str, '\n');
    if(find)
    *find = '\0';
    // 11-13替换掉\n,读取之后不要换行

    printf("recieve %s form stdin!\n", str);
    return 0;
}

int show_str()
{
    printf("recieve %s form 共享内存!\n", str);
    return 0;
}
*/

void *scan_str(void *arg) // 线程跑的函数名都应该这么写
{
    void *shm_0 = NULL; // 映射到线程0的共享内存地址

    while(1)
    {
    pthread_mutex_lock(&mutex); // 上锁
    printf("thread_0 hold mutex\n");

    shm_0 = shmat(shmid, NULL, 0); // 链接到共享内存
    if(shm_0 == (void*)-1)
    {
        printf("shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("\nthread_0 Memory attached at %p\n", shm_0);

    printf("Enter some text\n");
    fgets(str, 18, stdin); 
    // 想显示16个字母应读取18个,只读16个则只能显示14个字母,之后就会开始下一次循环,剩下的字母会在下个循环中显示
    // fgets会读回车(\n)进去,但用gets时如果输入的字符数目大于数组的长度,gets无法检测到这个问题,就会发生内存越界,所以编程时建议使用fgets()

    char *find = strchr(str, '\n');
    if(find)
    *find = '\0';
    // 11-13替换掉\n,读取之后不要换行
    printf("recieve %s form stdin!\n", str);

    strncpy(shm_0, str, 4096); // 将str中的字符拷贝进共享内存

    pthread_mutex_unlock(&mutex); // 解锁
    printf("thread_0 free mutex\n");
    usleep(15); // 设置必要的延时防止解锁之后当场被自己再次上锁
    }
    //pthread_exit(NULL);
}

void *show_str(void *arg)
{
    char *shm_1 = NULL; // 映射到线程1的共享内存地址
    
    while(1)
    {
    pthread_mutex_lock(&mutex); // 上锁
    printf("thread_1 hold mutex\n");

    shm_1 = shmat(shmid, 0, 0); // 链接到共享内存
    if(shm_1 == (void*)-1)
    {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("\nthread_1 Memory attached at %p\n", shm_1);
    
    printf("recieve %s form 共享内存!\n", shm_1);

    pthread_mutex_unlock(&mutex); // 解锁
    printf("thread_1 free mutex\n");

    usleep(20); // 设置必要的延时防止解锁之后当场被自己再次上锁
    }
    // pthread_exit(NULL);
}