#include<windows.h>
#include <GL/glut.h>
#include<bits/stdc++.h>
using namespace std;

const int width = 700;
const int height = 700;

GLfloat eyeX = 2;
GLfloat eyeY = 5;
GLfloat eyeZ = -12;

GLfloat lookX = 2;
GLfloat lookY = 0;
GLfloat lookZ = 0;

GLfloat centerX=-0.5;
GLfloat centerY=-0.5;
GLfloat centerZ=-0.5;


float rotating = 0;
int rotating_angle=0;

static GLfloat cube_vertices[8][3] =
{
    {0,0,0},
    {0,0,1},
    {0,1,0},
    {0,1,1},

    {1,0,0},
    {1,0,1},
    {1,1,0},
    {1,1,1}
};

static GLubyte cube_plane[6][4] =
{
    {0,2,6,4},
    {1,5,7,3},
    {0,4,5,1},
    {2,3,7,6},
    {0,1,3,2},
    {4,6,7,5}
};

void cube(float colR=0.5, float colG=0.5, float colB=0.5, float alpha=1)
{
    glBegin(GL_QUADS);
    for (GLint i = 0; i <6; i++)
    {
        glColor4f(colR,colG,colB,alpha);

        for (GLint j=0; j<4; j++)
        {
            glVertex3fv(&cube_vertices[cube_plane[i][j]][0]);
        }
    }
    glEnd();
}

void axis()
{
    float length=10;
    float width=0.2;
//x-axis
    glPushMatrix();
    glScaled(length,width,width);
    cube(1.0,0.0,0.0);
    glPopMatrix();

//y-axis
    glPushMatrix();
    glRotated(90,0,0,1);
    glScaled(length,width,width);
    cube(1.0,1.0,5.0);
    glPopMatrix();

//z-axis
    glPushMatrix();
    glRotated(90,0,1,0);
    glScaled(length,width,width);
    cube(0.0,1.0,0.0);
    glPopMatrix();
}

float flor_width=20;
float flor_length=20;
float flor_thick=1;
///floor of class room
void tiles(float x=0,float y=0,float z=0)
{
    //top
    glPushMatrix();
    glTranslated(x,y,z);
    glPushMatrix();
    glTranslated(0,0.1,0);
    glScaled(2.5,-0.2,2.5);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.9,0.9,0.9);
    glPopMatrix();

    //back
    glPushMatrix();
    glTranslated(0,0.1,0);
    glScaled(3.1,0.2,3.1);
    glTranslated(-0.5,-1.0,-0.5);
    cube(0.6,0.6,0.6);
    glPopMatrix();

    glPopMatrix();

}

//line like as tiles

void wLines(float z=0)
{
    glPushMatrix();
    glTranslated(0,0,z);
    glScaled(flor_width,0.1,0.1);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.6,0.6,0.6);
    glPopMatrix();

}

void hLines(float x=0)
{
    glPushMatrix();
    glTranslated(x,0,0);
    glScaled(0.1,0.1,flor_length);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.6,0.6,0.6);
    glPopMatrix();

}

void flor()
{
    //floor
    glPushMatrix();
    glScaled(flor_width,flor_thick,flor_length);
    glTranslated(-0.5,-1.0,-0.5);
    cube(0.9,0.9,0.9);
    glPopMatrix();

    //stage of class room
    glPushMatrix();
    glTranslated(0,0,flor_length/2-2);
    glScaled(7,-1.75,3.5);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.7,0.4,0.0);
    glPopMatrix();

    //tiles
//    tiles(flor_width/2-1.5,0,flor_length/2-1.5);
//    tiles(flor_width/2-1.5,0,flor_length/2-1.5-3);

    //line
    //width
    for(int i=0; i<10; i+=2)
    {
        wLines(i);
    }
    for(int i=0; i<10; i+=2)
    {
        wLines(-i);
    }
    //height line
    for(int i=2; i<10; i+=2)
    {
        hLines(i);
    }
    for(int i=2; i<10; i+=2)
    {
        hLines(-i);
    }

}

float wall_height=10;

