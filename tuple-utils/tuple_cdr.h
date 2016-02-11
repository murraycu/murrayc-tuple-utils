/* Copyright (C) 2016 Murray Cumming
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 */

#ifndef _MURRAYC_TUPLE_UTILS_TUPLE_CDR_H_
#define _MURRAYC_TUPLE_UTILS_TUPLE_CDR_H_

#include <tuple>
#include <type_traits>
#include <utility>

namespace tupleutils {

namespace {

template <typename T, typename Seq>
struct tuple_type_cdr_impl;

template <typename T, std::size_t I0, std::size_t... I>
struct tuple_type_cdr_impl<T, std::index_sequence<I0, I...>> {
  using type = std::tuple<typename std::tuple_element<I, T>::type...>;
};

} // anonymous namespace

/**
 * Get the type of a tuple without the first item.
 */
template <typename T>
struct tuple_type_cdr : tuple_type_cdr_impl<T,
                          std::make_index_sequence<std::tuple_size<T>::value>> {
};

namespace {

template <typename T, std::size_t I0, std::size_t... I>
decltype(auto)
tuple_cdr_impl(const T& t, std::index_sequence<I0, I...>) {
  return std::make_tuple(std::get<I>(t)...);
}

} // anonymous namespace

/**
 * Get the a tuple without the first item.
 * This is analogous to std::tuple_cat().
 */
template <typename T>
decltype(auto)
tuple_cdr(const T& t) {
  constexpr auto size = std::tuple_size<T>::value;
  const auto seq = std::make_index_sequence<size>{};
  return tuple_cdr_impl(t, seq);
}

} // namespace tupleutils

#endif //_MURRAYC_TUPLE_UTILS_TUPLE_CDR_H_
