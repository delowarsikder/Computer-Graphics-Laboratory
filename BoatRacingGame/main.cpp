#include <windows.h>
#include <GL/glut.h>
#include<GL/gl.h>
#include<GL/glu.h>
#include <bits/stdc++.h>
#include "BmpLoader.h"
using namespace std;
//

const int width = 640;
const int height = 480;
//const int width = 840;
//const int height = 680;
const int winPosX = 200;
const int winPosY = 100;
int TIME=0;

GLfloat eyeX = 2;
GLfloat eyeY = 5;
GLfloat eyeZ = -13;

GLfloat lookX = 2;
GLfloat lookY = 0;
GLfloat lookZ = -1;

GLfloat centerX = -0.5;
GLfloat centerY = -0.5;
GLfloat centerZ = -0.5;

GLfloat Near = 2.5;
GLfloat Far = 100.0;

//for boat
bool start=false;
bool jump=false;
float jum=0;
bool leftShift=false;
bool rightShift=false;
float left_right_Move=0;
bool welCome_screen=true; ///initial welcome screen

int point=0;

float rotating = 0;
int rotating_angle_fan = 0;
bool rotate_fan = false;

float spot_cut_off = 50;


//variable for lighting
bool left_light_on = true;
bool right_light_on = true;
bool spot_light_on = true;

bool ambient_light_state = false;
bool specular_light_state = false;
bool diffuse_light_state = false;

GLfloat Xmin = -3, Xmax = 3, Ymin = -3, Ymax = 3;
//light color
const GLfloat ambient[] = {0.3, 0.3, 0.3, 1.0};
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

unsigned int ID;
vector<int>textureID;

//cube
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
    //abti-clock wise from each side
    {0, 2, 6, 4}, //back
    {1, 5, 7, 3}, //front
    {0, 4, 5, 1}, //bottom
    {2, 3, 7, 6}, //top
    {0, 1, 3, 2}, //left
    {4, 6, 7, 5}  //right
};

//prism
static GLfloat prism_vertices[6][3]=
{
    {0, 0, 0},//0 0
    {0, 0, 1},//1 1
    {1, 0, 0},//2 4
    {1, 0, 1},//3 5
    {1, 1, 0},//4 6
    {1, 1, 1}//5 7
};
static GLubyte prism_plane_indics[3][4]=
{
    {2, 4, 5, 3}, //right
    {0, 1, 3, 2}, //bottom
    {1,5,4,0}  //left
};

static GLubyte prism_triangle_indics[2][3]=
{
    {1,3,5},//front
    {0,4,2}//back
};

//pyramid
static GLfloat v_pyramid[5][3] =
{
    {0.0, 0.0, 0.0},  //point index 0
    {0.0, 0.0, 2.0},  //point index 1
    {2.0, 0.0, 2.0},  //point index 2
    {2.0, 0.0, 0.0},  //point index 3
    {1.0, 4.0, 1.0}   //point index 4
};

static GLubyte p_Indices[4][3] =
{
    {4, 1, 2}, // indeces for drawing the triangle plane 1
    {4, 2, 3}, // indeces for drawing the triangle plane 2
    {4, 3, 0}, // indeces for drawing the triangle plane 3
    {4, 0, 1}  // indeces for drawing the triangle plane 4
};

static GLubyte quadIndices[1][4] = { {0, 3, 2, 1}}; // indices for drawing the quad plane

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

