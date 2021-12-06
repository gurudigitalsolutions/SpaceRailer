////////////////////////////////////////////////////////////////////////////////
//
//	Space Railer
//
////////////////////////////////////////////////////////////////////////////////

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <iostream>

#include "main.h"
#include "input.h"
#include "scripting.h"

using namespace std;

//	Set initial dimensions for the window.  The default values here are for
//	half of a 1080 display.
short windowWidth = 960;
short windowHeight = 540;

programMode currentProgramMode = PROGRAM_BOOT;
ProgramInput InputHandler;

// A simple two-dimensional point class to make life easy.  It allows you to
// reference points with x and y coordinates instead of array indices) and
// encapsulates a midpoint function.
struct Point {
  GLfloat x, y;
  Point(GLfloat x = 0, GLfloat y = 0): x(x), y(y) {}
  Point midpoint(Point p) {return Point((x + p.x) / 2.0, (y + p.y) / 2.0);}
};


//	The main entry point for the program.  This will need to initialize OpenGL,
//	the game engine, and setup callbacks.
int main(int argc, char** argv)
{
	//	Welcome message
	cout << "Space Railer\n";
	
	//	Configure OpenGL Utility Library (GLUT)
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutInitWindowPosition(40, 40);
	glutCreateWindow("Space Railer");
	
	//	Configure callbacks.
	//		DisplayFunc:	Called 60x/second to render graphics
	//		ReshapeFunc:	Called when the window is resized
	//		IdleFunc:		Called when rendering is complete.  This is where
	//						our program actually runs.
	glutDisplayFunc(handleRender);
	glutReshapeFunc(handleReshape);
	glutIdleFunc(handleIdle);
	
	//	Do the main initialization of our game.
	init();
	
	currentProgramMode = PROGRAM_MAINMENU;
	//	Enter the glutLoop.  This will drive the callbacks to our code.
	
	script_test(argc, argv);
	glutMainLoop();
}

// Draws a Sierpinski triangle with a fixed number of points. (Note that the
// number of points is kept fairly small because a display callback should
// NEVER run for too long.
void handleRender()
{
	glClear(GL_COLOR_BUFFER_BIT);

	static Point vertices[] = {Point(0, 0), Point(200, 500), Point(500, 0)};

	// Compute and plot 100000 new points, starting (arbitrarily) with one of
	// the vertices. Each point is halfway between the previous point and a
	// randomly chosen vertex.
	static Point p = vertices[0];
	
	//	glBegin/glEnd don't have { }, but they are essentially code blocks.  It
	//	can be easier to read if it is formatted like the code between them is
	//	part of a block.
	glBegin(GL_POINTS);
		for (int k = 0; k < 100000; k++)
		{
			p = p.midpoint(vertices[rand() % 3]);
			glVertex2f(p.x, p.y);
		}
	glEnd();
	
	glFlush();
}

//	Something has caused the window to resize.  Since we still want to be
//	looking at the same content, we need to adjust the viewport to the new
//	dimensions.  The grid will remain the same.
void handleReshape(GLint newWidth, GLint newHeight)
{
	// Set up the viewing volume: windowWidth x windowHeight window with origin upper left.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0.0, windowWidth, windowHeight, 0.0);
	glViewport(0, 0, newWidth, newHeight);
	
	return;
}


//	Idle is where the main processing for the program goes.  This will determine
//	what state the program is currently in and hand it off to the appropriate
//	subsystem.
void handleIdle()
{
	InputHandler.process();
	
	switch(currentProgramMode)
	{
		case PROGRAM_BOOT		: break;
		case PROGRAM_MAINMENU	: break;
		case PROGRAM_GAME		: break;
	}
	return;
}

//	Initialize our game here.  This will need to launch the startup sequence,
//	main menu, audio subsystem, etc.
void init()
{
	// Set a deep purple background and draw in a greenish yellow.
	glClearColor(0.25, 0.0, 0.2, 1.0);
	glColor3ub(154, 255, 0);

	// Set up the viewing volume: windowWidth x windowHeight window with origin upper left.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluOrtho2D(0.0, windowWidth, windowHeight, 0.0);
	glViewport(0, 0, windowWidth, windowHeight);
	
	//	Now that OpenGL is initialized, we need to initialize input handling.
	//InputHandler = ProgramInput;
	
}


