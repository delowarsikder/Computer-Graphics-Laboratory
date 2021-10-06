#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

const int width = 640;
const int height = 480;
const int winPosX = 50;
const int winPosY = 50;

GLfloat eyeX = 2;
GLfloat eyeY = 5;
GLfloat eyeZ = -12;

GLfloat lookX = 2;
GLfloat lookY = 0;
GLfloat lookZ = 0;

GLfloat centerX = -0.5;
GLfloat centerY = -0.5;
GLfloat centerZ = -0.5;

GLfloat Near = 2.5;
GLfloat Far = 50.0;

float rotating = 0;
int rotating_angle_fan = 0;
bool rotate_fan = false;

float spot_cut_off = 50;

//variable for lighting

bool left_light_on = false;
bool right_light_on = false;
bool spot_light_on = true;

bool ambient_light_state = false;
bool specular_light_state = false;
bool diffuse_light_state = false;

GLfloat Xmin = -3, Xmax = 3, Ymin = -3, Ymax = 3;
//light color
const GLfloat ambient[] = {0.5, 0.5, 0.5, 1.0};
const GLfloat black[] = {0.0, 0.0, 0.0, 1.0};
const GLfloat white[] = {1.0, 1.0, 1.0, 1.0};
const GLfloat gray[] = {0.8, 0.8, 0.8, 1.0};
const GLfloat silver[] = {0.75, 0.75, 0.75, 1.0};
const GLfloat red[] = {1.0, 0.0, 0.0, 1.0};
const GLfloat lime[] = {0.0, 1.0, 0.0, 1.0};
const GLfloat green[] = {0.0, 0.8, 0.0, 1.0};
const GLfloat blue[] = {0.0, 0.0, 1.0, 1.0};
const GLfloat yellow[] = {1.0, 1.0, 0.0, 1.0};
const GLfloat maroon[] = {0.8, 0.0, 0.0, 1.0};
const GLfloat woodColor[] = {0.56, 0.3, 0.2, 1.0};

static GLfloat cube_vertices[8][3] =
{
    {0, 0, 0},
    {0, 0, 1},
    {0, 1, 0},
    {0, 1, 1},

    {1, 0, 0},
    {1, 0, 1},
    {1, 1, 0},
    {1, 1, 1}
};

static GLubyte cube_plane_indics[6][4] =
{
    //consider y axis upper
    {0, 2, 6, 4}, //back
    {1, 5, 7, 3}, //front
    {0, 4, 5, 1}, //bottom
    {2, 3, 7, 6}, //top
    {0, 1, 3, 2}, //left
    {4, 6, 7, 5}  //right
};

float aspect_ratio = float(width) / float(height);

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

static void getNormal3p(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2, GLfloat x3, GLfloat y3, GLfloat z3)
{
    GLfloat Ux, Uy, Uz, Vx, Vy, Vz, Nx, Ny, Nz;

    Ux = x2 - x1;
    Uy = y2 - y1;
    Uz = z2 - z1;

    Vx = x3 - x1;
    Vy = y3 - y1;
    Vz = z3 - z1;

    Nx = Uy * Vz - Uz * Vy;
    Ny = Uz * Vx - Ux * Vz;
    Nz = Ux * Vy - Uy * Vx;

    glNormal3f(Nx, Ny, Nz);
}

void cube(float red = 0.5, float green = 0.5, float blue = 0.5, float alpha = 1)
{
    GLfloat no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat mat_ambient[] = {red, green, blue, 1.0f};
    GLfloat mat_diffuse[] = {red, green, blue, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat high_shininess[] = {50.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(cube_vertices[cube_plane_indics[i][0]][0], cube_vertices[cube_plane_indics[i][0]][1], cube_vertices[cube_plane_indics[i][0]][2],
                    cube_vertices[cube_plane_indics[i][1]][0], cube_vertices[cube_plane_indics[i][1]][1], cube_vertices[cube_plane_indics[i][1]][2],
                    cube_vertices[cube_plane_indics[i][2]][0], cube_vertices[cube_plane_indics[i][2]][1], cube_vertices[cube_plane_indics[i][2]][2]);

        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(&cube_vertices[cube_plane_indics[i][j]][0]);
        }
    }
    glEnd();
}