void room()
{
//left wall
    glPushMatrix();
    glTranslated(flor_width/2,0,0);
    glScaled(0.5,-wall_height,flor_length);
    glTranslated(-0.5,-1.0,-0.5);
    cube(0.5,0.2,0.2);
    glPopMatrix();

//right wall
    glPushMatrix();
    glTranslated(-flor_width/2,0,0);
    glScaled(0.5,-wall_height,flor_length);
    glTranslated(-0.5,-1.0,-0.5);
    cube(0.5,0.2,0.2);
    glPopMatrix();

//back wall
    glPushMatrix();
    glTranslated(0,0,flor_length/2);
    glScaled(flor_width,-wall_height,0.5);
    glTranslated(-0.5,-1.0,-0.5);
    cube(0.6,0.8,0.9);
    glPopMatrix();

//roof
    glPushMatrix();
    glTranslated(0,wall_height,0);
    glScaled(flor_width,flor_thick,flor_length);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.4,0.3,0.2);
    glPopMatrix();
}

void black_board()
{
    float bb_width=8;
    float bb_height=3;
    float hgt_f_btm=6;
    glPushMatrix();
    glTranslated(0,hgt_f_btm,flor_length/2-flor_thick+0.65);

    glPushMatrix();
    glScaled(bb_width,bb_height,0);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0,0,0);
    glPopMatrix();

    glPushMatrix();
    glScaled(bb_width+1,bb_height+1,0);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.3,0,0.2);
    glPopMatrix();

    glPopMatrix();
}

void almira()
{
    glPushMatrix();
    glTranslated(-flor_width/2-flor_thick+2,2,5);

//box
    glPushMatrix();
    glScaled(1,8,2);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.4,0.0,0.7);
    glPopMatrix();

//handler1
    glPushMatrix();
    glTranslated(0.5,2,0.5);
    glScaled(0.1,0.4,0.2);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.8,1.0,1.0);
    glPopMatrix();

//divider
    glPushMatrix();
    glTranslated(0.5,0,0);
    glScaled(0.1,8,0.1);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.5,1.0,1.0);
    glPopMatrix();

//handler2
    glPushMatrix();
    glTranslated(0.5,2,-0.5);
    glScaled(0.1,0.4,0.2);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.8,1.0,1.0);
    glPopMatrix();

    glPopMatrix();
}

void chair()
{
    float leg_length=1;
    float leg_width=0.25;

    glPushMatrix();
    glTranslated(0,0,-1);
//base
    glPushMatrix();
    glTranslated(0,leg_length,0);
    glScaled(2,0.25,1.5);
    glTranslated(centerX,centerY,centerZ);
    cube(0.7,0.6,0.4);
    glPopMatrix();

//leg1 -- front left
    glPushMatrix();
    glTranslated(0.80,0,0.5);
    glScaled(leg_width,leg_length,leg_width);
    glTranslated(centerX,0.0,centerZ);
    cube(0.9,0.5,0.0);
    glPopMatrix();

//leg2 --front right
    glPushMatrix();
    glTranslated(-0.80,0,0.5);
    glScaled(leg_width,leg_length,leg_width);
    glTranslated(centerX,0.0,centerZ);
    cube(0.9,0.5,0.0);
    glPopMatrix();

//leg3 back right
    glPushMatrix();
    glTranslated(-0.75,0,-0.75);
    glScaled(leg_width,leg_length*3,leg_width);
    glTranslated(centerX,0.0,centerZ);
    cube(0.9,0.5,0.0);
    glPopMatrix();

//leg4 back left
    glPushMatrix();
    glTranslated(0.75,0,-0.75);
    glScaled(leg_width,leg_length*3,leg_width);
    glTranslated(centerX,0.0,centerZ);
    cube(0.9,0.5,0.0);
    glPopMatrix();

//back_------
    glPushMatrix();
    glTranslated(0,1.4,-0.8);
    glScaled(1.7,0.2,0.2);
    glTranslated(centerX,centerY,centerZ);
    cube(0.5,0.9,0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,1.8,-0.8);
    glScaled(1.7,0.2,0.2);
    glTranslated(centerX,centerY,centerZ);
    cube(0.5,0.9,0.6);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,2.2,-0.8);
    glScaled(1.7,0.2,0.2);
    glTranslated(centerX,centerY,centerZ);
    cube(0.5,0.9,0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslated(0,2.6,-0.8);
    glScaled(1.7,0.2,0.2);
    glTranslated(centerX,centerY,centerZ);
    cube(0.5,0.9,0.7);
    glPopMatrix();

//side cover
    glPushMatrix();
    glTranslated(0.8,0.5,0);
    glScaled(0.2,0.15,1.2);
    glTranslated(centerX,centerY,centerZ);
    cube(0.5,0.9,0.7);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-0.8,0.5,0);
    glScaled(0.2,0.15,1.2);
    glTranslated(centerX,centerY,centerZ);
    cube(0.5,0.9,0.7);
    glPopMatrix();

    glPopMatrix();
}

