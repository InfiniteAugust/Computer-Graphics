#include "MyScene.h"
#include "Link.h"
#include "SunLight.h"
#include "Board.h"
#include "Sphere.h"
#include "Tele.h"
#include "Chair.h"

MyScene::MyScene(int argc, char** argv, const char *title, const int& windowWidth, const int& windowHeight)
	: Scene(argc, argv, title, windowWidth, windowHeight)
{

}

void MyScene::Initialise()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
	//four meteors
	Link *link1 = new Link(5.0f, 5.0f, "../Textures/meteor.bmp");
	link1->position(100.0f, 100.9f, -400.0f);
	link1->size(8.0f);
    
    Link *link2 = new Link(5.0f, 5.0f, "../Textures/meteor.bmp");
    link2->position(150.0f, 120.9f, -320.0f);
    link2->size(9.0f);
    
    Link *link3 = new Link(5.0f, 5.0f, "../Textures/meteor.bmp");
    link3->position(0.0f, 170.9f, -200.0f);
    link3->size(8.0f);
    
    Link *link4 = new Link(5.0f, 5.0f, "../Textures/meteor.bmp");
    link4->position(-10.0f, 230.9f, -230.0f);
    link4->size(12.0f);

    //the floor
	Board *board = new Board(20, 20, "../Textures/board.bmp");
    board->position(0.0f, -100.0f, 100.0f);
    board->size(900.0f);
    
    //celestial sphere
    Sphere *sphere = new Sphere("../Textures/starmap.bmp");
    sphere->size(600.0f);
    sphere-> SetResolution(10);
    
    //outer sphere, i.e., the milky way as background
    Sphere *sphere1 = new Sphere("../Textures/mw.bmp");
    sphere1->size(605.0f);
    sphere1-> SetResolution(10);
    
    //textures for the telescope
    GLuint baseTexture = Scene::GetTexture("../Textures/metal.bmp");
    GLuint cylinderTexture = Scene::GetTexture("../Textures/telescope.bmp");
    Tele* t = new Tele(baseTexture, cylinderTexture);
    t->size(8);
    t->position(150.0f, 0.0f, -100.0f);

    //add light
	SunLight *sl = new SunLight();
	sl->direction(0.0f, -1.0f, 0.0f);

    //chairs
    Chair *ch1 = new Chair();
    ch1 -> position(-175,-100,-100);
    
    Chair *ch2 = new Chair();
    ch2 -> position(-80,-100,-110);
    
    //add all to scene
    AddObjectToScene(sphere);
    AddObjectToScene(sphere1);
    AddObjectToScene(ch1);
    AddObjectToScene(ch2);
	AddObjectToScene(board);
	AddObjectToScene(link1);
    AddObjectToScene(link2);
    AddObjectToScene(link3);
    AddObjectToScene(link4);
    AddObjectToScene(t);
	AddObjectToScene(sl);
}

void MyScene::Projection()
{
	gluPerspective(static_cast<GLdouble>(60.0), static_cast<GLdouble>(windowWidth) / static_cast<GLdouble>(windowHeight), static_cast<GLdouble>(1.0), static_cast<GLdouble>(1000.0));
}