void prism(float red = 0.5, float green = 0.5, float blue = 0.5, float alpha = 1)
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
    glTranslated(centerX,centerY,centerZ);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <2; i++)
    {
        getNormal3p(prism_vertices[prism_triangle_indics[i][0]][0],prism_vertices[prism_triangle_indics[i][0]][1],prism_vertices[prism_triangle_indics[i][0]][2],
                    prism_vertices[prism_triangle_indics[i][1]][0],prism_vertices[prism_triangle_indics[i][1]][1],prism_vertices[prism_triangle_indics[i][1]][2],
                    prism_vertices[prism_triangle_indics[i][2]][0],prism_vertices[prism_triangle_indics[i][2]][1],prism_vertices[prism_triangle_indics[i][2]][2]);

        for(GLint k=0; k<3; k++)
        {
            glVertex3fv(&prism_vertices[p_Indices[i][k]][0]);
        }
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <3; i++)
    {
        getNormal3p(prism_vertices[prism_plane_indics[i][0]][0],prism_vertices[prism_plane_indics[i][0]][1],prism_vertices[prism_plane_indics[i][0]][2],
                    prism_vertices[prism_plane_indics[i][1]][0],prism_vertices[prism_plane_indics[i][1]][1],prism_vertices[prism_plane_indics[i][1]][2],
                    prism_vertices[prism_plane_indics[i][2]][0],prism_vertices[prism_plane_indics[i][2]][1],prism_vertices[prism_plane_indics[i][2]][2]);

        for(GLint k=0; k<4; k++)
        {
            glVertex3fv(&prism_vertices[prism_plane_indics[i][k]][0]);
        }

    }
    glEnd();
}

void drawpyramid(float red = 0.5, float green = 0.5, float blue = 0.5, float alpha = 1)
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

    glTranslated(centerX,centerY,centerZ);

    glBegin(GL_TRIANGLES);
    for (GLint i = 0; i <4; i++)
    {
        getNormal3p(v_pyramid[p_Indices[i][0]][0],v_pyramid[p_Indices[i][0]][1],v_pyramid[p_Indices[i][0]][2],
                    v_pyramid[p_Indices[i][1]][0],v_pyramid[p_Indices[i][1]][1],v_pyramid[p_Indices[i][1]][2],
                    v_pyramid[p_Indices[i][2]][0],v_pyramid[p_Indices[i][2]][1],v_pyramid[p_Indices[i][2]][2]);

        glVertex3fv(&v_pyramid[p_Indices[i][0]][0]);

        glVertex3fv(&v_pyramid[p_Indices[i][1]][0]);

        glVertex3fv(&v_pyramid[p_Indices[i][2]][0]);
    }
    glEnd();

    glBegin(GL_QUADS);
    for (GLint i = 0; i <1; i++)
    {
        getNormal3p(v_pyramid[quadIndices[i][0]][0],v_pyramid[quadIndices[i][0]][1],v_pyramid[quadIndices[i][0]][2],
                    v_pyramid[quadIndices[i][1]][0],v_pyramid[quadIndices[i][1]][1],v_pyramid[quadIndices[i][1]][2],
                    v_pyramid[quadIndices[i][2]][0],v_pyramid[quadIndices[i][2]][1],v_pyramid[quadIndices[i][2]][2]);

        glVertex3fv(&v_pyramid[quadIndices[i][0]][0]);

        glVertex3fv(&v_pyramid[quadIndices[i][1]][0]);

        glVertex3fv(&v_pyramid[quadIndices[i][2]][0]);

        glVertex3fv(&v_pyramid[quadIndices[i][3]][0]);
    }
    glEnd();
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

    glTranslated(centerX,centerY,centerZ);
    glBegin(GL_QUADS);
    for (GLint i = 0; i < 6; i++)
    {
        getNormal3p(cube_vertices[cube_plane_indics[i][0]][0], cube_vertices[cube_plane_indics[i][0]][1], cube_vertices[cube_plane_indics[i][0]][2],
                    cube_vertices[cube_plane_indics[i][1]][0], cube_vertices[cube_plane_indics[i][1]][1], cube_vertices[cube_plane_indics[i][1]][2],
                    cube_vertices[cube_plane_indics[i][2]][0], cube_vertices[cube_plane_indics[i][2]][1], cube_vertices[cube_plane_indics[i][2]][2]);

        /*for (GLint j = 0; j < 4; j++)
        {
            glTexCoord2d(i,j); //define co-ordinate for texturing
            glVertex3fv(&cube_vertices[cube_plane_indics[i][j]][0]);
        }*/

        glTexCoord2d(0,0); //define co-ordinate for texturing
        glVertex3fv(&cube_vertices[cube_plane_indics[i][0]][0]);
        glTexCoord2d(0,1); //define co-ordinate for texturing
        glVertex3fv(&cube_vertices[cube_plane_indics[i][1]][0]);
        glTexCoord2d(1,1); //define co-ordinate for texturing
        glVertex3fv(&cube_vertices[cube_plane_indics[i][2]][0]);
        glTexCoord2d(1,0); //define co-ordinate for texturing
        glVertex3fv(&cube_vertices[cube_plane_indics[i][3]][0]);

    }
    glEnd();

}

