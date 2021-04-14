#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>

static timer_t timer = (timer_t) 0;
static long int * mesure = NULL;
static int nb_mesures = 0;
static int nb_total_mesures = 0;

