#ifndef __LIBSM64_PROPERTIES_HPP
#define __LIBSM64_PROPERTIES_HPP

#include <functional>

namespace libsm64 {
  using std::function;

  /**
   * @brief A simple computed property that provides syntactic sugar over setters/getters.
   * @tparam T the type of this property
   */
  template <class T>
  class property {
  private:
    function<T()> m_getter;
    function<T&(T)> m_setter;
  public:
    /**
     * @brief Construct a new property object
     * 
     * @tparam GET A type assignable to `std::function<T()>`.
     * @tparam SET A type assignable to `std::function<T&(T)>`.
     * @param getter A function which gets this property.
     * @param setter A function which sets this property.
     */
    template<typename GET, typename SET>
    property(GET& getter, SET& setter) {
      m_getter = getter;
      m_setter = setter;
    }

    //Properties are non-copiable and non-movable
    property(const property&) = delete;
    property(property&&) = delete;

    /**
     * @brief Gets this property.
     * 
     * @return the value of this property
     */
    operator T() const {
      return m_getter();
    }
    /**
     * @brief Sets this property, as if by the standard assignment operator.
     * 
     * @param value the value to assign
     * @return the new value of this property, for chaining
     */
    T& operator=(const T& value){
      return m_setter(value);
    }
    
    /**
     * @brief Gets this property.
     * 
     * @return the value of this property
     */
    T get() {
      return m_getter();
    }
    /**
     * @brief Sets this property.
     * 
     * @param value the value to assign
     */
    void set(T& value) {
      m_setter(value);
    }
  };
}
#endif