# WIP
# Authored by ROSET Nathan for use during the REV party project (Autumn 2023)

CC = gcc
CFLAGS = -std=c11 -Wall
#-Werror -Wextra -pedantic
#LDFLAGS = -I.
#INC_FLAGS = -I./src

ifeq ($(DEBUG),yes)
	CFLAGS += -ggdb
	LDFLAGS +=
else
	CFLAGS += -O3 -DNDEBUG
	LDFLAGS +=
endif

TEAMNAME = REVParty_Equipe_001


# Couleurs
RED = \033[1;31m
GREEN = \033[1;32m
END_C = \e[00m

# Dossiers
SRCDIR = src
OBJDIR = obj
EXECDIR = bin
LOGDIR = log
SHADIR = $(SRCDIR)/SHA256
CSVDIR = $(SRCDIR)/CSV
METDIR = $(SRCDIR)/methodes_votes
UTILDIR = $(SRCDIR)/utils_sd
TESTDIR = $(UTILDIR)/test
PATHTOCSVFILE = fichiers_votes/
DOXYGENDIR = documentation/

#Exécutables
VERIFY_MY_VOTE = $(EXECDIR)/verify_my_vote
PROG_PRINCIPAL = $(EXECDIR)/scrutin
TESTSHA = $(EXECDIR)/test_sha
TESTMAT = $(EXECDIR)/testStructMatrice
TESTCSV = $(EXECDIR)/lecture_csv
TESTGRAPH = $(EXECDIR)/testStructGraph
UNI = $(EXECDIR)/uninominal
JGM = $(EXECDIR)/JugementMajoritaire

#Fichiers de test
TESTCLASSEMENT = fich_tests/vote10.csv
CLASSEMENT = fichiers_votes/VoteCondorcet.csv

##### Objets
# Nécessaire pour compiler verify_my_vote
OBJ_SHA_UTILS = $(OBJDIR)/sha256_utils.o $(OBJDIR)/sha256.o 
# Nécessaire pour compiler tous (?) les exécutables
OBJET_UTILS = $(OBJDIR)/matrice.o $(OBJDIR)/lecture_csv.o 
# Nécessaire pour compiler le programme "scrutin" et les méthodes
OBJETS_UTILS_EXTRAS = $(OBJET_UTILS) $(OBJDIR)/util_log.o $(OBJDIR)/graph.o 
REQUIRED_JUGEMENT = $(OBJETS_UTILS_EXTRAS) $(OBJDIR)/jugement.o
# REQUIRED_UNI = $(OBJETS_UTILS_EXTRAS) $(OBJDIR)/uninominal.o
# REQUIRED_CONDORCET = $(OBJETS_UTILS_EXTRAS) $(OBJDIR)/condorcet.o


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
	@$(CC) -o $(TESTMAT) $(OBJET_UTILS) $(TESTDIR)/test_matrice.c
	@echo "succès ! L'exécutable $(TESTMAT) est situé dans $(TESTMAT)"
	@./$(TESTMAT) $(TESTCLASSEMENT)

# test_graph: dirs $(OBJETS_UTILS_EXTRAS)
# 	@$(CC) -o $(TESTGRAPH) $(OBJETS_UTILS_EXTRAS) $(TESTDIR)/test_graph.c
# 	@echo "succès ! L'exécutable $(TESTGRAPH) est situé dans $(TESTGRAPH)"
# 	@./$(TESTGRAPH) $(TESTCLASSEMENT)

test_lecture_csv : dirs $(OBJET_UTILS)
	@$(CC) -o $(TESTCSV) $(OBJET_UTILS) $(CSVDIR)/test_lecteur.c
	@echo "succès ! L'exécutable $(TESTCSV) est situé dans $(TESTCSV)"
	@./$(TESTCSV) $(CLASSEMENT)

test_vmv : vmv
	@echo "**********************************************"
	@echo "$(GREEN)test 1 avec VoteCondorcet.csv: retour attendu: ligne du vote trouvée$(END_C)" 
	@./$(VERIFY_MY_VOTE) roset nathan e9RkoTAH $(CLASSEMENT)
	@echo "**********************************************"
	@echo "$(GREEN)test 2 avec jugement.csv : retour attendu: ligne du vote trouvée$(END_C)"
	@./$(VERIFY_MY_VOTE) roset nathan IXtE5L46o0T $(PATHTOCSVFILE)jugement.csv
	@echo "**********************************************"
	@echo "$(GREEN)test 3 avec code érroné: retour attendu: pas de ligne trouvée$(END_C)"
	@./$(VERIFY_MY_VOTE) roset nathan abcdefgh $(CLASSEMENT)
	@echo "\n**************** FIN DU PROGRAMME ***************\n"
	@echo "Vous pouvez tester les fuites mémoires avec \
	\"$(RED)valgrind --leak-check=full $(verify_my_vote) roset nathan e9RkoTAH $(CLASSEMENT)$(END_C)\""
	@echo "Vous pouvez générer la documentation avec make doxygen (les packages doxygen et dot sont requis.)"

# test_jgm : $(REQUIRED_JUGEMENT)
# 	@$(CC) -o $(JGM) $(REQUIRED_JUGEMENT) $(TESTDIR)/test_jugement.c
#	# @./$(JGM) $(TESTCLASSEMENT)

# test_uni: dirs $(REQUIRED_UNI)
# 	@$(CC) -o $(UNI) $(SRCDIR)/$@.c $(REQUIRED_UNI)
# 	@./$(UNI) fich_tests/vote10.csv

#... TODO
#scrutin: dirs... TODO
#	@$(CC) -o $(PROG_PRINCIPAL) $(OBJET_UTILS)

vpath %.c $(UTILDIR) $(SRCDIR) $(METDIR) $(SHADIR) $(CSVDIR) $(TESTDIR)
vpath %.h $(UTILDIR) $(SRCDIR) $(METDIR) $(SHADIR) $(CSVDIR) $(TESTDIR)

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< 

all_utils: vmv test_sha test_graph test_lecture_csv test_matrice 
all_methods: test_jgm test_uni test_uni

dirs:
	@if [ ! -d "./$(OBJDIR)" ]; then mkdir $(OBJDIR); fi
	@if [ ! -d "./$(EXECDIR)" ]; then mkdir $(EXECDIR); fi
	@if [ ! -d "./$(DOXYGENDIR)" ]; then mkdir $(DOXYGENDIR); fi
	@if [ ! -d "./$(LOGDIR)" ]; then mkdir $(LOGDIR); fi

doc:
	@doxygen Doxyfile

clean: dirs
	@rm -f $(OBJDIR)/*.o
	@echo "fichiers objets supprimés avec succès"
	@rm -f $(EXECDIR)/*
	@echo "fichiers exécutables supprimés avec succès"

remove_logs: dirs
	@rm -f $(LOGDIR)/*
	@echo "Tous les fichiers de log ont été supprimés"

remove_doc: dirs
	@rm -rf $(DOXYGENDIR)/*
	@echo "documentation doxygen effacée"

mrproper: dirs clean remove_doc remove_logs
	@echo "Tous les fichiers générés ont été retirés"

deliverCC2:
	@if [ ! -d "./$(TEAMNAME)" ]; then mkdir $(TEAMNAME); fi
	cp -r $(SRCDIR) $(TEAMNAME)
	cp -r $(PATHTOCSVFILE) $(TEAMNAME)
	cp Makefile Doxyfile $(TEAMNAME)
	cp README_DELIVER.md $(TEAMNAME)
	zip -r $(TEAMNAME).zip $(TEAMNAME)
	rm -rf $(TEAMNAME)

.PHONY: vmv test_sha test_matrice test_lecture_csv test_vmv scrutin
