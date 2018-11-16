#pragma once

#include <Eigen/Core>
#include <cstddef>

using Eigen::Dynamic;

template <typename T>
class Kernel
{
    using row_type      = Eigen::Array<T, 1, Dynamic>;
    using column_type   = Eigen::Array<T, Dynamic, 1>;
    using array_type    = Eigen::Array<T, Dynamic, Dynamic, Eigen::RowMajor>;

    std::size_t dimension, nrow;
    row_type    alpha;
    column_type result;
    array_type  array;

public:
    Kernel(std::size_t d, std::size_t m, std::size_t)
        : dimension(d), nrow(m)
        , alpha(dimension)
        , result(nrow)
        , array(nrow, dimension)
    {
    }

    Kernel(Kernel const&) = delete;
    Kernel(Kernel &&) = delete;
    Kernel& operator= (Kernel const&) = delete;
    Kernel& operator= (Kernel &&) = delete;

    // Initialization
    void init(T p1, T p2, T p3)
    {
        alpha = pow(p1, row_type::LinSpaced(dimension, 0, dimension-1));

        array =   column_type::LinSpaced(nrow, 0, nrow-1).replicate(1, dimension)
                + row_type::LinSpaced(dimension, 0, p2*(dimension-1)).replicate(nrow, 1);
    }

    // Kernel
    void run()
    {
        result = sqrt( (pow(array, 2).rowwise() * alpha).rowwise().sum() );
    }

    // Checksum
    T checksum() const
    {
        return result.sum();
    }

    ~Kernel()
    {
    }

};
