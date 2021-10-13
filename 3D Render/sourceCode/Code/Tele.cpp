#include "Tele.h"
#include "math.h"

Tele::Tele(GLuint baseTexture, GLuint cylinderTexture):
baseTexture(baseTexture), cylinderTexture(cylinderTexture), _rotation(0.0f), _velocity(0.0f) {
    
}

void rectangle(float x, float y) {
    glDisable(GL_CULL_FACE);
    glBegin(GL_QUADS);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glTexCoord2f(0.0, 0.0);
    glVertex2f(0, 0);
    glTexCoord2f(0.0, 1.0);
    glVertex2f(0, y);
    glTexCoord2f(1.0, 1.0);
    glVertex2f(x, y);
    glTexCoord2f(1.0, 0.0);
    glVertex2f(x, 0);

    glEnd();
    glEnable(GL_CULL_FACE);
}

void cylinder(float h, float tr, float br) {
    float res = 0.1f * M_PI;
    float x, z;
    float progress;
    float ratio = tr / br;

    glBegin(GL_QUAD_STRIP);
    for (float t = 0.f; t <= 2 * M_PI; t += res)
    {
        progress = t / (2 * M_PI);
        x = br*cos(t);
        z = br*sin(t);

        glNormal3f(x, 0, z);

        glTexCoord2f(progress, 0);
        glVertex3f(x, 0.f, z);
        glTexCoord2f(progress, 1);
        glVertex3f(x * ratio, h, z * ratio);
    }

    glNormal3f(0, 0, -1);
    glTexCoord2f(1, 0);
    glVertex3f(br, 0.f, 0.f);
    glTexCoord2f(1, 1);
    glVertex3f(tr, h, 0.f);
    glEnd();
}

void drawBase() {
    glMatrixMode(GL_MODELVIEW);
    glRotatef(30.0, 0.0, 0.0, 1.0);
    rectangle(1, -30);
    glRotatef(-60.0, 0.0, 0.0, 1.0);
    rectangle(1, -30);
    glRotatef(20.0, 0.0, 0.0, 1.0);
    rectangle(1, -30);
}
void drawCylinder() {
    glTranslated(-3, 0, 0);
    glRotated(-60, 0, 0, 1);
    cylinder(20, 2, 2);
    
}

void Tele::Update(const double& deltaTime) {
    pos[0] += static_cast<float>(deltaTime) * _velocity;
    pos[2] += static_cast<float>(deltaTime) * _rotation;
}

void Tele::HandleKey(unsigned char key, int state, int mx, int my) {
    switch (key)
    {
        case 'i':
        case 'I':
            _rotation = 10.0f;
            break;
        case 'k':
        case 'K':
            _rotation = -10.0f;
            break;
        case 'l':
        case 'L':
            _velocity = 10.0f;
            break;
        case 'j':
        case 'J':
            _velocity = -10.0f;
            
            break;
    }
}

void Tele::Display() {
    glPushMatrix();
    glPushAttrib(GL_ALL_ATTRIB_BITS);

    glTranslatef(pos[0], pos[1], pos[2]);
    glScalef(scale[0], scale[1], scale[2]);

    glRotatef(5.0, 0.0, 0.0, 1.0);


    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, baseTexture);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);

    drawBase();

    glBindTexture(GL_TEXTURE_2D, cylinderTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
    glGenerateMipmap(GL_TEXTURE_2D);

    drawCylinder();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
    glPopAttrib();
}
