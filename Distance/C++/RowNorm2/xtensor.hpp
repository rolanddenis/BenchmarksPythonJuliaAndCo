#pragma once

#define XTENSOR_USE_XSIMD
#include <xtensor/xarray.hpp>
#include <xtensor/xview.hpp>
#include <cstddef>

template <typename T>
class Kernel
{
    std::size_t dimension, nrow;
    xt::xtensor<T, 1> alpha, result;
    xt::xtensor<T, 2, xt::layout_type::row_major> array;

public:
    Kernel(std::size_t d, std::size_t m, std::size_t /* n */)
        : dimension(d), nrow(m)
        , alpha(typename xt::xtensor<T, 1>::shape_type{dimension})
        , result(typename xt::xtensor<T, 1>::shape_type{nrow})
        , array(typename xt::xtensor<T, 2>::shape_type{nrow, dimension})
    {
    }

    Kernel(Kernel const&) = delete;
    Kernel(Kernel &&) = delete;
    Kernel& operator= (Kernel const&) = delete;
    Kernel& operator= (Kernel &&) = delete;

    // Initialization
    void init(T p1, T p2, T /* p3 */)
    {
        using namespace xt;
        alpha = pow(p1, arange(dimension));

        array =   view(arange(nrow), all(), newaxis())
                + p2 * view(arange(dimension), newaxis(), all());
    }

    // Kernel
    void run()
    {
        using namespace xt;
        result = sqrt( sum(square(array) * view(alpha, newaxis(), all()), {1}) );
    }

    // Checksum
    T checksum() const
    {
        return xt::sum(result)();
    }

    ~Kernel() = default;
};