void light()
{
    const GLfloat *no_light = black;
    //left
    const GLfloat *left_light_ambient = ambient;
    const GLfloat *left_light_diffuse = green;
    const GLfloat *left_light_specular = green;
    //right
    const GLfloat *right_light_ambient = ambient;
    const GLfloat *right_light_diffuse = red;
    const GLfloat *right_light_specular = red;
    //spot
    const GLfloat *spot_light_ambient = ambient;
    const GLfloat *spot_light_diffuse = maroon;
    const GLfloat *spot_light_specular = maroon;
    //light position
    const GLfloat left_light_position[] = {9, 7, 0.5, 1.0};       //light_left
    const GLfloat right_light_position[] = {-9, 6.5, 0.5, 1.0}; //light _right
    const GLfloat spot_light_position[] = {-2.5, 2.5, 6, 1};

    //if you want off all light just dark
    /*GLfloat globalAmbient[] ={0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient)*/

    glEnable(GL_LIGHTING);

    //left light
    glEnable(GL_LIGHT0);

    if (left_light_on)
    {
        glLightfv(GL_LIGHT0, GL_AMBIENT, left_light_ambient);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, left_light_diffuse);
        glLightfv(GL_LIGHT0, GL_SPECULAR, left_light_specular);
        glLightfv(GL_LIGHT0, GL_POSITION, left_light_position);
    }
    else
    {
        //ambient, diffuse,specular
        if (ambient_light_state)
        {
            glLightfv(GL_LIGHT0, GL_AMBIENT, left_light_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
            glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
        }
        else if (specular_light_state)
        {
            glLightfv(GL_LIGHT0, GL_SPECULAR, left_light_specular);
            glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
        }
        else if (diffuse_light_state)
        {
            glLightfv(GL_LIGHT0, GL_DIFFUSE, left_light_diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
            glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
        }
        else
        {
            glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
            glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
        }
    }

    //right_light
    glEnable(GL_LIGHT1);
    if (right_light_on)
    {

        glLightfv(GL_LIGHT1, GL_AMBIENT, right_light_ambient);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, right_light_diffuse);
        glLightfv(GL_LIGHT1, GL_SPECULAR, right_light_specular);
        glLightfv(GL_LIGHT1, GL_POSITION, right_light_position);
    }
    else
    {
        glLightfv(GL_LIGHT1, GL_AMBIENT, no_light);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, no_light);
        glLightfv(GL_LIGHT1, GL_SPECULAR, no_light);
    }

    //spot light
    glEnable(GL_LIGHT2);
    GLfloat spot_direction[] = {0, 1, 0, 1};
    if (spot_light_on)
    {
        glLightfv(GL_LIGHT2, GL_AMBIENT, spot_light_ambient);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, spot_light_diffuse);
        glLightfv(GL_LIGHT2, GL_SPECULAR, spot_light_specular);
        glLightfv(GL_LIGHT2, GL_POSITION, spot_light_position);

        glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction);
        glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, spot_cut_off);
    }
    else
    {
        glLightfv(GL_LIGHT2, GL_AMBIENT, no_light);
        glLightfv(GL_LIGHT2, GL_DIFFUSE, no_light);
        glLightfv(GL_LIGHT2, GL_SPECULAR, no_light);
    }
}

void axis()
{
    float length = 10;
    float width = 0.3;
    //x-axis
    glPushMatrix();
    glTranslated(length / 2, 0, 0);
    glScaled(length, width, width);
    glTranslated(centerX, centerY, centerZ);
    cube(1.0, 0.0, 0.0);
    glPopMatrix();

    //y-axis
    glPushMatrix();
    glTranslated(0, length / 2, 0);
    glScaled(width, length, width);
    glTranslated(centerX, centerY, centerZ);
    cube(0.0, 0.0, 1.0);
    glPopMatrix();

    //z-axis
    glPushMatrix();
    glTranslated(0, 0, length / 2);
    glScaled(width, width, length);
    glTranslated(centerX, centerY, centerZ);
    cube(0.0, 1.0, 0.0);
    glPopMatrix();
}

float flor_width = 20;
float flor_length = 20;
float flor_thick = 1;

///floor of class room

//line like as tiles

void wLines(float z = 0)
{
    glPushMatrix();
    glTranslated(0, 0, z);
    glScaled(flor_width - 0.5, 0.1, 0.1);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.6, 0.6, 0.6);
    glPopMatrix();
}

