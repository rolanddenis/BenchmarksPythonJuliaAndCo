#include <chrono>
#include <cstddef>
#include <string>
#include <iostream>

#ifndef KERNEL
#define KERNEL Loop
#endif

#ifndef PROBLEM
#define PROBLEM DistanceMatrix2
#endif

#define XSTR(s) #s
#define STR(s) XSTR(s)
#include STR(PROBLEM/KERNEL.hpp)

/// Timer used in tic & toc
auto tic_timer = std::chrono::high_resolution_clock::now();

/// Launching the timer
void tic()
{
    tic_timer = std::chrono::high_resolution_clock::now();
}

/// Stopping the timer and returning the duration in seconds
double toc()
{
    const auto toc_timer = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> time_span = toc_timer - tic_timer;
    return time_span.count();
}


/// Program entry
int main( int argc, char* argv[] )
{
    // Config
    using real = double;
    const real p1 = 1.1;
    const real p2 = 1.2;
    const real p3 = 1.3;
    const double warming_time = 1.;
    const double run_time     = 10.;
    const std::size_t min_run = 3;

    // Command-line parameters
    const std::size_t dimension = std::stoull(argv[1]);
    const std::size_t nsample1  = std::stoull(argv[2]);
    const std::size_t nsample2  = std::stoull(argv[3]);

    // Kernel initialization
    Kernel<real> kernel(dimension, nsample1, nsample2);
    kernel.init(p1, p2, p3);

    // Runs
    std::size_t nrun = 0;
    bool is_warming = true;
    double total_duration = 0;
    tic();

    while ( true )
    {
        kernel.run();

        total_duration = toc();

        // Managing warming and run time
        if (is_warming && total_duration >= warming_time)
        {
            is_warming = false;
            tic();
        }
        else if (! is_warming)
        {
            ++nrun;
            
            // Ending benchmark
            if ( total_duration >= run_time && nrun >= min_run )
                break;
        }
    }

    // Checksum
    const double checksum = kernel.checksum();

    // Mean duration
    const double duration = total_duration / nrun;

    // Displaying results
    std::cout << std::fixed;
    std::cout << duration << " " << checksum << std::endl;

    return 0;
}
