#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>





int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s port", argv[0]);
        exit(1);
    }
    
    FILE* file = fopen(argv[1], "r");
    if (file == NULL)
    {
        perror("Echec ouverture fichier");
        exit(2);
    }

    typedef struct
    {
        int IDvotant;
        char date[50];
        char codeVote[50];
        char votant[50];
        int candidat1;
        int candidat2;
        int candidat3;
        int candidat4;  
    }Ballot;


    Ballot ballots[150];

    int read = 0;
    int records = 0;

    do
    {
        read = fscanf(file, "%d,%50[^,],%50[^,],%50[^,], %d, %d, %d, %d", ballots[records].IDvotant, ballots[records].date, ballots[records].codeVote,
        ballots[records].votant, ballots[records].candidat1, ballots[records].candidat2, ballots[records].candidat3, ballots[records].candidat4);
    } while (!feof(file));

    if (read == 8)
    {
        records++;
    }
    if (read!=8 && !feof(file))
    {
        printf("file inco");
        return 1;
    }
    

    fclose(file);
    


    
    


    return 0;
}