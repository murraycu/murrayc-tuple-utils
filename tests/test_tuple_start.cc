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

#include <cstdlib>
#include <string>
#include <tuple-utils/tuple_start.h>
#include <functional>
#include "gtest/gtest.h"

TEST(TestTupleStart, Type) {
  {
    using type_tuple = std::tuple<int, short, double>;
    using type_tuple_start = tupleutils::tuple_type_start<type_tuple, 1>::type;
    using type_tuple_expected = std::tuple<int>;

    static_assert(std::is_same<type_tuple_start, type_tuple_expected>::value,
      "unexpected type_tuple_start type");
  }

  {
    using type_tuple = std::tuple<int, short, double>;
    using type_tuple_start = tupleutils::tuple_type_start<type_tuple, 2>::type;
    using type_tuple_expected = std::tuple<int, short>;

    static_assert(std::is_same<type_tuple_start, type_tuple_expected>::value,
      "unexpected type_tuple_start type");
  }

  {
    using type_tuple = std::tuple<int, short, double>;
    using type_tuple_start = tupleutils::tuple_type_start<type_tuple, 3>::type;
    using type_tuple_expected = std::tuple<int, short, double>;

    static_assert(std::is_same<type_tuple_start, type_tuple_expected>::value,
      "unexpected type_tuple_start type");
  }
}

TEST(TestTupleStart, Simple) {
  //Check that tuple_star<0> returns an empty tuple:
  {
    auto t_original =
      std::make_tuple(1, 2, 3);
    auto t_prefix = tupleutils::tuple_start<0>(t_original);

    static_assert(std::tuple_size<decltype(t_prefix)>::value == 0,
      "unexpected tuple_start()ed tuple size.");

    static_assert(std::is_same<decltype(t_prefix), std::tuple<>>::value,
      "unexpected start()ed tuple type");
  }

  //Check that tuple_start<whole size> gets the original tuple:
  {
    auto t_original =
      std::make_tuple(nullptr, std::string("hello"), std::string("world"));
    auto t_prefix = tupleutils::tuple_start<3>(t_original);

    static_assert(std::tuple_size<decltype(t_prefix)>::value == 3,
      "unexpected tuple_start()ed tuple size.");

    EXPECT_EQ(nullptr, std::get<0>(t_prefix));
    EXPECT_EQ("hello", std::get<1>(t_prefix));
    EXPECT_EQ("world", std::get<2>(t_prefix));

    static_assert(std::is_same<decltype(t_prefix), decltype(t_original)>::value,
      "unexpected start()ed tuple type");
  }

  {
    auto t_original =
      std::make_tuple(nullptr, std::string("hello"), std::string("world"));
    auto t_prefix = tupleutils::tuple_start<2>(t_original);

    static_assert(std::tuple_size<decltype(t_prefix)>::value == 2,
      "unexpected tuple_start()ed tuple size.");

    EXPECT_EQ(nullptr, std::get<0>(t_prefix));
    EXPECT_EQ("hello", std::get<1>(t_prefix));

    using type_tuple_prefix = std::tuple<std::nullptr_t, std::string>;
    static_assert(std::is_same<decltype(t_prefix), type_tuple_prefix>::value,
      "unexpected start()ed tuple type");
  }

  {
    auto t_original =
      std::make_tuple(nullptr, std::string("hello"), std::string("world"));
    auto t_prefix = tupleutils::tuple_start<1>(t_original);

    static_assert(std::tuple_size<decltype(t_prefix)>::value == 1,
      "unexpected tuple_start()ed tuple size.");

    EXPECT_EQ(nullptr, std::get<0>(t_prefix));

    using type_tuple_prefix = std::tuple<std::nullptr_t>;
    static_assert(std::is_same<decltype(t_prefix), type_tuple_prefix>::value,
      "unexpected start()ed tuple type");
  }
}

TEST(TestTupleStart, StdRef) {
  std::string a = "yadda";
  std::string b = "yaddayadda";
  auto t_larger = std::make_tuple(std::ref(a), std::ref(b), 1);

  auto t_prefix = tupleutils::tuple_start<2>(t_larger);
  a = "hello";
  b = "world";
  //This works, but it's not what we are testing here:
  //assert(std::get<0>(t_larger) == "hello");

  EXPECT_EQ("hello", std::get<0>(t_prefix));
  EXPECT_EQ("world", std::get<1>(t_prefix));
}

// TODO: Does this test function itself need to be constexpr,
// and if so, how can we do that with googletest?
TEST(TestTupleStart, ConstExpr) {
  constexpr auto str_hello = "hello";
  constexpr auto str_world = "hello";

  constexpr auto t_original =
    std::make_tuple(nullptr, str_hello, str_world);
  constexpr auto t_prefix = tupleutils::tuple_start<2>(t_original);

  static_assert(std::tuple_size<decltype(t_prefix)>::value == 2,
    "unexpected tuple_start()ed tuple size.");

  static_assert(std::get<0>(t_prefix) == nullptr,
    "unexpected tuple element value.");

  static_assert(std::get<1>(t_prefix) == str_hello,
    "unexpected tuple element value.");
}
