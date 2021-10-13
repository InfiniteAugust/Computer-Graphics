#include <stdio.h>  
#define GLUT_DISABLE_ATEXIT_HACK 
#define GL_SILENCE_DEPRECATION 
#include <GLUT/GLUT.h>  

float angle = 0.0;
void drawSphere(){
	glColor3ub(170, 170, 170);
	glutSolidSphere(0.15f, 10, 10);
}

void drawCylinder(){
    GLUquadric *p; 
    p = gluNewQuadric();
	glColor3ub(150, 150, 150);
    gluCylinder(p, 0.1f, 0.1f, 1.0f, 10, 10);
}

void drawBlade(){
	glColor3ub(169, 102, 194);
    glTranslatef(0.0f, 0.4f, 0.0f);
    glScalef(1.0f,7.0f,5.0f);
	glutSolidCube(0.1f);
}

void display(void)  
{  
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glMatrixMode(GL_MODELVIEW); 

    glLoadIdentity(); 
	drawSphere();

    glPushMatrix();
    glTranslatef(0.0f,-1.0f,0.0f);
    glRotatef(90, -1.0, 0.0, 0.0);
	drawCylinder();
	glPopMatrix();

    glPushMatrix();
    glRotatef(angle, 0.0, 0.0, 1.0);
	drawBlade();
    glPopMatrix();

    glPushMatrix();
    glRotatef(120+angle, 0.0, 0.0, 1.0);
    drawBlade();
    glPopMatrix();

    glPushMatrix();
    glRotatef(240+angle, 0.0, 0.0, 1.0);
    drawBlade();
    glPopMatrix();

    glutSwapBuffers(); 
    angle += 1.2;
}

void reshape(int w, int h)  
{  
    GLfloat aspect = (GLfloat)w / (GLfloat)h;  
    GLfloat nRange = 2.0f;  
    glViewport(0,0,w,h);  
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();  
    if (w<=h)  
    {   glOrtho(-nRange, nRange, -nRange * aspect, nRange * aspect, -nRange, nRange);  }   
    else  
    {  glOrtho(-nRange, nRange, -nRange / aspect, nRange / aspect, -nRange, nRange);  }  
}  

void init()  
{    
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);  
    glEnable(GL_DEPTH_TEST);  
    glEnable(GL_DITHER);  
    glShadeModel(GL_SMOOTH);  
}  

int main(int argc,char* argv[])
{  
    glutInit(&argc,argv);  
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  
    glutInitWindowSize(500,500);  
    glutCreateWindow("windmill");  
   	init(); 
   	glutDisplayFunc(display); 
   	glutIdleFunc(display);      
    glutReshapeFunc(reshape);  
    glutMainLoop();
    return 0;
}