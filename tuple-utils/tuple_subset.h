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

#ifndef MURRAYC_TUPLE_UTILS_TUPLE_SUBSET_H
#define MURRAYC_TUPLE_UTILS_TUPLE_SUBSET_H

#include <tuple-utils/tuple_end.h>
#include <tuple-utils/tuple_start.h>

namespace tupleutils {

/**
 * Get the type of a tuple with @a len elements from position @pos of the
 * original tuple type.
 */
template <typename T, std::size_t pos, std::size_t len>
struct tuple_type_subset {
  // Get the start to remove the size - (pos+len);
  // then get the end to remove the first pos elements:
  using type = typename tuple_type_start<
    typename tuple_type_end<T, std::tuple_size<std::decay_t<T>>::value - pos>::type,
    len>::type;

  /*
  private:
    constexpr size = std::tuple_size<T>::value>;
    static_assert(pos < size, "pos is too large");
    static_assert(pos + len <= size, "len is too large");
  */
};

/**
 * Get the a tuple with @a len elements from position @pos of the original tuple
 * type.
 */
template <std::size_t pos, std::size_t len, typename T>
constexpr
decltype(auto)
tuple_subset(T&& t) {
  //We use std::decay_t<> because tuple_size is not defined for references.
  constexpr auto size = std::tuple_size<std::decay_t<T>>::value;
  static_assert(pos < size, "The position must be less than the tuple size.");
  static_assert(len <= size - pos , "The length must be less than, or equal to, the available size from the position.");

  return tuple_start<len>(tuple_end<size - pos>(std::forward<T>(t)));
}

} // namespace tupleutils;

#endif //MURRAYC_TUPLE_UTILS_TUPLE_SUBSET_H
