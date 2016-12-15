// Avery Rapson and Jacob London
// Nov. 17, 2015


/* ------------- */

/*   Project 3   */

/* ------------- */


/*
 -----------------------------------------------------------------------------------------------------------------------------------------------------------------------
 Objective of Program:
 
 - Requirements for 3D world:
 + Construct a boundary for your world within the projection's clipping planes.
 + The observer should not be allowed to move outside of the world's boundaries.
 + The world should contain at least three different obstacles that the observer can navigate around. The obstacles can be any 3D object of your choice.
 + The obstacles must be placed within the boundaries of the world and at different positions in the world.
 + At least one obstacle is specified with a bounding box that constrains the navigator from moving through the obstacle.
 The boundaries of the box will need to be checked each time the viewpoint position is modified.
 + Smooth, filled and colored 3D polygons must be used. Surface normals for each polygon must be defined or predefined by the object definition (glut/glu objects).
 + A least one positional light must be used (ambient-diffuse/specular) that moves with the navigator. Other lights may be used for special effects within the world.
 + Texuring
 
 
 - Requirements for Navigation:
 + You must use the gluLookAt command to move the navigator through your world.
 + You should provide a key control to return the navigator to a default position and line of sight.
 
 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 Controls:
 
 + To quit the program: Hit q or "esc"
 + To move forward: up arrow key
 + To move backwards: down arrow key
 + To turn right: right arrow key
 + To turn left: left arrow key
 + To reset to starting position: spacebar
 
 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 Bugs:
 
 + After returning from the 2nd room to the 1st, there is an awkward jump upon initial movement and rotation
 + Spaces between portal blocks sometimes also teleport you when they are not suppose to. (only collision with teleport blocks is ment to teleport you)
 + Do not back into portals, you will get stuck (we did not implement backwards logic for entering portals)
 
 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 Key Instructions:
 
 + At spawn in the first room (starting position) , correct portal to the second room is the middle portal on the left side.
 + In the second room, the giant portal on the left puts you in the lava and the portal on the right brings you back to the start position.
 + You lose if you have to hit spacebar (in other words if you get stuck in the lava)
 + After hitting spacebar to reset, hit the left or right key to begin playing again
 
 --------------------------------------------------------------------------------------------------------------------------------------------------------------------------
 
 */


#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <iostream>
#include <math.h>
#include <iostream>
#include "tgaClass.h"
#include "BoundaryBoxes.h"
#include "BoundaryBoxes.cpp"
#include "Portal.h"
#include "Portal.cpp"
#include <array>
using namespace std;


bool u = false;
//Portal Identifiers, both begin and ending points
array<float,7> portal3 ={0,-20, 12.5, 12.5, -.7, -.7, -.75};
array<float,7> portal4 ={15, -15, 12.5, 12.5,-.7, -.7, -.75};
array<float,7> portal6 ={15, 15, 12.5, -12.5,-.7, .7, -2.4};
array<float,7> portal2 = {-15, -15, -12.5, 12.5,.7, -.7, .75};
array<float,7> portal1 = {-15, 0, 0, -42, 0, -1, 0};
array<float,7> portal5={15, 0, 0 , 23,0, -1, 0};
array<float,7> portal7={0, 20, 0 , -17,0, 1, 9.4};
array<float,7> portal8 ={-15, 15, -12.5 , -12.5,.7, .7, 2.4};
array<float,7> portal9={25, -45, 0, 0, 0, 1,0};
array<float,7> portal10={-25, -45, 0, -90, 0, -1,0};
array<float,7> portal11;
array<float,7> portal12;
int position, lastPosition;

//declarations
array<float, 5> temp;
bool p1, p2, p3,p4,p5,p6,p7,p8,p9,p10;
int room; // 1-3
BoundaryBoxes Box;
BoundaryBoxes Box2;
Portal Portal1(portal1,portal2,portal3, portal4,portal5,portal6,portal7,portal8,portal9,portal10);

// angle of rotation for the camera direction
float angle=0.0;
// actual vector representing the camera's direction
float dx=0.0f,dz=-1.0f;
// XZ position of the camera
float x=0.0f,z=0.0f, z2=0.0f;

