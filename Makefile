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

#Exécutables
VERIFY_MY_VOTE = $(EXECDIR)/verify_my_vote
PROG_PRINCIPAL = $(EXECDIR)/revparty
TESTSHA = $(EXECDIR)/test_sha

#Objets
OBJ_SHA_UTILS = $(OBJDIR)/sha256_utils.o $(OBJDIR)/sha256.o 
OBJET_UTILS = #TODO

#Exécutables

vmv: dirs $(OBJ_SHA_UTILS)
	$(CC) -o $(VERIFY_MY_VOTE) $(OBJET_UTILS) $(OBJ_SHA_UTILS)

test_sha: dirs $(OBJ_SHA_UTILS)
	$(CC) -o $(EXECDIR)/$@ $(OBJ_SHA_UTILS) $(SHADIR)/test_sha.c

#REVparty: TODO
#	$(CC) -o $(PROG_PRINCIPAL) $(OBJET_UTILS)

$(OBJDIR)/%.o: $(SHADIR)/%.c
	$(CC) -o $@ -c $< $(COMPILEARGS) 

dirs:
	@if [ ! -d "./$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	@if [ ! -d "./$(EXECDIR)" ]; then mkdir $(EXECDIR); fi	

clean:
	rm -f $(OBJDIR)/*.o
	rm -f $(EXECDIR)/* 