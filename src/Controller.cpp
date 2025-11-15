#include "Controller.h"

namespace sn
{
Controller::Controller()
  : m_keyStates(0)
  , m_keyBindings(TotalButtons)
{
}

void Controller::setKeyBindings(const std::vector<sf::Keyboard::Key>& keys)
{
    m_keyBindings = keys;
}

void Controller::setButton(Buttons b, bool pressed)
{
    m_buttonStates[b] = pressed;
}

void Controller::strobe(Byte b)
{
    m_strobe = (b & 1);
    if (!m_strobe)
    {
        m_keyStates = 0;
        int shift   = 0;
        for (int button = A; button < TotalButtons; ++button)
        {
            bool keyPressed    = sf::Keyboard::isKeyPressed(m_keyBindings[button]);
            bool padPressed    = m_buttonStates[button];
            bool finalPressed  = keyPressed || padPressed;
            m_keyStates       |= (finalPressed << shift);
            ++shift;
        }
    }
}

Byte Controller::read()
{
    Byte ret;
    if (m_strobe)
    {
        // return only A button continuously
        bool keyA = sf::Keyboard::isKeyPressed(m_keyBindings[A]);
        bool padA = m_buttonStates[A];
        ret       = (keyA || padA);
    }
    else
    {
        ret           = (m_keyStates & 1);
        m_keyStates >>= 1;
    }
    return ret | 0x40;
}

}