// This holds the zoom value of our scope
float my_zoom = 0;

// This is our camera rotation degree
float my_rotateY = 0;
float my_zoom_inc = 0;

// switches color scheme
GLfloat color_switch_r = 0;
GLfloat color_switch_b = 0;
GLfloat color_switch_g = 0;



#define MAX_TEXTURES 10
#define SCREEN_WIDTH 640	// We want our screen width 640 pixels
#define SCREEN_HEIGHT 480


unsigned int my_Texture[MAX_TEXTURES] = {0};

/* --------------- */
/*     Lighting    */
/* --------------- */


// Ambient-Diffuse Specular Reflection Light

GLfloat light_x = 0, light_y = 0, light_z = 0;

GLfloat light_pos[] = { 0 , 0 , 0 , 1};

GLfloat light_ambient[] = {1, .5, .5, 1.0}; //ambient light intensity

GLfloat light_diffuse[] = {1.0, 1.0 , 1.0 ,1.0}; //diffuse light intensity

GLfloat light_specular[] ={1.0 ,1.0, 1.0,1.0}; //white light

GLfloat mat_specular[] = { 1.0 , 1.0, 1.0 ,1.0}; // white light

GLfloat mat_ambient_rm1[] = {0 , 1 , 1  , 1}; //ambient color - (how full of light room will be)

GLfloat mat_ambient_rm2[] = { 1 , 0 , 0, 1};

GLfloat shininess[] = {100.0}; // yay shininess



void reshape(int w, int h);


// source code to glutSolidCube(), hard coded texCoords to eneble acurable tex coord mapping

/* Copyright (c) Mark J. Kilgard, 1994, 1997.
 (c) Copyright 1993, Silicon Graphics, Inc. */

static void drawBox(GLfloat size, GLenum type)
{
    static GLfloat n[6][3] =
    {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
    };
    static GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
    };
    GLfloat v[8][3];
    GLint i;
    
    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size / 2;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size / 2;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size / 2;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size / 2;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size / 2;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size / 2;
    
    for (i = 5; i >= 0; i--) {
        glBegin(type);
        glNormal3fv(&n[i][0]);
        glTexCoord2f(0.0f, 1.0f); glVertex3fv(&v[faces[i][0]][0]);
        glTexCoord2f(1.0f, 1.0f); glVertex3fv(&v[faces[i][1]][0]);
        glTexCoord2f(1.0f, 0.0f); glVertex3fv(&v[faces[i][2]][0]);
        glTexCoord2f(0.0f, 0.0f); glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}


/* ---------------------- */
/*     Creates Texture    */
/* ---------------------- */
void CreateTexture(unsigned int textureArray[], char * strFileName, int textureID)
{
    
    char buffer[30];	//filename holder
    int status = 0;		//error codes for file read
    TGA myTGAImage;
    
    if(!strFileName){			// Return from the function if no file name was passed in
        
        cout <<"Error occurred, bad file name "<< endl;
        return;
    }
    
    sprintf (buffer, strFileName);		//load buffer with filename
    status = myTGAImage.readTGA(buffer);// Load into a TGA object
    if(status > 1) {
        cout <<"Error occurred = " << status <<strFileName<< endl;
        exit(0);
    }
    
    
    
    // Generate a texture with the associative texture ID stored in the array
    glGenTextures((GLsizei)1, (GLuint *)&textureArray[textureID]);
    
    // This sets the alignment requirements for the start of each pixel row in memory.
    glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
    
    
    // Bind the texture to the texture arrays index and init the texture
    glBindTexture(GL_TEXTURE_2D, textureArray[textureID]);
    
    
    // Build Mipmaps (builds different versions of the picture for distances - looks better)
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3,  myTGAImage.width,
                      myTGAImage.height, myTGAImage.format, GL_UNSIGNED_BYTE, myTGAImage.data);
    
    
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    
    
}


