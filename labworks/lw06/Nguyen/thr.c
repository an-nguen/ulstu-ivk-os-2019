#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Макрос вывода авторства
#define AUTHOR() printf("Лабораторная работа №6. Выполнил студент гр. ИСТбд-21 Нгуен Х.А.\n");
// Кол-во создаваемых потоков
#define N 3

int a = 0;

void *doWork(void *data) {
	pthread_t thread;
	thread = pthread_self();
	// sleep(1);
	a += 1;
	printf("Thread %d. Calculation result = %d\n", (int)thread, a);
	return NULL;
}

int main() {
	pthread_t main_thread;
	pthread_t *threads = (pthread_t*) malloc(N * sizeof(pthread_t));
	int result;

	AUTHOR()
	// Создаём потоки и проверяем успешность создания
	for (int i = 0; i < N; i++) {
		result = pthread_create(&(threads[i]), NULL, doWork, NULL);
		if (result != 0) {
			printf("Error on thread create, return value = %d\n", result);
			exit(-1);
		}
		// Выводим что мы создали потоки
		printf("Thread with ID %d created.\n", threads[i]);
	}

	// Вызываем функцию, которая возвращает ИД потока
	main_thread = pthread_self();

	a += 1;

	printf("Main thread %d. Calculation result = %d\n", (int)main_thread, a);

	// Ожидаем выполнение всех потоков
	for (int i = 0; i < N; i++) {
		pthread_join(threads[i], (void**)NULL);
	}
	free(threads);

	return 0;
}
