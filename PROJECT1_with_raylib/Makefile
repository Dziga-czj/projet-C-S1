CC=gcc
CFLAGS=-Wall -Wextra -fsanitize=address
OBJDIR=obj
NAME=exe

CFILES = $(wildcard *.c)
HEADERS = $(wildcard *.h)

_OBJS = $(CFILES:.c=.o)
OBJS= $(patsubst %,$(OBJDIR)/%,$(_OBJS))

INCLUDES=-I/home/$(USER)/raylib/src/
LIBS_EXTRA=-L/home/$(USER)/raylib/src/
LIBS=-lraylib -lGL -lm -lpthread -ldl -lrt $(LIBS_EXTRA)


$(OBJDIR)/%.o: %.c $(HEADERS) | $(OBJDIR)
	$(CC) $(INCLUDES) -c -o $@ $< $(CFLAGS) 

$(NAME): $(OBJS)
	$(CC) $(LIBS) -o $@ $^ $(CFLAGS) 
	

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean

clean:
	rm -v -r obj
	rm $(NAME)