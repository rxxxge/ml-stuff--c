# main: main.c
# 	gcc -Wall -Wextra -o main main.c

all: gates xor main

gates: gates.c
	gcc -Wall -Wextra -o gates gates.c

xor: xor.c
	gcc -Wall -Wextra -o xor xor.c

main: main.c
	gcc -Wall -Wextra -o main main.c







# test: test.c
# 	gcc -Wall -Wextra -o test test.c
