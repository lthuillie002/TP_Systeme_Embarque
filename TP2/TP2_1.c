#define BUFFER_SIZE 128
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>
#include <sys/time.h>
#include <sched.h>

int main() {
	int which = PRIO_PROCESS;	// Parametre de la fonction get
	id_t pid;					// Stockage du pid du processus
	int ret_A;					// Stockage du getpriority
	
	FILE* stat = NULL;
	
	char ret_B[BUFFER_SIZE];
	
	pid = getpid();
	ret_A = getpriority(which, pid);

	/* Ouverture du fichier */
	stat =  fopen("/proc/self/sched", "r");
	char buffer[BUFFER_SIZE];
	if (stat == NULL) {printf("Impossible d'ouvrir le fichier");}
	else {
		while(fgets(buffer, BUFFER_SIZE, stat) != NULL)
		{
			if (strstr(buffer, "prio") != NULL)
				strcpy(ret_B, buffer);
		}
	}
	fclose(stat);	// Fermeture du fichier

	/* Affichage des résultats */
	printf("La priorite de ce processus est : %d\n%s\n", ret_A, ret_B);

	setpriority(which, pid, 4);	// Changement de priorité

	/* Affichage des résultats */
	ret_A = getpriority(which, pid);
	printf("La priorite est maintenant de : %d\n", ret_A);

	struct sched_param sp = { .sched_priority = 50 };

	ret_A  = sched_setscheduler(pid, SCHED_FIFO, &sp);
	if (ret_A == -1) {
		perror("sched_setscheduler");
		return 1;
	}

	fopen("/proc/self/sched", "r");
	if (stat == NULL) {printf("Impossible d'ouvrir le fichier");}
        else {
                while(fgets(buffer, BUFFER_SIZE, stat) != NULL)
                {
                        if (strstr(buffer, "prio") != NULL)
                                strcpy(ret_B, buffer);
                }
        }
        fclose(stat);

	printf("%s\n", ret_B); 

	return 0;
}

