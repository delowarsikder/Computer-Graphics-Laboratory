#include <windows.h>
#include <GL/glut.h>
#include <bits/stdc++.h>
using namespace std;

const int width = 640;
const int height = 480;

GLfloat eyeX = 2;
GLfloat eyeY = 5;
GLfloat eyeZ = -12;

GLfloat lookX = 2;
GLfloat lookY = 0;
GLfloat lookZ = 0;

GLfloat centerX = -0.5;
GLfloat centerY = -0.5;
GLfloat centerZ = -0.5;

GLfloat Near = 2.0;
GLfloat Far = 50.0;

float rotating = 0;
int rotating_angle_fan = 0;
bool rotate_fan = false;

GLfloat Xmin=-3,Xmax=3,Ymin=-3,Ymax=3;

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

static GLubyte cube_plane[6][4] =
{
    {0, 2, 6, 4},
    {1, 5, 7, 3},
    {0, 4, 5, 1},
    {2, 3, 7, 6},
    {0, 1, 3, 2},
    {4, 6, 7, 5}
};

float aspect_ratio=float(width)/float(height);

static void resize(int width, int height)
{
    glViewport(0, 0, width, height);
}

void cube(float colR = 0.5, float colG = 0.5, float colB = 0.5, float alpha = 1)
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        glColor4f(colR, colG, colB, alpha);

        for (GLint j = 0; j < 4; j++)
        {
            glVertex3fv(&cube_vertices[cube_plane[i][j]][0]);
        }
    }
    glEnd();
}

void axis()
{
    float length = 10;
    float width = 0.3;
    //x-axis
    glPushMatrix();
    glTranslated(length/2,0,0);
    glScaled(length, width, width);
    glTranslated(centerX,centerY,centerZ);
    cube(1.0, 0.0, 0.0);
    glPopMatrix();

    //y-axis
    glPushMatrix();
    glTranslated(0,length/2,0);
    glScaled(width, length, width);
    glTranslated(centerX,centerY,centerZ);
    cube(1.0, 1.0, 0.0);
    glPopMatrix();

    //z-axis
    glPushMatrix();
    glTranslated(0,0,length/2);
    glScaled(width, width, length);
    glTranslated(centerX,centerY,centerZ);
    cube(0.0, 1.0, 0.0);
    glPopMatrix();
}

float flor_width = 20;
float flor_length = 20;
float flor_thick = 1;
///floor of class room
void tiles(float x = 0, float y = 0, float z = 0)
{
    //top
    glPushMatrix();
    glTranslated(x, y, z);
    glPushMatrix();
    glTranslated(0, 0.1, 0);
    glScaled(2.5, -0.2, 2.5);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.9, 0.9, 0.9);
    glPopMatrix();

    //back
    glPushMatrix();
    glTranslated(0, 0.1, 0);
    glScaled(3.1, 0.2, 3.1);
    glTranslated(-0.5, -1.0, -0.5);
    cube(0.6, 0.6, 0.6);
    glPopMatrix();

    glPopMatrix();
}

//line like as tiles

void wLines(float z = 0)
{
    glPushMatrix();
    glTranslated(0, 0, z);
    glScaled(flor_width, 0.1, 0.1);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.6, 0.6, 0.6);
    glPopMatrix();
}

void hLines(float x = 0)
{
    glPushMatrix();
    glTranslated(x, 0, 0);
    glScaled(0.1, 0.1, flor_length+0.5);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.6, 0.6, 0.6);
    glPopMatrix();
}