void light()
{
    const GLfloat *no_light = black;
    //left
    const GLfloat *left_light_ambient = ambient;
    const GLfloat *left_light_diffuse = white;
    const GLfloat *left_light_specular = white;
    //right
    const GLfloat *right_light_ambient = ambient;
    const GLfloat *right_light_diffuse = white;
    const GLfloat *right_light_specular = white;
    //spot
    const GLfloat *spot_light_ambient = ambient;
    const GLfloat *spot_light_diffuse = white;
    const GLfloat *spot_light_specular = white;
    //light position
    const GLfloat left_light_position[] = {9, 7, 0.5, 1.0};       //light_left
    const GLfloat right_light_position[] = {-9, 6.5, 0.5, 1.0}; //light _right
    const GLfloat spot_light_position[] = {-2.5, 2.5, 6, 1};

    //if you want off all light just dark
    GLfloat globalAmbient[] = {0.0,0.0,0.0,1.0};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT,globalAmbient);

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
//            cout<<"ambien light"<<endl;
            glLightfv(GL_LIGHT0, GL_AMBIENT, left_light_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
            glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
        }
        else if (specular_light_state)
        {
//            cout<<"specular light "<<endl;
            glLightfv(GL_LIGHT0, GL_SPECULAR, left_light_specular);
            glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
            glLightfv(GL_LIGHT0, GL_DIFFUSE, no_light);
        }
        else if (diffuse_light_state)
        {
//            cout<<"diffuse light"<<endl;
            glLightfv(GL_LIGHT0, GL_DIFFUSE, left_light_diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, no_light);
            glLightfv(GL_LIGHT0, GL_AMBIENT, no_light);
        }
        else
        {
//            cout<<"light off"<<endl;
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

float BankOfRiver_width = 10;
float BankOfRiver_length = 50;
float BankOfRiver_thick = 3;

//lamp
void lamp(float transferX=0,float transferY=0,float transferZ=0)
{
    glPushMatrix();
    //upper
    glTranslated(transferX,transferY,transferZ);
    glPushMatrix();
    glTranslated(-0.5,2.5,-0.5);
    drawpyramid(.30,0.4,0.3);
    glPopMatrix();

    //lamp stand
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureID[1]);
    glPushMatrix();
    glScaled(0.3,4,0.3);
    cube(1.0,1.0,1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

//game over obstacle
void obstacle()
{
    float x=1,y=1,z=0.5;

    //check touch or not
    glPushMatrix();
    glTranslated(0,0,0);
    glScaled(.5,.5,.5);
    cube(1,0.2,0);
    glPopMatrix();
    //

    glPushMatrix();
    glTranslated(10,0,0);
    glScaled(x,y,z);
    cube(0.1,0.2,0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslated(10,0,15);
    glScaled(x,y,z);
    cube(0.3,0.5,0.3);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-10,0,0);
    glScaled(x,y,z);
    cube(0.6,0.9,0.1);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-8,0,10);
    glScaled(x,y,z);
    cube(0.7,0.2,0.4);
    glPopMatrix();

    glPushMatrix();
    glTranslated(-6,0,-10);
    glScaled(x,y,z);
    cube(0.4,0.3,0.5);
    glPopMatrix();

    glPushMatrix();
    glTranslated(6,0,2);
    glScaled(x,y,z);
    cube(0.7,0.6,0.1);
    glPopMatrix();
}

void bench(float transferX=0,float transferY=0,float transferZ=0)
{
    glPushMatrix();
    glTranslated(transferX,transferY,transferZ);
    //upper
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureID[9]);
    glPushMatrix();
    glTranslated(0,0.9,0);
    glScaled(1.2,0.2,3);
    cube(1.0,1.0,1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);


//left
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureID[10]);
    glPushMatrix();
    glTranslated(0,0,1);
    glScaled(1,1.75,0.2);
    cube(1.0,1.0,1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
//right

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureID[10]);
    glPushMatrix();
    glTranslated(0,0,-1);
    glScaled(1,1.75,0.2);
    cube(1.0,1.0,1.0);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
