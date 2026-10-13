# OS_T1_V11 - 1-topshiriq, 11-variant

Kvadrat tenglama ax^2 + bx + c = 0 (kompleks ildizlar, a = 0 bo'lsa chiziqli).

## A qism (Hello World, 4 bosqich)
    cd partA
    gcc -E hello.c -o hello.i
    gcc -S hello.i -o hello.s
    gcc -c hello.s -o hello.o
    gcc hello.o -o hello
    ls -l hello.*

## B qism
    gcc -Wall -Wextra main.c -o main -lm
    ./main
