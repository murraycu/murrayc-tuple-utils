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

#ifndef _MURRAYC_TUPLE_UTILS_TUPLE_END_H_
#define _MURRAYC_TUPLE_UTILS_TUPLE_END_H_

#include <tuple-utils/tuple_cdr.h>

namespace tupleutils
{

namespace {

template<typename T, std::size_t remove_from_start>
struct tuple_type_end_impl
{
  using type = typename tuple_type_end_impl<typename tuple_type_cdr<T>::type, remove_from_start - 1>::type;
};

template<typename T>
struct tuple_type_end_impl<T, 0>
{
  using type = T;
};

} //anonymous namespace


/**
 * Get the type of a tuple with the last @a len types of the original.
 */
template<typename T, std::size_t len>
struct tuple_type_end
: tuple_type_end_impl<T, std::tuple_size<T>::value - len>
{};


namespace {

template<typename T, std::size_t remove_from_start>
struct tuple_end_impl
{
  static
  decltype(auto) //typename tuple_type_end<T, size - remove_from_start>::type 
  tuple_end(const T& t) {
    return tuple_end_impl<typename tuple_type_cdr<T>::type, remove_from_start - 1>::tuple_end(tuple_cdr(t));
  }
};

template<typename T>
struct tuple_end_impl<T, 0>
{
  static
  T
  tuple_end(const T& t) {
    return t;
  }
};

} //anonymous namespace

/**
 * Get the ttuple with the last @a len items of the original.
 */
template<std::size_t len, typename T>
decltype(auto) //typename tuple_type_end<T, len>::type 
tuple_end(const T& t) {
  constexpr auto size = std::tuple_size<T>::value; 
  return tuple_end_impl<T, size - len>::tuple_end(t);
}

} //namespace tupleutils;

#endif //_MURRAYC_TUPLE_UTILS_TUPLE_END_H_
