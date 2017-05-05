/*
    My First OpenGL code
    Author: Joshua Aditya Kosasih
*/
#ifdef __APPLE__

#else
#include <GL/glut.h>
#endif // __APPLE__

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string>
#include <gl/gl.h>
#include <gl/glext.h>
#include "SOIL.h"

float counter = 0.0;
GLuint tex_ID;

float tex_u_max = 1.0f;//0.2f;
float tex_v_max = 1.0f;//0.2f;
const float ref_mag = 0.1f;

void loadTexture(std::string load_me) {
    tex_ID = SOIL_load_OGL_texture(
        load_me.c_str(),
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_POWER_OF_TWO
        | SOIL_FLAG_MIPMAPS
        //| SOIL_FLAG_MULTIPLY_ALPHA
        //| SOIL_FLAG_COMPRESS_TO_DXT
        | SOIL_FLAG_DDS_LOAD_DIRECT
        //| SOIL_FLAG_NTSC_SAFE_RGB
        //| SOIL_FLAG_CoCg_Y
        //| SOIL_FLAG_TEXTURE_RECTANGLE
        );
    if( tex_ID > 0 )
    {
        glEnable( GL_TEXTURE_2D );
        glBindTexture( GL_TEXTURE_2D, tex_ID );
        std::cout << "the loaded texture ID was " << tex_ID << std::endl;
    } else
    {
        glDisable( GL_TEXTURE_2D );
        std::cout << "Texture loading failed: '" << SOIL_last_result() << "'" << std::endl;
    }
}

void bindTexture(int tex_ID) {
    glBindTexture( GL_TEXTURE_2D, tex_ID );
}

float scale = 0.7;
float inc = 0.0001;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    counter += 0.05;
    scale += inc;

    if(counter > 180) {
        counter = -180;
    }
    if(scale > 1) {
        inc = -0.0001;
    }
    else if(scale < 0.5) {
        inc = 0.0001;
    }

    // kubus
    glLoadIdentity();

    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
    //glNormal3f( 0.0f, 0.0f, 1.0f );

    glScalef(scale, scale, scale);
    glRotatef(counter, 0.9, 1, 0.7);

    // White side - BACK
    bindTexture(2);

    glBegin(GL_POLYGON);
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

        glNormal3f( -ref_mag, ref_mag, 1.0f );
        glTexCoord2f( 0.0f, tex_v_max );
        glVertex3f(  0.384, -0.75, 0.055 );

        glNormal3f( -ref_mag, -ref_mag, 1.0f );
        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f(  0.384,  0.75, 0.055 );

        glNormal3f( ref_mag, -ref_mag, 1.0f );
        glTexCoord2f( tex_u_max, 0.0f );
        glVertex3f( -0.384,  0.75, 0.055 );

        glNormal3f( ref_mag, ref_mag, 1.0f );
        glTexCoord2f( tex_u_max, tex_v_max );
        glVertex3f( -0.384, -0.75, 0.055 );
    glEnd();
    // Purple side - RIGHT
    bindTexture(5);

    glBegin(GL_POLYGON);
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

        glTexCoord2f( 0.0f, tex_v_max );
        glVertex3f( 0.384, -0.75, -0.055 );

        glTexCoord2f( tex_u_max, tex_v_max );
        glVertex3f( 0.384,  0.75, -0.055 );

        glTexCoord2f( tex_u_max, 0.0f );
        glVertex3f( 0.384,  0.75,  0.055 );

        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( 0.384, -0.75,  0.055 );
    glEnd();
    // Green side - LEFT
    bindTexture(6);

    glBegin(GL_POLYGON);
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( -0.384, -0.75,  0.055 );

        glTexCoord2f( tex_u_max, 0.0f );
        glVertex3f( -0.384,  0.75,  0.055 );

        glTexCoord2f( tex_u_max, tex_v_max );
        glVertex3f( -0.384,  0.75, -0.055 );

        glTexCoord2f( 0.0f, tex_v_max );
        glVertex3f( -0.384, -0.75, -0.055 );
    glEnd();
    // Blue side - TOP
    bindTexture(3);

    glBegin(GL_POLYGON);
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

        glTexCoord2f( tex_u_max, tex_v_max );
        glVertex3f(  0.384,  0.75,  0.055 );

        glTexCoord2f( tex_u_max, 0.0f );
        glVertex3f(  0.384,  0.75, -0.055 );

        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( -0.384,  0.75, -0.055 );

        glTexCoord2f( 0.0f, tex_v_max);
        glVertex3f( -0.384,  0.75,  0.055 );
    glEnd();

    // Red side - BOTTOM
    bindTexture(4);

    glBegin(GL_POLYGON);
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

        glTexCoord2f( tex_u_max, 0.0f );
        glVertex3f(  0.384, -0.75, -0.055 );

        glTexCoord2f( tex_u_max, tex_v_max );
        glVertex3f(  0.384, -0.75,  0.055 );

        glTexCoord2f( 0.0f, tex_v_max);
        glVertex3f( -0.384, -0.75,  0.055 );

        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( -0.384, -0.75, -0.055 );
    glEnd();
    // Yellow side - FRONT
    bindTexture(1);

    glBegin(GL_POLYGON);
        glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

        glNormal3f( ref_mag, -ref_mag, 1.0f );
        glTexCoord2f( tex_u_max, tex_v_max );
        glVertex3f(  0.384, -0.75, -0.055 );

        glNormal3f( ref_mag, ref_mag, 1.0f );
        glTexCoord2f( tex_u_max, 0.0f );
        glVertex3f(  0.384,  0.75, -0.055 );

        glNormal3f( -ref_mag, ref_mag, 1.0f );
        glTexCoord2f( 0.0f, 0.0f );
        glVertex3f( -0.384,  0.75, -0.055 );

        glNormal3f( -ref_mag, -ref_mag, 1.0f );
        glTexCoord2f( 0.0f, tex_v_max );
        glVertex3f( -0.384, -0.75, -0.055 );
    glEnd();


    glFlush();
    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
}

void initOpenGL() {
    // color --- r    g    b    alpha
    glClearColor(1.0, 1.0, 1.0, 1.0);
}

int main(int argc, char **argv) {

    //start up freeglut
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("First OpenGL App");

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    initOpenGL();

    loadTexture("C:/Users/Joshua A Kosasih/z1compact/front.jpg");
    loadTexture("C:/Users/Joshua A Kosasih/z1compact/back.jpg");
    loadTexture("C:/Users/Joshua A Kosasih/z1compact/top.JPG");
    loadTexture("C:/Users/Joshua A Kosasih/z1compact/bottom.JPG");
    loadTexture("C:/Users/Joshua A Kosasih/z1compact/right.JPG");
    loadTexture("C:/Users/Joshua A Kosasih/z1compact/left.JPG");

    glutDisplayFunc(display);
    glutIdleFunc(display);

    glutReshapeFunc(reshape);

    glutMainLoop();

    return 0;
}
