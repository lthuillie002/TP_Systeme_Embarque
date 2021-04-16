// ---------------------------------------------------------------------
// Fichier d'exemple pour le TP2 Question 4-a --> création des timers
// VO par Christophe BLAESS
// Adapté par Jalil Boukhobza
// ---------------------------------------------------------------------

#define SIG SIGRTMIN

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>


static timer_t timer = (timer_t) 0;
static long int * mesure = NULL;
static int nb_mesures = 0;
static int nb_total_mesures = 50000;

void handler_signal(int inutilise)
{
	// fonction à exécuter à chaque expiration du timer
	// *** à compléter --> incrémetner le nombre de mesures ici, nb_mesures, quelque part


	struct timespec heure;
	static struct timespec precedente = {0,0};

	nb_mesures ++;
	printf("%d\n", nb_mesures);
        // *** a compléter --> mesurer le temps
	clock_gettime (CLOCK_REALTIME, &heure);

	if (precedente.tv_sec > 0) {
        // *** à compléter --> mesure[nb_mesures] doit récupérer la dif$
        // ATTENTION ici à considérer la partie entière et fractionnair$
        }
        precedente = heure;
        if (nb_mesures == nb_total_mesures)
                timer_delete(timer);

}


int main(int argc, char * argv[])
{
	long int periode;
	struct sigevent event;
	struct itimerspec spec;

	if ((argc != 2) || (sscanf(argv[1], "%ld", & periode) != 1)){
		fprintf(stderr, "usage: %s periode_en_microsec\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	// nombre de mesues réalisées en 5 secondes (par exemple)
	nb_total_mesures = 5000000 / periode; // 5 secondes

	// Configurer le timer
	// à la reception du signal SIGRTMIN, executer la fonction handler_signal()
	signal(SIGRTMIN, handler_signal);

	//*** a compléter --> nous souhaitons être notifié par signal
	event.sigev_notify = SIGEV_SIGNAL;
	event.sigev_signo  = SIG;

	periode = periode * 1000;  // en nanosec

	//*** à compléter --> définir la partie entière et fractionnaire
	spec.it_interval.tv_sec  = periode / 1000000000;
	spec.it_interval.tv_nsec = periode % 1000000000;
	spec.it_value = spec.it_interval;


	// *** à compléter --> allouer le timer
	if (timer_create(CLOCK_REALTIME, &event, &timer) != 0) {
		perror("timer_create");
		exit(EXIT_FAILURE);
	}

	// à compléter --> programmer le timer
	if (timer_settime(timer, 0, &spec, NULL) != 0) {
		perror("timer_settime");
		exit(EXIT_FAILURE);
	}


	// Attendre le dernier signal
	while (nb_mesures < nb_total_mesures)
		pause();

	for (nb_mesures = 0; nb_mesures < nb_total_mesures; nb_mesures ++)
		printf("%ld\n", mesure[nb_mesures]/1000);

	return EXIT_SUCCESS;
}