void window()
{
    float bb_width=2;
    float bb_height=3;
    float hgt_f_btm=4;

    glPushMatrix();
    glTranslated(flor_width/2-0.25,hgt_f_btm,0);
    glPushMatrix();
    glScaled(0.1,bb_height,bb_width);
    glTranslated(-0.5,-0.5,-0.5);
    cube(1.0,1.0,1.0);
    glPopMatrix();

//divider1
    glPushMatrix();
    glScaled(0.2,bb_height,0.1);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.5,0.3,0.7);
    glPopMatrix();

//divider2
    glPushMatrix();
    glTranslated(0,0,0.4);
    glScaled(0.2,bb_height,-0.1);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.5,0.3,0.7);
    glPopMatrix();

//divider3
    glPushMatrix();
    glTranslated(0,0,-0.4);
    glScaled(0.2,bb_height,-0.1);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.5,0.3,0.7);
    glPopMatrix();

//divider4
    glPushMatrix();
    glTranslated(0,0,-0.8);
    glScaled(0.2,bb_height,-0.1);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.5,0.3,0.7);
    glPopMatrix();

//divider5
    glPushMatrix();
    glTranslated(0,0,0.8);
    glScaled(0.2,bb_height,-0.1);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.5,0.3,0.7);
    glPopMatrix();

    glPopMatrix();
}

void table(GLfloat x=0.0, GLfloat y=0.0, GLfloat z=0.0)
{
    float leg_length=2;
    float leg_width=0.25;
    float tab_len=4;
    float tab_width=2;
    float tab_thick=0.25;
    float leg_pos_x=(tab_len-(leg_length+leg_width));

    glPushMatrix();
    glTranslated(x,y,z); //control position of both chair_table

    //base
    glPushMatrix();
    glTranslated(0,leg_length,0);
    glScaled(4,0.25,2);
    glTranslated(centerX,centerY,centerZ);
    cube(0.8,0.5,0.2);
    glPopMatrix();

    //leg1  -- front left
    glPushMatrix();
    glTranslated(1.8,0,0.8);
    glScaled(leg_width,leg_length,leg_width);
    glTranslated(centerX,0.0,centerZ);
    cube(0.7,0.3,0.1);
    glPopMatrix();

    //leg2 --front right
    glPushMatrix();
    glTranslated(-1.8,0,0.8);
    glScaled(leg_width,leg_length,leg_width);
    glTranslated(centerX,0.0,centerZ);
    cube(0.7,0.3,0.1);
    glPopMatrix();

    //leg3 -- back right
    glPushMatrix();
    glTranslated(-1.8,0,-0.8);
    glScaled(leg_width,leg_length,leg_width);
    glTranslated(centerX,0.0,centerZ);
    cube(0.7,0.3,0.1);
    glPopMatrix();

    //leg4 --back left
    glPushMatrix();
    glTranslated(1.8,0,-0.8);
    glScaled(leg_width,leg_length,leg_width);
    glTranslated(centerX,0.0,centerZ);
    cube(0.7,0.3,0.1);
    glPopMatrix();

    chair();
    glPopMatrix();
}


void fanWheel(float cx, float cy, float cz, float r, int num_segments)
{
    glBegin(GL_POLYGON);
    glColor4f(0.6,0.5,0.7,1);
//    glRotated(90,1,0,0);
    for (int ii = 0; ii < num_segments; ii++)
    {
        float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle
        float x = r * cosf(theta);//calculate the x component
        float y = r * sinf(theta);//calculate the y component
        glVertex3f(x + cx, y + cy, cz);//output vertex
    }
    glEnd();
}


