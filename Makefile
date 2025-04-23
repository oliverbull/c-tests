IDIR =./include
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=./obj
LDIR=./lib
SDIR=./src

LIBS=-lm
DEBUG=-g3

_DEPS = 
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) $(DEBUG) -c -o $@ $< $(CFLAGS)

test: $(OBJ)
	$(CC) $(DEBUG) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o test
