#pragma once
#include <cstddef>
#include <memory>
#include <stdexcept>
#include <vector>

template <typename T> class CustomAllocator {
public:
  using value_type = T;
  using pointer = T *;
  using const_pointer = const T *;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;
  using difference_type = std::ptrdiff_t;

  CustomAllocator(std::size_t initialPoolSize = 100)
      : poolSize(initialPoolSize), allocated(0) {
    pool.reserve(initialPoolSize);
    for (size_type i = 0; i < initialPoolSize; ++i) {
      pool.push_back(new char[sizeof(T)]);
    }
  }

  template <typename U>
  CustomAllocator(const CustomAllocator<U> &other)
      : poolSize(other.poolSize), allocated(other.allocated) {
    pool.reserve(poolSize);
    for (size_type i = 0; i < allocated; ++i) {
      pool.push_back(new char[sizeof(T)]);
    }
  }

  ~CustomAllocator() {
    for (auto ptr : pool) {
      delete[] ptr;
    }
  }

  T *allocate(std::size_t n) {
    if (n > poolSize - allocated) {
      size_type newPoolSize = poolSize * 2; // Double the pool size
      while (n > newPoolSize - allocated) {
        newPoolSize *= 2; // Keep doubling until enough space is available
      }
      for (size_type i = poolSize; i < newPoolSize; ++i) {
        pool.push_back(new char[sizeof(T)]);
      }
      poolSize = newPoolSize;
    }
    T *ptr = reinterpret_cast<T *>(pool[allocated]);
    allocated += n;
    return ptr;
  }

  void deallocate(T *ptr, std::size_t n) noexcept {
    // Deallocation is a no-op in this allocator
  }

  template <typename U, typename... Args>
  void construct(U *ptr, Args &&...args) {
    new (ptr) U(std::forward<Args>(args)...);
  }

  template <typename U> void destroy(U *ptr) noexcept { ptr->~U(); }

  size_type max_size() const noexcept { return size_type(-1) / sizeof(T); }

  pointer address(reference x) const noexcept { return std::addressof(x); }

  const_pointer address(const_reference x) const noexcept {
    return std::addressof(x);
  }

  template <class U> struct rebind {
    typedef CustomAllocator<U> other;
  };

  size_type poolSize;
  std::vector<void *> pool;
  size_type allocated;
};

template <typename T, typename U>
bool operator==(const CustomAllocator<T> &p1,
                const CustomAllocator<U> &p2) noexcept {
  return p1.pool == p2.pool;
}

template <typename T, typename U>
bool operator!=(const CustomAllocator<T> &p1,
                const CustomAllocator<U> &p2) noexcept {
  return p1.pool == p2.pool; // Always return false since it's stateless
}