void fan(float x =0,float y=0,float z=0)
{
    glPushMatrix();
//    glRotated(rotating_angle,0,1,0);
    glTranslated(x,y,z);

    //handle of fan
    glPushMatrix();
    glTranslated(0,1.4,0);
    glScaled(0.25,2,0.25);
    glTranslated(centerX,centerY,centerZ);
    cube(0.4,0.1,0.0);
    glPopMatrix();

    //fan wing 1
    glPushMatrix();
    glRotated(rotating_angle,0,1,0);
    glTranslated(1.75,0.4,0);
    glScaled(3,0,.5);
    glTranslated(centerX,centerY,centerZ);
    cube(0.5,0.2,0.0);
    glPopMatrix();

    //fan wing 2
    glPushMatrix();
    glRotated(rotating_angle,0,1,0);
    glRotated(120,0,1,0);
    glTranslated(1.75,0.4,0);
    glScaled(3,0,.5);
    glTranslated(centerX,centerY,centerZ);
    cube(0.5,0.2,0.0);
    glPopMatrix();

    //fan wing 3
    glPushMatrix();
    glRotated(rotating_angle,0,1,0);
    glRotated(240,0,1,0);
    glTranslated(1.75,0.4,0);
    glScaled(3,0,.5);
    glTranslated(centerX,centerY,centerZ);
    cube(0.5,0.2,0.0);
    glPopMatrix();

    //circle of fan
    glPushMatrix();
    glRotated(rotating_angle,0,1,0);
    glTranslated(0.5,-0.1,-1.5);
    glRotated(90,1,0,0);
    glTranslated(centerX,centerX,centerZ);
    fanWheel(0.0, 2.0, 0.0, 1.5, 10000);
    glPopMatrix();

    glPopMatrix();
}

void airconditionar()
{
//ac1
    glPushMatrix();
    glTranslated(-flor_width/2+1,8,0);
    glScaled(0.75,0.75,2);
    glTranslated(-0.5,-0.5,-0.5);
    cube(.9,1.0,1.0);
    glPopMatrix();

//ac2
    glPushMatrix();
    glTranslated(flor_width/2-1,8,-2);
    glScaled(0.75,0.75,2);
    glTranslated(-0.5,-0.5,-0.5);
    cube(1.0,0.9,1.0);
    glPopMatrix();
}

float clock_rotate=0;
//show clock
void watch()
{
//clock
    glPushMatrix();
    glTranslated(-6,6,flor_length/2-0.5);

    glPushMatrix();
    glTranslated(0,2,0);
    glScaled(1.5,1.5,0.1);
    glTranslated(-0.5,-0.5,-0.5);
    cube(1.0,1.0,1.0);
    glPopMatrix();

//hours
    glPushMatrix();
    glTranslated(-0.4,2,-.2);
    glScaled(-0.75,0.1,0.1);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.0,0.0,0.0);
    glPopMatrix();

//minutes
    glPushMatrix();
//    glRotated(clock_rotate,0,0,1);
    glTranslated(0,2.4,-.2);
    glScaled(0.1,0.75,0.1);
    glTranslated(-0.5,-0.5,-0.5);
    cube(0.0,0.0,0.0);
    glPopMatrix();

    glPopMatrix();
}

void classRoomInstrument()
{
    room();
    black_board();
    almira();
    window();
    airconditionar();
    watch();

    GLfloat x=6,z=1.5;
//middle row table
    table(0,0,z);
    table(0,0,-1.2*z);
    table(0,0,-3.2*z);

//left row table
    table(x,0,1.5);
    table(x,0,-1.75);
    table(x,0,-4.75);

//right row table
    table(-x,0,1.5);
    table(-x,0,-1.75);
    table(-x,0,-4.75);

//fan

//first row
    fan(0,7.5,0);
    fan(6,7.5,0);
    fan(-6,7.5,0);

//second row
    fan(0,7.5,-4);
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-3, 3, -3, 3, 2.0, 50.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(eyeX,eyeY,eyeZ, lookX,lookY,lookZ, 0,1,0);
    glViewport(0, 0, width, height);

    glRotatef(rotating, 0,1,0);

//    axis();
    flor();
    classRoomInstrument();
    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27 :
    case 'q':
        exit(0);
        break;

    case 'r':
        rotating++;
        break;
    case 'l':
        rotating--;
        break;
    }

    glutPostRedisplay();
}

void animate()
{
    rotating_angle=(rotating_angle+1)%360;
    clock_rotate=clock_rotate+0.01;
    glutPostRedisplay();
}

void instruction()
{
    cout<<"press 'r' to rotate right"<<endl;
    cout<<"press 'l' to rotate left"<<endl;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width,height);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("1607094_Classroom");

//    glClearColor(1,1,1,1);

    glEnable(GL_DEPTH_TEST);
    glShadeModel( GL_SMOOTH );
    glEnable(GL_NORMALIZE);
    glEnable(GL_BLEND);

    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(animate);

    instruction();
    glutMainLoop();

    return EXIT_SUCCESS;
}
