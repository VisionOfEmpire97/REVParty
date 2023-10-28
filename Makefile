# WIP
# Authored by ROSET Nathan for use during the REV party project (Autumn 2023)

CC = gcc
COMPILEARGS = -std=c11 -Wall
#INC = -I.

TEAMNAME = REVParty_Equipe_001

# Couleurs
RED = \033[1;31m
GREEN = \033[1;32m
END_C = \e[00m

# Dossiers
SRCDIR = src
OBJDIR = obj
EXECDIR = bin
SHADIR = $(SRCDIR)/SHA256
CSVDIR = $(SRCDIR)/CSV
METDIR = $(SRCDIR)/methodes_votes
MATDIR = $(SRCDIR)/utils_sd/matrice
PATHTOCSVFILE = fichiers_votes/
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
	@$(CC) -o $(VERIFY_MY_VOTE) $(OBJET_UTILS) $(SRCDIR)/verify_my_vote.c $(OBJ_SHA_UTILS)
	@echo "\n$(GREEN)succès ! L'exécutable $(VERIFY_MY_VOTE) est situé dans $(VERIFY_MY_VOTE) $(END_C)"
	@echo "$(GREEN)Appelez l'exécutable avec ./$(VERIFY_MY_VOTE) \"nom\" \"prenom\" \"CodePersonnel\" \"$(PATHTOCSVFILE)nom-du-csv-de-vote\"$(END_C)"

test_sha: dirs $(OBJ_SHA_UTILS)
	@$(CC) -o $(TESTSHA) $(OBJ_SHA_UTILS) $(SHADIR)/test_sha.c
	@echo "succès ! L'exécutable $(TESTSHA) est situé dans $(TESTSHA)"
	@./$(TESTSHA)

test_matrice: dirs $(OBJET_UTILS)
	@$(CC) -o $(TESTMAT) $(OBJET_UTILS) $(MATDIR)/test/test_matrice.c
	@echo "succès ! L'exécutable $(TESTMAT) est situé dans $(TESTMAT)"
	@./$(TESTMAT)

test_lecture_csv : dirs $(OBJET_UTILS)
	@$(CC) -o $(TESTCSV) $(OBJET_UTILS) $(CSVDIR)/test_lecteur.c
	@echo "succès ! L'exécutable $(TESTCSV) est situé dans $(TESTCSV)"
	@./$(TESTCSV) fichiers_votes/VoteCondorcet.csv

test_vmv : vmv
	@echo "**********************************************"
	@echo "$(GREEN)test 1 avec VoteCondorcet.csv: retour attendu: ligne du vote trouvée$(END_C)" 
	@./$(VERIFY_MY_VOTE) roset nathan e9RkoTAH $(PATHTOCSVFILE)VoteCondorcet.csv
	@echo "**********************************************"
	@echo "$(GREEN)test 2 avec jugement.csv : retour attendu: ligne du vote trouvée$(END_C)"
	@./$(VERIFY_MY_VOTE) roset nathan IXtE5L46o0T $(PATHTOCSVFILE)jugement.csv
	@echo "**********************************************"
	@echo "$(GREEN)test 3 avec code érroné: retour attendu: pas de ligne trouvée$(END_C)"
	@./$(VERIFY_MY_VOTE) roset nathan abcdefgh $(PATHTOCSVFILE)VoteCondorcet.csv
	@echo "\n**************** FIN DU PROGRAMME ***************\n"
	@echo "Vous pouvez tester les fuites mémoires avec \
	\"$(RED)valgrind --leak-check=full $(verify_my_vote) roset nathan e9RkoTAH $(PATHTOCSVFILE)VoteCondorcet.csv$(END_C)\""
	@echo "Vous pouvez générer la documentation avec make doxygen (les packages doxygen et dot sont requis.)"
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

deliverCC2:
	@if [ ! -d "./$(TEAMNAME)" ]; then mkdir $(TEAMNAME); fi
	cp -r $(SRCDIR) $(TEAMNAME)
	cp -r $(PATHTOCSVFILE) $(TEAMNAME)
	cp Makefile Doxyfile $(TEAMNAME)
	cp README_DELIVER.md $(TEAMNAME)
	zip -r $(TEAMNAME).zip $(TEAMNAME)
	rm -rf $(TEAMNAME)

.PHONY: clean vmv mrproper test_sha test_matrice test_lecture_csv test_vmv REVparty
