#include "libsm64_utils/sm64.hpp"
#include "libsm64_utils/properties.hpp"

#ifndef __LIBSM64_GOBJECTS_HPP
#define __LIBSM64_GOBJECTS_HPP

#include <cstdint>

namespace libsm64 {
  /**
   * @brief Represents physical Mario (aka the Mario struct).
   */
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

  /**
   * @brief Represents an object (one in an object slot).
   */
  class g_object {
  protected:
    sm64& m_game;
    uint8_t m_slot;
  public:
    g_object() = delete;

    g_object(const g_object&) = delete;

    g_object(g_object&&) = delete;

    g_object(sm64& game, uint8_t slot) :
      m_game(game), m_slot(slot) {
      base_ptr = game.locate<void>("gObjectPool", (slot * 1392L));
    }

    /**
     * Copy behaviour of this object to another object.
     * @param that another object.
     */
    void copy_bhv(g_object that) {
      uint8_t* const src_ptr = m_game.locate<uint8_t>("gObjectPool", (this->m_slot * 1392) + 160);
      uint8_t* const dst_ptr = m_game.locate<uint8_t>("gObjectPool", (that.m_slot * 1392) + 160);
      memmove(dst_ptr, src_ptr, 1232);
    }

    const void* base_ptr;
  };

  class bully : public g_object {
  private:
    float* m_x_ptr, * m_y_ptr, * m_z_ptr, * m_h_speed_ptr;
    uint16_t* m_yaw_1_ptr, * m_yaw_2_ptr;
  public:
    bully(sm64& game, uint8_t slot) :
      g_object(game, slot),
      m_x_ptr(m_game.locate<float>("gObjectPool", (slot * 1392L) + 240)),
      m_y_ptr(m_game.locate<float>("gObjectPool", (slot * 1392L) + 244)),
      m_z_ptr(m_game.locate<float>("gObjectPool", (slot * 1392L) + 248)),
      m_h_speed_ptr(m_game.locate<float>("gObjectPool", (slot * 1392L) + 264)),
      m_yaw_1_ptr(m_game.locate<uint16_t>("gObjectPool", (slot * 1392L) + 280)),
      m_yaw_2_ptr(m_game.locate<uint16_t>("gObjectPool", (slot * 1392L) + 292)) {

    }

    /**
     * @brief Property to the bully's X position.
     */
    property<float> x = property<float>(
      [this]() {
        return *(this->m_x_ptr);
      },
      [this](float n) {
        return *(this->m_x_ptr) = n;
      });

    /**
     * @brief Property to the bully's Y position.
     */
    property<float> y = property<float>(
      [this]() {
        return *(this->m_y_ptr);
      },
      [this](float n) {
        return *(this->m_y_ptr) = n;
      });

    /**
     * @brief Property to the bully's Z position.
     */
    property<float> z = property<float>(
      [this]() {
        return *(this->m_z_ptr);
      },
      [this](float n) {
        return *(this->m_z_ptr) = n;
      });

    /**
     * @brief Property to the bully's H speed.
     */
    property<float> h_speed = property<float>(
      [this]() {
        return *(this->m_h_speed_ptr);
      },
      [this](float n) {
        return *(this->m_h_speed_ptr) = n;
      });
    /**
     * @brief Property to the bully's 1st yaw value.
     */
    property<uint16_t> yaw_1 = property<uint16_t>(
      [this]() {
        return *(this->m_yaw_1_ptr);
      },
      [this](float n) {
        return *(this->m_yaw_1_ptr) = n;
      });

    /**
     * @brief Property to the bully's 2nd yaw value.
     */
    property<uint16_t> yaw_1 = property<uint16_t>(
      [this]() {
        return *(this->m_yaw_1_ptr);
      },
      [this](float n) {
        return *(this->m_yaw_1_ptr) = n;
      });
  };
}
#endif