void hLines(float x = 0)
{
    glPushMatrix();
    glTranslated(x, 0, 0);
    glScaled(0.1, 0.1, flor_length);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.6, 0.6, 0.6);
    glPopMatrix();
}

void flor()
{
    float stage_length = 8;
    float stage_width = 6;
    float stage_height = 1;
    //floor
    glPushMatrix();
    glScaled(flor_width, flor_thick, flor_length);
    glTranslated(-0.5, -1.0, -0.5);
    cube(0.9, 0.9, 0.9);
    glPopMatrix();

    //stage of class room
    glPushMatrix();
    glTranslated(0, 0, flor_length / 3);
    glScaled(stage_length, stage_height, stage_width);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.7, 0.4, 0.2);
    glPopMatrix();

    //line
    //width
    for (int i = 0; i < 10; i += 2)
    {
        wLines(i);
    }
    for (int i = 0; i < 10; i += 2)
    {
        wLines(-i);
    }
    //height line
    for (int i = 2; i < 10; i += 2)
    {
        hLines(i);
    }
    for (int i = 2; i < 10; i += 2)
    {
        hLines(-i);
    }
}

float wall_height = 10;

void room()
{
    //left wall
    glPushMatrix();
    glTranslated(flor_width / 2, 0, 0);
    glScaled(0.5, -wall_height, flor_length);
    glTranslated(-0.5, -1.0, -0.5);
    cube(0.75, 0.75, 0.75);
    glPopMatrix();

    //right wall
    glPushMatrix();
    glTranslated(-flor_width / 2, 0, 0);
    glScaled(0.5, -wall_height, flor_length);
    glTranslated(-0.5, -1.0, -0.5);
    cube(0.9, 0.9, 0.9);
    glPopMatrix();

    //back wall
    glPushMatrix();
    glTranslated(0, 0, flor_length / 2);
    glScaled(flor_width, -wall_height, 0.5);
    glTranslated(-0.5, -1.0, -0.5);
    cube(0.7, 0.6, 0.7);
    glPopMatrix();

    //roof
    glPushMatrix();
    glTranslated(0, wall_height, 0);
    glScaled(flor_width, flor_thick, flor_length);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.4, 0.3, 0.2);
    glPopMatrix();
}

void black_board()
{
    float bb_width = 8;
    float bb_height = 3;
    float hgt_f_btm = 6;
    glPushMatrix();

    //front state
    glPushMatrix();
    glTranslated(0, hgt_f_btm, flor_length / 2 - flor_thick + 0.6);
    glScaled(bb_width, bb_height, 0);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0, 0, 0);
    glPopMatrix();
    //back state

    glPushMatrix();
    glTranslated(0, hgt_f_btm, flor_length / 2 - flor_thick + 0.7);
    glScaled(bb_width + 1, bb_height + 1, 0);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.3, 0.5, 0.2);
    glPopMatrix();

    glPopMatrix();
}

void almira()
{
    glPushMatrix();
    glTranslated(-flor_width / 2 - flor_thick + 2, 3, 5);

    //box
    glPushMatrix();
    glScaled(1, 6, 2);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.4, 0.0, 0.7);
    glPopMatrix();

    //handler1
    glPushMatrix();
    glTranslated(0.5, 2, 0.5);
    glScaled(0.1, 0.4, 0.2);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.8, 1.0, 1.0);
    glPopMatrix();

    //divider
    glPushMatrix();
    glTranslated(0.5, 0, 0);
    glScaled(0.1, 6, 0.1);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.5, 1.0, 1.0);
    glPopMatrix();

    //handler2
    glPushMatrix();
    glTranslated(0.5, 2, -0.5);
    glScaled(0.1, 0.4, 0.2);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.8, 1.0, 1.0);
    glPopMatrix();

    glPopMatrix();
}

