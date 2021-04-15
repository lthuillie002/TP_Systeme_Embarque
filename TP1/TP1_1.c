#define BUFFER_SIZE 256
#define TAB_SIZE	32
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
	FILE* cpu = NULL;	//Stockage des informations système du CPU
	FILE* mem = NULL;	//Stockage des informations système de la mémoire
	FILE* part = NULL;	//Stockage des informations système des partitions

	/* Déclaration des variables*/
	char model_name[BUFFER_SIZE];
	char frequency[BUFFER_SIZE];
	char cache_size[BUFFER_SIZE];
	char adress_size[BUFFER_SIZE];

	char mem_total[BUFFER_SIZE];
	char mem_free[BUFFER_SIZE];
	char part_size[TAB_SIZE][BUFFER_SIZE];
	char part_name[TAB_SIZE][BUFFER_SIZE];

	char buffer[BUFFER_SIZE];

	char split[] = " "; 
	int col = 0;
	int line = 0;

	/* Ouverture des fichiers */
	cpu = fopen("/proc/cpuinfo", "r");
	mem = fopen("/proc/meminfo", "r");
	part = fopen("/proc/partitions", "r");

	/* Récupération des informations du CPU */
	if (cpu == NULL)
	{	// Erreur
		printf("Impossible d'ouvrir le fichier");
	}
	else
	{	// Fichier ok
		while(fgets(buffer,BUFFER_SIZE,cpu) != NULL)	// On vient lire le fichier ligne par ligne
		{
			if (strstr(buffer, "model name") != NULL)
				strcpy(model_name, buffer);				
			if (strstr(buffer, "cpu MHz") != NULL)
				strcpy(frequency, buffer);
			if (strstr(buffer, "cache size") != NULL)
				strcpy(cache_size, buffer);
			if (strstr(buffer, "address sizes") != NULL)
				strcpy(adress_size, buffer);
		}    		
			
	}

	/* Récupération des informations de la mémoire */
    if (mem == NULL)
    {       // Erreur
                printf("Impossible d'ouvrir le fichier");
	}
	else
	{
		while(fgets(buffer,BUFFER_SIZE,mem) != NULL)
		{
			if (strstr(buffer, "MemTotal") != NULL)
				strcpy(mem_total, buffer);
			if (strstr(buffer, "MemFree") != NULL)
				strcpy(mem_free, buffer);
		}
	}

	/* Récupération des informations sur les partitions */
	if (part == NULL)
	{printf("Impossible d'ouvrir le fichier");}
	else {
		line = 0;
		while(fgets(buffer,BUFFER_SIZE,part) != NULL)
		{
			col = 0;
			char *p = strtok(buffer, split); // Découpage du buffer par le limiteur " "
			while (p != NULL)
			{
				col ++;
				if (col == 2 && line > 2)
                {
                    printf("size : %s\n", p);
					strcpy(part_size[col], p);
                }
				if (col == 3 && line > 3)
                {
                    printf("Name : %s\n", p);
					strcpy(part_name[col], p);
                }

				p = strtok(NULL, split);
			}
			line ++;
		}
	}

	/* Affichage des résultats */
	printf("\n%s\n%s\n%s\n%s\n", model_name, frequency, cache_size, adress_size);
	printf("%s\n%s\n", mem_total, mem_free);
	int i = 0;
	for(i = 0; i < col; i++)
		printf("%s\t%s", part_name[col], part_size[col]);

	return 0;
}

