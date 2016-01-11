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

#include <tuple-utils/tuple_for_each.h>
#include <utility>
#include <cstdlib>
#include <cassert>
//#include <typeinfo>
#include <iostream>

template <class T_element_from>
class for_each_simple
{
public:
  static
  void
  visit(const T_element_from& from) {
    std::cout << "for_each_simple(): " << std::to_string(from) << std::endl;
  } 
};

void test_tuple_for_each_same_types()
{
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
class for_each_simple_with_extras
{
public:
  static
  void
  visit(const T_element_from& from, int extra1, const std::string& extra2) {
    std::cout << "for_each_simple_with_extras(): from=" <<
      std::to_string(from) <<
      ", extra1: " << extra1 <<
      ", extra2: " << extra2 << std::endl;
  }
};

void test_tuple_for_each_same_types_with_extras()
{
  {
    auto t_original = std::make_tuple(1, 2, 3);
    tupleutils::tuple_for_each<for_each_simple_with_extras>(t_original, 99, "ninetynine");
  }

  {
    auto t_original = std::make_tuple(1, (double)2.1f, 3);
    tupleutils::tuple_for_each<for_each_simple_with_extras>(t_original, 89, "eightynine");
  }
}

//The general template declaration.
//We then provide specializations for each type,
//so we can test having a different return value for each T_element_from type.
template <class T_element_from>
class visitor_with_specializations;

//An int will be converted to a std::string:
template <>
class visitor_with_specializations<int>
{
public:
  static
  void
  visit(const int& from) {
    std::cout << "visitor_with_specializations::visit(): " << std::to_string(from) << std::endl;
  } 
};

//A double will be converted to a char:
template <>
class visitor_with_specializations<double>
{
public:
  static
  void
  visit(const double& from) {
    std::cout << "visitor_with_specializations::visit(): " << std::to_string(from)[0] << std::endl;
  } 
};

//A std::string will be converted to an int:
template <>
class visitor_with_specializations<std::string>
{
public:
  static
  void
  visit(const std::string& from) {
    std::cout << "visitor_with_specializations::visit(): " << std::stoi(from) << std::endl;
  } 
};

void test_tuple_for_each_multiple_types()
{
  auto t_original = std::make_tuple(1, (double)2.1f, std::string("3"));
  tupleutils::tuple_for_each<visitor_with_specializations>(t_original);
}

int main()
{
  test_tuple_for_each_same_types();
  test_tuple_for_each_same_types_with_extras();

  test_tuple_for_each_multiple_types();
      
  return EXIT_SUCCESS;
}
