CC = g++
CCFLAGS = -Wall -Wextra
LDFLAGS = $(shell sdl2-config --libs --cflags)

NAME = flappy

SRC = main.cpp graphics.cpp
OBJ = $(SRC:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.cpp
	$(CC) $(CCFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
