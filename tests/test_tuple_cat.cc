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

#include <tuple-utils/tuple_cat.h>
#include <utility>
#include <cstdlib>
#include <cassert>

void test_tuple_type_cat() {
  using type_tuple_is = std::tuple<int, short>;
  using type_tuple_dc = std::tuple<double, char>;
  using type_tuple_cat = tupleutils::tuple_type_cat<type_tuple_is, type_tuple_dc>::type;
  using type_tuple_expected = std::tuple<int, short, double, char>;

  static_assert(std::tuple_size<type_tuple_cat>::value == 4,
    "unexpected tuple_cat()ed tuple size.");
  static_assert(std::is_same<type_tuple_cat, type_tuple_expected>::value,
    "unexpected tuple_cat()ed tuple type");
}

int main() {
  test_tuple_type_cat();
  //There is no typeutils::tuple_cat() because std::tuple_cat() exists: test_tuple_cat();

  return EXIT_SUCCESS;
}
