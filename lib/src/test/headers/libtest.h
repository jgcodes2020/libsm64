#ifndef LIBTEST_H
#define LIBTEST_H

#include <sstream>
#include <string>
#include <vector>
#include <stdexcept>

using std::cout, std::endl, std::vector, std::string, std::ostringstream;
using std::logic_error;

#define LIBTEST_ASSERT(cond) \
if (!(cond)) {\
  std::ostringstream oss; \
  oss << "Error occurred in " << __FILE__ << " (line " << __LINE__ << "):\n"; \
  oss << "Assertion (" << #cond << ") failed.\n"; \
  std::cerr << oss.str(); \
  throw libtest::assertion_error(oss.str()); \
} ((void) 0)

/**
 * LIBTEST - Just a really simple header-only testing framework.
 */
namespace libtest {
  /**
   * @brief A function that performs a test. Is essentially a function taking void and returning void
   */
  typedef void (*test_function)(void);

  /**
   * @brief Thrown to indicate a failed assertion.
   */
  class assertion_error : public logic_error {
    using logic_error::logic_error;
  };

  /**
   * @brief Represents a single test.
   * 
   */
  class test {
    friend class test_suite;
  private:
    static size_t s_id_generator;
    test_function m_fn;
    string m_name;
  public:
    test(string name, test_function fn) :
      m_fn(fn), m_name(name) {
    }
    test(test_function fn) :
      m_fn(fn) {
      ostringstream fmt;
      fmt << "Untitled test " << s_id_generator++;
      m_name = fmt.str();
    }

    void operator()() {
      m_fn();
    }
  };
  class test_suite {
  private:
    vector<test> m_tests;
  public:
    test_suite() {
      m_tests.reserve(10);
    }
    test_suite(std::initializer_list<test> tests) {
      m_tests.reserve(tests.size());
      m_tests.insert(m_tests.end(), tests.begin(), tests.end());
    }
    void test_all() {
      for (auto& unit: m_tests) {
        unit();
      }
    }
  };
}

#endif