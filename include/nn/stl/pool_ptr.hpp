#pragma once

namespace nn {
template<typename T, typename Pool>
class pool_ptr {
private:
  Pool* m_pool{nullptr};
  T* m_obj{nullptr};

public:
  pool_ptr(Pool* p)
      : m_pool{p}
      , m_obj{m_pool->acquire()} {
  }

  pool_ptr(pool_ptr&& other)
      : m_pool{other.m_pool}
      , m_obj{other.m_obj} {
    other.m_pool = nullptr;
    other.m_obj = nullptr;
  }

  ~pool_ptr() {
    if (m_obj && m_pool) {
      m_pool->release(m_obj);
    }
  }

  T& operator*() {
    return *m_obj;
  }

  const T& operator*() const {
    return *m_obj;
  }

  T* operator->() {
    return m_obj;
  }

  const T* operator->() const {
    return m_obj;
  }
};
} // namespace nn