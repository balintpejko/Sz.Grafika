#include "pong.h"

void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width, height);
}

void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    bounce_ball(pong, &(pong->left_pad), &(pong->right_pad));
}

void render_pong(Pong* pong)
{
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
}

void set_left_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}

void set_left_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}

void set_right_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}

void set_right_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}

void bounce_ball(Pong* pong, Pad* left_pad, Pad* right_pad)
{
    // 1. Check if we hit the paddles (X-axis logic lives inside these)
    check_pad_collision(left_pad, &(pong->ball));
    check_pad_collision(right_pad, &(pong->ball));

    // 2. Wall Bounces (Top and Bottom only)
    // Top Wall
    if (pong->ball.y - pong->ball.radius < 0) {
        pong->ball.y = pong->ball.radius;
        pong->ball.speed_y *= -1;
    }
    // Bottom Wall
    if (pong->ball.y + pong->ball.radius > pong->height) {
        pong->ball.y = pong->height - pong->ball.radius;
        pong->ball.speed_y *= -1;
    }

    // 3. Scoring (If ball goes past the 50-pixel line and NO paddle hit it)
    if (pong->ball.x < 0) {
        init_ball(&(pong->ball), pong->width / 2, pong->height / 2);
    }
    if (pong->ball.x > pong->width) {
        init_ball(&(pong->ball), pong->width / 2, pong->height / 2);
    }
}