void building(float transferX=0,float transferY=0,float transferZ=0,int texID=2)
{
    glPushMatrix();
    glTranslated(transferX,transferY,transferZ);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureID[texID]);
    glPushMatrix();
    glTranslated(0,0,1);
    glScaled(3,8,2);
    cube(1,1,1);
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}

void parkOfRiverSide()
{
    glPushMatrix();

    lamp(15,3,5);
    lamp(15,3,0);
    lamp(15,3,-5);

    bench(14,2.5,4);
    bench(14,2.5,-4);

    glPopMatrix();
}

void BankOfRiver(float l = BankOfRiver_length,float w = BankOfRiver_width)
{
    glPushMatrix();
    //river left side
    glPushMatrix();
    glTranslated(2,0,9);
    parkOfRiverSide();
    glPopMatrix();

    glPushMatrix();
    glTranslated(2,0,-5);
    parkOfRiverSide();
    glPopMatrix();

    //right side

    glPushMatrix();
    glRotated(180,0,1,0);
    glTranslated(2,0,-10);
    parkOfRiverSide();
    glPopMatrix();

    glPushMatrix();
    glRotated(180,0,1,0);
    glTranslated(2,0,5);
    parkOfRiverSide();
    glPopMatrix();

    //building
//left
    building(23,5,-10,8);
    building(23,5,13,5);
    building(23,5,4,6);

    //right
    building(-23,5,15,7);
    building(-23,5,0,8);
    building(-23,5,-15,7);


//right side of bank of river
//upper texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureID[0]);
    glPushMatrix();
    glTranslated(-20,1.2,0);
    glScaled(w, 1, l);
    cube(1.0, 1.0,1.0 );
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //side cover
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureID[1]);
    glPushMatrix();
    glTranslated(-15,0,0);
    glRotatef(-90,0,0,1);
    glScaled(w-7, 1, l);
    cube(1.0, 1.0,1.0 );
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//    road
    glPushMatrix();
    glTranslated(-20,0,0);
    glScaled(w, BankOfRiver_thick, l);
    cube(1.0, 1.0,1.0 );
    glPopMatrix();

//left side of bank of river
//upper texture
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureID[0]);
    glPushMatrix();
    glTranslated(20,1.2,0);
    glScaled(w, 1, l);
    cube(1.0, 1.0,1.0 );
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //side cover
//side cover
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureID[1]);
    glPushMatrix();
    glTranslated(15,0,0);
    glRotatef(90,0,0,1);
    glScaled(w-7, 1, l);
    cube(1.0, 1.0,1.0 );
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

//road
    glPushMatrix();
    glTranslated(20,0,0);
    glScaled(w, BankOfRiver_thick, l);
    cube(1.0, 1.0,1.0 );
    glPopMatrix();

    glPopMatrix();

}

int river_width=35;
float sceneTranslate=0;

void river(int w=river_width,int l=BankOfRiver_length)
{
    glPushMatrix();
    BankOfRiver();
    //river water
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,textureID[2]);
    glPushMatrix();
    glTranslated(0,-1.50,0);
    glScaled(w,0.2,l);
    cube(0.3,0.1,0.6);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //obstacle
    glPushMatrix();
    obstacle();
    glTranslated(0,0,-8);
    obstacle();
    glPopMatrix();

    glPopMatrix();

}

float moveFront=0;
int moveBack=0;

