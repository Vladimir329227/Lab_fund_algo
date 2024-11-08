CC = gcc
STD_FLAGS = -Wall -Werror -Wextra -std=c11

all: My_String.o main.o Post.o
	$(CC) $(STD_FLAGS) $^ -lm -o task_3_4.out

My_String.o: My_String.c
	$(CC) $(STD_FLAGS) -c $<

Post.o: Post.c
	$(CC) $(STD_FLAGS) -c $<

main.o: main.c
	$(CC) $(STD_FLAGS) -c $<

clean:
	rm -f *.out *.o

rebuild: clean all