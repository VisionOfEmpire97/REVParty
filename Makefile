# WIP
# Authored by ROSET Nathan for use during the REV party project (Autumn 2023)

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
PATHTOCSVFILE = fichiers_vote/
DOXYGENDIR = documentation/

#Exécutables
VERIFY_MY_VOTE = $(EXECDIR)/verify_my_vote
PROG_PRINCIPAL = $(EXECDIR)/revparty
TESTSHA = $(EXECDIR)/test_sha
TESTMAT = $(EXECDIR)/testStructMatrice
TESTCSV = $(EXECDIR)/lecture_csv

#Objets
OBJ_SHA_UTILS = $(OBJDIR)/sha256_utils.o $(OBJDIR)/sha256.o 
OBJET_UTILS = $(OBJDIR)/matrice.o $(OBJDIR)/lecture_csv.o

#Exécutables

vmv: dirs $(OBJ_SHA_UTILS) $(OBJET_UTILS)
	@$(CC) -o $(VERIFY_MY_VOTE) $(OBJET_UTILS) $(SRCDIR)/verif_m_vote.c $(OBJ_SHA_UTILS)
	@echo "succès ! L'exécutable $(VERIFY_MY_VOTE) est situé dans bin/$(VERIFY_MY_VOTE)"
	@echo -e "Appelez l'exécutable avec ./bin/$(VERIFY_MY_VOTE) \"nom\" \"prenom\" \"CodePersonnel\" \"$(PATHTOCSVFILE)nom-du-csv-de-vote\""

test_sha: dirs $(OBJ_SHA_UTILS)
	@$(CC) -o $(TESTSHA) $(OBJ_SHA_UTILS) $(SHADIR)/test_sha.c
	@echo "succès ! L'exécutable $(TESTSHA) est situé dans bin/$(TESTSHA)"

test_matrice: dirs $(OBJET_UTILS)
	@$(CC) -o $(TESTMAT) $(OBJET_UTILS) $(MATDIR)/test/test_matrice.c
	@echo "succès ! L'exécutable $(TESTMAT) est situé dans bin/$(TESTMAT)"

test_lecture_csv : dirs $(OBJET_UTILS)
	@$(CC) -o $(TESTCSV) $(OBJET_UTILS) $(CSVDIR)/test_lecteur.c
	@echo "succès ! L'exécutable $(TESTCSV) est situé dans bin/$(TESTCSV)"

#... TODO

#REVparty: TODO
#	@$(CC) -o $(PROG_PRINCIPAL) $(OBJET_UTILS)

vpath %.c $(MATDIR) $(SRCDIR) $(METDIR) $(SHADIR) $(CSVDIR)

$(OBJDIR)/%.o: %.c
	@$(CC) -o $@ -c $< $(COMPILEARGS)

dirs:
	@if [ ! -d "./$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	@if [ ! -d "./$(EXECDIR)" ]; then mkdir $(EXECDIR); fi
	@if [ ! -d "./$(DOXYGENDIR)" ]; then mkdir $(DOXYGENDIR); fi

doxygen:
	@doxygen Doxyfile

clean:
	@rm -f $(OBJDIR)/*.o
	@echo "fichiers objets supprimés avec succès"
	@rm -f $(EXECDIR)/*
	@echo "fichiers exécutables supprimés avec succès"

mrproper: dirs clean
	@rm -rf $(DOXYGENDIR)/*
	@echo "documentation doxygen effacée"

.PHONY: clean vmv mrproper test_sha test_matrice test_lecture_csv REVparty