void flag()
{
    glPushMatrix();
    glTranslated(0,2.5,-2.5);
    //square
    glPushMatrix();
    glTranslated(0,1,-0.5);
    glScaled(0.02,0.6,1);
    cube(1,1,1);
    glPopMatrix();

    //stand
    glPushMatrix();
    glScaled(0.09,3,0.09);
    cube(0.5,0.9,0.4);
    glPopMatrix();

    glPopMatrix();
}

void ship()
{
    int ship_length=2.5;
    int ship_higth=1.5;
    int ship_width=0.75;

    glPushMatrix();

    if(rightShift)
    {
        glTranslated(left_right_Move,0,0);
//        glRotated(left_right_Move,0,1,0);
    }
    if(leftShift)
    {
        glTranslated(left_right_Move,0,0);
//        glRotated(left_right_Move,0,1,0);
    }
    if(jump)
    {
        glTranslated(0,1,0);
    }

    glTranslated(0,0,moveFront);
//    glTranslated(0,0,-2);
    flag();


    //front part-left
    glPushMatrix();
    glTranslated(0.4,0.5,-2.7);
    glRotated(-45,0,1,0);
    glScaled(0.05,1,1.1);
    cube(1,0.5,0.3);
    glPopMatrix();

    //front part-right
    glPushMatrix();
    glTranslated(-0.4,0.5,-2.7);
    glRotated(45,0,1,0);
    glScaled(0.05,1,1.1);
    cube(1,0.5,0.3);
    glPopMatrix();

    //bottom part
    glPushMatrix();
    glTranslated(-0.02,0,-4);
    glScaled(1.5,0.05,2);
    cube(1,0.2,0.3);
    glPopMatrix();

    //box1 on the ship
    glPushMatrix();
    glTranslated(-0.02,0.5,-4);
    glScaled(1.25,0.75,1.75);
    cube(0.2,0.6,0.9);
    glPopMatrix();

    //box2 on the ship
    glPushMatrix();
    glTranslated(-0.02,1,-4);
    glScaled(1,0.75,1.5);
    cube(0.2,0.1,0.2);
    glPopMatrix();

    //box3 on the ship
    glPushMatrix();
    glTranslated(-0.02,1.25,-4);
    glScaled(0.75,0.75,1.25);
    cube(0.1,0.6,0.3);
    glPopMatrix();


//done
    //side part
    //left side
    glPushMatrix();
    glTranslated(0.75,0.5,-4);
    glScaled(0.05,ship_higth,ship_length);
    cube(1,0.5,0.3);
    glPopMatrix();

    //right side
    glPushMatrix();
    glTranslated(-0.75,0.5,-4);
    glScaled(0.05,ship_higth,ship_length);
    cube(1,0.5,0.3);
    glPopMatrix();

    //back side
    glPushMatrix();
    glTranslated(0,0.5,-5);
    glScaled(1.5,ship_higth,0.05);
    cube(1,0.5,0.3);
    glPopMatrix();

    glPopMatrix();
}

void axis()
{
    float length = 10;
    float width = 0.3;
    //x-axis
    glPushMatrix();
    glTranslated(length / 2, 0, 0);
    glScaled(length, width, width);
    cube(1.0, 0.0, 0.0);
    glPopMatrix();

    //y-axis
    glPushMatrix();
    glTranslated(0, length / 2, 0);
    glScaled(width, length, width);
    cube(0.0, 0.0, 1.0);
    glPopMatrix();

    //z-axis
    glPushMatrix();
    glTranslated(0, 0, length / 2);
    glScaled(width, width, length);
    cube(0.0, 1.0, 0.0);
    glPopMatrix();
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
        lookZ+=0.3;
        break;
    case '-':
        eyeZ -= 0.3;
        lookZ-=0.3;
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
    case 'j':
        jump=!jump;

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

        left_light_on = false;
        right_light_on = false;
        spot_light_on=false;
        break;
    }
    glutPostRedisplay();
}

