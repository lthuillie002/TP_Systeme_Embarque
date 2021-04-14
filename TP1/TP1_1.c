#define BUFFER_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
	FILE* cpu = NULL;
	FILE* mem = NULL;
	FILE* part = NULL;

	cpu = fopen("/proc/cpuinfo", "r");
	mem = fopen("/proc/meminfo", "r");
	part = fopen("/proc/partitions", "r");

	char model_name[BUFFER_SIZE];
	char frequency[BUFFER_SIZE];
	char cache_size[BUFFER_SIZE];
	char adress_size[BUFFER_SIZE];

	char mem_total[BUFFER_SIZE];
	char mem_free[BUFFER_SIZE];

	char buffer[BUFFER_SIZE];
	if (cpu == NULL)
	{	// Erreur
		printf("Impossible d'ouvrir le fichier");
	}
	else
	{	// Fichier ok
		while(fgets(buffer,BUFFER_SIZE,cpu) != NULL)
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
	if (part == NULL)
	{printf("Impossible d'ouvrir le fichier");}
	else {
		while(fgets(buffer,BUFFER_SIZE,part) != NULL)
		{
			//TO DO
		}
	}


	printf("\n%s\n%s\n%s\n%s\n", model_name, frequency, cache_size, adress_size);
	printf("%s\n%s\n", mem_total, mem_free);


	return 0;
}