void chair()
{
    float leg_length = 1;
    float leg_width = 0.25;

    glPushMatrix();
    glTranslated(0, 0, -1);
    //base
    glPushMatrix();
    glTranslated(0, leg_length, 0);
    glScaled(2, 0.25, 1.5);
    glTranslated(centerX, centerY, centerZ);
    cube(0.7, 0.6, 0.4);
    glPopMatrix();

    //leg1 -- front left
    glPushMatrix();
    glTranslated(0.80, 0, 0.5);
    glScaled(leg_width, leg_length, leg_width);
    glTranslated(centerX, 0.0, centerZ);
    cube(0.9, 0.5, 0.0);
    glPopMatrix();

    //leg2 --front right
    glPushMatrix();
    glTranslated(-0.80, 0, 0.5);
    glScaled(leg_width, leg_length, leg_width);
    glTranslated(centerX, 0.0, centerZ);
    cube(0.9, 0.5, 0.0);
    glPopMatrix();

    //leg3 back right
    glPushMatrix();
    glTranslated(-0.75, 0, -0.75);
    glScaled(leg_width, leg_length * 3, leg_width);
    glTranslated(centerX, 0.0, centerZ);
    cube(0.9, 0.5, 0.0);
    glPopMatrix();

    //leg4 back left
    glPushMatrix();
    glTranslated(0.75, 0, -0.75);
    glScaled(leg_width, leg_length * 3, leg_width);
    glTranslated(centerX, 0.0, centerZ);
    cube(0.9, 0.5, 0.0);
    glPopMatrix();

    //back_------
    glPushMatrix();
    glTranslated(0, 1.4, -0.8);
    glScaled(1.7, 0.2, 0.2);
    glTranslated(centerX, centerY, centerZ);
    cube(0.5, 0.9, 0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 1.8, -0.8);
    glScaled(1.7, 0.2, 0.2);
    glTranslated(centerX, centerY, centerZ);
    cube(0.5, 0.9, 0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 2.2, -0.8);
    glScaled(1.7, 0.2, 0.2);
    glTranslated(centerX, centerY, centerZ);
    cube(0.5, 0.9, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0, 2.6, -0.8);
    glScaled(1.7, 0.2, 0.2);
    glTranslated(centerX, centerY, centerZ);
    cube(0.5, 0.9, 0.7);
    glPopMatrix();

    //side cover
    glPushMatrix();
    glTranslated(0.8, 0.5, 0);
    glScaled(0.2, 0.15, 1.2);
    glTranslated(centerX, centerY, centerZ);
    cube(0.5, 0.9, 0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.8, 0.5, 0);
    glScaled(0.2, 0.15, 1.2);
    glTranslated(centerX, centerY, centerZ);
    cube(0.5, 0.9, 0.7);
    glPopMatrix();

    glPopMatrix();
}

void window()
{
    float bb_width = 2;
    float bb_height = 3;
    float hgt_f_btm = 4;

    glPushMatrix();
    glTranslated(flor_width / 2 - 0.25, hgt_f_btm, 0);
    glPushMatrix();
    glScaled(0.1, bb_height, bb_width);
    glTranslated(-0.5, -0.5, -0.5);
    cube(1.0, 1.0, 1.0);
    glPopMatrix();

    //divider1
    glPushMatrix();
    glScaled(0.2, bb_height, 0.1);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.5, 0.3, 0.7);
    glPopMatrix();

    //divider2
    glPushMatrix();
    glTranslated(0, 0, 0.4);
    glScaled(0.2, bb_height, -0.1);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.5, 0.3, 0.7);
    glPopMatrix();

    //divider3
    glPushMatrix();
    glTranslated(0, 0, -0.4);
    glScaled(0.2, bb_height, -0.1);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.5, 0.3, 0.7);
    glPopMatrix();

    //divider4
    glPushMatrix();
    glTranslated(0, 0, -0.8);
    glScaled(0.2, bb_height, -0.1);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.5, 0.3, 0.7);
    glPopMatrix();

    //divider5
    glPushMatrix();
    glTranslated(0, 0, 0.8);
    glScaled(0.2, bb_height, -0.1);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.5, 0.3, 0.7);
    glPopMatrix();

    glPopMatrix();
}

