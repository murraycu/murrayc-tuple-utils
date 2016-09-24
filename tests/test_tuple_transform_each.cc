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
#include <tuple-utils/tuple_transform_each.h>
#include <functional>
#include <gtest/gtest.h>

template <class T_element_from>
class transform_to_string {
public:
  static decltype(auto)
  transform(const T_element_from& from) {
    return std::to_string(from);
  }
};

TEST(TestTupleTransformEach, TypeSameTypes) {
  using type_tuple_original = std::tuple<int, int>;
  using type_tuple_transformed =
    tupleutils::tuple_type_transform_each<type_tuple_original,
      transform_to_string>::type;
  using type_tuple_expected = std::tuple<std::string, std::string>;

  static_assert(
    std::is_same<type_tuple_transformed, type_tuple_expected>::value,
    "unexpected tuple_transform_each()ed tuple type");
}

// In these tests, t_expected has elements all of the same type.
TEST(TestTupleTransformEach, SameTypes) {
  {
    auto t_original = std::make_tuple(1, 2, 3);
    auto t_transformed =
      tupleutils::tuple_transform_each<transform_to_string>(t_original);
    auto t_expected =
      std::make_tuple(std::string("1"), std::string("2"), std::string("3"));

    static_assert(std::tuple_size<decltype(t_transformed)>::value == 3,
      "unexpected tuple_transform_each()ed tuple size.");

    EXPECT_EQ("1", std::get<0>(t_transformed));
    EXPECT_EQ("2", std::get<1>(t_transformed));
    EXPECT_EQ("3", std::get<2>(t_transformed));

    static_assert(
      std::is_same<decltype(t_transformed), decltype(t_expected)>::value,
      "unexpected transform_each()ed tuple type");
  }

  {
    auto t_original = std::make_tuple(1, (double)2.1f, 3);
    auto t_transformed =
      tupleutils::tuple_transform_each<transform_to_string>(t_original);
    auto t_expected =
      std::make_tuple(std::string("1"), std::string("2"), std::string("3"));

    static_assert(std::tuple_size<decltype(t_transformed)>::value == 3,
      "unexpected tuple_transform_each()ed tuple size.");

    EXPECT_EQ("1", std::get<0>(t_transformed));
    EXPECT_EQ("2.1", std::get<1>(t_transformed).substr(0, 3));
    EXPECT_EQ("3", std::get<2>(t_transformed));

    static_assert(
      std::is_same<decltype(t_transformed), decltype(t_expected)>::value,
      "unexpected transform_each()ed tuple type");
  }
}

// The general template declaration.
// We then provide specializations for each type,
// so we can test having a different return value for each T_element_from type.
template <class T_element_from>
class transform_to_something;

// An int will be converted to a std::string:
template <>
class transform_to_something<int> {
public:
  static std::string
  transform(int from) {
    return std::to_string(from);
  }
};

// A double will be converted to a char:
template <>
class transform_to_something<double> {
public:
  static char
  transform(double from) {
    return std::to_string(from)[0];
  }
};

// A std::string will be converted to an int:
template <>
class transform_to_something<std::string> {
public:
  static int
  transform(const std::string& from) {
    return std::stoi(from);
  }
};

TEST(TestTupleTransformEach, TypeMultipeTypes) {
  using type_tuple_original = std::tuple<int, double, std::string>;
  using type_tuple_transformed =
    tupleutils::tuple_type_transform_each<type_tuple_original,
      transform_to_something>::type;
  using type_tuple_expected = std::tuple<std::string, char, int>;

  static_assert(
    std::is_same<type_tuple_transformed, type_tuple_expected>::value,
    "unexpected tuple_transform_each()ed tuple type");
}

TEST(TestTupleTransformEach, MultipleTypes) {
  auto t_original = std::make_tuple(1, (double)2.1f, std::string("3"));
  auto t_transformed =
    tupleutils::tuple_transform_each<transform_to_something>(t_original);
  auto t_expected = std::make_tuple(std::string("1"), '2', 3);

  static_assert(std::tuple_size<decltype(t_transformed)>::value == 3,
    "unexpected tuple_transform_each()ed tuple size.");

  EXPECT_EQ("1", std::get<0>(t_transformed));
  EXPECT_EQ('2', std::get<1>(t_transformed));
  EXPECT_EQ(3, std::get<2>(t_transformed));

  static_assert(
    std::is_same<decltype(t_transformed), decltype(t_expected)>::value,
    "unexpected transform_each()ed tuple type");
}

template <class T_element_from>
class transform_each_nonconst {
public:
  static int
  transform(T_element_from& from) {
    from *= 2;
    // Or, for instance, call a non-const method on from.

    return from * 10;
  }
};

TEST(TestTupleTransformEach, NonConst) {
  auto t = std::make_tuple(1, 2, 3);
  auto t_transformed =
    tupleutils::tuple_transform_each<transform_each_nonconst>(t);

  // Check that t was changed (from * 2):
  EXPECT_EQ(2, std::get<0>(t));
  EXPECT_EQ(4, std::get<1>(t));
  EXPECT_EQ(6, std::get<2>(t));

  // Check that t_transformed has the expected values ( from * 2 * 10):
  EXPECT_EQ(20, std::get<0>(t_transformed));
  EXPECT_EQ(40, std::get<1>(t_transformed));
  EXPECT_EQ(60, std::get<2>(t_transformed));
}

