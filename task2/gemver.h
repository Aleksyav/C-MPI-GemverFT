#ifndef _GEMVER_H
#define _GEMVER_H
# if !defined(MINI_DATASET) && !defined(SMALL_DATASET) && !defined(MEDIUM_DATASET) && !defined(LARGE_DATASET) && !defined(EXTRALARGE_DATASET)
#define SMALL_DATASET
# endif
# if !defined(N)
# ifdef MINI_DATASET
#define N 40
# endif
# ifdef SMALL_DATASET
#define N 120
# endif
# ifdef MEDIUM_DATASET
#define N 400
# endif
# ifdef LARGE_DATASET
#define N 2000
# endif
# ifdef EXTRALARGE_DATASET
#define N 4000
# endif
#endif
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <signal.h>
#include <math.h>
#include <time.h>
#include "mpi.h"
#include <mpi-ext.h>
#include <sys/time.h>
#endif
