#include "scene.h"
#include <OpenGL/gl.h>
#include "math.h"

#define SPHERE_RADIUS 0.15f
#define SPHERE_SLICES 16
#define SPHERE_STACKS 16 
#define SPHERE_CENTER_X 0.25f
#define SPHERE_CENTER_Y 0.25f
#define SPHERE_CENTER_Z 0.25f

void init_scene(Scene* scene)
{
}

void update_scene(Scene* scene)
{
}

void render_scene(const Scene* scene)
{
    glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 1.0f, 0.0f);
        glVertex3f(0.2f, 0.2f, 0.5f);

        
        glColor3f(0.0f, 1.0f, 1.0f);
        glVertex3f(0.8f, 0.2f, 0.5f);

        
        glColor3f(1.0f, 0.0f, 1.0f);
        glVertex3f(0.5f, 0.8f, 0.5f);
    glEnd();

    draw_origin();

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glColor3f(0.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);

    for (int i = 0; i < SPHERE_STACKS; ++i) {
        float phi1 = M_PI * (float)i / (float)SPHERE_STACKS;
        float phi2 = M_PI * (float)(i + 1) / (float)SPHERE_STACKS;

        for (int j = 0; j < SPHERE_SLICES; ++j) {
            float theta1 = 2.0f * M_PI * (float)j / (float)SPHERE_SLICES;
            float theta2 = 2.0f * M_PI * (float)(j + 1) / (float)SPHERE_SLICES;

            float x1 = SPHERE_CENTER_X + SPHERE_RADIUS * sinf(phi1) * cosf(theta1);
            float y1 = SPHERE_CENTER_Y + SPHERE_RADIUS * sinf(phi1) * sinf(theta1);
            float z1 = SPHERE_CENTER_Z + SPHERE_RADIUS * cosf(phi1);

            float x2 = SPHERE_CENTER_X + SPHERE_RADIUS * sinf(phi1) * cosf(theta2);
            float y2 = SPHERE_CENTER_Y + SPHERE_RADIUS * sinf(phi1) * sinf(theta2);
            float z2 = SPHERE_CENTER_Z + SPHERE_RADIUS * cosf(phi1);

            float x3 = SPHERE_CENTER_X + SPHERE_RADIUS * sinf(phi2) * cosf(theta2);
            float y3 = SPHERE_CENTER_Y + SPHERE_RADIUS * sinf(phi2) * sinf(theta2);
            float z3 = SPHERE_CENTER_Z + SPHERE_RADIUS * cosf(phi2);

            float x4 = SPHERE_CENTER_X + SPHERE_RADIUS * sinf(phi2) * cosf(theta1);
            float y4 = SPHERE_CENTER_Y + SPHERE_RADIUS * sinf(phi2) * sinf(theta1);
            float z4 = SPHERE_CENTER_Z + SPHERE_RADIUS * cosf(phi2);

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
            glVertex3f(x3, y3, z3);

            glVertex3f(x1, y1, z1);
            glVertex3f(x3, y3, z3);
            glVertex3f(x4, y4, z4);
        }
    }
    glEnd();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}
