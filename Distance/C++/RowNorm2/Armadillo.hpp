#pragma once

#include <armadillo>
#include <cmath>
#include <cstddef>

template <typename T>
class Kernel
{
    using row_type      = arma::Row<T>;
    using column_type   = arma::Col<T>;
    using array_type    = arma::Mat<T>;

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
        using namespace arma;

        alpha = linspace<row_type>(0, dimension-1, dimension);

        // There is no pow(<scalar>, <matrix>)
        alpha.for_each( [&p1](auto & v) { v = std::pow(p1, v); } );

        array =   repmat(linspace<column_type>(0, nrow-1, nrow), 1, dimension)
                + repmat(linspace<row_type>(0, p2*(dimension-1), dimension), nrow, 1);
    }

    // Kernel
    void run()
    {
        using namespace arma;
        // each_row doesn't work on an expression, hence the eval()
        //result = sqrt( sum(pow(array, 2).eval().each_row() % alpha, 1) );
        result = sqrt( sum(pow(array.each_row() % sqrt(alpha), 2), 1) );
    }

    // Checksum
    T checksum() const
    {
        return arma::sum(result);
    }

    ~Kernel()
    {
    }

};

