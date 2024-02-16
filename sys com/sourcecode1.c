#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/stat.h>
int main()
{
    int fd;
    char *fifo = "/tmp/myfifo";  // nom du tube nommé
    char message[100];

    mkfifo(fifo, 0666);  // créer le tube nommé
    printf("\n\n\t***Taper EXIT pour quitter***\n\n");
    while(1)
    {
        printf("==>Vous: ");
     	scanf("%[^\n]s",message);  // saisir le message
        getchar();
	if(strcmp(message,"EXIT")==0) {
            fd = open(fifo, O_WRONLY);
            write(fd, "EXIT", strlen("EXIT")+1);
            printf("Exiting..\n");
            break;
 	}
	 // ouvrir le tube nommé en écriture
	fd = open(fifo, O_WRONLY);
        write(fd, message, strlen(message)+1);
        close(fd);
        // ouvrir le tube nommé en lecture
        fd = open(fifo, O_RDONLY);
        read(fd, message, sizeof(message));
        if(strcmp(message,"EXIT")==0){
            printf("L'autre a quitee\n");
            printf("Exiting..\n");
            break;
	}
	printf("==>L'autre: %s\n", message);
        close(fd);
    }
    unlink(fifo);  // supprimer le tube nommé

    return 0;
}
 
