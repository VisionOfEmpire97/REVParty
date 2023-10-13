/// \author Equipe 001
/// \date 23 Septembre 2023
/// \file le fichier lecture_csv devrait prendre un fichier CSV 
///       et retourner une matrice de type t_mat_char_star_dyn ????

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#define N 10
#define SEPARATEUR ","

char data[N], data2[N], data3[N], data4[N], data5[N];

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s port", argv[0]);
        exit(1);
    }
    
    int fd = popen(argv[1], "r");
    if (fd == -1)
    {
        perror("Echec ouverture fichier");
        exit(2);
    }

    char buffer[100];

    while (read(fd, sizeof(buffer), sizeof(buffer))!= -1)
    {
        write(1, buffer, sizeof(buffer));

    }
    
    
    close(fd);
    
    printf("%s\n", data);


    
    


    return 0;
}
