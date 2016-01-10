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

#ifndef _MURRAYC_TUPLE_UTILS_TUPLE_TRANSFORM_EACH_H_
#define _MURRAYC_TUPLE_UTILS_TUPLE_TRANSFORM_EACH_H_

#include <tuple-utils/tuple_cat.h>
#include <tuple-utils/tuple_cdr.h>
#include <tuple-utils/tuple_start.h>
#include <tuple-utils/tuple_end.h>
#include <type_traits>

namespace tupleutils
{

namespace {

template<typename T, template<typename> class T_transformer, std::size_t index>
struct tuple_type_transform_each_impl
{
private:
  using from_element_type = typename std::tuple_element<index, T>::type;

  using to_element_type =
    typename std::result_of<decltype(&T_transformer<from_element_type>::transform)(const from_element_type&)>::type;

  //This gets the type of the function, not its return type:
  //using to_element_type = decltype(T_transformer<from_element_type>::transform);
  //
  //This also seems to get the type of the function, not its return type:
  //using to_element_type = decltype(T_transformer<from_element_type>::transform(from_element_type()));

  using t_element_type = std::tuple<to_element_type>;

  using t_type_start = typename tuple_type_start<T, index>::type;

  using t_type_end = typename tuple_type_end<T, std::tuple_size<T>::value - index - 1>::type;

  using t_type_with_transformed_element =
    typename tuple_type_cat<
      typename tuple_type_cat<t_type_start, t_element_type>::type,
      t_type_end>::type;

public:
  using type = typename tuple_type_transform_each_impl<t_type_with_transformed_element, T_transformer, index - 1>::type;
};

template<typename T, template<typename> class T_transformer>
struct tuple_type_transform_each_impl<T, T_transformer, 0>
{
private:
  static constexpr std::size_t index = 0;
  using from_element_type = typename std::tuple_element<index, T>::type;
  using to_element_type = decltype(T_transformer<from_element_type>::transform);
  using t_element_type = std::tuple<to_element_type>;

  using t_type_end = typename tuple_type_end<T, std::tuple_size<T>::value - index - 1>::type;

  using t_type_with_transformed_element =
    typename tuple_type_cat<t_element_type, t_type_end>::type;

public:
  using type = t_type_with_transformed_element;
};

} //anonymous namespace


/**
 * Get a tuple with each element having the transformed value of the element
 * in the original tuple.
 */

template<typename T, template<typename> class T_transformer>
struct tuple_type_transform_each
{
  using type = typename tuple_type_transform_each_impl<T, T_transformer, std::tuple_size<T>::value - 1>::type;
};

namespace {

template<template<typename> class T_transformer, std::size_t index>
struct tuple_transform_each_impl
{
  template<typename T>
  static
  decltype(auto)
  tuple_transform_each(const T& t) {
    using element_type = typename std::tuple_element<index, T>::type;
    const auto element = T_transformer<element_type>::transform(std::get<index>(t));
    const auto t_element = std::make_tuple(element);
    
    const auto t_start = tuple_start<index>(t);

    constexpr auto size = std::tuple_size<T>::value; 
    const auto t_end = tuple_end<size - index - 1>(t);

    const auto t_with_transformed_element =
      std::tuple_cat(t_start, t_element, t_end);
    return tuple_transform_each_impl<T_transformer, index - 1>::tuple_transform_each(
      t_with_transformed_element);
  }
};

template<template<typename> class T_transformer>
struct tuple_transform_each_impl<T_transformer, 0>
{

  template<typename T>
  static
  decltype(auto)
  tuple_transform_each(const T& t) {
    constexpr std::size_t index = 0;

    using element_type = typename std::tuple_element<index, T>::type;
    const auto element = T_transformer<element_type>::transform(std::get<index>(t));
    const auto tuple_element = std::make_tuple(element);
    const auto tuple_rest = tuple_cdr(t);
    return std::tuple_cat(tuple_element, tuple_rest);
  }
};

} //anonymous namespace

/**
 * Get a tuple with each element having the transformed value of the element
 * in the original tuple.
 */
template<template<typename> class T_transformer, typename T>
decltype(auto)
tuple_transform_each(const T& t) {
  constexpr auto size = std::tuple_size<T>::value; 
  return tuple_transform_each_impl<T_transformer, size - 1>::tuple_transform_each(t);
}

} //namespace tupleutils

#endif //_MURRAYC_TUPLE_UTILS_TUPLE_TRANSFORM_EACH_H_
