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
#include <tuple-utils/tuple_subset.h>
#include "gtest/gtest.h"

TEST(TestTupleSubset, Type) {
  {
    using type_tuple = std::tuple<int, short, double>;
    using type_tuple_subset =
      tupleutils::tuple_type_subset<type_tuple, 0, 1>::type;
    using type_tuple_expected = std::tuple<int>;

    static_assert(std::is_same<type_tuple_subset, type_tuple_expected>::value,
      "unexpected type_tuple_subset type");
  }

  {
    using type_tuple = std::tuple<int, short, double>;
    using type_tuple_subset =
      tupleutils::tuple_type_subset<type_tuple, 0, 2>::type;
    using type_tuple_expected = std::tuple<int, short>;

    static_assert(std::is_same<type_tuple_subset, type_tuple_expected>::value,
      "unexpected type_tuple_subset type");
  }

  {
    using type_tuple = std::tuple<int, short, double>;
    using type_tuple_subset =
      tupleutils::tuple_type_subset<type_tuple, 0, 3>::type;
    using type_tuple_expected = std::tuple<int, short, double>;

    static_assert(std::is_same<type_tuple_subset, type_tuple_expected>::value,
      "unexpected type_tuple_subset type");
  }

  {
    using type_tuple = std::tuple<int, short, double>;
    using type_tuple_subset =
      tupleutils::tuple_type_subset<type_tuple, 1, 2>::type;
    using type_tuple_expected = std::tuple<short, double>;

    static_assert(std::is_same<type_tuple_subset, type_tuple_expected>::value,
      "unexpected type_tuple_subset type");
  }

  {
    using type_tuple = std::tuple<int, short, double>;
    using type_tuple_subset =
      tupleutils::tuple_type_subset<type_tuple, 2, 1>::type;
    using type_tuple_expected = std::tuple<double>;

    static_assert(std::is_same<type_tuple_subset, type_tuple_expected>::value,
      "unexpected type_tuple_subset type");
  }
}

TEST(TestTupleSubset, Simple) {
  {
    auto t_original =
      std::make_tuple(nullptr, std::string("hello"), std::string("world"));
    auto t_subset = tupleutils::tuple_subset<0, 3>(t_original);

    static_assert(std::tuple_size<decltype(t_subset)>::value == 3,
      "unexpected tuple_subset()ed tuple size.");

    EXPECT_EQ(nullptr, std::get<0>(t_subset));
    EXPECT_EQ("hello", std::get<1>(t_subset));
    EXPECT_EQ("world", std::get<2>(t_subset));

    static_assert(std::is_same<decltype(t_subset), decltype(t_original)>::value,
      "unexpected start()ed tuple type");
  }

  {
    auto t_original =
      std::make_tuple(nullptr, std::string("hello"), std::string("world"));
    auto t_subset = tupleutils::tuple_subset<0, 2>(t_original);

    static_assert(std::tuple_size<decltype(t_subset)>::value == 2,
      "unexpected tuple_subset()ed tuple size.");

    EXPECT_EQ(nullptr, std::get<0>(t_subset));
    EXPECT_EQ("hello", std::get<1>(t_subset));

    using type_tuple_subset = std::tuple<std::nullptr_t, std::string>;
    static_assert(std::is_same<decltype(t_subset), type_tuple_subset>::value,
      "unexpected start()ed tuple type");
  }

  {
    auto t_original =
      std::make_tuple(nullptr, std::string("hello"), std::string("world"));
    auto t_subset = tupleutils::tuple_subset<0, 1>(t_original);

    static_assert(std::tuple_size<decltype(t_subset)>::value == 1,
      "unexpected tuple_subset()ed tuple size.");

    EXPECT_EQ(nullptr, std::get<0>(t_subset));

    using type_tuple_subset = std::tuple<std::nullptr_t>;
    static_assert(std::is_same<decltype(t_subset), type_tuple_subset>::value,
      "unexpected start()ed tuple type");
  }

  {
    auto t_original =
      std::make_tuple(nullptr, std::string("hello"), std::string("world"));
    auto t_subset = tupleutils::tuple_subset<1, 1>(t_original);

    static_assert(std::tuple_size<decltype(t_subset)>::value == 1,
      "unexpected tuple_subset()ed tuple size.");

    EXPECT_EQ("hello", std::get<0>(t_subset));

    using type_tuple_subset = std::tuple<std::string>;
    static_assert(std::is_same<decltype(t_subset), type_tuple_subset>::value,
      "unexpected start()ed tuple type");
  }
}

TEST(TestTupleSubset, ConstExpr) {
  constexpr auto str_hello = "hello";
  constexpr auto str_world = "world";

  constexpr auto t_original =
    std::make_tuple(nullptr, str_hello, str_world);
  constexpr auto t_subset = tupleutils::tuple_subset<0, 2>(t_original);

  static_assert(std::tuple_size<decltype(t_subset)>::value == 2,
    "unexpected tuple_subset()ed tuple size.");

  EXPECT_EQ(nullptr, std::get<0>(t_subset));
  EXPECT_EQ(str_hello, std::get<1>(t_subset));
}