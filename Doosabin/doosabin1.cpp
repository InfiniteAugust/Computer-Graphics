#include <stdio.h>  
#define GLUT_DISABLE_ATEXIT_HACK 
#define GL_SILENCE_DEPRECATION 
#include <GLUT/GLUT.h>  
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

GLfloat angle = 0;

float halfLength = 1.0f; 
glm::vec3 v1[24];  //vertices for cube after first round of division 
//vertices of the original cube 
glm::vec3 v[] = {
    { halfLength, halfLength, halfLength },
    { halfLength, halfLength, -halfLength },
    { halfLength, -halfLength, halfLength },
    { halfLength, -halfLength, -halfLength },
    { -halfLength, halfLength, halfLength },
    { -halfLength, halfLength, -halfLength },
    { -halfLength, -halfLength, halfLength },
    { -halfLength, -halfLength, -halfLength },
};
//faces of the cube, composed of ordinal number of v[]
int f[6][4] = {{1, 0, 4, 5}, {2, 3 ,7, 6}, {5, 4, 6, 7}, {0, 1, 3, 2}, {1, 5, 7, 3}, {4, 0, 2, 6}};

void doosabin1(){
	int ord = 0;
	for (int i = 0; i < 6; i++)  //for each face of the cube
	{
		for (int j = 0; j < 4; j++)  //for each vertex of the face
		{
			//x-axis
			v1[ord][0] = v[f[i][j%4]][0]*9/16 + v[f[i][(j+1)%4]][0]*3/16 + v[f[i][(j+2)%4]][0]*1/16 + v[f[i][(j+3)%4]][0]*3/16;
			//y-axis
			v1[ord][1] = v[f[i][j%4]][1]*9/16 + v[f[i][(j+1)%4]][1]*3/16 + v[f[i][(j+2)%4]][1]*1/16 + v[f[i][(j+3)%4]][1]*3/16;
			//z-axis
			v1[ord][2] = v[f[i][j%4]][2]*9/16 + v[f[i][(j+1)%4]][2]*3/16 + v[f[i][(j+2)%4]][2]*1/16 + v[f[i][(j+3)%4]][2]*3/16;
			ord++;	
		}	
	}
}
  
void display(void)  
{  

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
    glMatrixMode(GL_MODELVIEW);  
    glLoadIdentity();  
	glRotatef(angle,1.0f,2.0f,0.0f);  

    //F-faces
    glBegin(GL_QUADS);
    glColor3ub(228, 69, 147);
    for (int i = 0; i < 24; ++i)
    	glVertex3fv(value_ptr(v1[i]));
    glEnd();

    //E-faces
    glBegin(GL_QUADS);
	glColor3ub(0, 150, 150);
    glVertex3fv(value_ptr(v1[0]));
    glVertex3fv(value_ptr(v1[3]));
    glVertex3fv(value_ptr(v1[17]));
    glVertex3fv(value_ptr(v1[16]));

    glVertex3fv(value_ptr(v1[0]));
    glVertex3fv(value_ptr(v1[1]));
    glVertex3fv(value_ptr(v1[12]));
    glVertex3fv(value_ptr(v1[13]));

    glVertex3fv(value_ptr(v1[1]));
    glVertex3fv(value_ptr(v1[2]));
    glVertex3fv(value_ptr(v1[20]));
    glVertex3fv(value_ptr(v1[21]));

    glVertex3fv(value_ptr(v1[2]));
    glVertex3fv(value_ptr(v1[3]));
    glVertex3fv(value_ptr(v1[8]));
    glVertex3fv(value_ptr(v1[9]));

    glVertex3fv(value_ptr(v1[21]));
    glVertex3fv(value_ptr(v1[12]));
    glVertex3fv(value_ptr(v1[15]));
    glVertex3fv(value_ptr(v1[22]));

    glVertex3fv(value_ptr(v1[13]));
    glVertex3fv(value_ptr(v1[16]));
    glVertex3fv(value_ptr(v1[19]));
    glVertex3fv(value_ptr(v1[14]));

    glVertex3fv(value_ptr(v1[17]));
    glVertex3fv(value_ptr(v1[8]));
    glVertex3fv(value_ptr(v1[11]));
    glVertex3fv(value_ptr(v1[18]));

    glVertex3fv(value_ptr(v1[9]));
    glVertex3fv(value_ptr(v1[10]));
    glVertex3fv(value_ptr(v1[23]));
    glVertex3fv(value_ptr(v1[20]));

    glVertex3fv(value_ptr(v1[23]));
    glVertex3fv(value_ptr(v1[22]));
    glVertex3fv(value_ptr(v1[4]));
    glVertex3fv(value_ptr(v1[7]));

    glVertex3fv(value_ptr(v1[4]));
    glVertex3fv(value_ptr(v1[5]));
    glVertex3fv(value_ptr(v1[14]));
    glVertex3fv(value_ptr(v1[15]));

    glVertex3fv(value_ptr(v1[5]));
    glVertex3fv(value_ptr(v1[6]));
    glVertex3fv(value_ptr(v1[18]));
    glVertex3fv(value_ptr(v1[19]));

    glVertex3fv(value_ptr(v1[7]));
    glVertex3fv(value_ptr(v1[6]));
    glVertex3fv(value_ptr(v1[11]));
    glVertex3fv(value_ptr(v1[10]));
    glEnd();

     //V-faces
    glBegin(GL_TRIANGLES);
    glColor3ub(30, 100, 200);
    glVertex3fv(value_ptr(v1[1]));
    glVertex3fv(value_ptr(v1[12]));
    glVertex3fv(value_ptr(v1[21]));

    glVertex3fv(value_ptr(v1[0]));
    glVertex3fv(value_ptr(v1[13]));
    glVertex3fv(value_ptr(v1[16]));

    glVertex3fv(value_ptr(v1[3]));
    glVertex3fv(value_ptr(v1[17]));
    glVertex3fv(value_ptr(v1[8]));

    glVertex3fv(value_ptr(v1[2]));
    glVertex3fv(value_ptr(v1[9]));
    glVertex3fv(value_ptr(v1[20]));

    glVertex3fv(value_ptr(v1[7]));
    glVertex3fv(value_ptr(v1[23]));
    glVertex3fv(value_ptr(v1[10]));

    glVertex3fv(value_ptr(v1[6]));
    glVertex3fv(value_ptr(v1[11]));
    glVertex3fv(value_ptr(v1[18]));

    glVertex3fv(value_ptr(v1[5]));
    glVertex3fv(value_ptr(v1[14]));
    glVertex3fv(value_ptr(v1[19]));

    glVertex3fv(value_ptr(v1[4]));
    glVertex3fv(value_ptr(v1[22]));
    glVertex3fv(value_ptr(v1[15]));
    glEnd();

    glutSwapBuffers(); 
    angle += 1; 
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
    glutCreateWindow("Doo-sabin1");  
   	init(); 
   	doosabin1();
    glutDisplayFunc(display);  
    glutIdleFunc(display);
	glutReshapeFunc(reshape);  
    glutMainLoop();  
    return 0;
}
