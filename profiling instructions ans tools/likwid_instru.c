#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
// This block enables compilation of the code with and without LIKWID in place
#ifdef LIKWID_PERFMON
#include <likwid-marker.h>
#else
#define LIKWID_MARKER_INIT
#define LIKWID_MARKER_THREADINIT
#define LIKWID_MARKER_SWITCH
#define LIKWID_MARKER_REGISTER(regionTag)
#define LIKWID_MARKER_START(regionTag)
#define LIKWID_MARKER_STOP(regionTag)
#define LIKWID_MARKER_CLOSE
#define LIKWID_MARKER_GET(regionTag, nevents, events, time, count)
#endif

#define N 10000

int main(int argc, char* argv[])
{
    int i;
    double data[N];
    LIKWID_MARKER_INIT;
#pragma omp parallel
{
    LIKWID_MARKER_REGISTER("foo");
}
#pragma omp parallel
{
    LIKWID_MARKER_START("foo");
    #pragma omp for
    for(i = 0; i < N; i++)
    {
        data[i] = omp_get_thread_num();
    }
    LIKWID_MARKER_STOP("foo");
}
    LIKWID_MARKER_CLOSE;
    return 0;
}



/*

At first we need to know the include and library paths for LIKWID. There is no common way but if you used the default build process you can use this:

$ /bin/bash -c "echo LIKWID_LIB=$(dirname $(which likwid-perfctr))/../lib/"
$ /bin/bash -c "echo LIKWID_INCLUDE=$(dirname $(which likwid-perfctr))/../include/"

This prints the paths to the LIKWID library and the header files. Assuming you have exported the paths in your environment, you can build your application using gcc:

$ gcc -fopenmp -DLIKWID_PERFMON -L$LIKWID_LIB -I$LIKWID_INCLUDE <SRC> -o <EXEC> -llikwid

You can (de)activate the Marker API integration with the define -DLIKWID_PERFMON. If you omit it, the calls resolve to an empty string causing no overhead.

By now, we have not defined which performance counters should be measured and which metrics be derived for our application. This is done using likwid-perfctr which also performs the pinning of threads and the validity checking of the given eventsets.

Run the application serially:

$ likwid-perfctr -C S0:0 -g L3 -m <EXEC>

Run the application parallel using multiple CPUs:

$ likwid-perfctr -C S0:0-3 -g L3 -m <EXEC>

*/

