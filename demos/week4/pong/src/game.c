#include "game.h"
#include <OpenGL/gl.h>
#include <stdio.h>

void draw_texture(GLuint texture_id, float x, float y, float w, float h);

void load_score_textures(Game* game) {
    char filename[32];
    for (int i = 0; i < 10; i++) {
        sprintf(filename, "assets/num_%d.png", i);
        
        SDL_Surface* surface = IMG_Load(filename);
        if (!surface) {
            printf("[ERROR] Failed to load %s\n", filename);
            continue;
        }

        glGenTextures(1, &game->score_textures[i]);
        glBindTexture(GL_TEXTURE_2D, game->score_textures[i]);
        
        // Setup scaling filters (NEAREST for pixel art, LINEAR for smooth)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, surface->w, surface->h, 0, 
                     GL_RGBA, GL_UNSIGNED_BYTE, surface->pixels);
        
        SDL_FreeSurface(surface);
        printf("[SUCCESS] Loaded texture for digit %d (ID: %u)\n", i, game->score_textures[i]);
    }
}

void draw_texture(GLuint texture_id, float x, float y, float w, float h) {
    glEnable(GL_TEXTURE_2D); // CRITICAL: Turn texturing back ON
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f); // Reset color to full white/opaque
    
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 1.0f); glVertex2f(x, y + h); // Bottom Left
        glTexCoord2f(1.0f, 1.0f); glVertex2f(x + w, y + h); // Bottom Right
        glTexCoord2f(1.0f, 0.0f); glVertex2f(x + w, y); // Top Right
        glTexCoord2f(0.0f, 0.0f); glVertex2f(x, y); // Top Left
    glEnd();
    
    glDisable(GL_TEXTURE_2D); // Turn it off so it doesn't mess up other draws
}

void init_game(Game* game, int width, int height)
{
    game->is_running = false;
    game->width = width;
    game->height = height;
    if (init_sdl(game) == false) return;

    init_opengl(game);
    load_score_textures(game); // <--- DONT MISS THIS!
    
    init_pong(&(game->pong), width, height);
    game->last_update_time = (double)SDL_GetTicks() / 1000.0;
    game->is_running = true;
}

void destroy_game(Game* game)
{
    if (game->gl_context != NULL) {
        SDL_GL_DeleteContext(game->gl_context);
    }

    if (game->window != NULL) {
        SDL_DestroyWindow(game->window);
    }

    SDL_Quit();
}

void handle_game_events(Game* game)
{
    SDL_Event event;
    static bool is_mouse_down = false;
    static int mouse_x = 0;
    static int mouse_y = 0;
    int x;
    int y;

    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_ESCAPE:
                game->is_running = false;
                break;
            case SDL_SCANCODE_W:
                set_left_pad_speed(&(game->pong), -400);
                break;
            case SDL_SCANCODE_S:
                set_left_pad_speed(&(game->pong), +400);
                break;
            default:
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.scancode) {
            case SDL_SCANCODE_W:
            case SDL_SCANCODE_S:
                set_left_pad_speed(&(game->pong), 0);
                break;
            case SDL_SCANCODE_D:
                if (game->pong.ball.radius < 100) 
                    game->pong.ball.radius += 10;
                break;
            case SDL_SCANCODE_A:
                if (game->pong.ball.radius > 20) {
                    game->pong.ball.radius -= 10;
                }
                break;
            default:
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            SDL_GetMouseState(&x, &y);
            set_right_pad_position(&(game->pong), y);
            break;
        
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT) {
                // Teleport the ball to the click position
                game->pong.ball.x = event.button.x;
                game->pong.ball.y = event.button.y;

                //Reset speed or give it a fresh start
                game->pong.ball.speed_x = 300; 
                game->pong.ball.speed_y = 300;
            }
            break;
        case SDL_QUIT:
            game->is_running = false;
            break;
        default:
            break;
        }
    }
}

void update_game(Game* game)
{
    double current_time;
    double elapsed_time;

    current_time = (double)SDL_GetTicks() / 1000;
    elapsed_time = current_time - game->last_update_time;
    game->last_update_time = current_time;

    update_pong(&(game->pong), elapsed_time);
}

void render_game(Game* game) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    render_pong(&(game->pong));

    int left_score = game->left_score; 
    int right_score = game->right_score;

    float score_y = 30.0f;
    float score_w = 40.0f; 
    float score_h = 60.0f;
    float left_x = (game->width / 2) - 100;
    float right_x = (game->width / 2) + 60;

    glDisable(GL_TEXTURE_2D);
    glColor3f(1.0f, 1.0f, 1.0f);
    
    // Left Box
    glBegin(GL_QUADS);
        glVertex2f(left_x - 5, score_y - 5);
        glVertex2f(left_x + score_w + 5, score_y - 5);
        glVertex2f(left_x + score_w + 5, score_y + score_h + 5);
        glVertex2f(left_x - 5, score_y + score_h + 5);
    glEnd();

    // Right Box
    glBegin(GL_QUADS);
        glVertex2f(right_x - 5, score_y - 5);
        glVertex2f(right_x + score_w + 5, score_y - 5);
        glVertex2f(right_x + score_w + 5, score_y + score_h + 5);
        glVertex2f(right_x - 5, score_y + score_h + 5);
    glEnd();

    // 4. Draw the actual number textures
    draw_texture(game->score_textures[left_score % 10], left_x, score_y, score_w, score_h);
    draw_texture(game->score_textures[right_score % 10], right_x, score_y, score_w, score_h);

    SDL_GL_SwapWindow(game->window);
}

bool init_sdl(Game* game)
{
    int error_code;

    error_code = SDL_Init(SDL_INIT_EVERYTHING);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return false;
    }

    game->window = SDL_CreateWindow(
        "Pong!",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        game->width, game->height,
        SDL_WINDOW_OPENGL);
    if (game->window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
        return false;
    }

    game->gl_context = SDL_GL_CreateContext(game->window);
    if (game->gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
        return false;
    }

    return true;
}

void init_opengl(Game* game) {
    glShadeModel(GL_SMOOTH);
    glClearColor(0.1, 0.1, 0.1, 1.0);

    // Add these two lines for transparency support!
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, game->width, game->height, 0, -200, 200);
    glViewport(0, 0, game->width, game->height);
}
