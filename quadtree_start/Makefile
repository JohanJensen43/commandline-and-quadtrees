
# code details

EXE_DIR = .
EXE = $(EXE_DIR)/quad

SRC= test.c writeTree.c buildTree.c destroyTree.c valueTree.c

# generic build details

CC=      cc
COPT=    -g
CFLAGS= -lm

# compile to  object code

OBJ= $(SRC:.c=.o)

.c.o:
	$(CC) $(COPT) -c -o $@ $<

# build executable

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EXE) 

# clean up compilation

clean:
	rm -f $(OBJ) $(EXE)

# dependencies

test.o: test.c
buildTree.o: buildTree.c
writeTree.o: writeTree.c
destroyTree.o: destroyTree.c
valueTree.o: valueTree.c

