#include "pad.h"

#include <OpenGL/gl.h>
#include "ball.h"

void init_pad(Pad* pad, float x, float table_height, enum ColorTheme color_theme)
{
    pad->x = x;
    pad->y = 0;
    pad->width = 50;
    pad->height = 120;
    pad->limit = table_height - pad->height;
    pad->speed = 0;
    pad->color_theme = color_theme;
}

void set_pad_position(Pad* pad, float position)
{
    if (position < 0.0) {
        pad->y = 0.0;
    } else if (position > pad->limit) {
        pad->y = pad->limit;
    } else {
        pad->y = position;
    }
}

void set_pad_speed(Pad* pad, float speed)
{
    pad->speed = speed;
}

void update_pad(Pad* pad, double time)
{
    float new_position;

    new_position = pad->y + pad->speed * time;
    set_pad_position(pad, new_position);
}

void render_pad(Pad* pad)
{
    float x1, x2, y1, y2;

    x1 = pad->x;
    x2 = x1 + pad->width;
    y1 = pad->y;
    y2 = y1 + pad->height;

    glBegin(GL_QUADS);
    if (pad->color_theme == RED_THEME) {
        glColor3f(1.0, 0.0, 0.0);
        glVertex2f(x1, y1);
        glColor3f(0.8, 0.2, 0.0);
        glVertex2f(x2, y1);
        glColor3f(1.0, 0.4, 0.0);
        glVertex2f(x2, y2);
        glColor3f(0.9, 0.3, 0.0);
        glVertex2f(x1, y2);
    } else if (pad->color_theme == GREEN_THEME) {
        glColor3f(0.0, 0.1, 0.0);
        glVertex2f(x1, y1);
        glColor3f(0.0, 0.8, 0.2);
        glVertex2f(x2, y1);
        glColor3f(0.0, 1.0, 0.4);
        glVertex2f(x2, y2);
        glColor3f(0.0, 0.9, 0.2);
        glVertex2f(x1, y2);
    }
    glEnd();
}
void check_pad_collision(Pad* pad, Ball* ball) {
    if (ball->x + ball->radius > pad->x && ball->x - ball->radius < pad->x + pad->width &&
        ball->y + ball->radius > pad->y && ball->y - ball->radius < pad->y + pad->height) 
    {
        float overlap_left   = (ball->x + ball->radius) - pad->x;
        float overlap_right  = (pad->x + pad->width) - (ball->x - ball->radius);
        float overlap_top    = (ball->y + ball->radius) - pad->y;
        float overlap_bottom = (pad->y + pad->height) - (ball->y - ball->radius);

        
        float min_overlap = overlap_left;
        int side = 0;

        if (overlap_right < min_overlap) { min_overlap = overlap_right; side = 1; }
        if (overlap_top < min_overlap)   { min_overlap = overlap_top;   side = 2; }
        if (overlap_bottom < min_overlap){ min_overlap = overlap_bottom; side = 3; }

        float paddle_center_y = pad->y + (pad->height / 2.0f);
        float d_y = ball->y - paddle_center_y; 
        float normalized_d_y = d_y / (pad->height / 2.0f);

        switch(side) {
            case 0: 
            case 1:
                ball->speed_x *= -1.05f; 
                ball->speed_y = normalized_d_y * 400.0f; 
                
                if (side == 0) ball->x = pad->x - ball->radius;
                else           ball->x = pad->x + pad->width + ball->radius;
                break;

            case 2:
            case 3: 
                ball->speed_y *= -1.0f;
                if (side == 2) ball->y = pad->y - ball->radius;
                else           ball->y = pad->y + pad->height + ball->radius;
                break;
            }
                
                ball->speed_x *= 1.05f; 
            }
}