TEST(TestTupleTransformEach, StdRef) {
  int a = 1;
  int b = 2;
  int c = 3;
  auto t_original = std::make_tuple(std::ref(a), std::ref(b), std::ref(c));
  auto t_transformed =
    tupleutils::tuple_transform_each<transform_to_string>(t_original);
  auto t_expected =
    std::make_tuple(std::string("1"), std::string("2"), std::string("3"));

  static_assert(std::tuple_size<decltype(t_transformed)>::value == 3,
    "unexpected tuple_transform_each()ed tuple size.");

  EXPECT_EQ("1", std::get<0>(t_transformed));
  EXPECT_EQ("2", std::get<1>(t_transformed));
  EXPECT_EQ("3", std::get<2>(t_transformed));

  static_assert(
    std::is_same<decltype(t_transformed), decltype(t_expected)>::value,
    "unexpected transform_each()ed tuple type");
}


//This can only be used via std::ref(), for instance.
//Any attempt to copy or move it, should cause a compiler error.
class NonCopyable {
public:
  explicit NonCopyable(int val)
  : m_val(val)
  {}

  int get_val() const {
    return m_val;
  }

  NonCopyable(const NonCopyable& src) = delete;
  NonCopyable& operator=(const NonCopyable& src) = delete;

  NonCopyable(NonCopyable&& src) = delete;
  NonCopyable& operator=(NonCopyable&& src) = delete;

private:
  int m_val;
};


template <class T_element_from>
class transform_noncopyable_to_string {
public:
  static decltype(auto)
  transform(T_element_from&& from) {
    return std::to_string(from.get_val());
  }
};

TEST(TestTupleTransformEach, StdRefNonCopyable) {
  NonCopyable a(1);
  NonCopyable b(2);
  NonCopyable c(3);
  auto t_original = std::make_tuple(std::ref(a), std::ref(b), std::ref(c));
  auto t_transformed =
    tupleutils::tuple_transform_each<transform_noncopyable_to_string>(t_original);
  auto t_expected =
    std::make_tuple(std::string("1"), std::string("2"), std::string("3"));

  static_assert(std::tuple_size<decltype(t_transformed)>::value == 3,
    "unexpected tuple_transform_each()ed tuple size.");

  EXPECT_EQ("1", std::get<0>(t_transformed));
  EXPECT_EQ("2", std::get<1>(t_transformed));
  EXPECT_EQ("3", std::get<2>(t_transformed));

  static_assert(
    std::is_same<decltype(t_transformed), decltype(t_expected)>::value,
    "unexpected transform_each()ed tuple type");
}

static std::string correct_sequence_output;

template <class T_element_from>
class transform_each_correct_sequence {
public:
  static decltype(auto)
  transform(int from) {
    correct_sequence_output += std::to_string(from);
    return std::to_string(from);
  }
};

TEST(TestTupleTransformEach, CorrectSequence) {
  correct_sequence_output.clear();
  auto t = std::make_tuple(1, 2, 3);
  tupleutils::tuple_transform_each<transform_each_correct_sequence>(t);
  //std::cout << "correct_sequence_output: " << correct_sequence_output << std::endl;
  EXPECT_EQ("123", correct_sequence_output);
}

TEST(TestTupleTransformEach, EmptyTuple) {
  auto t = std::tuple<>();
  tupleutils::tuple_transform_each<transform_to_string>(t);
}

// The general template declaration.
// We then provide specializations for each type,
// so we can test having a different return value for each T_element_from type.
template <class T_element_from>
class transform_as_constexpr_to_something;

// An int will be converted to a char:
template <>
class transform_as_constexpr_to_something<int> {
public:
  constexpr
  static
  char
  transform(int from) {
    return 'a' + from;
  }
};

// A double will be converted to an int:
template <>
class transform_as_constexpr_to_something<const double> {
public:
  constexpr
  static
  int
  transform(double from) {
    return (int)from;
  }
};

/*
// g++ 5.2.1 gives this error:
//   error: accessing uninitialized member ‘std::tuple<char>::<anonymous>’
// though it works with clang++.
// TODO: Try it with a newer g++.
TEST(TestTupleTransformEach, ConstExpr) {
  constexpr auto t_original = std::make_tuple(1, (double)2.1f);
  constexpr auto t_transformed =
    tupleutils::tuple_transform_each<transform_as_constexpr_to_something>(t_original);
  constexpr auto t_expected = std::make_tuple('b', 2);

  static_assert(std::tuple_size<decltype(t_transformed)>::value == 2,
    "unexpected tuple_transform_each()ed tuple size.");

  EXPECT_EQ('b', std::get<0>(t_transformed));
  EXPECT_EQ(2, std::get<1>(t_transformed));

  static_assert(
    std::is_same<decltype(t_transformed), decltype(t_expected)>::value,
    "unexpected transform_each()ed tuple type");
}
*/

