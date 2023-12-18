# WIP
# Authored by ROSET Nathan for use during the REV party project (Autumn 2023)

CC = gcc
CFLAGS = -std=c17 
#CFLAGS += -Wall -Werror -Wextra -pedantic
LDFLAGS =
#INC_FLAGS = -I./src

ifeq ($(DEBUG),yes)
	CFLAGS += -ggdb
	LDFLAGS += -rdynamic
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
# METDIR = $(SRCDIR)/methodes_votes
UTILDIR = $(SRCDIR)/utils_sd
TESTDIR = $(UTILDIR)/test
PATHTOCSVFILE = fichiers_votes/
PATHTOCSVTEST = fich_tests/
DOXYGENDIR = documentation/

#Exécutables
VERIFY_MY_VOTE = $(EXECDIR)/verify_my_vote
PROG_PRINCIPAL = $(EXECDIR)/scrutin
TESTSHA = $(EXECDIR)/test_sha
TESTMAT = $(EXECDIR)/testStructMatrice
TESTCSV = $(EXECDIR)/lecture_csv
TESTGRAPH = $(EXECDIR)/testStructGraph
TESTCONDORCET = $(EXECDIR)/testCondorcet
TESTUNI = $(EXECDIR)/uninominal
JGM = $(EXECDIR)/JugementMajoritaire

#Fichiers de test
TESTCLASSEMENTDIX = fich_tests/vote10.csv
TESTCLASSEMENTCENT = fich_tests/vote100.csv
TESTDUEL = fich_tests/calcul1.csv
CLASSEMENT = fichiers_votes/VoteCondorcet.csv

##### Objets
# Nécessaire pour compiler verify_my_vote
OBJ_SHA_UTILS = $(OBJDIR)/sha256_utils.o $(OBJDIR)/sha256.o 
# Nécessaire pour compiler tous (?) les exécutables
OBJET_UTILS = $(OBJDIR)/matrice.o $(OBJDIR)/lecture_csv.o 
# Nécessaire pour compiler le programme "scrutin" et les méthodes
OBJETS_UTILS_EXTRAS = $(OBJET_UTILS) $(OBJDIR)/util_log.o $(OBJDIR)/graph.o 
REQUIRED_JUGEMENT = $(OBJETS_UTILS_EXTRAS) $(OBJDIR)/jugement.o
REQUIRED_UNI = $(OBJETS_UTILS_EXTRAS) $(OBJDIR)/uninominal.o
REQUIRED_CONDORCET = $(OBJETS_UTILS_EXTRAS) $(OBJDIR)/condorcet.o
METHODS_ONLY = $(OBJDIR)/uninominal.o $(OBJDIR)/jugement.o $(OBJDIR)/condorcet.o
REQUIRED_SCRUTIN = $(OBJETS_UTILS_EXTRAS) $(METHODS_ONLY) $(OBJDIR)/arg_parse_util.o 


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
	@./$(TESTMAT) $(TESTCLASSEMENTDIX)

test_graph: dirs $(OBJETS_UTILS_EXTRAS)
	@$(CC) -o $(TESTGRAPH) $(OBJETS_UTILS_EXTRAS) $(TESTDIR)/test_graph.c
	@echo "succès ! L'exécutable $(TESTGRAPH) est situé dans $(TESTGRAPH)"
	@./$(TESTGRAPH) $(TESTCLASSEMENTDIX) 0
	@./$(TESTGRAPH) $(TESTDUEL) 1

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

test_jgm: scrutin
	@./$(PROG_PRINCIPAL) -i $(TESTCLASSEMENTDIX) -m jm -o $(LOGDIR)/jugement_vote10.txt
	@./$(PROG_PRINCIPAL) -i $(TESTCLASSEMENTCENT) -m jm -o $(LOGDIR)/jugement_vote100.txt
	@./$(PROG_PRINCIPAL) -i $(CLASSEMENT) -m jm -o $(LOGDIR)/jugement_votecondorcet.txt
	
