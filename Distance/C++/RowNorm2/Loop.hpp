#pragma once

#include <cstddef>
#include <cmath>
#include <numeric>
#include <new>
#include "tools.hpp"

template <typename T>
class Kernel
{
    std::size_t dimension, nrow;
    T *alpha, *array, *result;

public:
    Kernel(std::size_t d, std::size_t m, std::size_t)
        : dimension(d), nrow(m)
    {
        // Allocation
        alpha   = new T[dimension];
        array   = new T[nrow * dimension];
        result  = new T[nrow];

        // Prevent dead code elimination related to the calculation result.
        escape(result);
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

        #pragma omp parallel for
        for ( std::size_t i = 0; i < nrow; ++i )
            for ( std::size_t d = 0; d < dimension; ++d )
                array[d + i*dimension] = i + p2*d;
    }

    // Kernel
    void run()
    {
        #pragma omp parallel for
        for ( std::size_t i = 0; i < nrow; ++i )
        {
            T sum = 0;
            for ( std::size_t d = 0; d < dimension; ++d )
            {
                sum += std::pow(array[d + i*dimension], 2) * alpha[d];
            }
            result[i] = std::sqrt(sum);
        }

        // Prevent dead code elimination of the previous calculation.
        clobber();
    }

    // Checksum
    T checksum() const
    {
        return std::accumulate(result, result + nrow, 0.);
    }

    // Freeing memory
    ~Kernel()
    {
        delete[] alpha;
        delete[] array;
        delete[] result;
    }

};
