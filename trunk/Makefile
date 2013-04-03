IDIR =.
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR =.

LIBS=-lm -lgmp

_DEPS = tools.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = wiener.o 
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

wiener: $(OBJ)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
	rm -f wiener arr rsatools a.out freq 

