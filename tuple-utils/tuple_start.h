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

#ifndef _MURRAYC_TUPLE_UTILS_TUPLE_START_H_
#define _MURRAYC_TUPLE_UTILS_TUPLE_START_H_

#include <tuple>
#include <utility>

namespace tupleutils {

namespace {

template <typename T, typename Seq>
struct tuple_type_start_impl;

template <typename T, std::size_t... I>
struct tuple_type_start_impl<T, std::index_sequence<I...>> {
  using type = std::tuple<typename std::tuple_element<I, T>::type...>;
};

} // anonymous namespace

/**
 * Get the type of a tuple with just the first @len items.
 */
template <typename T, std::size_t len>
struct tuple_type_start
  : tuple_type_start_impl<T, std::make_index_sequence<len>> {};

namespace {

template <typename T, typename Seq>
struct tuple_start_impl;

template <typename T, std::size_t... I>
struct tuple_start_impl<T, std::index_sequence<I...>> {
  static decltype(auto)
  tuple_start(T&& t) {
    constexpr auto size = std::tuple_size<std::decay_t<T>>::value;
    constexpr auto len = sizeof...(I);
    static_assert(len <= size, "The tuple size must be less than or equal to the length.");

    using start = typename tuple_type_start<std::decay_t<T>, len>::type;
    return start(std::get<I>(std::forward<T>(t))...);
  }
};

} // anonymous namespace

/**
 * Get the tuple with the last @a len items of the original.
 */
template <std::size_t len, typename T>
decltype(auto) // typename tuple_type_end<T, len>::type
  tuple_start(T&& t) {
  constexpr auto size = std::tuple_size<std::decay_t<T>>::value;
  static_assert(len <= size, "The tuple size must be less than or equal to the length.");

  return tuple_start_impl<T, std::make_index_sequence<len>>::tuple_start(
    std::forward<T>(t));
}

} // namespace tupleutils;

#endif //_MURRAYC_TUPLE_UTILS_TUPLE_START_H_
