#include "ball.h"

#include <OpenGL/gl.h>

#include <math.h>

void init_ball(Ball *ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 300;
    ball->speed_y = 300;
}

void update_ball(Ball *ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;

    float rotation_speed = ball->speed_x * 0.5f; 
    ball->angle += rotation_speed * time;


    if (ball->angle > 360) ball->angle -= 360;
    if (ball->angle < 0) ball->angle += 360;
}

void render_ball(Ball* ball) {
    glPushMatrix(); // Save the current coordinate system

    // 1. Move to the ball's position
    glTranslatef(ball->x, ball->y, 0);

    // 2. Rotate the coordinate system around the Z-axis
    glRotatef(ball->angle, 0, 0, 1);

    // 3. Draw the ball body (Circle)
    glBegin(GL_TRIANGLE_FAN);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(0, 0);
        for(int i = 0; i <= 20; i++) {
            float theta = 2.0f * 3.14159f * i / 20;
            glVertex2f(ball->radius * cos(theta), ball->radius * sin(theta));
        }
    glEnd();

    glBegin(GL_LINES);
        glColor3f(0.0f, 0.0f, 0.0f); 
        glVertex2f(0, 0);
        glVertex2f(ball->radius, 0); 
    glEnd();

    glPopMatrix(); 
}