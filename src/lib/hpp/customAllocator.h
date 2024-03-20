#pragma once
#include <cstddef>
#include <limits>
#include <memory>

// teplate<typename T> class CustomAllocator {
// public:
//   using value_type = T;
//   CustomAllocator() = default;

//   template <typename U> CustomAllocator(const CustomAllocator<U> &) noexcept
//   {}

//   T *allocate(std::size_t n) {
//     if (n > max_sizes())
//       throw std::bad_alloc();
//     return static_cast<T *>(::operator new(n * sizeof(T)));
//   }
//   void deallocate(T *p, std::size_t) noexcept { ::operator delete(p); }

//   teplate<typename... args> void construct(T *p, args &&...args) {
//     new (p) T(std::forward<args>(args)...);
//   }
//   void destroy(T *p) { p->~T(); }

//   std::size_t max_size() const noexcept {
//     return std::numeric_limits<std::size_t>::max() / sizeof(T);
//   }
// };

// template <typename T, typename U>
// bool operator==(const CustomAllocator<T> &,
//                 const CustomAllocator<U> &) noexcept {
//   return true;
// }

// template <typename T, typename U>
// bool operator!=(const CustomAllocator<T> &,
//                 const CustomAllocator<U> &) noexcept {
//   return false;
// }
