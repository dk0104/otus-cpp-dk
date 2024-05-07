#pragma once
#include <iostream>
#include <list>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>

namespace HA4 {

// tuple wrapper and helper

/*
 *@brief Wrapper for tuple handling
 *@tparam T - tuple
 *@tparam I - index
 *@tparam M - Max Index
 */

template <typename T, unsigned I, unsigned M> struct TuplePrinter {

  /*
   *@brief print recursive all tuple elements until the last one
   *@param[in] t - tuple
   *@param[in] out - output stream
   */

  inline static void print(const T &t, std::ostream &out) {
    const auto &next = std::get<I + 1>(t);
    const auto &current = std::get<I>(t);
    static_assert(std::is_same<decltype(next), decltype(current)>::value,
                  "Types in tuple must be the same");
    out << std::get<I>(t) << ".";
    TuplePrinter<T, I + 1, M>::print(t, out);
  }
};

/*
 *@brief Wrapper for tuple handling
 *@tparam T - tuple
 *@tparam N - last index
 */

template <typename T, unsigned N> struct TuplePrinter<T, N, N> {
  static void print(const T &t, std::ostream &out) {
    out << std::get<N>(t) << std::endl;
  }
};

/*
 *@brief is_iterable test for iterable types
 */
template <typename T, typename U = void>
struct is_iterable : std::false_type {};

/*
 *@breif is_itarable test for iterable types
 */
template <typename T>
struct is_iterable<T, std::void_t<decltype(std::begin(std::declval<T>())),
                                  decltype(std::end(std::declval<T>()))>>
    : std::true_type {};

/*
 *@brief Test for iterable types
 */
template <typename T>
inline constexpr bool is_iterable_v = is_iterable<T>::value;

/*
 *@ Trait for r value tuple
 */
template <typename T> struct is_tuple : std::false_type {};

/*
 *@ Trait for r value tuple
 */
template <typename... Args>
struct is_tuple<std::tuple<Args...>> : std::true_type {};

/*
 *@brief print_ip - print ip integer value
 *@param[in] integerIp - integer value
 *@param[in] out - output stream
 */

template <typename T, std::enable_if_t<std::is_integral<T>::value, bool> = true>
void print_ip(T integerIp, std::ostream &out = std::cout) {
  const std::size_t cnt = sizeof(T);
  union {
    unsigned char block[cnt];
    T val;
  };
  val = integerIp;

  for (std::size_t i = cnt - 1; i > 0; --i) {
    out << static_cast<int>(block[i]) << ".";
  }
  out << static_cast<int>(block[0]) << std::endl;
}

template <typename Container>
    typename std::enable_if <
    std::is_same<
        Container,
        std::vector<typename Container::value_type> ||
            std::is_same<Container, std::list<typename Container::value_type>>
                Container::value>::type
    print_ip(const Container &cont, std::ostream &out = std::cout) {
  auto begin_it = cont.cbegin();
  auto end_it = cont.cend();
  for (auto it = begin_it; it != end_it; ++it) {
    if (it != begin_it) {
      out << ".";
    }
    out << *it;
  }
}

// template <typename Container>
// typename std::enable_if<std::is_same<
//     Container, std::list<typename Container::value_type>>::value>::type
// print_ip(const Container &cont, std::ostream &out = std::cout) {
//   auto begin_it = cont.cbegin();
//   auto end_it = cont.cend();
//   for (auto it = begin_it; it != end_it; ++it) {
//     if (it != begin_it) {
//       out << ".";
//     }
//     out << *it;
//   }
// }

/*
 *@brief print_ip - print for tuple
 *@param[in] str - string value
 *@param[in] out - output stream
 */
template <typename T,
          std::enable_if_t<std::is_same<T, std::string>::value, bool> = true>
void print_ip(T &str, std::ostream &out = std::cout) {
  out << str << std::endl;
}

/*
 *@brief print_wrapper
 *@param[in] t = tupple template
 *@param[in] cout = output stream
 */
template <typename... Args>
void print_wrapper(std::tuple<Args...> const &t,
                   std::ostream &out = std::cout) {
  TuplePrinter<std::tuple<Args...>, 0, sizeof...(Args) - 1>::print(t, out);
}

/*
 *@brief print_ip using print wrapper
 */

template <typename T, std::enable_if_t<is_tuple<T>::value, bool> = true>
void print_ip(T const &t, std::ostream &out = std::cout) {
  print_wrapper(t, out);
}

} // namespace HA4
