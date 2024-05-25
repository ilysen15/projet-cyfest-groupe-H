all: salle

festivalier.o:festivalier.c festivalier.h
        gcc -Wall -Wextra -Wpedantic -c festivalier.c

save.o: save.c save.h
	gcc -Wall -Wextra -Wpedantic -c save.c

manager.o: manager.c manager.h
	gcc -Wall -Wextra -Wpedantic -c manager.c

menu.o: menu.c menu.h
	gcc -Wall -Wextra -Wpedantic -c menu1.c

salle : main.c save.o manager.o menu.o festivalier.o
	gcc -Wall -Wextra -Wpedantic main.c save.o filemanagement.o menu.o -o salle
