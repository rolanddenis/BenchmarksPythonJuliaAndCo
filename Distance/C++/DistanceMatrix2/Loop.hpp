#pragma once

#include <cstddef>
#include <cmath>
#include <numeric>
#include <new>
#include "tools.hpp"

template <typename T>
class Kernel
{
    std::size_t dimension, nsample1, nsample2;
    T *alpha, *points1, *points2, *dist;

public:
    Kernel(std::size_t d, std::size_t m, std::size_t n)
        : dimension(d), nsample1(m), nsample2(n)
    {
        // Allocation
        alpha   = new T[dimension];
        points1 = new T[nsample1 * dimension];
        points2 = new T[nsample2 * dimension];
        dist    = new T[nsample1 * nsample2];

        // Prevent dead code elimination related to the calculation result.
        escape(dist);
    }

    Kernel(Kernel const&) = delete;
    Kernel(Kernel &&) = delete;
    Kernel& operator= (Kernel const&) = delete;
    Kernel& operator= (Kernel &&) = delete;

    // Initialization
    void init(T p1, T p2, T p3)
    {
        for ( std::size_t d = 0; d < dimension; ++d )
            alpha[d] = std::pow(p1, d);

        for ( std::size_t m = 0; m < nsample1; ++m )
            for ( std::size_t d = 0; d < dimension; ++d )
                points1[d + m*dimension] = m + p2 * d;

        for ( std::size_t n = 0; n < nsample2; ++n )
            for ( std::size_t d = 0; d < dimension; ++d )
                points2[d + n*dimension] = n + p3 * d;
    }

    // Kernel
    void run()
    {
        #pragma omp parallel for
        for ( std::size_t m = 0; m < nsample1; ++m )
        {
            for ( std::size_t n = 0; n < nsample2; ++n )
            {
                T sum = 0;
                for ( std::size_t d = 0; d < dimension; ++d )
                {
                    const T diff = points1[d + m*dimension] - points2[d + n*dimension];
                    sum += std::pow(diff, 2) * alpha[d];
                }
                dist[n + m*nsample2] = std::sqrt(sum);
            }
        }

        // Prevent dead code elimination of the previous calculation.
        clobber();
    }

    // Checksum
    T checksum() const
    {
        return std::accumulate(dist, dist + nsample1*nsample2, 0.);
    }

    // Freeing memory
    ~Kernel()
    {
        delete[] alpha;
        delete[] points1;
        delete[] points2;
        delete[] dist;
    }

};
