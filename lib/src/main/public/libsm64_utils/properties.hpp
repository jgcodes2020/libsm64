#ifndef __LIBSM64_PROPERTIES_HPP
#define __LIBSM64_PROPERTIES_HPP

#include <functional>

namespace libsm64 {
  using std::function;

  /**
   * @brief A simple computed property that provides syntactic sugar over setters/getters.
   * @tparam T the type of this property
   */
  template <typename T>
  class property {
  private:
    function<T()>& m_getter;
    function<void(T)>& m_setter;
  public:
    /**
     * @brief Creates a new property.
     * 
     * @param getter a function which gets the value of the property
     * @param setter a function which sets the value of the property
     */
    property(function<T()> getter, function<void(T)> setter) :
      m_getter(getter), m_setter(setter) {}

    void operator=(const T& value) { m_setter(value); }
    operator T() { return m_getter(); }
  };
}
#endif