#ifndef G53GRA_FRAMEWORK_Tele_H
#define G53GRA_FRAMEWORK_Tele_H

#include "DisplayableObject.h"
#include "Animation.h"
#include "Input.h"


class Tele :
    public DisplayableObject,
    public Animation,
    public Input
{
public:
    Tele(GLuint baseTexture, GLuint cylinderTexture);
    ~Tele() {};
    void Display();
    void Update(const double& deltaTime);
    void HandleKey(unsigned char key, int state, int mx, int my);
private:
    GLuint baseTexture, cylinderTexture;
protected:
    float _rotation, _velocity;
};


#endif
