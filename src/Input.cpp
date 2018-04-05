#include "Input.h"

Input::Input() : m_x(0), m_y(0), m_relX(0), m_relY(0), m_stop(false)
{
    for (int i = 0; i < SDL_NUM_SCANCODES; i ++)
    {
        m_keys[i] = false;
    }
    for (int i = 0; i < 8; i ++)
    {
        m_buttons[i] = false;
    }
}

void Input::update()
{
    m_relX = 0;
    m_relY = 0;

    while(SDL_PollEvent(&m_event))
    {
        switch(m_event.type)
        {
            case SDL_KEYDOWN:
                m_keys[m_event.key.keysym.scancode] = true;
            break;
            case SDL_KEYUP:
                m_keys[m_event.key.keysym.scancode] = false;
            break;
            case SDL_MOUSEBUTTONDOWN:
                m_buttons[m_event.button.button] = true;
            break;
            case SDL_MOUSEBUTTONUP:
                m_buttons[m_event.button.button] = false;
            break;
            case SDL_MOUSEMOTION:
                m_x = m_event.motion.x;
                m_y = m_event.motion.y;

                m_relX = m_event.motion.xrel;
                m_relY = m_event.motion.yrel;
            break;
            case SDL_WINDOWEVENT:
                if (m_event.window.event == SDL_WINDOWEVENT_CLOSE)
                {
                    m_stop = true;
                }
            break;
            default:
            break;
        }
    }
}

int Input::getMouseX() const
{
    return m_x;
}

int Input::getMouseY() const
{
    return m_y;
}

int Input::getMouseRelativeX() const
{
    return m_relX;
}

int Input::getMouseRelativeY() const
{
    return m_relY;
}

bool Input::getKeyPressed(const SDL_Scancode keyCode) const
{
    return m_keys[keyCode];
}

bool Input::getButtonPressed(const Uint8 buttonCode) const
{
    return m_buttons[buttonCode];
}

bool Input::getMouseMoved() const
{
    if (m_relX == 0 && m_relY == 0)
        return false;
    else
        return true;
}

void Input::showCursor(bool param) const
{
    if (param)
        SDL_ShowCursor(SDL_ENABLE);
    else
        SDL_ShowCursor(SDL_DISABLE);
}

void Input::setRelativeMode(bool param) const
{
    if (param)
        SDL_SetRelativeMouseMode(SDL_TRUE);
    else
        SDL_SetRelativeMouseMode(SDL_FALSE);
}

bool Input::getStop() const
{
    return m_stop;
}

Input::~Input()
{

}
