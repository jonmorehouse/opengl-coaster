// load classes
#include "classes/state.hpp" // basic state of the application this is a global variable
#include "classes/controller.hpp" //basic controller of the application

// load modules 
#include "modules/application.hpp"//initialize basic application handling -- this is modularized so that our world can be controlled from outside of the actual controller singleton class
// #include "modules/interaction.hpp" //responsible for handling user interaction

// include application code base / namespaces
#include <stdlib.h>
#include <vector>//store splines in vector in our controller class
#include <OpenGL/gl.h>//initialize gl interfaces 
#include <OpenGL/glu.h>//initialize gl ui
#include <GLUT/glut.h>//initialize gl user interaction libraries
#include <pic.h>//initialize pic librar

// initialize a global state object
// keep this in memory for speed
application::State * state = new application::State();//this is the global state object 
application::Controller * controller;

// initialize main functionality etc
int main (int argc, char ** argv) {

  // 
  char track[10] = "track.txt";

  // send controller init a state pointer and pointer to spline vector
  controller = new application::Controller(application::loadSplines(track), state);//initialize the application controller with the proper state as well as the proper vector of splines

  // set up the initializer function for glut
  glutInit(&argc, argv);

  // initialize double buffer element
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGBA);

  // set up the window size 
  glutInitWindowSize(state->getScreenWidth(), state->getScreenHeight());

  // set the window position
  // could initialize this later to have the state class get the full screen or something?
  glutInitWindowPosition(100, 100);

  // name the window etc ... 
  glutCreateWindow("RollerCoaster");

  // set up the main display function
  glutDisplayFunc(application::display);

  // set the various callbacks for the interaction with opengl
  glutIdleFunc(application::idle);
  // glutSpecialFunc(interaction::keyPress);//enable the keypress handling

  // enable our mouse drag function for controlling the heightfield image
  // glutMotionFunc(interaction::mousedrag);
  // glutPassiveMotionFunc(interaction::mouseidle);
  // glutMouseFunc(interaction::mousebutton);

  // enable 3d buffering / z-buffer
  glEnable(GL_DEPTH_TEST);
  // enable point size for this particular program
  // glEnable(GL_PROGRAM_POINT_SIZE);

  // going to assume that we are using the default reshape function
  // just need our viewport set to 0,0,w,h
  // now enter the main glut loop 
  glutMainLoop();
}