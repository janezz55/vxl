#ifndef VXL_RSQRT_HPP
# define VXL_RSQRT_HPP
# pragma once

#include "vector.hpp"

#if defined(__SSE__)

# include "xmmintrin.h"

#endif // __SSE__

#if defined(__SSE3__)

#include "pmmintrin.h"

#endif // __SSE3__

#if defined (__SSE4_1__)

#include "smmintrin.h"

#endif // __SSE4_1__

#if defined(__ARM_NEON__)

#include "arm_neon.h"

#endif // __ARM_NEON__

namespace vxl
{

#if defined(__ARM_NEON__)

//__attribute__ ((noinline))
inline vector<float, 2> csqrt(float const xx) noexcept
{
  using vector_type = typename vector_traits<float, 2>::vector_type;

  vector_type const x{xx};

  r *= vrsqrts_f32(float32x2_t(x), r * r);

  return {
    vector_type(
      r * (vrsqrts_f32(float32x2_t(x), r * r))
    )
  };
}

//__attribute__ ((noinline))
inline vector<float, 2> crsqrt(vector<float, 2> const x) noexcept
{
  using vector_type = typename vector_traits<float, 2>::vector_type;

  auto r(vrsqrte_f32(float32x2_t(x.data_)));

  r *= vrsqrts_f32(float32x2_t(x.data_), r * r);

  return {
    vector_type(
      r * (vrsqrts_f32(float32x2_t(x.data_), r * r))
    )
  };
}

//__attribute__ ((noinline))
inline vector<float, 3> crsqrt(vector<float, 3> const x) noexcept
{
  using vector_type = typename vector_traits<float, 3>::vector_type;

  auto r(vrsqrteq_f32(float32x4_t(x.data_)));

  r *= vrsqrtsq_f32(float32x4_t(x.data_), r * r);

  return {
    vector_type(
      r * (vrsqrtsq_f32(float32x4_t(x.data_), r * r))
    )
  };
}

//__attribute__ ((noinline))
inline vector<float, 4> crsqrt(vector<float, 4> const x) noexcept
{
  using vector_type = typename vector_traits<float, 4>::vector_type;

  auto r(vrsqrteq_f32(float32x4_t(x.data_)));

  r *= vrsqrtsq_f32(float32x4_t(x.data_), r * r);

  return {
    vector_type(
      r * (vrsqrtsq_f32(float32x4_t(x.data_), r * r))
    )
  };
}

#elif defined(__SSE__)

//__attribute__ ((noinline))
inline vector<float, 4> crsqrt(float const xx) noexcept
{
  using vector_type = typename vector_traits<float, 4>::vector_type;

  vector_type const x{xx};

  auto r(_mm_rsqrt_ss(x));

  return {
    r * (cvector<float, 4>(1.5f) - cvector<float, 4>(.5f) * x * r * r)
  };
}

//__attribute__ ((noinline))
inline vector<float, 2> crsqrt(vector<float, 2> const x) noexcept
{
  auto r(_mm_rsqrt_ps(x.data_));

  return {
    r * (cvector<float, 2>(1.5f) - cvector<float, 2>(.5f) * x.data_ * r * r)
  };
}

//__attribute__ ((noinline))
inline vector<float, 3> crsqrt(vector<float, 3> const x) noexcept
{
  auto r(_mm_rsqrt_ps(x.data_));

  return {
    r * (cvector<float, 3>(1.5f) - cvector<float, 3>(.5f) * x.data_ * r * r)
  };
}

//__attribute__ ((noinline))
inline vector<float, 4> crsqrt(vector<float, 4> const x) noexcept
{
  auto r(_mm_rsqrt_ps(x.data_));

  return {
    r * (cvector<float, 4>(1.5f) - cvector<float, 4>(.5f) * x.data_ * r * r)
  };
}

#endif

template <unsigned N>
//__attribute__ ((noinline))
inline vector<float, N> crsqrt(vector<float, N> const& x) noexcept
{
  using int_value_type = typename vector_traits<float, N>::int_value_type;
  using int_vector_type = typename vector_traits<float, N>::int_vector_type;
  using vector_type = typename vector_traits<float, N>::vector_type;

  auto r(vector_type(cvector<int_value_type, N>(0x5f375a86) -
    (int_vector_type(x.data_) >> 1)));

  auto const xhalf(cvector<float, N>(.5f) * x.data_);

  r *= cvector<float, N>(1.5f) - xhalf * r * r;
  r *= cvector<float, N>(1.5f) - xhalf * r * r;

  return {
    r * (cvector<float, N>(1.5f) - xhalf * r * r)
  };
}

template <unsigned N>
//__attribute__ ((noinline))
inline vector<double, N> crsqrt(vector<double, N> const& x) noexcept
{
  using int_value_type = typename vector_traits<double, N>::int_value_type;
  using int_vector_type = typename vector_traits<double, N>::int_vector_type;
  using vector_type = typename vector_traits<double, N>::vector_type;

  auto r(vector_type(cvector<int_value_type, N>(0x5fe6eb50c7b537a9) -
    (int_vector_type(x.data_) >> 1)));

  auto const xhalf(cvector<double, N>(.5) * x.data_);

  r *= cvector<double, N>(1.5) - xhalf * r * r;
  r *= cvector<double, N>(1.5) - xhalf * r * r;

  return {
    r * (cvector<double, N>(1.5) - xhalf * r * r)
  };
}

}

#endif // VXL_RSQRT_HPP