void table(GLfloat x = 0.0, GLfloat y = 0.0, GLfloat z = 0.0)
{
    float leg_length = 2;
    float leg_width = 0.25;
    float tab_len = 4;
    float tab_width = 2;
    float tab_thick = 0.25;
    float leg_pos_x = (tab_len - (leg_length + leg_width));

    glPushMatrix();
    glTranslated(x, y, z); //control position of both chair_table

    //base
    glPushMatrix();
    glTranslated(0, leg_length, 0);
    glScaled(4, 0.25, 2);
    glTranslated(centerX, centerY, centerZ);
    cube(0.8, 0.5, 0.2);
    glPopMatrix();

    //leg1  -- front left
    glPushMatrix();
    glTranslated(1.8, 0, 0.8);
    glScaled(leg_width, leg_length, leg_width);
    glTranslated(centerX, 0.0, centerZ);
    cube(0.7, 0.3, 0.1);
    glPopMatrix();

    //leg2 --front right
    glPushMatrix();
    glTranslated(-1.8, 0, 0.8);
    glScaled(leg_width, leg_length, leg_width);
    glTranslated(centerX, 0.0, centerZ);
    cube(0.7, 0.3, 0.1);
    glPopMatrix();

    //leg3 -- back right
    glPushMatrix();
    glTranslated(-1.8, 0, -0.8);
    glScaled(leg_width, leg_length, leg_width);
    glTranslated(centerX, 0.0, centerZ);
    cube(0.7, 0.3, 0.1);
    glPopMatrix();

    //leg4 --back left
    glPushMatrix();
    glTranslated(1.8, 0, -0.8);
    glScaled(leg_width, leg_length, leg_width);
    glTranslated(centerX, 0.0, centerZ);
    cube(0.7, 0.3, 0.1);
    glPopMatrix();

    chair();
    glPopMatrix();
}

void fanWheel(float cx, float cy, float cz, float r, int num_segments)
{

    GLfloat no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat mat_ambient[] = {0.7, 0.7, 0.5, 1.0f};
    GLfloat mat_diffuse[] = {0.7, 0.7, 0.5, 1.0f};
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0f};
    GLfloat high_shininess[] = {50.0f};

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glBegin(GL_POLYGON);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments); //get the current angle
        float x = r * cosf(theta);                                         //calculate the x component
        float y = r * sinf(theta);                                         //calculate the y component
        glVertex3f(x + cx, y + cy, cz);                                    //output vertex
    }
    glEnd();
}

void fan(float x = 0, float y = 0, float z = 0)
{
    glPushMatrix();
    glTranslated(x, y, z);

    //handle of fan
    glPushMatrix();
    glTranslated(0, 1.45, 0);
    glScaled(0.25, 2, 0.25);
    glTranslated(centerX, centerY, centerZ);
    cube(0.40, 0.30, 0.0);
    glPopMatrix();

    //fan wing 1
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glTranslated(1.75, 0.45, 0);
    glScaled(2.75, 0, .5);
    glTranslated(centerX, centerY, centerZ);
    cube(0.8, 0.8, 0.8);
    glPopMatrix();

    //fan wing 2
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glRotated(120, 0, 1, 0);
    glTranslated(1.75, 0.45, 0);
    glScaled(2.75, 0, .5);
    glTranslated(centerX, centerY, centerZ);
    cube(0.8, 0.8, 0.8);
    glPopMatrix();

    //fan wing 3
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glRotated(240, 0, 1, 0);
    glTranslated(1.75, 0.45, 0);
    glScaled(2.75, 0, .5);
    glTranslated(centerX, centerY, centerZ);
    cube(0.8, 0.8, 0.8);
    glPopMatrix();

    //circle of fan
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glTranslated(0.5, -0.1, -1.5);
    glRotated(90, 1, 0, 0);
    glTranslated(centerX, centerX, centerZ);
    fanWheel(0.0, 2.0, 0.0, 1.25, 10000);
    glPopMatrix();

    glPopMatrix();
}

void tubeLight()
{
    //light_right
    glPushMatrix();
    glTranslated(-flor_width / 2, 8, 2);
    glScaled(0.2, 0.4, 2);
    glTranslated(-0.5, -0.5, -0.5);
    cube(1.0, 0.0, 0.0);

    glPopMatrix();

    //light_left
    glPushMatrix();
    glTranslated(flor_width / 2, 8, 1);
    glScaled(0.2, 0.4, 2);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.0, 1.0, 0.0);
    glPopMatrix();
}

