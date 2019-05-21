#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define AUTHOR() printf("Лабораторная работа #7. Выполнил студент Нгуен Х.А. группы ИСТбд-21 \n")

int main() {
	int semid;
	char pathname[] = "1.c";
	key_t key;
	struct sembuf mybuf;

	AUTHOR();

	if ((key = ftok(pathname, 0)) < 0) {
		printf ("Can't generate key!\n");
		exit(-1);
	}	

	if ((semid = semget (key, 1, 0666 | IPC_CREAT)) < 0) {
		printf("Can't get semid!\n");
		exit(-1);
	}

	// n = 1, A(S, n) while S = S - n
	mybuf.sem_op = 1;
	mybuf.sem_flg = 0;
	mybuf.sem_num = 0;
	if (semop(semid, &mybuf, 1) < 0) {
		printf("Can't wait for condition!\n");
		exit(-1);
	}
	printf("Condition is set!\n");

	return 0;
}
