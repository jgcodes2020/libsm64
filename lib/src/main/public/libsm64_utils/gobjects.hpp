#include "libsm64_utils/sm64.hpp"
#include "libsm64_utils/properties.hpp"

#ifndef __LIBSM64_GOBJECTS_HPP
#define __LIBSM64_GOBJECTS_HPP

#include <cstdint>

namespace libsm64 {
  class mario {
  private:
    sm64& m_game;
    float* m_x_ptr, * m_y_ptr, * m_z_ptr;
  public:
    mario(sm64& game) :
      m_game(game) {
      m_x_ptr = this->m_game.locate<float>("gMarioStates", 60);
      m_y_ptr = this->m_game.locate<float>("gMarioStates", 64);
      m_z_ptr = this->m_game.locate<float>("gMarioStates", 68);
    };

    /**
     * @brief Property to physical Mario's X position.
     */
    property<float> x = property<float>(
      [this]() {
        return *(this->m_x_ptr);
      },
      [this](float n) {
        return *(this->m_x_ptr) = n;
      });

    /**
     * @brief Property to physical Mario's Y position.
     */
    property<float> y = property<float>(
      [this]() {
        return *(this->m_y_ptr);
      },
      [this](float n) {
        return *(this->m_y_ptr) = n;
      });

    /**
     * @brief Property to physical Mario's Z position.
     */
    property<float> z = property<float>(
      [this]() {
        return *(this->m_z_ptr);
      },
      [this](float n) {
        return *(this->m_z_ptr) = n;
      });

  };
}
#endif