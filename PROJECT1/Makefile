CC=gcc
CFLAGS=-Wall -Wextra -fsanitize=address
OBJDIR=obj
NAME=exe

CFILES = $(wildcard *.c)
HEADERS = $(wildcard *.h)

_OBJS = $(CFILES:.c=.o)
OBJS= $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(HEADERS) | $(OBJDIR)
	$(CC) -c -o $@ $< $(CFLAGS) 

$(NAME): $(OBJS)
	$(CC) -o $@ $^ $(CFLAGS) 
	

$(OBJDIR):
	mkdir $(OBJDIR)

.PHONY: clean

clean:
	rm -v -r obj
	rm $(NAME)