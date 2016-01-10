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

#include <tuple-utils/tuple_transform_each.h>
#include <utility>
#include <cstdlib>
#include <cassert>

void test_tuple_type_transform_each()
{
 //TODO
}

template <class T_element_from>
class transform_to_string
{
public:
  static
  decltype(auto)
  transform(const T_element_from& from) {
    return std::to_string(from);
  } 
};

void test_tuple_transform_each()
{
  {
    auto t_original = std::make_tuple(1, 2, 3);
    auto t_transformed = tupleutils::tuple_transform_each<transform_to_string>(t_original);
    auto t_expected = std::make_tuple(std::string("1"), std::string("2"), std::string("3"));

    static_assert(std::tuple_size<decltype(t_transformed)>::value == 3,
      "unexpected tuple_transform_each()ed tuple size.");

    assert(std::get<0>(t_transformed) == "1");
    assert(std::get<1>(t_transformed) == "2");
    assert(std::get<2>(t_transformed) == "3");

    static_assert(std::is_same<decltype(t_transformed), decltype(t_expected)>::value,
      "unexpected transform_each()ed tuple type");
  }

  {
    auto t_original = std::make_tuple(1, (double)2.1f, 3);
    auto t_transformed = tupleutils::tuple_transform_each<transform_to_string>(t_original);
    auto t_expected = std::make_tuple(std::string("1"), std::string("2"), std::string("3"));

    static_assert(std::tuple_size<decltype(t_transformed)>::value == 3,
      "unexpected tuple_transform_each()ed tuple size.");

    assert(std::get<0>(t_transformed) == "1");
    assert(std::get<1>(t_transformed).substr(0, 3) == "2.1");
    assert(std::get<2>(t_transformed) == "3");

    static_assert(std::is_same<decltype(t_transformed), decltype(t_expected)>::value,
      "unexpected transform_each()ed tuple type");
  }

  //TODO: A test in which the transformer returns different types depending on the input element type.

}

int main()
{
  test_tuple_type_transform_each();
  test_tuple_transform_each();
      
  return EXIT_SUCCESS;
}
