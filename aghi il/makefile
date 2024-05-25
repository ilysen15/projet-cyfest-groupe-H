# Compiler
CC = gcc
# Options de compilation
CFLAGS = -Wall -Wextra -std=c11

# Liste des fichiers source
SRCS = main.c save.c festivalier.c manager.c
# Liste des fichiers objet correspondants
OBJS = $(SRCS:.c=.o)
# Nom de l'exécutable final
TARGET = mon_programme

# Règle par défaut
all: $(TARGET)

# Règle de compilation pour chaque fichier objet
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Règle de création de l'exécutable final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Règle pour nettoyer les fichiers temporaires et l'exécutable
clean:
	rm -f $(OBJS) $(TARGET)
