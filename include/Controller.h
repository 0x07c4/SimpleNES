#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <SFML/Window.hpp>
#include <cstdint>
#include <vector>

namespace sn
{
using Byte = std::uint8_t;
class Controller
{
public:
    Controller();
    enum Buttons
    {
        A,
        B,
        Select,
        Start,
        Up,
        Down,
        Left,
        Right,
        TotalButtons,
    };

    void strobe(Byte b);
    Byte read();
    void setKeyBindings(const std::vector<sf::Keyboard::Key>& keys);

    // joystick button/axis mapping
    void setButton(Buttons b, bool pressed);

private:
    bool         m_strobe = false;
    unsigned int m_keyStates = 0;

    std::vector<sf::Keyboard::Key> m_keyBindings;
    // runtime-stored button states for joystick
    bool m_buttonStates[TotalButtons] = {false};
};
}

#endif // CONTROLLER_H