/* -------------------- */
/*     Init Function    */
/* -------------------- */
void init(void)
{
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int width = glutGet(GLUT_WINDOW_WIDTH);
    int height = glutGet(GLUT_WINDOW_HEIGHT);
    glViewport(0,0,width,height);
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height, .5f, 150.0f);
    //    glOrtho(-width, width, -height, height, 0, 10 );
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Here we load all of our textures.
    CreateTexture(my_Texture, "room2wall.tga", 2); // room 2 wall
    CreateTexture(my_Texture, "myLava.tga", 3); // lava
    CreateTexture(my_Texture, "help.tga", 4); // floor
    CreateTexture(my_Texture, "portal.tga", 5); // portal texture
    
    
    // light enabling/disabling
    glDisable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glEnable(GL_TEXTURE_2D);
    
}



/* ------------------------ */
/*     Keyboard Function    */
/* ------------------------ */
void processNormalKeys(unsigned char key, int x, int y)
{
    switch ( key )
    {
        case 'q': // q to quit the program
            
            exit (0);
            break;
        case 27:
            exit(0);
            break;
        case 'a':
            u = !u;
            glutPostRedisplay();
            break;
            
        case ' ':
            x = 0;
            z = 2;
            dx = 0;
            dz = 0;
            angle = 0;
            room = 1;
            
            gluLookAt( x, 1.0f, z,
                      x+dx, 1.0f,  z+dz,
                      0.0f, 1.0f,  0.0f);
            
            glutPostRedisplay();
            
            break;
            
        default:
            break;
    }
    
}


/* ------------------------ */
/*     First Room           */
/* ------------------------ */
void FirstRoom()
{
    
    // Bind the wall texture to the wall quads
    glBindTexture(GL_TEXTURE_2D,  my_Texture[2]);
    
    
    // "front wal
    glBegin(GL_QUADS);
    glColor3f(.2, .2, .2);
    glTexCoord2f(0.0f, 12.0f); glVertex3f(-30, 50, -30);
    glTexCoord2f(4.0f, 12.0f); glVertex3f(-30, -1, -30);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(30, -1, -30);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(30, 50, -30);
    glEnd();
    
    //left wall
    glBegin(GL_QUADS);
    glColor3f(.5, .5, .5);
    glTexCoord2f(0.0f, 12.0f); glVertex3f(-30, 50, 30); //right top
    glTexCoord2f(4.0f, 12.0f); glVertex3f(-30, -1, 30); // left top
    glTexCoord2f(4.0f, 0.0f); glVertex3f(-30, -1, -30); // left bottom
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-30, 50, -30); // right bottom
    glEnd();
    
    // right walls
    glBegin(GL_QUADS);
    glColor3f(.5, .5, .5);
    glTexCoord2f(0.0f, 12.0f); glVertex3f(30, 50, -30);
    glTexCoord2f(4.0f, 12.0f); glVertex3f(30, -1, -30);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(30, -1, 30);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(30, 50, 30);
    glEnd();
    
    // "back wall"
    glBegin(GL_QUADS);
    glColor3f(.2, .2, .2);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(30, 50, 30);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(30, -1, 30);
    glTexCoord2f(4.0f, 12.0f); glVertex3f(-30, -1, 30); // back
    glTexCoord2f(0.0f, 12.0f); glVertex3f(-30, 50, 30); // top left
    
    
    
    glEnd();
    
    // Bind this texture to the floor quad
    glBindTexture(GL_TEXTURE_2D,  my_Texture[4]);
    
    // floor
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 6.0f); glVertex3f(-30, -1, 30);  // back left
    glTexCoord2f(6.0f, 6.0f); glVertex3f(30, -1, 30);  // back right
    glTexCoord2f(6.0f, 0.0f); glVertex3f(30, -1, -30);  // front right
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-30, -1, -30);  // front left
    glEnd();
    
}


/* ------------------------ */
/*     Second Room          */
/* ------------------------ */

