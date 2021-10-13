#include <stdio.h>  
#define GLUT_DISABLE_ATEXIT_HACK 
#define GL_SILENCE_DEPRECATION 
#include <GLUT/GLUT.h>  
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
 
GLfloat angle = 0;
//vertices for cube after second round of division  
glm::vec3 v2[96];  

//24 vertices for cube after first round of division
glm::vec3 v1[] = {
    {0.5, 1, -0.5}, {0.5, 1, 0.5}, {-0.5, 1, 0.5}, {-0.5, 1, -0.5},
    {0.5, -1, 0.5}, {0.5, -1, -0.5}, {-0.5, -1, -0.5}, {-0.5, -1, 0.5},
    {-1, 0.5, -0.5}, {-1, 0.5, 0.5}, {-1, -0.5, 0.5}, {-1, -0.5, -0.5},
    {1, 0.5, 0.5}, {1, 0.5, -0.5}, {1, -0.5, -0.5}, {1, -0.5, 0.5},
    {0.5, 0.5, -1}, {-0.5, 0.5, -1}, {-0.5, -0.5, -1}, {0.5, -0.5, -1},
    {-0.5, 0.5, 1}, {0.5, 0.5, 1}, {0.5, -0.5, 1}, {-0.5, -0.5, 1}
};
//faces of the cube after initial division represented by ordinal number of vertices in v1
int ff[6][4] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}, {12,13,14,15}, {16,17,18,19}, {20,21,22,23}};
int ef[12][4] = {
    {1,2,20,21}, {0,3,17,16}, {0,1,12,13}, {2,3,8,9},
    {21,12,15,22}, {13,16,19,14}, {17,8,11,18}, {9,10,23,20},
    {23,22,4,7},{4,5,14,15},{5,6,18,19},{6,7,10,11}
};
int vf[8][3] = {
    {1,12,21},{0,13,16},{3,17,8},{2,9,20},
    {7,23,10},{6,11,18},{5,14,19},{4,22,15}
};

