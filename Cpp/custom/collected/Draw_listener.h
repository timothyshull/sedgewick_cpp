#ifndef DRAW_LISTENER_H
#define DRAW_LISTENER_H

class Draw_listener {
public:
    virtual ~Draw_listener() = 0;

    virtual void mouse_pressed(double x, double y) = 0;

    virtual void mouse_dragged(double x, double y) = 0;

    virtual void mouse_released(double x, double y) = 0;

    virtual void key_typed(char c) = 0;

    virtual void key_pressed(int keycode) = 0;

    virtual void key_released(int keycode) = 0;
};

#endif // DRAW_LISTENER_H
