#ifndef INPUT_H
#define INPUT_H

#include <SDL2/SDL.h>


class Input
{
    public:
        Input();
        int getMouseX() const;
        int getMouseY() const;
        int getMouseRelativeX() const;
        int getMouseRelativeY() const;
        bool getKeyPressed(const SDL_Scancode keyCode) const;
        bool getButtonPressed(const Uint8 ButtonCode) const;
        bool getMouseMoved() const;
        void showCursor(bool param) const;
        void setRelativeMode(bool param) const;
        bool getStop() const;
        void update();
        ~Input();
    private:
        SDL_Event m_event;
        bool m_keys[SDL_NUM_SCANCODES];
        bool m_buttons[8];
        int m_x, m_y;
        int m_relX, m_relY;
        bool m_stop;
};

#endif // INPUT_H