void doosabin2(){
	int ord = 0;
    //for each F-face of the cube
	for (int i = 0; i < 6; i++)  
	{
		for (int j = 0; j < 4; j++)  //for each vertex of the face
		{
			//x-axis
			v2[ord][0] = v1[ff[i][j%4]][0]*9/16 + v1[ff[i][(j+1)%4]][0]*3/16 + v1[ff[i][(j+2)%4]][0]*1/16 + v1[ff[i][(j+3)%4]][0]*3/16;
			//y-axis
			v2[ord][1] = v1[ff[i][j%4]][1]*9/16 + v1[ff[i][(j+1)%4]][1]*3/16 + v1[ff[i][(j+2)%4]][1]*1/16 + v1[ff[i][(j+3)%4]][1]*3/16;
			//z-axis
			v2[ord][2] = v1[ff[i][j%4]][2]*9/16 + v1[ff[i][(j+1)%4]][2]*3/16 + v1[ff[i][(j+2)%4]][2]*1/16 + v1[ff[i][(j+3)%4]][2]*3/16;
			ord++;	
		}	
	}

    //for each E-face of the cube 
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //x-axis
            v2[ord][0] = v1[ef[i][j%4]][0]*9/16 + v1[ef[i][(j+1)%4]][0]*3/16 + v1[ef[i][(j+2)%4]][0]*1/16 + v1[ef[i][(j+3)%4]][0]*3/16;
            //y-axis
            v2[ord][1] = v1[ef[i][j%4]][1]*9/16 + v1[ef[i][(j+1)%4]][1]*3/16 + v1[ef[i][(j+2)%4]][1]*1/16 + v1[ef[i][(j+3)%4]][1]*3/16;
            //z-axis
            v2[ord][2] = v1[ef[i][j%4]][2]*9/16 + v1[ef[i][(j+1)%4]][2]*3/16 + v1[ef[i][(j+2)%4]][2]*1/16 + v1[ef[i][(j+3)%4]][2]*3/16;
            ord++;
        }
    }

    //for each V-face of the cube 
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            //x-axis
            v2[ord][0] = v1[vf[i][j%3]][0]*14/24 + v1[vf[i][(j+1)%3]][0]*5/24 + v1[vf[i][(j+2)%3]][0]*5/24;
            //y-axis
            v2[ord][1] = v1[vf[i][j%3]][1]*14/24 + v1[vf[i][(j+1)%3]][1]*5/24 + v1[vf[i][(j+2)%3]][1]*5/24;
            //z-axis
            v2[ord][2] = v1[vf[i][j%3]][2]*14/24 + v1[vf[i][(j+1)%3]][2]*5/24 + v1[vf[i][(j+2)%3]][2]*5/24;
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
    glColor3ub(30, 100, 200);
    for (int i = 0; i < 24; i++)
        glVertex3fv(value_ptr(v2[i]));

    for (int j = 24; j < 72; j++)
        glVertex3fv(value_ptr(v2[j]));
    glEnd();

    glBegin(GL_TRIANGLES);
    for (int k = 72; k < 96; k++)
        glVertex3fv(value_ptr(v2[k]));
    glEnd();

    //stripes 
    glBegin(GL_QUAD_STRIP);
    glColor3ub(0, 150, 150);
    glVertex3fv(value_ptr(v2[1]));
    glVertex3fv(value_ptr(v2[2]));
    glVertex3fv(value_ptr(v2[24]));
    glVertex3fv(value_ptr(v2[25]));
    glVertex3fv(value_ptr(v2[27]));
    glVertex3fv(value_ptr(v2[26]));
    glVertex3fv(value_ptr(v2[21]));
    glVertex3fv(value_ptr(v2[20]));
    glVertex3fv(value_ptr(v2[22]));
    glVertex3fv(value_ptr(v2[23]));
    glVertex3fv(value_ptr(v2[57]));
    glVertex3fv(value_ptr(v2[56]));
    glVertex3fv(value_ptr(v2[58]));
    glVertex3fv(value_ptr(v2[59]));
    glVertex3fv(value_ptr(v2[4]));
    glVertex3fv(value_ptr(v2[7]));
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3fv(value_ptr(v2[1]));
    glVertex3fv(value_ptr(v2[0]));
    glVertex3fv(value_ptr(v2[33]));
    glVertex3fv(value_ptr(v2[32]));
    glVertex3fv(value_ptr(v2[34]));
    glVertex3fv(value_ptr(v2[35]));
    glVertex3fv(value_ptr(v2[12]));
    glVertex3fv(value_ptr(v2[13]));
    glVertex3fv(value_ptr(v2[15]));
    glVertex3fv(value_ptr(v2[14]));
    glVertex3fv(value_ptr(v2[63]));
    glVertex3fv(value_ptr(v2[62]));
    glVertex3fv(value_ptr(v2[60]));
    glVertex3fv(value_ptr(v2[61]));
    glVertex3fv(value_ptr(v2[4]));
    glVertex3fv(value_ptr(v2[5]));
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3fv(value_ptr(v2[0]));
    glVertex3fv(value_ptr(v2[3]));
    glVertex3fv(value_ptr(v2[28]));
    glVertex3fv(value_ptr(v2[29]));
    glVertex3fv(value_ptr(v2[31]));
    glVertex3fv(value_ptr(v2[30]));
    glVertex3fv(value_ptr(v2[16]));
    glVertex3fv(value_ptr(v2[17]));
    glVertex3fv(value_ptr(v2[18]));
    glVertex3fv(value_ptr(v2[19]));
    glVertex3fv(value_ptr(v2[66]));
    glVertex3fv(value_ptr(v2[67]));
    glVertex3fv(value_ptr(v2[65]));
    glVertex3fv(value_ptr(v2[64]));
    glVertex3fv(value_ptr(v2[6]));
    glVertex3fv(value_ptr(v2[5]));
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3fv(value_ptr(v2[2]));
    glVertex3fv(value_ptr(v2[3]));
    glVertex3fv(value_ptr(v2[36]));
    glVertex3fv(value_ptr(v2[37]));
    glVertex3fv(value_ptr(v2[39]));
    glVertex3fv(value_ptr(v2[38]));
    glVertex3fv(value_ptr(v2[9]));
    glVertex3fv(value_ptr(v2[8]));
    glVertex3fv(value_ptr(v2[10]));
    glVertex3fv(value_ptr(v2[11]));
    glVertex3fv(value_ptr(v2[70]));
    glVertex3fv(value_ptr(v2[71]));
    glVertex3fv(value_ptr(v2[69]));
    glVertex3fv(value_ptr(v2[68]));
    glVertex3fv(value_ptr(v2[7]));
    glVertex3fv(value_ptr(v2[6]));
    glEnd();