void flor()
{
    float stage_length=8;
    float stage_width=6;
    float stage_height=1;
    //floor
    glPushMatrix();
    glScaled(flor_width, flor_thick, flor_length);
    glTranslated(-0.5, -1.0, -0.5);
    cube(0.9, 0.9, 0.9);
    glPopMatrix();

    //stage of class room
    glPushMatrix();
    glTranslated(0, 0, flor_length / 2 - 2);
    glScaled(stage_length, stage_height, stage_width);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.7, 0.4, 0.2);
    glPopMatrix();

    //tiles
    //    tiles(flor_width/2-1.5,0,flor_length/2-1.5);
    //    tiles(flor_width/2-1.5,0,flor_length/2-1.5-3);

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
    cube(0.7, 0.6, 0.7);
    glPopMatrix();

    //right wall
    glPushMatrix();
    glTranslated(-flor_width / 2, 0, 0);
    glScaled(0.5, -wall_height, flor_length);
    glTranslated(-0.5, -1.0, -0.5);
    cube(0.7, 0.6, 0.7);
    glPopMatrix();

    //back wall
    glPushMatrix();
    glTranslated(0, 0, flor_length / 2);
    glScaled(flor_width, -wall_height, 0.5);
    glTranslated(-0.5, -1.0, -0.5);
    cube(0.7, 0.6, 0.8);
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
    cube(0.3, 0, 0.2);
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
    glBegin(GL_POLYGON);
    glColor4f(0.3, 0.6, 0.3, 1);
    //    glRotated(90,1,0,0);
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
    cube(0.4, 0.1, 0.0);
    glPopMatrix();

    //fan wing 1
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glTranslated(1.75, 0.45, 0);
    glScaled(2.75, 0, .5);
    glTranslated(centerX, centerY, centerZ);
    cube(0.5, 0.2, 0.0);
    glPopMatrix();

    //fan wing 2
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glRotated(120, 0, 1, 0);
    glTranslated(1.75, 0.45, 0);
    glScaled(2.75, 0, .5);
    glTranslated(centerX, centerY, centerZ);
    cube(0.5, 0.2, 0.0);
    glPopMatrix();

    //fan wing 3
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glRotated(240, 0, 1, 0);
    glTranslated(1.75, 0.45, 0);
    glScaled(2.75, 0, .5);
    glTranslated(centerX, centerY, centerZ);
    cube(0.5, 0.2, 0.0);
    glPopMatrix();

    //circle of fan
    glPushMatrix();
    glRotated(rotating_angle_fan, 0, 1, 0);
    glTranslated(0.5, -0.1, -1.5);
    glRotated(90, 1, 0, 0);
    glTranslated(centerX, centerX, centerZ);
    fanWheel(0.0, 2.0, 0.0, 1.5, 10000);
    glPopMatrix();

    glPopMatrix();
}

void airconditionar()
{
    //ac1
    glPushMatrix();
    glTranslated(-flor_width / 2 + 1, 8, 0);
    glScaled(0.75, 0.75, 2);
    glTranslated(-0.5, -0.5, -0.5);
    cube(.9, 1.0, 1.0);
    glPopMatrix();

    //ac2
    glPushMatrix();
    glTranslated(flor_width / 2 - 1, 8, -2);
    glScaled(0.75, 0.75, 2);
    glTranslated(-0.5, -0.5, -0.5);
    cube(1.0, 0.9, 1.0);
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
    glTranslated(0.35,1.9,-0.5);
    glScaled(0.8, 0.07, 0.09);
    glTranslated(-0.5, -0.5, -0.5);
    cube(0.0, 0.0, 0.0);
    glPopMatrix();

    glPopMatrix();
}
///teacher desk

void teacher_table(GLfloat x=0.0, GLfloat y=0.0, GLfloat z=0.0)
{
    glPushMatrix();
    glTranslated(x,1.75,0);
    glScaled(0.3,-5,3);
    glTranslated(centerX,centerY,centerZ);
    cube(0.8,0.7,0.5);
    glPopMatrix();
}

void baseOfTable(GLfloat x=0.0, GLfloat y=0.0, GLfloat z=0.0)
{
    glPushMatrix();
    glTranslated(0,5,0);
    glScaled(4.5,0.3,3);
    glTranslated(centerX,centerY,centerZ);
    cube(0.8,0.7,0.5);
    glPopMatrix();

}

