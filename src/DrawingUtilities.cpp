#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <iostream>
#include <vector>
#include "globalVariables.h"
#include "DrawingUtilities.h"

void drawCuboid(GLfloat height, GLfloat width, GLfloat depth, GLfloat xc, GLfloat yc, GLfloat zc){
     ArrayOfVertices vertices = {{
            {(xc - 0.5f * width), (yc + 0.5f * height), zc}, // Top-Left (0)
            {(xc + 0.5f * width), (yc + 0.5f * height), zc}, // Top-Right (1
            {(xc + 0.5f * width), (yc - 0.5f * height), zc}, // Bottom-Right (2 
            {(xc - 0.5f * width), (yc - 0.5f * height), zc}, // Bottom-Left 3 

            {(xc - 0.5f * width), (yc + 0.5f * height), zc - depth}, // Top-Left 4 
            {(xc + 0.5f * width), (yc + 0.5f * height), zc - depth}, // Top-Right 5 
            {(xc + 0.5f * width), (yc - 0.5f * height), zc - depth}, // Bottom-Right 6 
            {(xc - 0.5f * width), (yc - 0.5f * height), zc - depth}, // Bottom-Left 7 

    }};


    glBegin(GL_QUADS);
        // glColor3f(1.0f, 0.0f, 0.0f);     // Green
        glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
        glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
        glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
        glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);

        // glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
        glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
        glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
        glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);

        // glColor3f(0.0f, 1.0f, 0.0f);     // Green
        glVertex3f(vertices[1][0], vertices[1][1], vertices[1][2]);
        glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
        glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
        glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
        //
        // glColor3f(1.0f, 0.0f, 1.0f);     // Green
        glVertex3f(vertices[2][0], vertices[2][1], vertices[2][2]);
        glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
        glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
        glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
        //
        // glColor3f(1.0f, 1.0f, 0.0f);     // Green
        glVertex3f(vertices[0][0], vertices[0][1], vertices[0][2]);
        glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
        glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
        glVertex3f(vertices[3][0], vertices[3][1], vertices[3][2]);
        //
        // glColor3f(1.0f, 1.0f, 1.0f);     // Green
        glVertex3f(vertices[4][0], vertices[4][1], vertices[4][2]);
        glVertex3f(vertices[5][0], vertices[5][1], vertices[5][2]);
        glVertex3f(vertices[6][0], vertices[6][1], vertices[6][2]);
        glVertex3f(vertices[7][0], vertices[7][1], vertices[7][2]);
    glEnd();
}


void drawLand(void) {
    // glPushMatrix(); 
    glColor3f(0.4f,0.4f,0.4f);
    glBegin(GL_LINES);
    for(GLfloat i =- 100.0f; i < 100.0f; i += 1.0f) {
        glVertex3f(-100.0f,-1.0f,i);
        glVertex3f( 100.0f,-1.0f,i);
        glVertex3f(i,-1.0f,-100.0f);
        glVertex3f(i,-1.0f,100.0f);
    }
    glEnd();
    // glPopMatrix(); 
}

// flag --> 1 (left)
// flag --> 0 (right)
void drawWindow(GLfloat flag, GLfloat xc, GLfloat yc, GLboolean rotate, GLfloat depth){
    if (flag == 1.0) flag = -1.3f;
    else flag = 2.5f;
    glPushMatrix(); 
        glTranslatef(flag * windowWidth, 0.0f, 0.0f); 
    if(rotate){
        glRotatef(windowAngle, 0.0f, 1.0f, 0.0f);     
    }
        glTranslatef(-0.5f * windowWidth, 0.0f, 0.0f); 
        drawCuboid(0.2f, 0.2f, windowDepth, xc, yc, windowDepth * depth);
    glPopMatrix();
}

void drawCylinder(float x1, float y1, float z1, float x2, float y2, float z2, float radius, float length, int slices, int stacks) {
    GLUquadric *quadric = gluNewQuadric();

    float vx = x2 - x1;
    float vy = y2 - y1;
    float vz = z2 - z1;
    float v = sqrt(vx * vx + vy * vy + vz * vz);
    float ax = 57.2957795 * acos(vz / v);
    if (vz < 0.0) {
        ax = -ax;
    }
    float rx = -vy * vz;
    float ry = vx * vz;

    glPushMatrix();
    glTranslatef(x1, y1, z1);
    glRotatef(ax, rx, ry, 0.0);
    gluQuadricOrientation(quadric, GLU_OUTSIDE);
    gluCylinder(quadric, radius, radius, length, slices, stacks);
    gluDeleteQuadric(quadric);
    glPopMatrix();
}
GLfloat radius = 5.0f;
void drawBicycle() {
    float x = radius * cos(bicycleAngle);
    float y = radius * sin(bicycleAngle);
    // Draw the wheels using torus
    // glTranslatef(0.0f, 0.0f, -bicycleAngle);

    glPushMatrix();        
        glTranslatef(x, 0.0f, y);
        // glTranslatef(-1.0f, 0.5f, -1.0f);
        // glRotatef(bicycleAngle, 0.0f, 0.0f, 1.0f);
        // rotation around the house
        glColor3f(0.5f, 0.5f, 0.5f); 

        glPushMatrix();
            glTranslatef(-0.7f, -0.5f, 0.0f);
            glutSolidTorus(0.08, 0.38, 12, 36); // Left wheel
        glPopMatrix();
        
        glPushMatrix();
            glTranslatef(0.7f, -0.5f, 0.0f);
            glutSolidTorus(0.08, 0.38, 12, 36); // Right wheel
        glPopMatrix();

        // Draw the cylinder connecting the wheels
        glPushMatrix();
            glTranslatef(-0.7f, 0.0f, -0.69f);
            glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            glColor3f(0.8f, 0.2f, 0.0f); 
            drawCylinder(-0.7f, -0.5f, 0.0f, 0.7f, -0.5f, 0.0f, 0.05f, 1.4f,  12, 12);
        glPopMatrix();

        // el gadawn
        glPushMatrix();
            glTranslatef(0.0f, 0.8f, -0.69f);
            // glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
            glColor3f(0.8f, 0.2f, 0.0f);
            drawCylinder(-0.7f, -0.5f, 0.0f, 0.7f, -0.5f, 0.0f, 0.05f, 1.2f,12, 12);
        glPopMatrix();

        // between gadawn and cylinder
        glPushMatrix();
            glTranslatef(0.0f, +0.4f, +0.5);
            glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
            glColor3f(1.0f, 1.0f, 0.0f);
            drawCylinder(-0.7f, -0.5f, 0.0f, 0.7f, -0.8f, 0.0f, 0.05f, 0.92f,12, 12);
        glPopMatrix();
    glPopMatrix();
}