//sides 
    glBegin(GL_QUAD_STRIP);
    glColor3ub(228, 69, 147);
    glVertex3fv(value_ptr(v2[1]));
    glVertex3fv(value_ptr(v2[33]));
    glVertex3fv(value_ptr(v2[24]));
    glVertex3fv(value_ptr(v2[72]));
    glVertex3fv(value_ptr(v2[27]));
    glVertex3fv(value_ptr(v2[74]));
    glVertex3fv(value_ptr(v2[21]));
    glVertex3fv(value_ptr(v2[40]));
    glVertex3fv(value_ptr(v2[22]));
    glVertex3fv(value_ptr(v2[43]));
    glVertex3fv(value_ptr(v2[57]));
    glVertex3fv(value_ptr(v2[94]));
    glVertex3fv(value_ptr(v2[58]));
    glVertex3fv(value_ptr(v2[93]));
    glVertex3fv(value_ptr(v2[4]));
    glVertex3fv(value_ptr(v2[60]));
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3fv(value_ptr(v2[72]));
    glVertex3fv(value_ptr(v2[33]));
    glVertex3fv(value_ptr(v2[73]));
    glVertex3fv(value_ptr(v2[34]));
    glVertex3fv(value_ptr(v2[41]));
    glVertex3fv(value_ptr(v2[12]));
    glVertex3fv(value_ptr(v2[42]));
    glVertex3fv(value_ptr(v2[15]));
    glVertex3fv(value_ptr(v2[95]));
    glVertex3fv(value_ptr(v2[63]));
    glVertex3fv(value_ptr(v2[93]));
    glVertex3fv(value_ptr(v2[60]));
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3fv(value_ptr(v2[0]));
    glVertex3fv(value_ptr(v2[28]));
    glVertex3fv(value_ptr(v2[32]));
    glVertex3fv(value_ptr(v2[75]));
    glVertex3fv(value_ptr(v2[35]));
    glVertex3fv(value_ptr(v2[76]));
    glVertex3fv(value_ptr(v2[13]));
    glVertex3fv(value_ptr(v2[44]));
    glVertex3fv(value_ptr(v2[14]));
    glVertex3fv(value_ptr(v2[47]));
    glVertex3fv(value_ptr(v2[62]));
    glVertex3fv(value_ptr(v2[91]));
    glVertex3fv(value_ptr(v2[61]));
    glVertex3fv(value_ptr(v2[90]));
    glVertex3fv(value_ptr(v2[5]));
    glVertex3fv(value_ptr(v2[64]));
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3fv(value_ptr(v2[28]));
    glVertex3fv(value_ptr(v2[75]));
    glVertex3fv(value_ptr(v2[31]));
    glVertex3fv(value_ptr(v2[77]));
    glVertex3fv(value_ptr(v2[16]));
    glVertex3fv(value_ptr(v2[45]));
    glVertex3fv(value_ptr(v2[19]));
    glVertex3fv(value_ptr(v2[46]));
    glVertex3fv(value_ptr(v2[67]));
    glVertex3fv(value_ptr(v2[92]));
    glVertex3fv(value_ptr(v2[64]));
    glVertex3fv(value_ptr(v2[90]));
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3fv(value_ptr(v2[3]));
    glVertex3fv(value_ptr(v2[37]));
    glVertex3fv(value_ptr(v2[29]));
    glVertex3fv(value_ptr(v2[78]));
    glVertex3fv(value_ptr(v2[30]));
    glVertex3fv(value_ptr(v2[79]));
    glVertex3fv(value_ptr(v2[17]));
    glVertex3fv(value_ptr(v2[48]));
    glVertex3fv(value_ptr(v2[18]));
    glVertex3fv(value_ptr(v2[51]));
    glVertex3fv(value_ptr(v2[66]));
    glVertex3fv(value_ptr(v2[89]));
    glVertex3fv(value_ptr(v2[65]));
    glVertex3fv(value_ptr(v2[87]));
    glVertex3fv(value_ptr(v2[6]));
    glVertex3fv(value_ptr(v2[68]));
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3fv(value_ptr(v2[78]));
    glVertex3fv(value_ptr(v2[37]));
    glVertex3fv(value_ptr(v2[80]));
    glVertex3fv(value_ptr(v2[38]));
    glVertex3fv(value_ptr(v2[49]));
    glVertex3fv(value_ptr(v2[8]));
    glVertex3fv(value_ptr(v2[50]));
    glVertex3fv(value_ptr(v2[11]));
    glVertex3fv(value_ptr(v2[88]));
    glVertex3fv(value_ptr(v2[71]));
    glVertex3fv(value_ptr(v2[87]));
    glVertex3fv(value_ptr(v2[68]));
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3fv(value_ptr(v2[2]));
    glVertex3fv(value_ptr(v2[25]));
    glVertex3fv(value_ptr(v2[36]));
    glVertex3fv(value_ptr(v2[81]));
    glVertex3fv(value_ptr(v2[39]));
    glVertex3fv(value_ptr(v2[82]));
    glVertex3fv(value_ptr(v2[9]));
    glVertex3fv(value_ptr(v2[52]));
    glVertex3fv(value_ptr(v2[10]));
    glVertex3fv(value_ptr(v2[53]));
    glVertex3fv(value_ptr(v2[70]));
    glVertex3fv(value_ptr(v2[86]));
    glVertex3fv(value_ptr(v2[69]));
    glVertex3fv(value_ptr(v2[84]));
    glVertex3fv(value_ptr(v2[7]));
    glVertex3fv(value_ptr(v2[59]));
    glEnd();

    glBegin(GL_QUAD_STRIP);
    glVertex3fv(value_ptr(v2[81]));
    glVertex3fv(value_ptr(v2[25]));
    glVertex3fv(value_ptr(v2[83]));
    glVertex3fv(value_ptr(v2[26]));
    glVertex3fv(value_ptr(v2[55]));
    glVertex3fv(value_ptr(v2[20]));
    glVertex3fv(value_ptr(v2[54]));
    glVertex3fv(value_ptr(v2[23]));
    glVertex3fv(value_ptr(v2[85]));
    glVertex3fv(value_ptr(v2[56]));
    glVertex3fv(value_ptr(v2[84]));
    glVertex3fv(value_ptr(v2[59]));
    glEnd();

    //other
    glBegin(GL_QUADS);
    glColor3ub(169, 102, 194);
    glVertex3fv(value_ptr(v2[74]));
    glVertex3fv(value_ptr(v2[73]));
    glVertex3fv(value_ptr(v2[41]));
    glVertex3fv(value_ptr(v2[40]));

    glVertex3fv(value_ptr(v2[76]));
    glVertex3fv(value_ptr(v2[77]));
    glVertex3fv(value_ptr(v2[45]));
    glVertex3fv(value_ptr(v2[44]));

    glVertex3fv(value_ptr(v2[80]));
    glVertex3fv(value_ptr(v2[79]));
    glVertex3fv(value_ptr(v2[48]));
    glVertex3fv(value_ptr(v2[49]));

    glVertex3fv(value_ptr(v2[82]));
    glVertex3fv(value_ptr(v2[83]));
    glVertex3fv(value_ptr(v2[55]));
    glVertex3fv(value_ptr(v2[52]));

    glVertex3fv(value_ptr(v2[91]));
    glVertex3fv(value_ptr(v2[92]));
    glVertex3fv(value_ptr(v2[46]));
    glVertex3fv(value_ptr(v2[47]));

    glVertex3fv(value_ptr(v2[94]));
    glVertex3fv(value_ptr(v2[95]));
    glVertex3fv(value_ptr(v2[42]));
    glVertex3fv(value_ptr(v2[43]));

    glVertex3fv(value_ptr(v2[85]));
    glVertex3fv(value_ptr(v2[86]));
    glVertex3fv(value_ptr(v2[53]));
    glVertex3fv(value_ptr(v2[54]));

    glVertex3fv(value_ptr(v2[88]));
    glVertex3fv(value_ptr(v2[89]));
    glVertex3fv(value_ptr(v2[51]));
    glVertex3fv(value_ptr(v2[50]));
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
    glutCreateWindow("Doo-sabin2");  
   	init(); 
   	doosabin2();
    glutDisplayFunc(display); 
    glutIdleFunc(display); 
	glutReshapeFunc(reshape);  
    glutMainLoop();  
    return 0;
}