test_uni: scrutin
	@./$(PROG_PRINCIPAL) -i $(TESTCLASSEMENTCENT) -m uni1 -o $(LOGDIR)/uninom1_vote100.txt
	@./$(PROG_PRINCIPAL) -i $(TESTCLASSEMENTCENT) -m uni2 -o $(LOGDIR)/uninom2_vote100.txt
	@./$(PROG_PRINCIPAL) -i $(CLASSEMENT) -m uni1 -o $(LOGDIR)/uninom1_votecondorcet.txt
	@./$(PROG_PRINCIPAL) -i $(CLASSEMENT) -m uni2 -o $(LOGDIR)/uninom2_votecondorcet.txt

scrutin: dirs $(REQUIRED_SCRUTIN)
	@$(CC) -o $(PROG_PRINCIPAL) $(REQUIRED_SCRUTIN) $(SRCDIR)/scrutin.c

test_scrutin: scrutin
	@./$(PROG_PRINCIPAL) -i $(CLASSEMENT) -m uni2 -o $(LOGDIR)/test_log.txt
	@echo "$(GREEN)Vous pouvez consulter le fichier de log dans $(LOGDIR)/test_log.txt$(END_C)"

test_condorcet: scrutin
	@./$(PROG_PRINCIPAL) -d $(TESTDUEL) -m cm -o $(LOGDIR)/condorcet_minimax_calcul1.txt
	@./$(PROG_PRINCIPAL) -i $(TESTCLASSEMENTCENT) -m cm -o $(LOGDIR)/condorcet_minimax_vote100.txt
	@./$(PROG_PRINCIPAL) -d $(TESTDUEL) -m cs -o $(LOGDIR)/condorcet_schulze_calcul1.txt
	@./$(PROG_PRINCIPAL) -i $(TESTCLASSEMENTCENT) -m cs -o $(LOGDIR)/condorcet_schulze_vote100.txt
	@./$(PROG_PRINCIPAL) -d $(TESTDUEL) -m cp -o $(LOGDIR)/condorcet_paires_calcul1.txt
	@./$(PROG_PRINCIPAL) -i $(TESTCLASSEMENTCENT) -m cp -o $(LOGDIR)/condorcet_paires_vote100.txt
	@dot -Tpdf log/*.dot -O

test_all_methods: scrutin
	@./$(PROG_PRINCIPAL) -i $(CLASSEMENT) -m all -o $(LOGDIR)/all_votecondorcet.txt
	@./$(PROG_PRINCIPAL) -d $(TESTDUEL) -m all -o $(LOGDIR)/all_calcul1.txt
	@dot -Tpdf log/*.dot -O
	

test_cd_paires: scrutin
	@./$(PROG_PRINCIPAL) -i $(PATHTOCSVTEST)/sansegalite1000.csv -m cp -o $(LOGDIR)/test_log1.txt
	@./$(PROG_PRINCIPAL) -i $(PATHTOCSVTEST)/sansegalite1000.csv -m cp -o $(LOGDIR)/test_log2.txt
	@./$(PROG_PRINCIPAL) -i $(PATHTOCSVTEST)/sansegalite1000.csv -m cp -o $(LOGDIR)/test_log3.txt
	@dot -Tpdf log/*.dot -O

vpath %.c $(UTILDIR) $(SRCDIR) $(SHADIR) $(CSVDIR) $(TESTDIR)
vpath %.h $(UTILDIR) $(SRCDIR) $(SHADIR) $(CSVDIR)

$(OBJDIR)/%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

all: all_tests doc test_vmv
all_tests: test_uni test_jgm test_condorcet

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

deliverCC:
	@if [ ! -d "./$(TEAMNAME)" ]; then mkdir $(TEAMNAME); fi
	cp -r $(SRCDIR) $(TEAMNAME)
	cp -r $(PATHTOCSVFILE) $(TEAMNAME)
	cp -r $(PATHTOCSVTEST) $(TEAMNAME)
	cp -r $(LOGDIR) $(TEAMNAME)
	cp Makefile Doxyfile $(TEAMNAME)
	cp README_DELIVER.md $(TEAMNAME)
	zip -r $(TEAMNAME).zip $(TEAMNAME)
	rm -rf $(TEAMNAME)

.PHONY: vmv test_sha test_matrice test_lecture_csv test_vmv scrutin