void SecondRoom()
{
    
    // Bind the wall texture to the wall quads
    glBindTexture(GL_TEXTURE_2D,  my_Texture[2]);
    
    
    //left wall
    glBegin(GL_QUADS);
    glColor3f(.5, .5, .5);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-30, 50, -40);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-30, -1, -40);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(-30, -1, -70);
    glTexCoord2f(4.0f, 1.0f); glVertex3f(-30, 50, -70);
    glEnd();
    
    
    // right walls
    glBegin(GL_QUADS);
    glColor3f(.5, .5, .5);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(30, 50, -70);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(30, -1, -70);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(30, -1, -40);
    glTexCoord2f(4.0f, 1.0f); glVertex3f(30, 50, -40);
    glEnd();
    
    // "back wall"
    // define vert. backwards
    glBegin(GL_QUADS);
    glColor3f(.2, .2, .2);
    glTexCoord2f(4.0f, 1.0f); glVertex3f(30, 50, -40);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(30, -1, -40);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-30, -1, -40);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-30, 50, -40);
    glEnd();
    
    // Bind this texture to the floor quad
    glBindTexture(GL_TEXTURE_2D,  my_Texture[4]);
    
    
    // floor
    glColor3f(1, 1, 1);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 6.0f); glVertex3f(-30, -1, -70); // back left
    glTexCoord2f(6.0f, 6.0f); glVertex3f(-30, -1, -40);
    glTexCoord2f(6.0f, 0.0f); glVertex3f(30, -1, -40);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(30, -1, -70);
    glEnd();
    
}

/*----------------------*/
/*---- Lava Room   -----*/
/*----------------------*/

void LavaRoom() {
    
    //glBindTexture(GL_TEXTURE_2D,  my_Texture[1]);
    
    
    
    glBindTexture(GL_TEXTURE_2D,  my_Texture[3]);
    
    
    // "lava floor"
    glBegin(GL_QUADS);
    glColor3f(.2, .2, .2);
    glTexCoord2f(0.0f, 10.0f); glVertex3f(-50, -1, -70);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(50, -1, -70);
    glTexCoord2f(10.0f, 0.0f); glVertex3f(50, -1, -130);
    glTexCoord2f(10.0f, 10.0f); glVertex3f(-50, -1, -130);
    glEnd();
    
    
    glBindTexture(GL_TEXTURE_2D,  my_Texture[2]);
    // Left lava wall
    glBegin(GL_QUADS);
    glColor3f(.2, .2, .2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-30, 50, -70);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-30, -1, -70);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(-50, -1, -120);
    glTexCoord2f(4.0f, 1.0f); glVertex3f(-50, 50, -120);
    glEnd();
    
    // Right lava wall
    glBegin(GL_QUADS);
    glColor3f(.2, .2, .2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(30, 50, -70);
    glTexCoord2f(4.0f, 1.0f); glVertex3f(50, 50, -120);
    glTexCoord2f(4.0f, 0.0f); glVertex3f(50, -1, -120);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(30, -1, -70);
    glEnd();
    
    // back lava wall
    glBegin(GL_QUADS);
    glColor3f(.2, .2, .2);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-50, 50, -120);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50, -1, -120);
    glTexCoord2f(8.0f, 0.0f); glVertex3f(50, -1, -120);
    glTexCoord2f(8.0f, 1.0f); glVertex3f(50, 50, -120);
    glEnd();
    
}

/* ------------------------ */
/*    Draw Portals          */
/* ------------------------ */

void portals() {
    //intro push
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, my_Texture[5]);
    
    glPushMatrix();
    glTranslatef(0, 2, -20);
    drawBox(6, GL_QUADS);
    glTranslatef(0, 0, 40);
    drawBox(6, GL_QUADS);
    glPopMatrix();
    
    
    int cube_change = 0;
    int angle_change = -45;
    for (int i=0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(-15 , 2, -15 + cube_change);
        glRotatef(angle_change, 0, 1, 0);
        drawBox(6, GL_QUADS);
        glPopMatrix();
        cube_change += 15;
        angle_change += 45;
    }
    
    angle_change = -45;
    cube_change = 0;
    for (int i=0; i < 3; i++) {
        glPushMatrix();
        glTranslatef(15 , 2, -15 + cube_change);
        glRotatef(angle_change, 0, 1, 0);
        
        drawBox(6, GL_QUADS);
        glPopMatrix();
        cube_change += 15;
        angle_change += 45;
        
    }
    glPopMatrix();
    
    
    
    
    glPopMatrix();
    //exit pop
}


