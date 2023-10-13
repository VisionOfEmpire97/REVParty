# work in progress it doesn't work
CC = gcc
COMPILEARGS = -std=c11 -Wall
#INC = -I.

# Dossiers
SRCDIR = src
OBJDIR = obj
EXECDIR = bin
SHADIR = $(SRCDIR)/SHA256
CSVDIR = $(SRCDIR)/CSV
METDIR = $(SRCDIR)/methodes_votes
MATDIR = $(SRCDIR)/utils_sd/matrice

#Exécutables
VERIFY_MY_VOTE = $(EXECDIR)/verify_my_vote
PROG_PRINCIPAL = $(EXECDIR)/revparty
TESTSHA = $(EXECDIR)/test_sha
TESTMAT = $(EXECDIR)/testStructMatrice

#Objets
OBJ_SHA_UTILS = $(OBJDIR)/sha256_utils.o $(OBJDIR)/sha256.o 
OBJET_UTILS = $(OBJDIR)/matrice.o

#Exécutables

vmv: dirs $(OBJ_SHA_UTILS)
	$(CC) -o $(VERIFY_MY_VOTE) $(OBJET_UTILS) $(OBJ_SHA_UTILS)

test_sha: dirs $(OBJ_SHA_UTILS)
	$(CC) -o $(EXECDIR)/$@ $(OBJ_SHA_UTILS) $(SHADIR)/test_sha.c

test_matrice: dirs $(OBJET_UTILS)
	$(CC) -o $(TESTMAT) $(OBJET_UTILS) $(MATDIR)/test/test_matrice.c

#REVparty: TODO
#	$(CC) -o $(PROG_PRINCIPAL) $(OBJET_UTILS)

$(OBJDIR)/%.o: $(MATDIR)/%.c
	$(CC) -o $@ -c $< $(COMPILEARGS) 

dirs:
	@if [ ! -d "./$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	@if [ ! -d "./$(EXECDIR)" ]; then mkdir $(EXECDIR); fi	

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(EXECDIR)/* 