#pragma once

#define XTENSOR_USE_XSIMD
#include <xtensor/xarray.hpp>
#include <xtensor/xview.hpp>
#include <xtensor-blas/xlinalg.hpp>
#include <cstddef>
#include "tools.hpp"

template <typename T>
class Kernel
{
    std::size_t dimension, nsample1, nsample2;
    xt::xtensor<T, 1> alpha;
    xt::xtensor<T, 2, xt::layout_type::row_major> points1, points2, dist;

public:
    Kernel(std::size_t d, std::size_t m, std::size_t n)
        : dimension(d), nsample1(m), nsample2(n)
        , alpha(typename xt::xtensor<T, 1>::shape_type{dimension})
        , points1(typename xt::xtensor<T, 2>::shape_type{nsample1, dimension})
        , points2(typename xt::xtensor<T, 2>::shape_type{nsample2, dimension})
        , dist(typename xt::xtensor<T, 2>::shape_type{nsample1, nsample2})
    {
    }

    Kernel(Kernel const&) = delete;
    Kernel(Kernel &&) = delete;
    Kernel& operator= (Kernel const&) = delete;
    Kernel& operator= (Kernel &&) = delete;

    // Initialization
    void init(T p1, T p2, T p3)
    {
        using namespace xt;
        alpha = pow(p1, arange(dimension));

        points1 =   view(arange(nsample1), all(), newaxis())
                  + p2 * view(arange(dimension), newaxis(), all());
        
        points2 =   view(arange(nsample2), all(), newaxis())
                  + p3 * view(arange(dimension), newaxis(), all());
    }

    // Kernel
    void run()
    {
        using namespace xt;
        dist = sqrt(
              view( sum( square(points1) * view(alpha, newaxis(), all()), {1}), all(), newaxis())
            + view( sum( square(points2) * view(alpha, newaxis(), all()), {1}), newaxis(), all())
            - 2 * linalg::dot( points1 * view(alpha, newaxis(), all()), transpose(points2, {1,0}) )
        );
    }

    // Checksum
    T checksum() const
    {
        return xt::sum(dist)();
    }

    ~Kernel()
    {
    }

};



