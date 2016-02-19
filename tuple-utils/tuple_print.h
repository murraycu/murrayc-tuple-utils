/* Copyright (C) 2015 Murray Cumming
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

#ifndef MURRAYC_TUPLE_UTILS_TUPLE_PRINT_H
#define MURRAYC_TUPLE_UTILS_TUPLE_PRINT_H

#include <iostream>
#include <tuple>

namespace tupleutils {

namespace detail {

// Based on example code from here:
// http://en.cppreference.com/w/cpp/utility/tuple/tuple_cat

template <class T, std::size_t N>
class TuplePrinter {
public:
  static void
  print(T&& t, std::ostream& output_stream) {
    TuplePrinter<T, N - 1>::print(t, output_stream);
    output_stream << ", " << std::get<N - 1>(std::forward<T>(t));
  }
};

template <class T>
class TuplePrinter<T, 1> {
public:
  static void
  print(T&& t, std::ostream& output_stream) {
    output_stream << std::get<0>(std::forward<T>(t));
  }
};

} // detail namespace

// TODO: Take a const std::tuple<Args...>& instead,
// to restrict the type allowed?
template <class T>
void
tuple_print(T&& t, std::ostream& output_stream = std::cout) {
  //We use std::decay_t<> because tuple_size is not defined for references.
  constexpr auto size = std::tuple_size<std::decay_t<T>>::value;
  detail::TuplePrinter<T, size>::print(std::forward<T>(t), output_stream);
}

} // namespace tupleutils

#endif //MURRAYC_TUPLE_UTILS_TUPLE_PRINT_H
