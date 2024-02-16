#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd;
    char *fifo = "/tmp/myfifo";  // nom du tube nommé
    char message[100];
    while(1)
    {
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
    }
    return 0;
}
