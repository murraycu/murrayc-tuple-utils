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

#include <cassert>
#include <cstdlib>
#include <tuple-utils/tuple_for_each.h>
#include <utility>
//#include <typeinfo>
#include <iostream>
#include <functional>
#include "gtest/gtest.h"

template <class T_element_from>
class for_each_simple {
public:
  static void
  visit(const T_element_from& from) {
    std::cout << "for_each_simple(): " << std::to_string(from) << std::endl;
  }
};

TEST(TestTupleForEach, SameType) {
  {
    auto t_original = std::make_tuple(1, 2, 3);
    tupleutils::tuple_for_each<for_each_simple>(t_original);
  }

  {
    auto t_original = std::make_tuple(1, (double)2.1f, 3);
    tupleutils::tuple_for_each<for_each_simple>(t_original);
  }
}

template <class T_element_from>
class for_each_simple_with_extras {
public:
  static void
  visit(const T_element_from& from, int extra1, const std::string& extra2) {
    std::cout << "for_each_simple_with_extras(): from=" << std::to_string(from)
              << ", extra1: " << extra1 << ", extra2: " << extra2 << std::endl;
  }
};

TEST(TestTupleForEach, SameTypesWithExtra) {
  {
    auto t_original = std::make_tuple(1, (double)2.1f, 3);
    tupleutils::tuple_for_each<for_each_simple_with_extras>(
      t_original, 89, "eightynine");
  }
}

template <class T_element_from>
class for_each_simple_with_nonconst_extras {
public:
  static void
  visit(const T_element_from& from, int& extra) {
    extra += (int)from;
  }
};

TEST(TestTupleForEach, SameTypesWithNonConstExtra) {
  {
    auto t_original = std::make_tuple(1, (double)2.1f, 3);
    int extra = 0;

    tupleutils::tuple_for_each<for_each_simple_with_nonconst_extras>(t_original, extra);
    // std::cout << "extra: " << extra << std::endl;
    EXPECT_EQ(6, extra);
  }
}

// The general template declaration.
// We then provide specializations for each type,
// so we can test having a different return value for each T_element_from type.
template <class T_element_from>
class visitor_with_specializations;

// An int will be converted to a std::string:
template <>
class visitor_with_specializations<int> {
public:
  static void
  visit(const int& from) {
    std::cout << "visitor_with_specializations::visit(): "
              << std::to_string(from) << std::endl;
  }
};

// A double will be converted to a char:
template <>
class visitor_with_specializations<double> {
public:
  static void
  visit(const double& from) {
    std::cout << "visitor_with_specializations::visit(): "
              << std::to_string(from)[0] << std::endl;
  }
};

// A std::string will be converted to an int:
template <>
class visitor_with_specializations<std::string> {
public:
  static void
  visit(const std::string& from) {
    std::cout << "visitor_with_specializations::visit(): " << std::stoi(from)
              << std::endl;
  }
};

// A const char* will be converted to an int:
template <>
class visitor_with_specializations<const char*> {
public:
  static void
  visit(const char* from) {
    std::cout << "visitor_with_specializations::visit(): " << std::stoi(from)
              << std::endl;
  }
};

TEST(TestTupleForEach, MultipleTypes) {
  auto t_original = std::make_tuple(1, (double)2.1f, std::string("3"));
  tupleutils::tuple_for_each<visitor_with_specializations>(t_original);
}

template <class T_element_from>
class for_each_nonconst {
public:
  static void
  visit(T_element_from& from) {
    from *= 2;
    // Or, for instance, call a non-const method on from.
  }
};

TEST(TestTupleForEach, NonConst) {
  auto t = std::make_tuple(1, 2, 3);
  tupleutils::tuple_for_each<for_each_nonconst, decltype(t)&>(t);
  std::cout << std::get<0>(t) << std::endl;
  EXPECT_EQ(2, std::get<0>(t));
  EXPECT_EQ(4, std::get<1>(t));
  EXPECT_EQ(6, std::get<2>(t));
}

TEST(TestTupleForEach, StdRef) {
  {
    int a = 1;
    int b = 2;
    int c = 3;
    auto t_original = std::make_tuple(std::ref(a), std::ref(b), std::ref(c));
    tupleutils::tuple_for_each<for_each_simple>(t_original);
  }

  {
    int a = 1;
    int b = 2;
    int c = 3;
    auto t_original = std::make_tuple(std::ref(a), std::ref(b), std::ref(c));
    tupleutils::tuple_for_each<for_each_nonconst>(t_original);
    EXPECT_EQ(2, a);
    EXPECT_EQ(4, b);
    EXPECT_EQ(6, c);
  }
}

static std::string correct_sequence_output;

template <class T_element_from>
class for_each_correct_sequence {
public:
  static void
  visit(const T_element_from& from) {
    //std::cout << "from: " << from << std::endl;
    correct_sequence_output += std::to_string(from);
  }
};

TEST(TestTupleForEach, CorrectSequence) {
  correct_sequence_output.clear();
  auto t = std::make_tuple(1, 2, 3);
  tupleutils::tuple_for_each<for_each_correct_sequence>(t);
  //std::cout << "correct_sequence_output: " << correct_sequence_output << std::endl;
  EXPECT_EQ("123", correct_sequence_output);
}

TEST(TestTupleForEach, EmptyTuple) {
  auto t = std::tuple<>();
  tupleutils::tuple_for_each<for_each_simple>(t);
}

// TODO: Does this test function itself need to be constexpr,
// and if so, how can we do that with googletest?
TEST(TestTupleForEach, ConstExpr) {
  constexpr auto t_original = std::make_tuple(1, (double)2.1f, "3");
  tupleutils::tuple_for_each<visitor_with_specializations>(t_original);
}