float clock_rotate = 0;
//show clock
void watch()
{
    //clock
    glPushMatrix();
    glTranslated(-6, 6, flor_length / 2 - 0.5);

    glPushMatrix();
    glTranslated(0, 2, 0);
    glScaled(1.5, 1.5, 0.1);
    glTranslated(-0.5, -0.5, -0.5);
    cube(1.0, 1.0, 1.0);
    glPopMatrix();

    //hours
    glPushMatrix();
    glTranslated(-0.3, 2, -0.2);
    glScaled(-0.7, 0.1, 0.1);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.0, 0.0, 0.0);
    glPopMatrix();

    //minutes
    glPushMatrix();
    glTranslated(0, 2.4, -0.2);
    glScaled(0.07, 0.75, 0.1);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.0, 0.0, 0.0);
    glPopMatrix();

    //second
    glPushMatrix();
    //    glRotated(clock_rotate,0,0,1);
    glTranslated(0.35, 1.9, -0.5);
    glScaled(0.8, 0.07, 0.09);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.0, 0.0, 0.0);
    glPopMatrix();

    glPopMatrix();
}

///teacher desk
void table_side_cover(GLfloat x = 0.0, GLfloat y = 0.0, GLfloat z = 0.0)
{
    glPushMatrix();
    glTranslated(x, 1.75, 0);
    glScaled(0.4, -5, 3);
    glTranslated(centerX, centerY, centerZ);
    cube(0.7, 0.7, 0.5);
    glPopMatrix();
}

void warDrobe()
{
    table_side_cover(2.0, 0.0, 0.0);  //right from teacher
    table_side_cover(0.25, 0.0, 0.0); //middle
    table_side_cover(-2.0, 0.0, 0.0); //left from teacher

    //upper base
    glPushMatrix();
    glTranslated(0, 4, 0);
    glScaled(4.5, 0.3, 3);
    glTranslated(centerX, centerY, centerZ);
    cube(0.9, 0.8, 0.5);
    glPopMatrix();

    //single stair
    glPushMatrix();
    glTranslated(1, 3, 0);
    glScaled(2, 0.3, 3);
    glTranslated(centerX, centerY, centerZ);
    cube(0.7, 0.7, 0.5);
    glPopMatrix();

    //double upper stair
    glPushMatrix();
    glTranslated(-0.8, 2, 0);
    glScaled(2.4, 0.3, 3);
    glTranslated(centerX, centerY, centerZ);
    cube(0.7, 0.7, 0.5);
    glPopMatrix();

    //double bottom stair
    glPushMatrix();
    glTranslated(-0.8, 1, 0);
    glScaled(2.4, 0.3, 3);
    glTranslated(centerX, centerY, centerZ);
    cube(0.7, 0.7, 0.5);
    glPopMatrix();

    //back cover

    glPushMatrix();
    glTranslated(1, 2.75, 1.5);
    glScaled(2.1, 1.75, 0.3);
    glTranslated(centerX, centerY, centerZ);
    cube(0.8, 0.8, 0.5);
    glPopMatrix();
}

void teacher_desk()
{
    glPushMatrix();
    glTranslated(7, 0, 7);
    glRotated(-180, 0, 1, 0);
    warDrobe();
    glPopMatrix();
}

