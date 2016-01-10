#include <cstdlib>
#include <cassert>
#include <utility>
#include <tuple-utils/tuple_interlace.h>

void test_tuple_type_interlace_empty() {
  using type_tuple1 = std::tuple<>;
  using type_tuple2 = std::tuple<>;
  using type_tuple12 = std::tuple<>;

  using type_tuple_interlaced =
    tupleutils::tuple_type_interlace<type_tuple1, type_tuple2>::type;

  static_assert(std::is_same<type_tuple_interlaced, type_tuple12>::value,
      "unexpected tuple_interlace()ed tuple type");
}

void test_tuple_type_interlace() {
  using type_tuple_is = std::tuple<int, short>;
  using type_tuple_dc = std::tuple<double, char>;
  using type_tuple_idsc = std::tuple<int, double, short, char>;

  using type_tuple_interlaced =
    tupleutils::tuple_type_interlace<type_tuple_is, type_tuple_dc>::type;

  static_assert(std::is_same<type_tuple_interlaced, type_tuple_idsc>::value,
      "unexpected tuple_interlace()ed tuple type");
}

void test_tuple_interlace_empty() {
  using type_tuple1 = std::tuple<>;
  using type_tuple2 = std::tuple<>;
  using type_tuple12 = std::tuple<>;
  
  type_tuple1 tuple1;
  type_tuple2 tuple2;

  auto tuple_interlaced = tupleutils::tuple_interlace(tuple1, tuple2);
  static_assert(
    std::is_same<decltype(tuple_interlaced), type_tuple12>::value,
    "unexpected interlaced tuple type");
}

void test_tuple_interlace() {
  using type_tuple_is = std::tuple<int, short>;
  using type_tuple_dc = std::tuple<double, char>;
  using type_tuple_idsc = std::tuple<int, double, short, char>;
  
  type_tuple_is tuple_is(1, 2);
  type_tuple_dc tuple_dc(3.0, '4');

  auto tuple_interlaced = tupleutils::tuple_interlace(tuple_is, tuple_dc);
  static_assert(
    std::is_same<decltype(tuple_interlaced), type_tuple_idsc>::value,
    "unexpected interlaced tuple type");

  assert(std::get<0>(tuple_interlaced) == 1);
  assert(std::get<1>(tuple_interlaced) == 3.0);
  assert(std::get<2>(tuple_interlaced) == 2);
  assert(std::get<3>(tuple_interlaced) == '4');
}

int main() {
  test_tuple_type_interlace_empty();
  test_tuple_type_interlace();
  test_tuple_interlace_empty();
  test_tuple_interlace();
 
  return EXIT_SUCCESS;
}
