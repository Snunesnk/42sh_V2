#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>

#include "ft_printf.h"
#include "ft_queue.h"

int main(void)
{
	struct	s_queue myqueue = {.rear = NULL, .front = NULL};
	
	char	*s1;
	char	*s2;
	char	*s3;
	char	*s4;
	char	*s5;
	char	*s6;
	char	*s7;
	char	*s8;

	s1 = strdup("1st line\n");
	s2 = strdup("2nd line\n");
	s3 = strdup("3rd line\n");
	s4 = strdup("4th line\n");
	s5 = strdup("5th line\n");
	s6 = strdup("6th line\n");
	s7 = strdup("7th line\n");
	s8 = strdup("8th line\n");

	fprintf(stderr, "size: %zu\n", queue_size(&myqueue));

	fprintf(stderr, "%s\n", (char*)queue_front(&myqueue));
	char *stest = (char*)queue_dequeue(&myqueue, NULL);
	fprintf(stderr, "%s\n", stest);
	free(stest);
	fprintf(stderr, "%s\n", (char*)queue_front(&myqueue));
	queue_dequeue(&myqueue, free);

	queue_enqueue(&myqueue, s2);
	queue_enqueue(&myqueue, s3);
	queue_enqueue(&myqueue, s5);
	queue_enqueue(&myqueue, s6);
	queue_enqueue(&myqueue, s4);
	queue_enqueue(&myqueue, s7);
	queue_enqueue(&myqueue, s1);
	queue_enqueue(&myqueue, s8);

	fprintf(stderr, "size: %zu\n", queue_size(&myqueue));
	fprintf(stderr, "Check front: %s\n", (char*)queue_front(&myqueue));
	fprintf(stderr, "Should not change: %s\n", (char*)queue_front(&myqueue));

	fprintf(stderr, "\nInitial queue:\n\n");
	queue_apply_to_each(&myqueue, (void (*)())printf);
	fprintf(stderr, "\n");

	fprintf(stderr, "\nSorted queue:\n\n");
	queue_sort(&myqueue, (int (*)(void *, void *))strcmp);
	queue_apply_to_each(&myqueue, (void (*)())ft_printf);
	

	fprintf(stderr, "\n");
	fprintf(stderr, "Should not change: %s\n", (char*)queue_front(&myqueue));
	fprintf(stderr, "size: %zu\n", queue_size(&myqueue));

	char *str2;
	str2 = (char*)queue_dequeue(&myqueue, NULL);
	fprintf(stderr, "OK: %s\n", str2);
	free(str2);


	queue_reverse(&myqueue);
	queue_reverse(&myqueue);
	queue_reverse_recursion(&myqueue);
	fprintf(stderr, "\nReversed queue:\n\n");
	queue_apply_to_each(&myqueue, (void (*)())printf);
	fprintf(stderr, "\n");

	queue_dequeue(&myqueue, free);
	queue_dequeue(&myqueue, free);
	queue_dequeue(&myqueue, free);
	fprintf(stderr, "\nDequeued queue:\n\n");
	queue_apply_to_each(&myqueue, (void (*)())printf);
	fprintf(stderr, "\n");

	char *str;

	str = (char*)queue_dequeue(&myqueue, NULL);
	fprintf(stderr, "%s\n", str);
	free(str);

	fprintf(stderr, "size: %zu\n", queue_size(&myqueue));
	queue_delete(&myqueue, free);
	return (0);
}