void classRoomInstrument()
{
    room();
    flor();
    black_board();
    almira();
    window();
    tubeLight();
    watch();
    teacher_desk();

    GLfloat x = 6, z = 1.5;

    //middle row table
    table(0, 0, z);
    table(0, 0, -1.2 * z);
    table(0, 0, -3.2 * z);
    table(0, 0, -5.2 * z);

    //left row table
    table(x, 0, 1.5);
    table(x, 0, -1.75);
    table(x, 0, -4.75);
    table(x, 0, -7.75);

    //right row table
    table(-x, 0, 1.5);
    table(-x, 0, -1.75);
    table(-x, 0, -4.75);
    table(-x, 0, -7.75);

    //fan
    //first column
    fan(0, 7.5, 1);
    fan(6, 7.5, 1);
    fan(-6, 7.5, 1);

    //second column
    fan(0, 7.5, -5);
    fan(6, 7.5, -5);
    fan(-6, 7.5, -5);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glFrustum(Xmin, Xmax, Ymin, Ymax, Near, Far);
    //gluPerspective(60,1,5,100);
    //glOrtho(-5,5,-5,5, 4, 50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);

    glRotatef(rotating, 0, 1, 0);

    // axis();
    // flor();
    // watch();
    classRoomInstrument();
    // tubeLight();
    light();

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
    case 'q':
        exit(0);
        break;

    case 'r':
        rotating++;
        break;
    case 'l':
        rotating--;
        break;
    case 'x':
        eyeX += 0.5;
        lookX += 0.5;
        break;
    case 'k':
        eyeX -= 0.5;
        lookX -= 0.5;
    case 'y':
        eyeY += 0.3;
        break;
    case 'z':
        eyeY -= 0.3;
        break;
    case '+':
        eyeZ += 0.3;
        break;
    case '-':
        eyeZ -= 0.3;
        break;
    case 'f':
        rotate_fan = !rotate_fan;
        break;

    case '0':
        left_light_on = !left_light_on;
        ambient_light_state = false;
        specular_light_state = false;
        diffuse_light_state = false;
        break;
    case '1':
        right_light_on = !right_light_on;
        break;
    case '2':
        spot_light_on = !spot_light_on;
        break;
    case 'p':
        spot_cut_off = spot_cut_off + 10;
        break;
    case 'n':
        spot_cut_off = spot_cut_off - 10;
        break;
    case 'a':
        ambient_light_state = !ambient_light_state;
        break;
    case 's':
        specular_light_state = !specular_light_state;
        break;
    case 'd':
        diffuse_light_state = !diffuse_light_state;
        break;

    case 'm':
        const int width = 640;
        const int height = 480;
        const int winPosX = 50;
        const int winPosY = 50;

        eyeX = 2;
        eyeY = 5;
        eyeZ = -12;

        lookX = 2;
        lookY = 0;
        lookZ = 0;

        centerX = -0.5;
        centerY = -0.5;
        centerZ = -0.5;

        Near = 2.5;
        Far = 50.0;

        rotating = 0;
        rotating_angle_fan = 0;
        rotate_fan = false;

        spot_cut_off = 50;

        left_light_on = true;
        right_light_on = true;
        break;
    }

    glutPostRedisplay();
}

void instruction()
{
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "$$$$$$$$$$$$$  Please Follow this Instruction $$$$$$$$$$$$$$" << endl;
    cout << "$$$$$$$$$$$$$$$    To Control the ClassRoom    $$$$$$$$$$" << endl;
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "Press 'Esc' or 'q' to terminate the project" << endl;
    cout << "\nPress 'r' to rotate right <--<-- " << endl;
    cout << "Press 'l' to rotate left  <--<-- " << endl;
    cout << "Press 'x' to increase lookX  <--<--" << endl;
    cout << "Press 'k' to decrease lookX  <--<--" << endl;
    cout << "Press 'y' to top from Y axis   <--<--" << endl;
    cout << "Press 'z' to bottom form Y axis <--<--" << endl;
    cout << "Press 'm' to reset Eye Position <--<--" << endl;
    cout << "Press 'f' to switch on & off fan: Like Toggle <--<--" << endl;
    cout << "Press '+' to Zoom in <--<--" << endl;
    cout << "Press '-' to Zoom out <--<--  " << endl;
    cout << "Press '0' to switch on & off  left Light: Like Toggle" << endl;
    cout << "Press '1' to switch on & off  right Light: Like Toggle" << endl;
    cout << "Press 'p' to increase the brightness of spot light" << endl;
    cout << "Press 'n' to decrease the brightness of spot light" << endl;

    cout << "Press 'a' to toggle the ambient light" << endl;
    cout << "Press 's' to toggle the specular light" << endl;
    cout << "Press 'd' to toggle the diffuse light" << endl;
    cout << "\n\nN.B : if you want to set ambient, specular, and diffuse effect please turn off light pressing the '1' key(toggle) " << endl;
    cout << "Light on off switch can eliminate the ambient, specular, and diffuse effect state" << endl;
    cout << "*ambient, specular, and diffuse effect work only left light" << endl;
}

void animate()
{
    if (rotate_fan)
    {
        rotating_angle_fan = rotating_angle_fan + 4;
    }
    clock_rotate = clock_rotate + 0.01;
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(winPosX, winPosY);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("1607094_lighting_classroom");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(animate);
    //    glutIdleFunc(idle);

    // glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);

    //lighting
    //all property define in lighting function

    instruction(); //here describe all control instruction
    glutMainLoop();

    return EXIT_SUCCESS;
}
