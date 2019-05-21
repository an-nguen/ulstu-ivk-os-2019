#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define AUTHOR() printf("Лабораторная работа #7. Выполнил студент Нгуен Х.А. группы ИСТбд-21 \n")

int main() {
	int fd[2], res_pipe, res_fork, semid;
	char pathname[] = "3.c";
	key_t key;
	struct sembuf mybuf;
    char buf[32];

	AUTHOR();

	res_pipe = pipe(fd);

	key = ftok(pathname, 0);
	semid = semget (key, 1, 0666 | IPC_CREAT);

    res_fork = fork();
    
	switch(res_fork) {
        case -1:
            exit(-1);
            break;
        case 0:
            read(fd[0], buf, 32);
            printf("Child get message - %s\n", buf);
            write(fd[1], "Hi, I'm child!", 16);
            // n = 1, A(S, n)
            mybuf.sem_op = 1;
            mybuf.sem_flg = 0;
            mybuf.sem_num = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can't wait for condition!\n");
                exit(-1);
            }
            
            printf("Condition is set!\n");
            break;
        default:
            write(fd[1], "Hi, I'm parent!", 32);
            
            // n = 1, D(S, n)
            mybuf.sem_op = -1;
            mybuf.sem_flg = 0;
            mybuf.sem_num = 0;
            if (semop(semid, &mybuf, 1) < 0) {
                printf("Can't wait for condition!\n");
                exit(-1);
            }
            printf("Condition is present!\n");
            
            read(fd[0], buf, 32);
            printf("Parent get message - %s\n", buf);
            
            if (semctl(semid, 0, IPC_RMID, NULL) < 0) {
                printf("Can't remove sem-s\n");
                exit(-1);
            }
            break;
	}

	return 0;
}
