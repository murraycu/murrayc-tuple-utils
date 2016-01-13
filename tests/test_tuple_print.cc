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

#include <tuple-utils/tuple_print.h>
#include <cstdlib>
#include <cassert>
#include <sstream>

int main()
{
  std::ostringstream strstream;
  const auto t = std::make_tuple(1, 2, "three");
  tupleutils::tuple_print(t, strstream);
  assert("1, 2, three" == strstream.str()); 
      
  return EXIT_SUCCESS;
}
