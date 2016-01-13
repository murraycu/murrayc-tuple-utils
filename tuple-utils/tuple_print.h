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

#ifndef _MURRAYC_TUPLE_UTILS_TUPLE_PRINT_H
#define _MURRAYC_TUPLE_UTILS_TUPLE_PRINT_H

#include <tuple>
#include <iostream>

namespace tupleutils {

namespace { //anonymous namespace

// Based on example code from here:
// http://en.cppreference.com/w/cpp/utility/tuple/tuple_cat

template<class T, std::size_t N>
class TuplePrinter {
public:
  static void print(const T& t, std::ostream& output_stream) 
  {
    TuplePrinter<T, N-1>::print(t, output_stream);
    output_stream << ", " << std::get<N-1>(t);
  }
};

template<class T>
class TuplePrinter<T, 1> {
public:
  static void print(const T& t, std::ostream& output_stream)  {
    output_stream << std::get<0>(t);
  }
};

} //anonymous namespace

//TODO: Take a const std::tuple<Args...>& instead,
//to restrict the type allowed?
template<class T>
void tuple_print(const T& t, std::ostream& output_stream = std::cout) {
  TuplePrinter<T, std::tuple_size<T>::value>::print(t, output_stream);
}

} //namespace tupleutils

#endif //_MURRAYC_TUPLE_UTILS_TUPLE_PRINT_H
