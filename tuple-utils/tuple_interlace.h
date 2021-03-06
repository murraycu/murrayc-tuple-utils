/* Copyright (C) 2015 Murray Cumming
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3.0 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef MURRAYC_TUPLE_UTILS_TUPLE_INTERLACE_H
#define MURRAYC_TUPLE_UTILS_TUPLE_INTERLACE_H

#include <tuple-utils/tuple_cdr.h>
#include <tuple>
#include <type_traits>
#include <utility>

namespace tupleutils {

// Based on this:
// http://stackoverflow.com/a/28182793/1123654

/* This doesn't work, though that would be nice:
 * See http://en.cppreference.com/w/cpp/language/parameter_pack
 * where something like this creates an interlaced (zip) tuple<pair, pair>.
template<class ...Args1> struct tuple_type_interlace {
  template<class ...Args2> struct with {
    using type = std::tuple<(Args1, Args2)...>;
  };
};
*/

namespace detail {

template <class T, class... T_tuples>
struct tuple_type_interlace_ {
  using type = T;
};

template <class... T_result_types, template <class...> class T, class T_first,
  class... T_tail_types, class... T_tuples>
struct tuple_type_interlace_<std::tuple<T_result_types...>,
  T<T_first, T_tail_types...>, T_tuples...>
  : tuple_type_interlace_<std::tuple<T_result_types..., T_first>, T_tuples...,
      T<T_tail_types...>> {};

template <class... T_result_types, template <class...> class T, class T_first,
  class... T_tuples>
struct tuple_type_interlace_<std::tuple<T_result_types...>, T<T_first>,
  T_tuples...>
  : tuple_type_interlace_<std::tuple<T_result_types..., T_first>, T_tuples...> {
};

} // detail namespace

template <class... T_tuples>
using tuple_type_interlace = detail::tuple_type_interlace_<std::tuple<>, T_tuples...>;

namespace detail {

template <typename T_tuple1, typename T_tuple2, std::size_t N>
struct tuple_interlace_impl {
  constexpr
  static
  decltype(auto)
  interlace(T_tuple1&& tuple1, T_tuple2&& tuple2) {
    if constexpr(N == 0) {
      return std::forward<T_tuple1>(tuple1);
    } else if constexpr(N == 1) {
      //We don't use std::make_tuple(), to preserve std::ref()ed elements.
      return std::tuple_cat(std::forward<T_tuple1>(tuple1), std::forward<T_tuple2>(tuple2));
    } else {
      auto first_interlaced =
        std::make_tuple(std::get<0>(std::forward<T_tuple1>(tuple1)), std::get<0>(std::forward<T_tuple2>(tuple2)));

      //We use std::decay_t<> because tuple_size is not defined for references.
      constexpr auto size1 = std::tuple_size<std::decay_t<T_tuple1>>::value;
      constexpr auto size2 = std::tuple_size<std::decay_t<T_tuple2>>::value;
      static_assert(
        size1 == size2, "remaining1 and remaining2 must have the same size.");

      using cdr1 = typename tuple_type_cdr<std::decay_t<T_tuple1>>::type;
      using cdr2 = typename tuple_type_cdr<std::decay_t<T_tuple2>>::type;

      auto remaining_interlaced =
        tuple_interlace_impl<cdr1, cdr2, size1 - 1>::interlace(
          tuple_cdr(std::forward<T_tuple1>(tuple1)),
          tuple_cdr(std::forward<T_tuple2>(tuple2)));

      return std::tuple_cat(first_interlaced, remaining_interlaced);
    }
  }
};

} // detail namespace

/**
 * Get the a tuple that interlaces two other tuples.
 *
 * For instance,
 * @code
 * std::tuple<int, short> tuple_is(1, 2);
 * std::tuple<double, char> tuple_dc(3.0, '4');
 * std::tuple<int, double, short, char> interlaced =
 * tupleutils::interlace(tuple_is, tuple_dc);
 * @endcode
 *
 * This is analogous to std::tuple_cat().
 */
template <typename T_tuple1, typename T_tuple2>
constexpr
decltype(auto)
tuple_interlace(T_tuple1&& tuple1, T_tuple2&& tuple2) {
  //We use std::decay_t<> because tuple_size is not defined for references.
  constexpr auto size1 = std::tuple_size<std::decay_t<T_tuple1>>::value;
  constexpr auto size2 = std::tuple_size<std::decay_t<T_tuple2>>::value;
  static_assert(size1 == size2, "tuple1 and tuple2 must have the same size.");

  return detail::tuple_interlace_impl<T_tuple1, T_tuple2, size1>::interlace(
    std::forward<T_tuple1>(tuple1), std::forward<T_tuple2>(tuple2));
}

} // namespace tupleutils

#endif //MURRAYC_TUPLE_UTILS_TUPLE_INTERLACE_H
