#pragma once

#include <Eigen/Core>
#include <cstddef>
#include "tools.hpp"

using Eigen::Dynamic;

template <typename T>
class Kernel
{
    using row_type      = Eigen::Array<T, 1, Dynamic>;
    using column_type   = Eigen::Array<T, Dynamic, 1>;
    using array_type    = Eigen::Array<T, Dynamic, Dynamic, Eigen::RowMajor>;

    std::size_t dimension, nsample1, nsample2;
    row_type alpha;
    array_type points1, points2, dist;

public:
    Kernel(std::size_t d, std::size_t m, std::size_t n)
        : dimension(d), nsample1(m), nsample2(n)
        , alpha(dimension)
        , points1(nsample1, dimension), points2(nsample2, dimension)
        , dist(nsample1, nsample2)
    {
    }

    Kernel(Kernel const&) = delete;
    Kernel(Kernel &&) = delete;
    Kernel& operator= (Kernel const&) = delete;
    Kernel& operator= (Kernel &&) = delete;
    
    // Initialization
    void init(T p1, T p2, T p3)
    {
        for ( std::size_t d = 0; d < dimension; ++d )
            alpha(d) = std::pow(p1, d);

        for ( std::size_t m = 0; m < nsample1; ++m )
            for ( std::size_t d = 0; d < dimension; ++d )
                points1(m, d) = m + p2 * d;

        for ( std::size_t n = 0; n < nsample2; ++n )
            for ( std::size_t d = 0; d < dimension; ++d )
                points2(n, d) = n + p3 * d;
    }

    // Kernel
    void run()
    {
        dist = sqrt(
              (pow(points1, 2).rowwise() * alpha).rowwise().sum().replicate(1, nsample2).rowwise()
            + (pow(points2, 2).rowwise() * alpha).rowwise().sum().transpose()
            - 2 * ((points1.rowwise() * alpha).matrix() * points2.matrix().transpose()).array()
        );
    }
    
    // Checksum
    T checksum() const
    {
        return dist.sum();
    }

    ~Kernel()
    {
    }

};
