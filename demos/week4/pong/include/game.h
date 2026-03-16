#ifndef GAME_H
#define GAME_H

#include "pong.h"
#include <SDL.h>
#include <OpenGL/gl.h>
#include <SDL_image.h>

/**
 * Game state representation
 */
typedef struct Game
{
    SDL_Window *window;
    SDL_GLContext gl_context;
    bool is_running;
    double last_update_time;
    int width;
    int left_score;
    int right_score;
    int height;
    Pong pong;
    GLuint score_textures[10];
} Game;

/**
 * Init the game.
 */
void init_game(Game *game, int width, int height);

/**
 * Free the allocated resources.
 */
void destroy_game(Game *game);

void draw_texture(GLuint texture_id, float x, float y, float w, float h);

void load_score_textures(Game *game);

/**
 * Handle the game events.
 */
void handle_game_events(Game *game);

void render_score(Game *game);

/**
 * Update the state of the game.
 */
void update_game(Game *game);

/**
 * Render the game.
 */
void render_game(Game *game);

/**
 * Initialize the SDL context.
 */
bool init_sdl(Game *game);

/**
 * Initialize the OpenGL.
 */
void init_opengl(Game *game);

#endif /* GAME_H */
