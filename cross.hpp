#ifndef VXL_CROSS_HPP
# define VXL_CROSS_HPP
# pragma once

#include "vector.hpp"

namespace vxl
{

// http://fastcpp.blogspot.si/2011/04/vector-cross-product-using-sse-code.html
template <typename T>
//__attribute__ ((noinline))
inline constexpr auto cross(vector<T, 3> const& l,
  vector<T, 3> const& r) noexcept
{
/*
  return vector<T, N>{
    l.data_[1] * r.data_[2] - l.data_[2] * r.data_[1],
    l.data_[2] * r.data_[0] - l.data_[0] * r.data_[2],
    l.data_[0] * r.data_[1] - l.data_[1] * r.data_[0]
  };
*/
  return swizzled<1, 2, 0>(
    l * swizzled<1, 2, 0>(r) -
    r * swizzled<1, 2, 0>(l)
  );
}

}

#endif // VXL_CROSS_HPP
