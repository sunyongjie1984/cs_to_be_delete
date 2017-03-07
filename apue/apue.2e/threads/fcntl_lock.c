/*
 * 设置记录锁子函数lock_set.c
 *
 * 记录锁分为读取锁和写入锁，其中读取锁又称为共享锁，可以使多个
 * 进程都能够在文件的同一部分建立读取锁。而写入锁又称为互斥锁，
 * 在任何时刻只能有一个进程在文件的某个部分建立写入锁。当然，在
 * 文件的同一部分不能同时建立读取锁和写入锁。
 *
 * fcntl的lock结构如下所示：
 * struct flock {
 * short l_type;
 * off_t l_start;
 * short l_whence;
 * off_t l_len;
 * pid_t l_pid;
 * }
 *
 * 技巧：为加锁整个文件，通常的方法是将l_start说明为0，l_whence
 * 说明为SEEK_SET，l_len说明为0。
 */
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>


void print_lock(struct flock lock)
{
        printf(" -----------------------------\n");

        if (lock.l_type == F_RDLCK) {
                printf("\tl_type: F_RDLCK\n");
        }
        else if (lock.l_type == F_WRLCK) {
                printf("\tl_type: F_WRLCK\n");
        }
        else if (lock.l_type == F_UNLCK) {
                printf("\tl_type: F_UNLCK\n");
        }

        printf("\tl_start: %d\n", (int)lock.l_start);

        if (lock.l_whence == SEEK_SET) {
                printf("\tl_whence: SEEK_SET\n");
        }
        else if (lock.l_whence == SEEK_CUR) {
                printf("\tl_whence: SEEK_CUR\n");
        }
        else if (lock.l_whence == SEEK_END) {
                printf("\tl_whence: SEEK_END\n");
        }

        printf("\tl_len: %d\n", (int)lock.l_len);

        printf(" -----------------------------\n");
}

void lock_set(int fd, int type)
{
        struct flock lock;

        /*赋值lock结构体，加锁整个文件*/
        lock.l_whence = SEEK_SET;
        lock.l_start = 0;
        lock.l_len = 0;

        while (1) {
                lock.l_type = type;

                /*
                 * 根据不同的type来给文件加锁或解锁，
                 * 如果成功，则返回0，失败则返回1。
                 * 举例：如果一个文件原来已经建立了互斥锁，那么再调用fcntl
                 * 建立锁就会失败，返回-1。
                 */
                if ((fcntl(fd, F_SETLK, &lock)) == 0) {
                        /*如果是共享锁*/
                        if (lock.l_type == F_RDLCK) {
                                printf("read only set by %d\n", getpid());
                        }
                        /*如果是互斥锁*/
                        else if (lock.l_type == F_WRLCK) {
                                printf("write lock set by %d\n", getpid());
                        }
                        else if (lock.l_type == F_UNLCK) {
                                printf("release lock by %d\n", getpid());
                        }
                        print_lock(lock);
                        return;
                }
                else {
                        /*
                         * 获得lock的描述，也就是将文件fd的加锁信息存入到lock结构中
                         * 如果成功则返回0
                         * 如果失败则返回-1
                         */
                        if ((fcntl(fd, F_GETLK, &lock)) == 0) {
                                if (lock.l_type != F_UNLCK) {
                                        if (lock.l_type == F_RDLCK) {
                                                printf("read lock already set by %d\n", lock.l_pid);
                                        }
                                        else if (lock.l_type == F_WRLCK) {
                                                printf("write lock already set by %d\n", lock.l_pid);
                                        }
                                        getchar();
                                }
                        }
                        else {
                                printf("cannot get the description of struck flock.\n");
                        }
                }
        }
}
 

/*
 * 测试文件读写锁
 */


void die(char *msg)
{
        perror(msg);
        exit(1);
}

int open_file(void)
{
        int fd;

        if ((fd = open("/tmp/hello.c", O_CREAT | O_TRUNC | O_RDWR, 0666)) < 0) {
                perror("open error");
				exit(-1);
        }
        else {
                printf("Open file: hello.c %d\n", fd);
        }

        return fd;
}

void close_file(int fd)
{
        if (close(fd) < 0) {
				perror("close error");
				exit(-1);
        }
        else {
                printf("Close file: hello.c\n");
        }
}

int main(void)
{
        int fd;

        fd = open_file();

		/*给文件加写入锁*/
//      lock_set(fd, F_WRLCK);
        /*给文件加读取锁*/
        lock_set(fd, F_RDLCK);
        /*等待键盘任意键触发*/
        getchar();
        /*给文件解锁*/
        lock_set(fd, F_UNLCK);
        getchar();
        close_file(fd);

        return 0;
}