/* ------------------------ */
/*     draw Columns         */
/* ------------------------ */
// draw the wall that blocks from entering lava
void columns () {
    
    glBindTexture(GL_TEXTURE_2D,  my_Texture[5]);
    
    int column_change_x = 0;
    int column_change_y = 0;
    int line_increase_x = 0;
    int line_increase_y = 0;
    
    
    // draw boxes
    glPushMatrix();
    for (int i=0; i < 6; i++) {
        for (int k = 0; k<15; k++) {
            glPushMatrix();
            glTranslatef(-30 + column_change_x, 16 + column_change_y, -71 );
            glutSolidCube(2);
            column_change_x += 5;
            glPopMatrix();
        }
        column_change_y -= 5;
        column_change_x = 0;
        
        
    }
    
    
    // draw lines
    for (int i =0; i<20; i++) {
        glPushMatrix();
        glBegin(GL_LINES);
        glVertex3f(-30 , 0+ line_increase_y, -70);
        glVertex3f(30 , 0+ line_increase_y, -70);
        line_increase_y +=1;
        glEnd();
        glPopMatrix();
        
    }
    glPopMatrix();
    
}




/* ---------------------- */
/*     Display Function   */
/* ---------------------- */
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glEnable(GL_DEPTH_TEST);
    
    glEnable(GL_LIGHTING);
    // Reset transformations
    glLoadIdentity();
    
    
    if (p3) {
        position = Portal1.getPosition();
        temp = Portal1.switchPos(Portal1.getPosition());
        x = temp[0]; z = temp[1]; dx= temp[2]; dz = temp[3] ; angle = temp[4];
        
        gluLookAt( x, 1.0f, z,
                  dx, 1.0f,  dz,
                  0.0f, 1.0f,  0.0f);
        
        
        p3 = false;
        temp[0] = 0;
        temp[1] = 0;
        temp[3] = 0;
        temp[4] = 0;
        temp[5] = 0;
    }
    else{
        gluLookAt( x, 1.0f, z,
                  x+dx, 1.0f,  z+dz,
                  0.0f, 1.0f,  0.0f);
        
        
    }
    
    
    
    /* --------------------------------------------------- */
    /*                                                     */
    /*                      ROOM ONE                       */
    /*                                                     */
    /* --------------------------------------------------- */
    
    // room one push
    columns();
    glPushMatrix();
    
    // set up lighting
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    
    glLightfv(GL_LIGHT0, GL_SPECULAR ,light_specular);
    
    glEnable(GL_LIGHT0);
    
    
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_rm1);
    
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    
    glMaterialfv(GL_FRONT,GL_SHININESS,shininess);
    
    
    
    // create trippy lights in room one
    
    color_switch_b += 1;
    color_switch_g -= 1;
    color_switch_r += 1;
    
    GLfloat mat_diffuse_rm1[] = { 0 + color_switch_r, 1 + color_switch_g,  1+ color_switch_b ,1.0};  // diffuse color - (changes color of room/objects
    
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_rm1);
    
    // draw
    FirstRoom();
    portals();
    
    // light follows us! neat!
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    
    
    glPopMatrix();
    glDisable(GL_LIGHT0);
    
    /* --------------------------------------------------- */
    /*                                                     */
    /*                      ROOM TWO                       */
    /*                                                     */
    /* --------------------------------------------------- */
    
    //room two push
    glEnable(GL_LIGHT1);
    glPushMatrix();
    
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
    
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    
    glLightfv(GL_LIGHT1, GL_SPECULAR ,light_specular);
    
    glMaterialfv(GL_FRONT,GL_AMBIENT,mat_ambient_rm2);
    
    
    glMaterialfv(GL_FRONT,GL_SPECULAR,mat_specular);
    
    GLfloat mat_diffuse_rm2[] = {1 , 0 , 0 ,1.0};  // diffuse color -
    
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse_rm2);
    
    SecondRoom();
    LavaRoom();
    
    
    glBindTexture(GL_TEXTURE_2D, my_Texture[5]);
    
    glPushMatrix();
    glTranslatef(-42 , 8, - 55);
    drawBox(25, GL_QUADS);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef( 42, 8, - 55);
    drawBox(25, GL_QUADS);
    glPopMatrix();
    
    
    glLightfv(GL_LIGHT1, GL_POSITION, light_pos);
    
    
    glEnd();
    glDisable(GL_LIGHT1);
    
    glPopMatrix();
    
    
    glDisable(GL_LIGHT0);
    
    glutSwapBuffers();
}




