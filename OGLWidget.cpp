#include "OGLWidget.hpp"

#include <iostream>

OGLWidget::OGLWidget(QWidget *parent)
    : QOpenGLWidget(parent)
{
    std::cout << "Construct OGLWidget\n";
}

void OGLWidget::initializeGL()
{
    initializeOpenGLFunctions();
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    //glColorMaterial(GL_AMBIENT_AND_DIFFUSE);
    //glColorMaterial(GL_FRONT_AND_BACK | GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_COLOR_MATERIAL);
}

void OGLWidget::paintGL()
{
    // if contect needs to be implemented in other place
    //QOpenGLFunctions_3_2_Compatibility *fa = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_3_2_Compatibility>();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw a line
    glBegin(GL_LINES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(1.0f, 0.0f, 0.0f); 
    glEnd();

    // draw a triangle
    glBegin(GL_TRIANGLES);
    glColor3f(0.0f, 0.0f, 1.0f);
    glVertex3f(0.5f, 0.0, 0.0f);
    glVertex3f(0.0f, -0.5, 0.0f); 
    glVertex3f(-0.5f, 0.0, 0.0f);
    glEnd();
}

void OGLWidget::resizeGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