void warDrobe()
{
    teacher_table(2.0,0.0,0.0);
    teacher_table(0.25,0.0,0.0);
    teacher_table(-2.0,0.0,0.0);
    //upper base
    glPushMatrix();
    glTranslated(0,4,0);
    glScaled(4.5,0.3,3);
    glTranslated(centerX,centerY,centerZ);
    cube(0.9,0.8,0.5);
    glPopMatrix();

    //bottom left
    glPushMatrix();
    glTranslated(1,3,0);
    glScaled(2,0.3,3);
    glTranslated(centerX,centerY,centerZ);
    cube(0.7,0.7,0.5);
    glPopMatrix();

    //bottom right
    glPushMatrix();
    glTranslated(-0.8,2,0);
    glScaled(2.4,0.3,3);
    glTranslated(centerX,centerY,centerZ);
    cube(0.7,0.7,0.5);
    glPopMatrix();
    //bottom right bottom
    glPushMatrix();
    glTranslated(-0.8,1,0);
    glScaled(2.4,0.3,3);
    glTranslated(centerX,centerY,centerZ);
    cube(0.7,0.7,0.5);
    glPopMatrix();

    //back cover

    glPushMatrix();
    glTranslated(1,2.75,1.5);
    glScaled(2.1,1.75,0.3);
    glTranslated(centerX,centerY,centerZ);
    cube(0.8,0.8,0.5);
    glPopMatrix();
}


void teacher_desk()
{
    glPushMatrix();
    glTranslated(7,0,7);
    glRotated(-180,0,1,0);
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
    airconditionar();
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

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, 0, 1, 0);

    glRotatef(rotating, 0, 1, 0);

//    axis();
//    flor();
    classRoomInstrument();
//    watch();
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
        lookX+=0.5;
        break;
    case 'k':
        lookX-=0.5;
    case 'y':
        eyeY+=0.3;
        break;
    case 'z':
        eyeY-=0.3;
        break;

    case 'm':
        eyeX = 2;
        eyeY = 5;
        eyeZ = -12;

        lookX = 2;
        lookY = 0;
        lookZ = 0;

        Near = 2.0;
        Far = 50.0;

        rotating = 0;
        rotating_angle_fan = 0;
        rotate_fan = false;
        break;

    case '+':
        Near += 0.3;
        break;
    case '-':
        Near -= 0.3;
        break;
    case 'f':
        rotate_fan = true;
        break;
    case 'o':
        rotate_fan = false;
        break;
    }

    glutPostRedisplay();
}

void instruction()
{
    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    cout << "$$$->-> "<< "press 'r' to rotate right <--<-- "<<"$$$$$$" << endl;
    cout << "$$$->-> "<< "press 'l' to rotate left  <--<-- " <<"$$$$$$" << endl;
    cout << "$$$->-> "<< "press 'x' to increase lookX  <--<--"<<  "$$$$$$"<< endl;
    cout << "$$$->-> "<< "press 'k' to decrease lookX  <--<--"<<"$$$$$$" << endl;
    cout << "$$$->-> "<< "press 'y' to top from Y axis   <--<--"<< "$$$$$$"<< endl;
    cout << "$$$->-> "<< "press 'z' to bottom form Y axis <--<--"<< "$$$$$$"<< endl;
    cout << "$$$->-> "<< "press 'm' to reset Eye Position <--<--"<< "$$$$$$"<< endl;
    cout << "$$$->-> "<< "press 'f' to switch on fan <--<--  "<<"$$$$$$" << endl;
    cout << "$$$->-> "<< "press 'o' to switch off fan <--<--  "<< "$$$$$$"<< endl;
    cout << "$$$->-> "<< "press '+' to Zoom in <--<--         "<<"$$$$$$" << endl;
    cout << "$$$->-> "<< "press '-' to Zoom off <--<--        "<<"$$$$$$" << endl;
    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"<<endl;
    cout<<"$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n\n"<<endl;
}

void animate()
{
    if (rotate_fan)
    {
        rotating_angle_fan = rotating_angle_fan+4;
    }
    clock_rotate=clock_rotate+0.01;
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
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("1607094_classroom");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(animate);
//    glutIdleFunc(idle);

//    glClearColor(1,1,1,1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);


    instruction(); //here describe all control instruction
    glutMainLoop();

    return EXIT_SUCCESS;
}