/* -------------------------- */
/*     Arrow Keys Function    */
/* -------------------------- */

//uses special keys to move the camera around (left, right, front, back)
void processSpecialKeys(int key, int xx, int yy)
{
    float fraction = 1.0f;
    
    switch (key) {
        case GLUT_KEY_LEFT :
            
            angle -= .03f;
            dx = sin(angle);
            dz = -cos(angle);
            
            glutPostRedisplay();
            break;
            
        case GLUT_KEY_RIGHT :
            angle += .03f;
            dx = sin(angle);
            dz = -cos(angle);
            
            glutPostRedisplay();
            break;
            
            
        case GLUT_KEY_UP :
            // check if you are in boundry of teleport box, if so, teleport.
            // set up and check wall boundries
            if (room == 1){
                if(Box.check(x, z, dx, dz, 0, room)) {
                    if (Portal1.checkPortal(x, z)) {
                        p3=true;
                        if(Portal1.getPosition() == 1){
                            room = 2;
                        }
                    }
                    else{
                        // move forward
                        x += dx * fraction;
                        z += dz * fraction;
                    }
                    
                }
            }
            
            else if (room == 2){
                // check if you are in boundry of teleport box, if so, teleport.
                // set up and check wall boundries
                if(Box.check(x, z, dx, dz, 0, room)) {
                    if (Portal1.checkPortal(x, z)) {
                        
                        p3 = true;
                        if(Portal1.getPosition() == 9){
                            room = 1;
                        }
                        if(Portal1.getPosition() == 10){
                            room = 3;
                        }
                    }
                    else {
                        // move forward
                        x += dx * fraction;
                        z += dz * fraction;
                    }
                    
                    
                }
            }
            
            glutPostRedisplay();
            break;
        case GLUT_KEY_DOWN :
            if (room == 1){
                if(Box.check(x, z, dx, dz, 1, room)) {
                    if (Portal1.checkPortal(x, z)) {
                        p1=true;
                        room = 2;
                    }
                    else{
                        //empty
                    }
                    
                    x -= dx * fraction;
                    z -= dz * fraction;
                    
                }
            }
            else if (room == 2){
                if(Box.check(x, z, dx, dz, 1, room)){
                    if (Portal1.checkPortal(x, z)) {
                        p2 = true;
                        room = 1;
                    }
                    else {
                        //empty
                    }
                    x -= dx * fraction;
                    z -= dz * fraction;
                    
                }
            }
            
            glutPostRedisplay();
            break;
            
            
    }
}

/* -------------------------- */
/*     Main Function          */
/* -------------------------- */

int main(int argc, char *argv[])
{
    position =0;
    room = 1;
    p1 = p2=p3=p4=p5=p6=p7=p8=p9=p10=false;
    Box = *new BoundaryBoxes();
    Box2 = *new BoundaryBoxes();
    Portal1= *new Portal(portal1,portal2,portal3, portal4,portal5,portal6,portal7,portal8,portal9,portal10);
    
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(100,100);
    glutCreateWindow("Project 3 Rapson and London");
    
    init();
    glutDisplayFunc(display);
    //    glutReshapeFunc(reshape);
    glutIdleFunc(display);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardFunc(processNormalKeys);
    
    glEnable(GL_DEPTH_TEST);
    
    glutMainLoop();
    return 0;
}