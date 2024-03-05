CC = gcc
CFLAGS = -g -Wall
OBJDIR = obj
SRCDIR = src

OBJECTS = $(addprefix $(OBJDIR)/, main.o logging.o ganttio.o)
SHARED_HEADERS = $(addprefix $(SRCDIR)/, _data.h, ganttio.h, logging.h)

default: main

main: $(OBJECTS)
	$(CC) $(CFLAGS) -o bin/gantt $(OBJECTS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	$(RM) gantt $(OBJECTS)
