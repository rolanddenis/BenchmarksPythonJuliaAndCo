#!/usr/bin/env python3

if __name__ == '__main__':
    import argparse
    import sys
    import time

    # Command-line parameters
    parser = argparse.ArgumentParser()
    parser.add_argument('problem', help='Benchmarked problem')
    parser.add_argument('method', help='Calculation method') 
    parser.add_argument('dimension', type=int, help='Space dimension')
    parser.add_argument('nsample1', type=int, help='Size of the first sample')
    parser.add_argument('nsample2', type=int, help='Size of the second sample')
    parser.add_argument('--p1', type=float, default=1.1, help='Initialization parameter #1')
    parser.add_argument('--p2', type=float, default=1.2, help='Initialization parameter #2')
    parser.add_argument('--p3', type=float, default=1.3, help='Initialization parameter #3')
    parser.add_argument('--warming_time', type=float, default=1., help='Minimal warming time')
    parser.add_argument('--run_time', type=float, default=10., help='Minimal run time')
    parser.add_argument('--min_run', type=int, default=3, help='Minimal number of kernel execution')
    args = parser.parse_args()

    # Kernel initialization
    sys.path.append(args.problem + '/' + args.method)
    from kernel import Kernel
    kernel = Kernel(args.dimension, args.nsample1, args.nsample2)
    kernel.init(args.p1, args.p2, args.p3)

    # Runs
    nrun = 0
    is_warming = False
    total_duration = 0.
    tic = time.time()

    while True:

        kernel.run()

        total_duration = time.time() - tic

        # Managing warming and run time
        if is_warming and duration >= args.warming_time:
            is_warming = False
            tic = time.time()
        elif not is_warming:
            nrun += 1

            # Ending benchmark
            if total_duration >= args.run_time and nrun >= args.min_run:
                break

    # Checksum
    checksum = kernel.checksum()

    # Mean duration
    duration = total_duration / nrun

    # Displaying results
    print( "{} {}".format(duration, checksum) )

