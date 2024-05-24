all: salle

festivalier.o:festivalier.c festivalier.h
        gcc -Wall -Wextra -Wpedantic -c festivalier.c

save.o: save.c save.h
	gcc -Wall -Wextra -Wpedantic -c save.c

maneger.o: maneger.c maneger.h
	gcc -Wall -Wextra -Wpedantic -c maneger.c

menu.o: menu1.c menu.h
	gcc -Wall -Wextra -Wpedantic -c menu1.c

salle : main.c save.o maneger.o menu.o festivalier.o
	gcc -Wall -Wextra -Wpedantic main.c save.o filemanagement.o menu.o -o salle