static void SpecialKeyFunc( int Key, int x, int y )
{
    switch ( Key )
    {
    case GLUT_KEY_UP:
        start=true;//start the boat
        break;
    case GLUT_KEY_LEFT:
        left_right_Move+=0.5;
        if(left_right_Move>=11)
        {
            left_right_Move=11;
        }
        leftShift=true;
        rightShift=false;
        break;
    case GLUT_KEY_RIGHT:
        left_right_Move-=0.5;
        if(left_right_Move<=-11)
        {
            left_right_Move=-11;
        }

        rightShift=true;
        leftShift=false;
        break;
    case GLUT_KEY_DOWN:
        start=false;
        break;

    case GLUT_KEY_PAGE_UP:
        jump=!jump;
        break;
    case GLUT_KEY_F1:
        welCome_screen=false;
        break;
    default:
        break;
    }
    glutPostRedisplay();
}


static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

///draw text in upper right corner
void drawStrokeText(string str,int x,int y,int z)
{
    glColor3f(1.0,1.0,1.0);
    glPushMatrix();
    glTranslatef(x, y,moveFront);
    glRotated(180,0,1,0);
    glScalef(0.009f,0.009f,z);
    int len=str.length();
    for (int i=0; i<len; i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
    }
    glPopMatrix();
    glutPostRedisplay();
}

float tz=100;
void repeatScene()
{
    for(int i=0; i<tz; i+=40)
    {
        glPushMatrix();
        glTranslated(0,0,i);
        river();
        glPopMatrix();
    }
    tz=int(tz+moveFront*1.5)%1000;
}

//this function contain most scene
void allScene()
{
    double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    double a = t*90.0;
    TIME = t;
    //time
    if(start)
    {
        point++;
    }
    drawStrokeText("Score: "+to_string(point/100),-1,10,0);
    ship();
    repeatScene();
}

//display string
void display_string(int x, int y,int z, char *string, int font=2)
{
    int len,i;
    glColor3f(0.8,0.8,1.0);
    glRasterPos3f(x, y,z);
    len = (int) strlen(string);
    for (i = 0; i < len; i++)
    {
        if(font==1)
        {
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
        }
        if(font==2)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,string[i]);
        }
        if(font==3)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,string[i]);
        }
        if(font==4)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10,string[i]);
        }
    }
}

static void display(void)
{
    glClearColor(0.2,0.4,0.75,0.5); //draw sky
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
    allScene();
//    axis();
    light();
    glutPostRedisplay();
    glutSwapBuffers();
    glFlush();
}

///text for welcome screen
void init()
{
    glClearColor(0,0,0,0);
    glPointSize(5.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0,900.0,0.0,600.0,50.0,-50.0);
    glutPostRedisplay();
}

void display_welcome()
{
    int xwidth_int=10;
    int yHeight_int=560;
    int z_depth=0;
    float diff_height=40;
    glClearColor(0.0,0.0,0.0,0.5);
    glClear(GL_COLOR_BUFFER_BIT);

    display_string(xwidth_int,yHeight_int,z_depth,"Khulna University of Engineering & Technology,Khulna-9203",2);
    display_string(xwidth_int,yHeight_int-diff_height*1,z_depth,"Department of Computer Science and Engineering",2);
    display_string(xwidth_int,yHeight_int-diff_height*2,z_depth,"Project Title:  Boat Racing In the River",2);
    display_string(xwidth_int,yHeight_int-diff_height*3,z_depth,"Developed By: Delowar Sikder \n Roll: 1607094",2);
    display_string(xwidth_int+diff_height,yHeight_int-diff_height*4,z_depth,"Instruction :",1);
    display_string(xwidth_int+diff_height,yHeight_int-diff_height*5,z_depth,"KEYBOARD :",3);
    display_string(xwidth_int+diff_height,yHeight_int-diff_height*6,z_depth,"1.UP ARROW(^) TO START MOVING AND  DOWN ARROW(!) TO STOP MOVE",3);
    display_string(xwidth_int+diff_height,yHeight_int-diff_height*6.5,z_depth,"2.LEFT ARROW(<-) TO MOVE LEFT AND RIGHT ARROW(->) TO MOVE RIGHT SIDE",3);
    display_string(xwidth_int+diff_height,yHeight_int-diff_height*7,z_depth,"KEYBOARDKEYBOARD :",3);
    display_string(xwidth_int+diff_height,yHeight_int-diff_height*10,z_depth,"PRESS F1 TO ENTER THE GAME SCEEN",2);

    glutPostRedisplay();
    glutSwapBuffers();
}

GLvoid DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(welCome_screen)
    {
        init();
        display_welcome();
    }
    else
    {
        display();
    }
}

///

void animate()
{
    glutPostRedisplay();
}

void LoadTexture(const char*filename)
{
    glGenTextures(1, &ID);
    glBindTexture(GL_TEXTURE_2D, ID);
    glPixelStorei(GL_UNPACK_ALIGNMENT, ID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    BmpLoader bl(filename);
    gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, bl.iWidth, bl.iHeight, GL_RGB, GL_UNSIGNED_BYTE, bl.textureData );
}

void update (int value)
{
    if(start)
    {
        eyeZ += 0.2;
        lookZ+=0.2;
        moveFront+=0.2;
    }

    glutPostRedisplay();
    glutTimerFunc(100, update, 0);
}

void instruction()
{
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    cout << "$$$$$$$$$$$$$  Please Follow this Instruction $$$$$$$$$$$$$$" << endl;
    cout << "$$$$$$$$$$$$$$$    To Control The Game    $$$$$$$$$$" << endl;
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

void LoadTextureImage()
{
//    LoadTexture("G:\\Study\\4-2\\CSE_4208_Graphics_Lab\\project\\Go_Forward\\brick.bmp");

    LoadTexture("G:/Study/4-2/CSE_4208_Graphics_Lab/project/Go_Forward/texture/road.bmp");
    textureID.push_back(ID);
    LoadTexture("G:/Study/4-2/CSE_4208_Graphics_Lab/project/Go_Forward/texture/brick.bmp");
    textureID.push_back(ID);
    LoadTexture("G:/Study/4-2/CSE_4208_Graphics_Lab/project/Go_Forward/texture/riverWater.bmp");
    textureID.push_back(ID);
    LoadTexture("G:/Study/4-2/CSE_4208_Graphics_Lab/project/Go_Forward/texture/building.bmp");
    textureID.push_back(ID);
    LoadTexture("G:/Study/4-2/CSE_4208_Graphics_Lab/project/Go_Forward/texture/building1.bmp");
    textureID.push_back(ID);
    LoadTexture("G:/Study/4-2/CSE_4208_Graphics_Lab/project/Go_Forward/texture/building.bmp");
    textureID.push_back(ID);
    LoadTexture("G:/Study/4-2/CSE_4208_Graphics_Lab/project/Go_Forward/texture/building3.bmp");
    textureID.push_back(ID);

    LoadTexture("G:/Study/4-2/CSE_4208_Graphics_Lab/project/Go_Forward/texture/building4.bmp");
    textureID.push_back(ID);

    LoadTexture("G:/Study/4-2/CSE_4208_Graphics_Lab/project/Go_Forward/texture/building5.bmp");
    textureID.push_back(ID);

    LoadTexture("G:/Study/4-2/CSE_4208_Graphics_Lab/project/Go_Forward/texture/tiles1.bmp");
    textureID.push_back(ID);
    LoadTexture("G:/Study/4-2/CSE_4208_Graphics_Lab/project/Go_Forward/texture/tiles2.bmp");
    textureID.push_back(ID);
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(winPosX, winPosY);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("1607094_Racing Boat");

    glutReshapeFunc(resize);
//    glutDisplayFunc(display); //second screen
    glutDisplayFunc(DrawGLScene); //first screen
    glutKeyboardFunc(key);

    glutSpecialFunc( SpecialKeyFunc );
    glutIdleFunc(animate);
    glutTimerFunc(1000, update, 0);

    //load texture
    LoadTextureImage();
    // glClearColor(1, 1, 1, 1);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    instruction();

    glutMainLoop();

    return EXIT_SUCCESS;
}
