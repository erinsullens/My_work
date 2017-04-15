#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define _USE_MATH_DEFINES
#include <math.h>

#ifdef WIN32
#include <windows.h>
#pragma warning(disable:4996)
#include <GL/glew.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
float rotateA = 0;
float rotateD = 0;
float rotateG = 0;
float rotateC = 0;

bool playing = false;
//	This is a sample OpenGL / GLUT program
//
//	The objective is to draw a 3d object and change the color of the axes
//		with a glut menu
//
//	The left mouse button does rotation
//	The middle mouse button does scaling
//	The user interface allows:
//		1. The axes to be turned on and off
//		2. The color of the axes to be changed
//		3. Debugging to be turned on and off
//		4. Depth cueing to be turned on and off
//		5. The projection to be changed
//		6. The transformations to be reset
//		7. The program to quit
//
//	Author:			Joe Graphics

// NOTE: There are a lot of good reasons to use const variables instead
// of #define's.  However, Visual C++ does not allow a const variable
// to be used as an array size or as the case in a switch( ) statement.  So in
// the following, all constants are const variables except those which need to
// be array sizes or cases in switch( ) statements.  Those are #defines.


// title of these windows:

const char *WINDOWTITLE = { "Erin's Final Project" };
const char *GLUITITLE   = { "User Interface Window" };
float lokity = -2;

// what the glui package defines as true and false:

const int GLUITRUE  = { true  };
const int GLUIFALSE = { false };

float a = -.91;
float d = -.405;
float g = .405;
float c = .91;

bool aLeft;
bool dLeft;
bool gLeft;
bool cLeft;

bool playA = false;
bool playD = false;
bool playG= false;
bool playC = false;
// the escape key:
//int MS_IN_THE_ANIMATION_CYCLE = 20;
#define ESCAPE		0x1b
float Time;

// initial window size:

const int INIT_WINDOW_SIZE = { 600 };


// size of the box:

const float BOXSIZE = { 2.f };



// multiplication factors for input interaction:
//  (these are known from previous experience)

const float ANGFACT = { 1. };
const float SCLFACT = { 0.005f };


// minimum allowable scale factor:

const float MINSCALE = { 0.05f };


// active mouse buttons (or them together):

const int LEFT   = { 4 };
const int MIDDLE = { 2 };
const int RIGHT  = { 1 };


// which projection:

enum Projections
{
	ORTHO,
	PERSP
};


// which button:

enum ButtonVals
{
	RESET,
	QUIT
};
float White[] = { 1.,1.,1.,1. };

float * Array3(float a, float b, float c)
{
	static float array[4];
	array[0] = a;
	array[1] = b;
	array[2] = c;
	array[3] = 1.;
	return array;
}
// utility to create an array from a multiplier and an array:
float *
MulArray3(float factor, float array0[3])
{
	static float array[4];
	array[0] = factor * array0[0];
	array[1] = factor * array0[1];
	array[2] = factor * array0[2];
	array[3] = 1.;
	return array;
}

void
SetMaterial(float r, float g, float b, float shininess)
{
	glMaterialfv(GL_BACK, GL_EMISSION, Array3(0., 0., 0.));
	glMaterialfv(GL_BACK, GL_AMBIENT, MulArray3(.4f, White));
	glMaterialfv(GL_BACK, GL_DIFFUSE, MulArray3(1., White));
	glMaterialfv(GL_BACK, GL_SPECULAR, Array3(0., 0., 0.));
	glMaterialf(GL_BACK, GL_SHININESS, 5.f);

	glMaterialfv(GL_FRONT, GL_EMISSION, Array3(0., 0., 0.));
	glMaterialfv(GL_FRONT, GL_AMBIENT, Array3(r, g, b));
	glMaterialfv(GL_FRONT, GL_DIFFUSE, Array3(r, g, b));
	glMaterialfv(GL_FRONT, GL_SPECULAR, MulArray3(.8f, White));
	glMaterialf(GL_FRONT, GL_SHININESS, shininess);
}


void
SetPointLight(int ilight, float x, float y, float z, float r, float g, float b)
{
	glLightfv(ilight, GL_POSITION, Array3(x, y, z));
	glLightfv(ilight, GL_AMBIENT, Array3(0., 0., 0.));
	glLightfv(ilight, GL_DIFFUSE, Array3(r, g, b));
	glLightfv(ilight, GL_SPECULAR, Array3(r, g, b));
	glLightf(ilight, GL_CONSTANT_ATTENUATION, 1.);
	glLightf(ilight, GL_LINEAR_ATTENUATION, 0.);
	glLightf(ilight, GL_QUADRATIC_ATTENUATION, 0.);
	glEnable(ilight);
}

// window background color (rgba):

const GLfloat BACKCOLOR[ ] = { 0., 0., 0., 1. };


// line width for the axes:

const GLfloat AXES_WIDTH   = { 3. };


// the color numbers:
// this order must match the radio button order

enum Colors
{
	RED,
	YELLOW,
	GREEN,
	CYAN,
	BLUE,
	MAGENTA,
	WHITE,
	BLACK
};

char * ColorNames[ ] =
{
	"Red",
	"Yellow",
	"Green",
	"Cyan",
	"Blue",
	"Magenta",
	"White",
	"Black"
};


// the color definitions:
// this order must match the menu order

const GLfloat Colors[ ][3] = 
{
	{ 1., 0., 0. },		// red
	{ 1., 1., 0. },		// yellow
	{ 0., 1., 0. },		// green
	{ 0., 1., 1. },		// cyan
	{ 0., 0., 1. },		// blue
	{ 1., 0., 1. },		// magenta
	{ 1., 1., 1. },		// white
	{ 0., 0., 0. },		// black
};


// fog parameters:

const GLfloat FOGCOLOR[4] = { .0, .0, .0, 1. };
const GLenum  FOGMODE     = { GL_LINEAR };
const GLfloat FOGDENSITY  = { 0.30f };
const GLfloat FOGSTART    = { 1.5 };
const GLfloat FOGEND      = { 4. };


// non-constant global variables:

int		ActiveButton;			// current button that is down
GLuint	AxesList;				// list to hold the axes
int		AxesOn;					// != 0 means to draw the axes
int		DebugOn;				// != 0 means to print debugging info
int		DepthCueOn;				// != 0 means to use intensity depth cueing
GLuint	BowBody;				// object display list
GLuint	cube1;
GLuint	cube2;
GLuint	cube3;
GLuint	cube4;
GLuint	cube5;
GLuint	cube6;
GLuint	cube7;
GLuint  cube8;
GLuint	peg;
GLuint  neckTop;
GLuint  quarterOfTop;
GLuint  bodyCube;
GLuint  quarterOfBottom;
GLuint  cubeBody2;
GLuint  cubeBody3;
GLuint  cubeBody4;
GLuint  cubeBody5;
GLuint  cubeBody6;
GLuint  cubeBody7;
GLuint  cubeBody8;
GLuint  cubeBody9;
GLuint  cubeBody10;
GLuint  cubeBody11;
GLuint  cubeBody12;
GLuint  cubeBody13;
GLuint  woodthing;
GLuint  triangle;
GLuint  bowTop;
GLuint  bowCube1;
GLuint  bowCube2;
GLuint  bowCube3;
GLuint  bowCube4;
GLuint  hair;
int		MainWindow;				// window id for main graphics window
float	Scale;					// scaling factor
int		WhichColor;				// index into Colors[ ]
int		WhichProjection;		// ORTHO or PERSP
int		Xmouse, Ymouse;			// mouse values
float	Xrot, Yrot;				// rotation angles in degrees
float aBowz = 0;
float aBowy = 0;
bool aUp = true;

float dBowz = 0;
float dBowy = 0;
bool dUp = true;

float gBowz = 0;
float gBowy = 0;
bool gUp = true;

float cBowz = 0;
float cBowy = 0;
bool cUp = true;

// function prototypes:

void	Animate( );
void	Display( );
void	DoAxesMenu( int );
void	DoColorMenu( int );
void	DoDepthMenu( int );
void	DoDebugMenu( int );
void	DoMainMenu( int );
void	DoProjectMenu( int );
void	DoRasterString( float, float, float, char * );
void	DoStrokeString( float, float, float, float, char * );
float	ElapsedSeconds( );
void	InitGraphics( );
void	InitLists( );
void	InitMenus( );
void	Keyboard( unsigned char, int, int );
void	MouseButton( int, int, int, int );
void	MouseMotion( int, int );
void	Reset( );
void	Resize( int, int );
void	Visibility( int );

void	Axes( float );
void	HsvRgb( float[3], float [3] );

// main program:

int
main( int argc, char *argv[ ] )
{
	// turn on the glut package:
	// (do this before checking argc and argv since it might
	// pull some command line arguments out)

	glutInit( &argc, argv );


	// setup all the graphics stuff:

	InitGraphics( );


	// create the display structures that will not change:

	InitLists( );


	// init all the global variables used by Display( ):
	// this will also post a redisplay

	Reset( );


	// setup all the user interface stuff:

	InitMenus( );


	// draw the scene once and wait for some interaction:
	// (this will never return)

	glutSetWindow( MainWindow );
	glutMainLoop( );


	// this is here to make the compiler happy:

	return 0;
}


// this is where one would put code that is to be called
// everytime the glut main loop has nothing to do
//
// this is typically where animation parameters are set
//
// do not call Display( ) from here -- let glutMainLoop( ) do it
float bowSpeed = .2;
float stringSpeed = .04;
bool playString = true;
void
Animate( )
{
	// put animation stuff in here -- change some global variables
	// for Display( ) to find:
	if (playA && playString) {
		if (aLeft) {
			a += stringSpeed;
			if (a > -.82)
				aLeft = false;
		}
		else {
			a -= stringSpeed;
			if (a < -1)
				aLeft = true;
		}
	}
	else a = -.91;

	if (playD && playString) {
		if (dLeft) {
			d += stringSpeed;
			if (d > -.315)
				dLeft = false;
		}
		else {
			d -= stringSpeed;
			if (d < -.495)
				dLeft = true;
		}
	}
	else d = -.405;
	if (playG && playString) {
		if (gLeft) {
			g += stringSpeed;
			if (g > .495)
				gLeft = false;
		}
		else {
			g -= stringSpeed;
			if (g < .315)
				gLeft = true;
		}
	}
	else g = .405;

	if (playC && playString) {
		if (cLeft) {
			c += .04;
			if (c > 1)
				cLeft = false;
		}
		else {
			c -= .04;
			if (c < .82)
				cLeft = true;
		}
	}
	else c = .91;


	if (playA) {
		if (aUp) {
			//aBowz += sqrt(3)/8 ;
			aBowz += bowSpeed;
			//aBowy += .1/8;
			if (aBowz > 100)
				aUp = false;
		}
		else {
			aBowz -= bowSpeed;
			//aBowy -= .1/8;
			if (aBowz < -100)
				aUp = true;
		}
	}

	if (playD) {
		if (dUp) {
			dBowz += bowSpeed;
			//dBowy += .1 / 8;
			if (dBowz > 100)
				dUp = false;
		}
		else {
			dBowz -= bowSpeed;
		//	dBowy -= .1 / 8;
			if (dBowz < -100)
				dUp = true;
		}
	}

	if (playC) {
		if (cUp) {
			cBowz += bowSpeed;
		//	cBowy += .1 / 8;
			if (cBowz > 100)
				cUp = false;
		}
		else {
			cBowz -= bowSpeed;
		//	cBowy -= .1 / 8;
			if (cBowz < -100)
				cUp = true;
		}
	}

	if (playG) {
		if (gUp) {
			gBowz += bowSpeed;
			//gBowy += .1 / 8;
			if (gBowz > 100)
				gUp = false;
		}
		else {
			gBowz -= bowSpeed;
		//	gBowy -= .1 / 8;
			if (gBowz < -100)
				gUp = true;
		}
	}
	// force a call to Display( ) next time it is convenient:

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// draw the complete scene:

void
Display( )
{
	if( DebugOn != 0 )
	{
		fprintf( stderr, "Display\n" );
	}


	// set which window we want to do the graphics into:

	glutSetWindow( MainWindow );


	// erase the background:

	glDrawBuffer( GL_BACK );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	glEnable( GL_DEPTH_TEST );


	// specify shading to be flat:

	glShadeModel( GL_FLAT );


	// set the viewport to a square centered in the window:

	GLsizei vx = glutGet( GLUT_WINDOW_WIDTH );
	GLsizei vy = glutGet( GLUT_WINDOW_HEIGHT );
	GLsizei v = vx < vy ? vx : vy;			// minimum dimension
	GLint xl = ( vx - v ) / 2;
	GLint yb = ( vy - v ) / 2;
	glViewport( xl, yb,  v, v );


	// set the viewing volume:
	// remember that the Z clipping  values are actually
	// given as DISTANCES IN FRONT OF THE EYE
	// USE gluOrtho2D( ) IF YOU ARE DOING 2D !

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	if( WhichProjection == ORTHO )
		glOrtho( -3., 3.,     -3., 3.,     0.1, 1000. );
	else
		gluPerspective( 90., 1.,	0.1, 1000. );


	// place the objects into the scene:

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );


	// set the eye position, look-at position, and up-vector:

	//gluLookAt( 0., lokity, 3.,     0., lokity, 0.,     0., 1., 0. );
	gluLookAt( 40., -20, 3.,     0., -20, 0.,     0., 1., 0. );


	// rotate the scene:

	glRotatef( (GLfloat)Yrot, 0., 1., 0. );
	glRotatef( (GLfloat)Xrot, 1., 0., 0. );


	// uniformly scale the scene:

	if( Scale < MINSCALE )
		Scale = MINSCALE;
	glScalef( (GLfloat)Scale, (GLfloat)Scale, (GLfloat)Scale );


	// set the fog parameters:

	if( DepthCueOn != 0 )
	{
		glFogi( GL_FOG_MODE, FOGMODE );
		glFogfv( GL_FOG_COLOR, FOGCOLOR );
		glFogf( GL_FOG_DENSITY, FOGDENSITY );
		glFogf( GL_FOG_START, FOGSTART );
		glFogf( GL_FOG_END, FOGEND );
		glEnable( GL_FOG );
	}
	else
	{
		glDisable( GL_FOG );
	}


	// possibly draw the axes:

	if( AxesOn != 0 )
	{
		glColor3fv( &Colors[WhichColor][0] );
		//glCallList( AxesList );
	}
	GLUquadric* bigC = gluNewQuadric();


	// since we are using glScalef( ), be sure normals get unitized:

	glEnable( GL_NORMALIZE );

	glColor3f(.5, .2, 0);

	// draw the current object:
	glPushMatrix();
	glTranslatef(.25, -1.8, 0);
	glScalef(.8,.8,1);
	
	glPushMatrix();
	glutSolidTorus(1,1,20,20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0,0,.55);
	glScalef(.7,.7,.7);
	glColor3f(.5, .2, 0);
	glutSolidTorus(1, 1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -.55);
	glScalef(.7, .7, .7);
	glColor3f(.5, .2, 0);
	glutSolidTorus(1, 1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 1.3);
	glScalef(.3, .3, .3);
	glColor3f(.5, .2, 0);
	glutSolidTorus(1, 1, 20, 20);
	glPopMatrix();
	glPushMatrix();
	glTranslatef(0, 0, -1.3);
	glScalef(.3, .3, .3);
	glColor3f(.5, .2, 0);
	glutSolidTorus(1, 1, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	
	glTranslatef(-1.1,-1,0);
//	glScalef(2, 2, 1);
	glCallList(cube1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	glCallList(cube2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -2, 0);
	glScalef(1,2,1);
	glCallList(cube2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cube3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cube4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cube5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(.9, -7, 0);
	glScalef(1, 2, 1);
	glCallList(cube2);
	glPopMatrix();
	glPopMatrix();

	//neck back
	glPushMatrix();
	glColor3f(.9, .8, .5);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cube6);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.2, .2, .2);
	
	glTranslatef(-.6, -4, .5);
	glTranslatef(0, -1.5, 0);
	glRotatef(rotateG, 0, 0, 1);
	//glScalef(1, 2, 1);
	glCallList(peg);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.2, .2, .2);
	glTranslatef(0, -6, .5);
	glTranslatef(0, -1.5, 0);
	glRotatef(rotateC, 0, 0, 1);
	//glScalef(1, 2, 1);
	glCallList(peg);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.2, .2, .2);
	glTranslatef(0, -5, -.5);
	glTranslatef(0, -1.5, 0);
	glRotatef(180, 0, 0, 0);
	glRotatef(rotateA, 0, 0, 1);
	//glScalef(1, 2, 1);
	glCallList(peg);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.2, .2, .2);
	glTranslatef(-.8, -3, -.5);
	glTranslatef(0, -1.5, 0);
	glRotatef(180, 0, 0, 0);
	glRotatef(rotateD, 0, 0, 1);
	//glScalef(1, 2, 1);
	glCallList(peg);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.2, .2, .2);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(neckTop);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cube8);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(quarterOfTop);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(bodyCube);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(quarterOfBottom);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody6);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody7);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody8);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody9);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody10);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody11);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody12);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.5, .2, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(cubeBody13);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.9, .8, .5);
	glTranslatef(-1.1, -.9, 0);
	//glScalef(1, 2, 1);
	glCallList(woodthing);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.2, .2, .2);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(triangle);
	glPopMatrix();






	glPushMatrix();
	
		glTranslatef(-1.1, -1, 0);
	// strings
	glColor3f(.7,.7,.7);
	float x0[] = {2.5, 2.5 ,2.5, 2.5 };
	float y0[] = {-8, -8, -8, -8 };
	float z0[] = {.6, .2, -.2, -.6  };
	float x1[] = { 3.114, 3.18, 3.14, 3.05};
	float y1[] = {-23.1,-23.1,-23.1,-23.1 };
	float z1[] = {c, g,d, a };
	float x2[] = { 3.114, 3.18, 3.14, 3.05 };
	float y2[] = { -23.1,-23.1,-23.1,-23.1 };
	float z2[] = { c, g,d, a };
	float x3[] = {3.728, 3.86, 3.78, 3.57  };
	float y3[] = {-38.2, -38.2, -38.2, -38.2 };
	float z3[] = {1.22, .61, -.61, -1.22  };
	//glCallList( BoxList );
	for (int j = 0; j < 6; j++) {
		glBegin(GL_LINE_STRIP);
		for (int i = 0; i < 300; i++) {
			float t = (float)i / (float)300;
			float x = (1. - t)*(1. - t)*(1. - t)*x0[j] + 3 * t*(1. - t)*(1. - t)*x1[j] + 3 * t*(t)*(1. - t)*x2[j] + t*t*t*x3[j];
			float y = (1. - t)*(1. - t)*(1. - t)*y0[j] + 3 * t*(1. - t)*(1. - t)*y1[j] + 3 * t*(t)*(1. - t)*y2[j] + t*t*t*y3[j];
			float z = (1. - t)*(1. - t)*(1. - t)*z0[j] + 3 * t*(1. - t)*(1. - t)*z1[j] + 3 * t*(t)*(1. - t)*z2[j] + t*t*t*z3[j];
			//glColor3f(0, 1, 0);
			glVertex3f(x, y, z);
		}
		glEnd();
	}
	glPopMatrix();
	glPushMatrix();
	glTranslatef(-1.1, -1, 0);
	glBegin(GL_LINES);
	glVertex3f(3.728, -38.2, 1.22);
	glVertex3f(3.08,-41.05,.96);

	glVertex3f(3.86, -38.2, .61);
	glVertex3f(3.08, -41.05, .32);

	glVertex3f(3.78, -38.2, -.61);
	glVertex3f(3.08, -41.05, -.32);

	glVertex3f(3.57, -38.2, -1.22);
	glVertex3f(3.08, -41.05, -.96);

	glEnd();
	glPopMatrix();


	glPushMatrix();
	if (!playA && !playD && !playG && !playC) {
	//	glTranslatef(0, -6, 10);
	// this is for rotating to play	glRotatef(-90, 0,1,0);
		
		glRotatef(-90,1,0,0);
		glTranslatef(0, 50, -20);
	}
	if (playA) {
		glRotatef(30, 0, 1, 0);
		glTranslatef(-.5,0,0);
		glTranslatef(0, aBowy/100, aBowz/10);
	}

	if (playD) {
		glRotatef(20, 0, 1, 0);
		glTranslatef(-.5, 0, 0);
		glTranslatef(0, dBowy / 100, dBowz / 10);
	}
	if (playG) {
		glRotatef(-20, 0, 1, 0);
		glTranslatef(-.5, 0, 0);
		glTranslatef(0, gBowy / 100, gBowz / 10);
	}
	if (playC) {
		glRotatef(-30, 0, 1, 0);
		glTranslatef(-.5, 0, 0);
		glTranslatef(0, cBowy / 100, cBowz / 10);
	}

	glPushMatrix();
	glColor3f(.2, .1, 0);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(bowTop);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.2, .2, .2);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(bowCube1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.2, .2, .2);
	glTranslatef(-1.554, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(bowCube2);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.2, .2, .2);
	glTranslatef(-2.008, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(bowCube1);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.2, .2, .2);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(bowCube3);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.2, .2, .2);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(bowCube4);
	glPopMatrix();

	glPushMatrix();
	glColor3f(.8, .8, .7);
	glTranslatef(-1.1, -1, 0);
	//glScalef(1, 2, 1);
	glCallList(hair);
	glPopMatrix();

	glPopMatrix();
	// draw some gratuitous text that just rotates on top of the scene:

	glDisable( GL_DEPTH_TEST );
	glColor3f( 0., 1., 1. );
//	DoRasterString( 0., 1., 0., "Text That Moves" );


	// draw some gratuitous text that is fixed on the screen:
	//
	// the projection matrix is reset to define a scene whose
	// world coordinate system goes from 0-100 in each axis
	//
	// this is called "percent units", and is just a convenience
	//
	// the modelview matrix is reset to identity as we don't
	// want to transform these coordinates

	glDisable( GL_DEPTH_TEST );
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );
	gluOrtho2D( 0., 100.,     0., 100. );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glColor3f( .8, .8, .8 );
	DoRasterString( 5., 5., 0., "Press a, d, g, and c to play strings. Press 1 to slow bow and 2 to speed up." );


	// swap the double-buffered framebuffers:

	glutSwapBuffers( );


	// be sure the graphics buffer has been sent:
	// note: be sure to use glFlush( ) here, not glFinish( ) !

	glFlush( );
}


void
DoAxesMenu( int id )
{
	AxesOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoColorMenu( int id )
{
	WhichColor = id - RED;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoDebugMenu( int id )
{
	DebugOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoDepthMenu( int id )
{
	DepthCueOn = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// main menu callback:

void
DoMainMenu( int id )
{
	switch( id )
	{
		case RESET:
			Reset( );
			break;

		case QUIT:
			// gracefully close out the graphics:
			// gracefully close the graphics window:
			// gracefully exit the program:
			glutSetWindow( MainWindow );
			glFinish( );
			glutDestroyWindow( MainWindow );
			exit( 0 );
			break;

		default:
			fprintf( stderr, "Don't know what to do with Main Menu ID %d\n", id );
	}

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


void
DoProjectMenu( int id )
{
	WhichProjection = id;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// use glut to display a string of characters using a raster font:

void
DoRasterString( float x, float y, float z, char *s )
{
	glRasterPos3f( (GLfloat)x, (GLfloat)y, (GLfloat)z );

	char c;			// one character to print
	for( ; ( c = *s ) != '\0'; s++ )
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, c );
	}
}


// use glut to display a string of characters using a stroke font:

void
DoStrokeString( float x, float y, float z, float ht, char *s )
{
	glPushMatrix( );
		glTranslatef( (GLfloat)x, (GLfloat)y, (GLfloat)z );
		float sf = ht / ( 119.05f + 33.33f );
		glScalef( (GLfloat)sf, (GLfloat)sf, (GLfloat)sf );
		char c;			// one character to print
		for( ; ( c = *s ) != '\0'; s++ )
		{
			glutStrokeCharacter( GLUT_STROKE_ROMAN, c );
		}
	glPopMatrix( );
}


// return the number of seconds since the start of the program:

float
ElapsedSeconds( )
{
	// get # of milliseconds since the start of the program:

	int ms = glutGet( GLUT_ELAPSED_TIME );

	// convert it to seconds:

	return (float)ms / 1000.f;
}


// initialize the glui window:

void
InitMenus( )
{
	glutSetWindow( MainWindow );

	int numColors = sizeof( Colors ) / ( 3*sizeof(int) );
	int colormenu = glutCreateMenu( DoColorMenu );
	for( int i = 0; i < numColors; i++ )
	{
		glutAddMenuEntry( ColorNames[i], i );
	}

	int axesmenu = glutCreateMenu( DoAxesMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int depthcuemenu = glutCreateMenu( DoDepthMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int debugmenu = glutCreateMenu( DoDebugMenu );
	glutAddMenuEntry( "Off",  0 );
	glutAddMenuEntry( "On",   1 );

	int projmenu = glutCreateMenu( DoProjectMenu );
	glutAddMenuEntry( "Orthographic",  ORTHO );
	glutAddMenuEntry( "Perspective",   PERSP );

	int mainmenu = glutCreateMenu( DoMainMenu );
	glutAddSubMenu(   "Axes",          axesmenu);
	glutAddSubMenu(   "Colors",        colormenu);
	glutAddSubMenu(   "Depth Cue",     depthcuemenu);
	glutAddSubMenu(   "Projection",    projmenu );
	glutAddMenuEntry( "Reset",         RESET );
	glutAddSubMenu(   "Debug",         debugmenu);
	glutAddMenuEntry( "Quit",          QUIT );

// attach the pop-up menu to the right mouse button:

	glutAttachMenu( GLUT_RIGHT_BUTTON );
}



// initialize the glut and OpenGL libraries:
//	also setup display lists and callback functions

void
InitGraphics( )
{
	// request the display modes:
	// ask for red-green-blue-alpha color, double-buffering, and z-buffering:

	glutInitDisplayMode( GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH );

	// set the initial window configuration:

	glutInitWindowPosition( 0, 0 );
	glutInitWindowSize( INIT_WINDOW_SIZE, INIT_WINDOW_SIZE );

	// open the window and set its title:

	MainWindow = glutCreateWindow( WINDOWTITLE );
	glutSetWindowTitle( WINDOWTITLE );

	// set the framebuffer clear values:

	glClearColor( BACKCOLOR[0], BACKCOLOR[1], BACKCOLOR[2], BACKCOLOR[3] );

	// setup the callback functions:
	// DisplayFunc -- redraw the window
	// ReshapeFunc -- handle the user resizing the window
	// KeyboardFunc -- handle a keyboard input
	// MouseFunc -- handle the mouse button going down or up
	// MotionFunc -- handle the mouse moving with a button down
	// PassiveMotionFunc -- handle the mouse moving with a button up
	// VisibilityFunc -- handle a change in window visibility
	// EntryFunc	-- handle the cursor entering or leaving the window
	// SpecialFunc -- handle special keys on the keyboard
	// SpaceballMotionFunc -- handle spaceball translation
	// SpaceballRotateFunc -- handle spaceball rotation
	// SpaceballButtonFunc -- handle spaceball button hits
	// ButtonBoxFunc -- handle button box hits
	// DialsFunc -- handle dial rotations
	// TabletMotionFunc -- handle digitizing tablet motion
	// TabletButtonFunc -- handle digitizing tablet button hits
	// MenuStateFunc -- declare when a pop-up menu is in use
	// TimerFunc -- trigger something to happen a certain time from now
	// IdleFunc -- what to do when nothing else is going on

	glutSetWindow( MainWindow );
	glutDisplayFunc( Display );
	glutReshapeFunc( Resize );
	glutKeyboardFunc( Keyboard );
	glutMouseFunc( MouseButton );
	glutMotionFunc( MouseMotion );
	glutPassiveMotionFunc( NULL );
	glutVisibilityFunc( Visibility );
	glutEntryFunc( NULL );
	glutSpecialFunc( NULL );
	glutSpaceballMotionFunc( NULL );
	glutSpaceballRotateFunc( NULL );
	glutSpaceballButtonFunc( NULL );
	glutButtonBoxFunc( NULL );
	glutDialsFunc( NULL );
	glutTabletMotionFunc( NULL );
	glutTabletButtonFunc( NULL );
	glutMenuStateFunc( NULL );
	glutTimerFunc( -1, NULL, 0 );
	glutIdleFunc( Animate );

	// init glew (a window must be open to do this):

#ifdef WIN32
	GLenum err = glewInit( );
	if( err != GLEW_OK )
	{
		fprintf( stderr, "glewInit Error\n" );
	}
	else
		fprintf( stderr, "GLEW initialized OK\n" );
	fprintf( stderr, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

}


// initialize the display lists that will not change:
// (a display list is a way to store opengl commands in
//  memory so that they can be played back efficiently at a later time
//  with a call to glCallList( )

void
InitLists( )
{
	float dx = BOXSIZE / 2.f;
	float dy = BOXSIZE / 2.f;
	float dz = BOXSIZE / 2.f;
	glutSetWindow( MainWindow );

	// create the object:

	

	glEndList( );
	cube1 = glGenLists(1);
	glNewList(cube1, GL_COMPILE);
	glBegin(GL_QUADS);
	glNormal3f(4., 0., 0.);
	glVertex3f(0,0,1);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 2.5, -.5);
	glVertex3f(0, 2.5, .5);

	glNormal3f(0., 4., 0.);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 0, -1);
	glVertex3f(-2, 0, 1);
	glVertex3f(-2, 0, -1);

	glNormal3f(2.5, -2, 0.);
	glVertex3f(0, 2.5, -.5);
	glVertex3f(0, 2.5, .5);
	glVertex3f(-2, 0, 1);
	glVertex3f(-2, 0, -1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glNormal3f(0, 1, 5);
	glVertex3f(-2, 0, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 2.5, .5);

	glNormal3f(0, 1, -5);
	glVertex3f(-2, 0, -1);
	glVertex3f(0, 2.5, -.5);
	glVertex3f(0, 0, -1);
	glEnd();

	glEnd();

	glEndList();


	cube2 = glGenLists(1);
	glNewList(cube2, GL_COMPILE);
	glBegin(GL_QUADS);
	
	glNormal3f(0, 4, 0);
	glVertex3f(0,-1,1);
	glVertex3f(0, -1, -1);
	glVertex3f(-2, -1, -1);
	glVertex3f(-2, -1, 1);

	//glNormal3f(0, , 0);
	glVertex3f(0, 0, 1);
	glVertex3f(0, 0, -1);
	glVertex3f(-2, 0, -1);
	glVertex3f(-2, 0, 1);

	glVertex3f(0, -1, 1);
	glVertex3f(0, -1, -1);
	glVertex3f(0, 0, -1);
	glVertex3f(0, 0, 1);

	glVertex3f(-2, -1, 1);
	glVertex3f(0, -1, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(-2, -1, -1);

	glVertex3f(0, -1, -1);
	glVertex3f(0, 0, -1);
	glVertex3f(-2, 0, -1);
	glVertex3f(-2, -1, -1);

	glVertex3f(-2, 0, -1);
	glVertex3f(-2, -1, -1);
	glVertex3f(-2, -1, 1);
	glVertex3f(-2,0,1);

	glVertex3f(-2, -1, 1);
	glVertex3f(-2, 0, 1);
	glVertex3f(0, 0, 1);
	glVertex3f(0, -1, 1);

	


	glEnd();
	glEndList();


	cube3 = glGenLists(1);
	glNewList(cube3, GL_COMPILE);
	glBegin(GL_QUADS);
//	glColor3f(1,0,0);
	glVertex3f(-2, -3, -1);
	glVertex3f(0, -3, -1);
	glVertex3f(0, -3, 1);
	glVertex3f(-2, -3, 1);

	glVertex3f(0, -3, 1);
	glVertex3f(0, -6, 1);
	glVertex3f(0, -6, -1);
	glVertex3f(0, -3, -1);

	glVertex3f(-2, -3, 1);
	glVertex3f(0, -6, 1);
	glVertex3f(0, -6, -1);
	glVertex3f(-2, -3, -1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(-2, -3, 1);
	glVertex3f(0, -6, 1);
	glVertex3f(0, -3, 1);

	glVertex3f(-2, -3, -1);
	glVertex3f(0, -3, -1);
	glVertex3f(0, -6, -1);
	glEnd();

	glEnd();

	glEndList();

	cube4 = glGenLists(1);
	glNewList(cube4, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(0,0,-1);
	glVertex3f(0, 0, 1);
	glVertex3f(0, -6, 1);
	glVertex3f(0, -6, -1);

	glVertex3f(0, 0, -1);
	glVertex3f(0, 0, 1);
	glVertex3f(2, -4, 1);
	glVertex3f(2, -4, -1);

	glVertex3f(2, -4, -1);
	glVertex3f(2, -4, 1);
	glVertex3f(0, -6, 1);
	glVertex3f(0, -6, -1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0, 0, 1);
	glVertex3f(2, -4, 1);
	glVertex3f(0, -6, 1);

	glVertex3f(0, 0, -1);
	glVertex3f(2, -4, -1);
	glVertex3f(0, -6, -1);
	glEnd();

	glEnd();

	glEndList();

	cube5 = glGenLists(1);
	glNewList(cube5, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(2, -4, -1);
	glVertex3f(2, -4, 1);
	glVertex3f(2, -6, 1);
	glVertex3f(2, -6, -1);

	glVertex3f(2, -6, -1);
	glVertex3f(2, -6, 1);
	glVertex3f(0, -6, 1);
	glVertex3f(0, -6, -1);

	glVertex3f(0, -6, 1);
	glVertex3f(0, -6, -1);
	glVertex3f(2, -4, 1);
	glVertex3f(2, -4, -1);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(0, -6, 1);
	glVertex3f(2, -6, 1);
	glVertex3f(2, -4, 1);

	glVertex3f(0, -6, -1);
	glVertex3f(2, -4, 1);
	glVertex3f(2, -4, -1);
	glEnd();

	glEnd();

	glEndList();

	//neck bottom
	cube6 = glGenLists(1);
	glNewList(cube6, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.2, -8, -1);
	glVertex3f(2, -8, -1);
	glVertex3f(2, -8, 1);
	glVertex3f(1.2, -8, 1);

	glVertex3f(1, -23, -1.3);
	glVertex3f(1, -23, 1.3);
	glVertex3f(2, -23, 1.3);
	glVertex3f(2, -23, -1.3);

	glVertex3f(1.2, -8, 1);
	glVertex3f(2, -8, 1);
	glVertex3f(2, -23, 1.3);
	glVertex3f(1, -23, 1.3);

	glVertex3f(2, -8, 1);
	glVertex3f(2, -8, -1);
	glVertex3f(2, -23, -1.3);
	glVertex3f(2, -23, 1.3);

	glVertex3f(2, -8, -1);
	glVertex3f(1.2, -8, -1);
	glVertex3f(1, -23, -1.3);
	glVertex3f(2, -23, -1.3);

	glVertex3f(1.2, -8, -1);
	glVertex3f(1.2, -8, 1);
	glVertex3f(1, -23, 1.3);
	glVertex3f(1, -23, -1.3);

	



	glEnd();
	glEndList();


	peg = glGenLists(1);
	glNewList(peg, GL_COMPILE);
	glBegin(GL_QUADS);
	//long strip peg
	glVertex3f(0, .17, .5);
	glVertex3f(0, -.17, .5);
	glVertex3f(0, -.17, 2.5);
	glVertex3f(0, .17, 2.5);

	glVertex3f(-.33, .17, .5);
	glVertex3f(-.33, -.17, .5);
	glVertex3f(-.33, -.17, 2.5);
	glVertex3f(-.33, .17, 2.5);

	glVertex3f(0, -.17, .5);
	glVertex3f(0, -.17, 2.5);
	glVertex3f(-.33, -.17, 2.5);
	glVertex3f(-.33, -.17, .5);

	glVertex3f(0, .17, .5);
	glVertex3f(0, -.17, .5);
	glVertex3f(-.33, -.17, .5);
	glVertex3f(-.33, -.17, .5);

	glVertex3f(0, .17, .5);
	glVertex3f(0, .17, 2.5);
	glVertex3f(-.33, .17, 2.5);
	glVertex3f(-.33, .17, .5);

	glVertex3f(0, .17, .5);
	glVertex3f(0, -.17, .5);
	glVertex3f(-.33, -.17, .5);
	glVertex3f(-.33, .17, .5);
	
	//circle part
	glVertex3f(0, -.17, 1.5);
	glVertex3f(0, -.5, 1.83);
	glVertex3f(0, -.5, 2.17);
	glVertex3f(0, -.17, 2.5);

	glVertex3f(0, .17, 1.5);
	glVertex3f(0, .5, 1.83);
	glVertex3f(0, .5, 2.17);
	glVertex3f(0, .17, 2.5);

	glVertex3f(-.33, -.17, 1.5);
	glVertex3f(-.33, -.5, 1.83);
	glVertex3f(-.33, -.5, 2.17);
	glVertex3f(-.33, -.17, 2.5);

	glVertex3f(-.33, .17, 1.5);
	glVertex3f(-.33, .5, 1.83);
	glVertex3f(-.33, .5, 2.17);
	glVertex3f(-.33, .17, 2.5);

	glVertex3f(0, -.5, 1.83);
	glVertex3f(0, -.5, 2.17);
	glVertex3f(-.33, -.5, 2.17);
	glVertex3f(-.33, -.5, 1.83);

	glVertex3f(0, .5, 1.83);
	glVertex3f(0, .5, 2.17);
	glVertex3f(-.33, .5, 2.17);
	glVertex3f(-.33, .5, 1.83);
	

	glVertex3f(0, -.17, 1.5);
	glVertex3f(0, -.5, 1.83);
	glVertex3f(-.33, -.5, 1.83);
	glVertex3f(-.33, -.17, 1.5);

	glVertex3f(0, .17, 1.5);
	glVertex3f(0, .5, 1.83);
	glVertex3f(-.33, .5, 1.83);
	glVertex3f(-.33, .17, 1.5);

	glVertex3f(0, -.5, 2.17);
	glVertex3f(0, -.17, 2.5);
	glVertex3f(-.33, -.17, 2.5);
	glVertex3f(-.33, -.5, 2.17);

	glVertex3f(0, .5, 2.17);
	glVertex3f(0,.17, 2.5);
	glVertex3f(-.33, .17, 2.5);
	glVertex3f(-.33, .5, 2.17);
	
	glEnd();

	glEndList();


	neckTop = glGenLists(1);
	glNewList(neckTop, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(2, -8, -1);
	glVertex3f(2.5, -8, -1);
	glVertex3f(2.5, -8, 1);
	glVertex3f(2, -8, 1);

	glVertex3f(2, -34, -1.6);
	glVertex3f(2.7, -34, -1.6);//
	glVertex3f(2.7, -34, 1.6);//
	glVertex3f(2, -34, 1.6);

	glVertex3f(2, -8, 1);
	glVertex3f(2.5, -8, 1);
	glVertex3f(2.7, -34, 1.6);   //
	glVertex3f(2, -34, 1.6);

	glVertex3f(2, -8, -1);
	glVertex3f(2.5, -8, -1);
	glVertex3f(2.7, -34, -1.6);	//
	glVertex3f(2, -34, -1.6);

	glVertex3f(2.5, -8, 1);
	glVertex3f(2.5, -8, -1);
	glVertex3f(2.7, -34, -1.6);	//
	glVertex3f(2.5, -34, 1.6);

	glVertex3f(2, -8, 1);
	glVertex3f(2, -8, -1);
	glVertex3f(2, -34, -1.6);
	glVertex3f(2, -34, 1.6);





	glEnd();
	glEndList();

	cube8 = glGenLists(1);
	glNewList(cube8, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(-1.95, -23, 1.3);
	glVertex3f(1, -23, 1.3);
	glVertex3f(1, -23, -1.3);
	glVertex3f(-1.95, -23, -1.3);

	glVertex3f(-1.95, -22.25, 1.3);
	glVertex3f(1, -22.25, 1.3);
	glVertex3f(1, -22.25, -1.3);
	glVertex3f(-1.95, -22.25, -1.3);

	glVertex3f(-1.95, -23, -1.3);
	glVertex3f(-1.95, -23, 1.3);
	glVertex3f(-1.95, -22.25, 1.3);
	glVertex3f(-1.95, -22.25, -1.3);

	glVertex3f(-1.95, -23, 1.3);
	glVertex3f(1, -23, 1.3);
	glVertex3f(1, -22.25, 1.3);
	glVertex3f(-1.95, -22.25, 1.3);

	glVertex3f(1, -23, -1.3);
	glVertex3f(-1.95, -23, -1.3);
	glVertex3f(-1.95, -22.25, -1.3);
	glVertex3f(1, -22.25, -1.3);

	glEnd();
	glEndList();


	quarterOfTop = glGenLists(1);
	glNewList(quarterOfTop, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	//left side
	glVertex3f(1.25, -28.24, 0);
	glVertex3f(1.25, -22.75, 0);
	glVertex3f(1.25, -23.25, 3.6);

	glVertex3f(1.25, -28.24, 0);
	glVertex3f(1.25, -23.25, 3.6);
	glVertex3f(1.25, -24.88, 5.6);

	glVertex3f(1.25, -28.24, 0);
	glVertex3f(1.25, -24.88, 5.6);
	glVertex3f(1.25, -26.9, 6.6);

	glVertex3f(1.25, -28.24, 0);
	glVertex3f(1.25, -26.9, 6.6);
	glVertex3f(1.25, -28.24, 6.9);

	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(-1.95, -22.75, 0);
	glVertex3f(-1.95, -23.25, 3.6);

	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(-1.95, -23.25, 3.6);
	glVertex3f(-1.95, -24.88, 5.6);

	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(-1.95, -24.88, 5.6);
	glVertex3f(-1.95, -26.9, 6.6);

	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(-1.95, -26.9, 6.6);
	glVertex3f(-1.95, -28.24, 6.9);  // use
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(1.25, -22.75, 0);
	glVertex3f(1.25, -23.25, 3.6);
	glVertex3f(-1.95, -23.25, 3.6);
	glVertex3f(-1.95, -22.75, 0);

	glVertex3f(1.25, -23.25, 3.6);
	glVertex3f(-1.95, -23.25, 3.6);
	glVertex3f(-1.95, -24.88, 5.6);
	glVertex3f(1.25, -24.88, 5.6);

	glVertex3f(1.25, -24.88, 5.6);
	glVertex3f(-1.95, -24.88, 5.6);
	glVertex3f(-1.95, -26.9, 6.6);
	glVertex3f(1.25, -26.9, 6.6);

	glVertex3f(-1.95, -26.9, 6.6);
	glVertex3f(1.25, -26.9, 6.6);
	glVertex3f(1.25, -28.24, 6.9);
	glVertex3f(-1.95, -28.24, 6.9);

	glVertex3f(1.25, -22.75, 0);
	glVertex3f(1.25, -23.25, 3.6);
	glVertex3f(-1.95, -23.25, 3.6);
	glVertex3f(-1.95, -22.75, 0);

	glEnd();
	//right side

	glBegin(GL_TRIANGLES);
	glVertex3f(1.25, -28.24, 0);
	glVertex3f(1.25, -22.75, 0);
	glVertex3f(1.25, -23.25, -3.6);

	glVertex3f(1.25, -28.24, 0);
	glVertex3f(1.25, -23.25, -3.6);
	glVertex3f(1.25, -24.88,- 5.6);

	glVertex3f(1.25, -28.24, 0);
	glVertex3f(1.25, -24.88, -5.6);
	glVertex3f(1.25, -26.9, -6.6);

	glVertex3f(1.25, -28.24, 0);
	glVertex3f(1.25, -26.9, -6.6);
	glVertex3f(1.25, -28.24, -6.9);

	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(-1.95, -22.75, 0);
	glVertex3f(-1.95, -23.25, -3.6);

	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(-1.95, -23.25, -3.6);
	glVertex3f(-1.95, -24.88, -5.6);

	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(-1.95, -24.88, -5.6);
	glVertex3f(-1.95, -26.9, -6.6);

	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(-1.95, -26.9, -6.6);
	glVertex3f(-1.95, -28.24, -6.9);
	glEnd();


	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(1.25, -22.75, 0);
	glVertex3f(1.25, -23.25, -3.6);
	glVertex3f(-1.95, -23.25, -3.6);
	glVertex3f(-1.95, -22.75, 0);

	glVertex3f(1.25, -23.25, -3.6);
	glVertex3f(-1.95, -23.25, -3.6);
	glVertex3f(-1.95, -24.88, -5.6);
	glVertex3f(1.25, -24.88, -5.6);

	glVertex3f(1.25, -24.88, -5.6);
	glVertex3f(-1.95, -24.88, -5.6);
	glVertex3f(-1.95, -26.9, -6.6);
	glVertex3f(1.25, -26.9, -6.6);

	glVertex3f(-1.95, -26.9, -6.6);
	glVertex3f(1.25, -26.9, -6.6);
	glVertex3f(1.25, -28.24, -6.9);
	glVertex3f(-1.95, -28.24, -6.9);

	glVertex3f(1.25, -22.75, 0);
	glVertex3f(1.25, -23.25, -3.6);
	glVertex3f(-1.95, -23.25, -3.6);
	glVertex3f(-1.95, -22.75, 0);

	glEnd();

	glEndList();

	bodyCube = glGenLists(1);
	glNewList(bodyCube, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -28.24, 4.57);
	glVertex3f(1.25, -28.24, -4.57);
	glVertex3f(1.25, -44.71, -4.57);
	glVertex3f(1.25, -44.71, 4.57);

	glVertex3f(-1.95, -28.24, 4.57);
	glVertex3f(-1.95, -28.24, -4.57);
	glVertex3f(-1.95, -44.71, -4.57);
	glVertex3f(-1.95, -44.71, 4.57);

	glVertex3f(1.25, -28.24, 4.57);
	glVertex3f(1.25, -28.24, -4.57);
	glVertex3f(-1.95, -28.24, -4.57);
	glVertex3f(-1.95, -28.24, 4.57);

	glVertex3f(1.25, -44.71, 4.57);
	glVertex3f(1.25, -44.71, -4.57);
	glVertex3f(-1.95, -44.71, -4.57);
	glVertex3f(-1.95, -44.71, 4.57);

	glVertex3f(1.25, -28.24, 4.57);
	glVertex3f(1.25, -44.71, 4.57);
	glVertex3f(-1.95, -44.71, 4.57);
	glVertex3f(-1.95, -28.24, 4.57);

	glVertex3f(1.25, -28.24, -4.570);
	glVertex3f(1.25, -44.71, -4.570);
	glVertex3f(-1.95, -44.71, -4.570);
	glVertex3f(-1.95, -28.24, -4.570);
	glEnd();
	glEndList();


	quarterOfBottom = glGenLists(1);
	glNewList(quarterOfBottom, GL_COMPILE);
	glBegin(GL_TRIANGLES);
	//left side
	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -52.03, 0);
	glVertex3f(1.25, -51.36, 3.5);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -51.36, 3.5);
	glVertex3f(1.25, -50, 6);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -50, 6);
	glVertex3f(1.25, -47, 8.2);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -47, 8.2);
	glVertex3f(1.25, -44.71, 8.69);

	glVertex3f(-1.95, -44.71, 0);
	glVertex3f(-1.95, -52.03, 0);
	glVertex3f(-1.95, -51.36, 3.5);

	glVertex3f(-1.95, -44.71, 0);
	glVertex3f(-1.95, -51.36, 3.5);
	glVertex3f(-1.95, -50, 6);

	glVertex3f(-1.95, -44.71, 0);
	glVertex3f(-1.95, -50, 6);
	glVertex3f(-1.95, -47, 8.2);

	glVertex3f(-1.95, -44.71, 0);
	glVertex3f(-1.95, -47, 8.2);
	glVertex3f(-1.95, -44.71, 8.69);
	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -44.71, 8.69);
	glVertex3f(-1.95, -44.71, 8.69);
	glVertex3f(-1.95, -44.71, 0);

	glVertex3f(1.25, -44.71, 8.69);
	glVertex3f(1.25, -47, 8.2);
	glVertex3f(-1.95, -47, 8.2);
	glVertex3f(-1.95, -44.71, 8.69);

	glVertex3f(1.25, -47, 8.2);
	glVertex3f(1.25, -50, 6);
	glVertex3f(-1.95, -50, 6);
	glVertex3f(-1.95, -47, 8.2);

	glVertex3f(1.25, -50, 6);
	glVertex3f(1.25, -51.36, 3.5);
	glVertex3f(-1.95, -51.36, 3.5);
	glVertex3f(-1.95, -50, 6);

	glVertex3f(1.25, -51.36, 3.5);
	glVertex3f(1.25, -52.03, 0);
	glVertex3f(-1.95, -52.03, 0);
	glVertex3f(-1.95, -51.36, 3.5);

	glEnd();
	//right side

	glBegin(GL_TRIANGLES);
	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -52.03, 0);
	glVertex3f(1.25, -51.36, -3.5);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -51.36, -3.5);
	glVertex3f(1.25, -50, -6);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -50, -6);
	glVertex3f(1.25, -47, -8.2);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -47, -8.2);
	glVertex3f(1.25, -44.71, -8.69);

	glVertex3f(-1.95, -44.71, 0);
	glVertex3f(-1.95, -52.03, 0);
	glVertex3f(-1.95, -51.36, -3.5);

	glVertex3f(-1.95, -44.71, 0);
	glVertex3f(-1.95, -51.36, -3.5);
	glVertex3f(-1.95, -50, -6);

	glVertex3f(-1.95, -44.71, 0);
	glVertex3f(-1.95, -50, -6);
	glVertex3f(-1.95, -47, -8.2);

	glVertex3f(-1.95, -44.71, 0);
	glVertex3f(-1.95, -47, -8.2);
	glVertex3f(-1.95, -44.71, -8.69);
	glEnd();


	glEnd();

	glBegin(GL_QUADS);
	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -44.71, -8.69);
	glVertex3f(-1.95, -44.71, -8.69);
	glVertex3f(-1.95, -44.71, 0);

	glVertex3f(1.25, -44.71, -8.69);
	glVertex3f(1.25, -47, -8.2);
	glVertex3f(-1.95, -47, -8.2);
	glVertex3f(-1.95, -44.71,-8.69);

	glVertex3f(1.25, -47, -8.2);
	glVertex3f(1.25, -50, -6);
	glVertex3f(-1.95, -50, -6);
	glVertex3f(-1.95, -47, -8.2);

	glVertex3f(1.25, -50, -6);
	glVertex3f(1.25, -51.36, -3.5);
	glVertex3f(-1.95, -51.36, -3.5);
	glVertex3f(-1.95, -50, -6);

	glVertex3f(1.25, -51.36, -3.5);
	glVertex3f(1.25, -52.03, 0);
	glVertex3f(-1.95, -52.03, 0);
	glVertex3f(-1.95, -51.36, -3.5);

	glEnd();

	glEndList();

	cubeBody2 = glGenLists(1);
	glNewList(cubeBody2, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -28.24, 6.9);
	glVertex3f(1.25, -33.27, 5.527);
	glVertex3f(1.25, -33.27, 0);
	glVertex3f(1.25, -28.24, 0);

	glVertex3f(-1.95, -28.24, 6.9);
	glVertex3f(-1.95, -33.27, 5.527);
	glVertex3f(-1.95, -33.27, 0);
	glVertex3f(-1.95, -28.24, 0);

	glVertex3f(1.25, -28.24, 6.9);
	glVertex3f(1.25, -33.27, 5.527);
	glVertex3f(-1.95, -33.27, 5.527);
	glVertex3f(-1.95, -28.24, 6.9);

	glVertex3f(1.25, -33.27, 0);
	glVertex3f(1.25, -28.24, 0);
	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(-1.95, -33.27, 0);

	glVertex3f(1.25, -28.24, 6.9);
	glVertex3f(1.25, -28.24, 0);
	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(1.25, -28.24, 0);
	glVertex3f(-1.95, -28.24, 6.9);

	glVertex3f(1.25, -33.27, 5.527);
	glVertex3f(1.25, -33.27, 0);
	glVertex3f(-1.95, -33.27, 0);
	glVertex3f(-1.95, -33.27, 5.527);





	glEnd();
	glEndList();

	cubeBody3 = glGenLists(1);
	glNewList(cubeBody3, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -28.24, -6.9);
	glVertex3f(1.25, -33.27, -5.527);
	glVertex3f(1.25, -33.27, 0);
	glVertex3f(1.25, -28.24, 0);

	glVertex3f(-1.95, -28.24, -6.9);
	glVertex3f(-1.95, -33.27, -5.527);
	glVertex3f(-1.95, -33.27, 0);
	glVertex3f(-1.95, -28.24, 0);

	glVertex3f(1.25, -28.24, -6.9);
	glVertex3f(1.25, -33.27, -5.527);
	glVertex3f(-1.95, -33.27, -5.527);
	glVertex3f(-1.95, -28.24, -6.9);

	glVertex3f(1.25, -33.27, 0);
	glVertex3f(1.25, -28.24, 0);
	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(-1.95, -33.27, 0);

	glVertex3f(1.25, -28.24, -6.9);
	glVertex3f(1.25, -28.24, 0);
	glVertex3f(-1.95, -28.24, 0);
	glVertex3f(1.25, -28.24, 0);
	glVertex3f(-1.95, -28.24, -6.9);

	glVertex3f(1.25, -33.27, -5.527);
	glVertex3f(1.25, -33.27, 0);
	glVertex3f(-1.95, -33.27, 0);
	glVertex3f(-1.95, -33.27, -5.527);

	glEnd();
	glEndList();

	cubeBody4 = glGenLists(1);
	glNewList(cubeBody4, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -31.9, 5.9);
	glVertex3f(1.25, -33.27, 5.527);
	glVertex3f(-1.95, -33.27, 5.527);
	glVertex3f(-1.95, -31.9, 5.9);

	glVertex3f(1.25, -33.5, 6.4);
	glVertex3f(1.25, -31.9, 5.9);
	glVertex3f(-1.95, -31.9, 5.9);
	glVertex3f(-1.95, -33.5, 6.4);

	glVertex3f(1.25, -33.5, 6.4);
	glVertex3f(1.25, -33.27, 5.527);
	glVertex3f(-1.95, -33.27, 5.527);
	glVertex3f(-1.95, -33.5, 6.4);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.25, -31.9, 5.9);
	glVertex3f(1.25, -33.27, 5.527);
	glVertex3f(1.25, -33.5, 6.4);

	glVertex3f(-1.95, -31.9, 5.9);
	glVertex3f(-1.95, -33.27, 5.527);
	glVertex3f(-1.95, -33.5, 6.4);
	glEnd();

	glEnd();

	glEndList();

	cubeBody5 = glGenLists(1);
	glNewList(cubeBody5, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -31.9, -5.9);
	glVertex3f(1.25, -33.27, -5.527);
	glVertex3f(-1.95, -33.27, -5.527);
	glVertex3f(-1.95, -31.9,- 5.9);

	glVertex3f(1.25, -33.5, -6.4);
	glVertex3f(1.25, -31.9, -5.9);
	glVertex3f(-1.95, -31.9, -5.9);
	glVertex3f(-1.95, -33.5, -6.4);

	glVertex3f(1.25, -33.5, -6.4);
	glVertex3f(1.25, -33.27, -5.527);
	glVertex3f(-1.95, -33.27, -5.527);
	glVertex3f(-1.95, -33.5, -6.4);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.25, -31.9, -5.9);
	glVertex3f(1.25, -33.27, -5.527);
	glVertex3f(1.25, -33.5, -6.4);

	glVertex3f(-1.95, -31.9, -5.9);
	glVertex3f(-1.95, -33.27, -5.527);
	glVertex3f(-1.95, -33.5, -6.4);
	glEnd();

	glEnd();

	glEndList();





	cubeBody6 = glGenLists(1);
	glNewList(cubeBody6, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -44.71, 8.69);
	glVertex3f(1.25, -39.22, 5.94);
	glVertex3f(1.25, -39.22, 0);

	glVertex3f(-1.95, -44.71, 0);
	glVertex3f(-1.95, -44.71, 8.69);
	glVertex3f(-1.95, -39.22, 5.94);
	glVertex3f(-1.95, -39.22, 0);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -44.71, 8.69);
	glVertex3f(-1.95, -44.71, 8.69);
	glVertex3f(-1.95, -44.71, 0);

	glVertex3f(1.25, -44.71, 8.69);
	glVertex3f(1.25, -39.22, 5.94);
	glVertex3f(-1.95, -39.22, 5.94);
	glVertex3f(-1.95, -44.71, 8.69);

	glVertex3f(1.25, -39.22, 5.94);
	glVertex3f(1.25, -39.22, 0);
	glVertex3f(-1.95, -39.22, 0);
	glVertex3f(-1.95, -39.22, 5.94);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -39.22, 0);
	glVertex3f(-1.95, -39.22, 0);
	glVertex3f(-1.95, -44.71, 0);

	glEnd();
	glEndList();

	cubeBody7 = glGenLists(1);
	glNewList(cubeBody7, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -44.71, -8.69);
	glVertex3f(1.25, -39.22, -5.94);
	glVertex3f(1.25, -39.22, 0);

	glVertex3f(-1.95, -44.71, 0);
	glVertex3f(-1.95, -44.71, -8.69);
	glVertex3f(-1.95, -39.22, -5.94);
	glVertex3f(-1.95, -39.22, 0);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -44.71, -8.69);
	glVertex3f(-1.95, -44.71, -8.69);
	glVertex3f(-1.95, -44.71, 0);

	glVertex3f(1.25, -44.71, -8.69);
	glVertex3f(1.25, -39.22, -5.94);
	glVertex3f(-1.95, -39.22, -5.94);
	glVertex3f(-1.95, -44.71, -8.69);

	glVertex3f(1.25, -39.22, -5.94);
	glVertex3f(1.25, -39.22, 0);
	glVertex3f(-1.95, -39.22, 0);
	glVertex3f(-1.95, -39.22, -5.94);

	glVertex3f(1.25, -44.71, 0);
	glVertex3f(1.25, -39.22, 0);
	glVertex3f(-1.95, -39.22, 0);
	glVertex3f(-1.95, -44.71, 0);

	glEnd();
	glEndList();

	cubeBody8 = glGenLists(1);
	glNewList(cubeBody8, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -39.22, 5.94);
	glVertex3f(1.25, -41, 6.68);
	glVertex3f(-1.95, -41, 6.68);
	glVertex3f(-1.95, -39.22, 5.94);

	glVertex3f(1.25, -41, 6.68);
	glVertex3f(1.25, -38.8, 7.2);
	glVertex3f(-1.95, -38.8, 7.2);
	glVertex3f(-1.95, -41, 6.68);

	glVertex3f(1.25, -39.22, 5.94);
	glVertex3f(1.25, -38.8, 7.2);
	glVertex3f(-1.95, -38.8, 7.2);
	glVertex3f(-1.95, -39.22, 5.94);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.25, -39.22, 5.94);
	glVertex3f(1.25, -41, 6.68);
	glVertex3f(1.25, -38.8, 7.2);

	glVertex3f(-1.95, -39.22, 5.94);
	glVertex3f(-1.95, -41, 6.68);
	glVertex3f(-1.95, -38.8, 7.2);
	glEnd();

	glEnd();

	glEndList();
	//bottom points
	cubeBody9 = glGenLists(1);
	glNewList(cubeBody9, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -39.22, -5.94);
	glVertex3f(1.25, -41, -6.68);
	glVertex3f(-1.95, -41, -6.68);
	glVertex3f(-1.95, -39.22, -5.94);

	glVertex3f(1.25, -41, -6.68);
	glVertex3f(1.25, -38.8, -7.2);
	glVertex3f(-1.95, -38.8, -7.2);
	glVertex3f(-1.95, -41, -6.68);

	glVertex3f(1.25, -39.22, -5.94);
	glVertex3f(1.25, -38.8, -7.2);
	glVertex3f(-1.95, -38.8, -7.2);
	glVertex3f(-1.95, -39.22, -5.94);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.25, -39.22, -5.94);
	glVertex3f(1.25, -41, -6.68);
	glVertex3f(1.25, -38.8, -7.2);

	glVertex3f(-1.95, -39.22, -5.94);
	glVertex3f(-1.95, -41, -6.68);
	glVertex3f(-1.95, -38.8, -7.2);
	glEnd();

	glEnd();

	glEndList();

	cubeBody10 = glGenLists(1);
	glNewList(cubeBody10, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -32.9, 6);
	glVertex3f(1.25, -34, 4.5);
	glVertex3f(-1.95, -34, 4.5);
	glVertex3f(-1.95, -32.9, 6);

	glVertex3f(1.25, -34, 4.5);
	glVertex3f(1.25, -32.9, 4.5);
	glVertex3f(-1.95, -32.9, 4.5);
	glVertex3f(-1.95, -34, 4.5);

	glVertex3f(1.25, -32.9, 6);
	glVertex3f(1.25, -32.9, 4.5);
	glVertex3f(-1.95, -32.9, 4.5);
	glVertex3f(-1.95, -32.9, 6);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.25, -32.9, 6);
	glVertex3f(1.25, -34, 4.5);
	glVertex3f(1.25, -32.9, 4.5);

	glVertex3f(-1.95, -32.9, 6);
	glVertex3f(-1.95, -34, 4.5);
	glVertex3f(-1.95, -32.9, 4.5);
	glEnd();

	glEnd();

	glEndList();

	cubeBody11 = glGenLists(1);
	glNewList(cubeBody11, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -32.9, -6);
	glVertex3f(1.25, -34, -4.5);
	glVertex3f(-1.95, -34, -4.5);
	glVertex3f(-1.95, -32.9, -6);

	glVertex3f(1.25, -34, -4.5);
	glVertex3f(1.25, -32.9, -4.5);
	glVertex3f(-1.95, -32.9, -4.5);
	glVertex3f(-1.95, -34, -4.5);

	glVertex3f(1.25, -32.9, -6);
	glVertex3f(1.25, -32.9,-4.5);
	glVertex3f(-1.95, -32.9, -4.5);
	glVertex3f(-1.95, -32.9, -6);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.25, -32.9, -6);
	glVertex3f(1.25, -34, -4.5);
	glVertex3f(1.25, -32.9, -4.5);

	glVertex3f(-1.95, -32.9, -6);
	glVertex3f(-1.95, -34, -4.5);
	glVertex3f(-1.95, -32.9, -4.5);
	glEnd();

	glEnd();

	glEndList();

	cubeBody12 = glGenLists(1);
	glNewList(cubeBody12, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -39.22, 5.5);
	glVertex3f(1.25, -39.22, 4.5);
	glVertex3f(-1.95, -39.22, 4.5);
	glVertex3f(-1.95, -39.22, 5.5);

	glVertex3f(1.25, -39.22, 4.5);
	glVertex3f(1.25, -37, 4.5);
	glVertex3f(-1.95, -37, 4.5);
	glVertex3f(-1.95, -39.22, 4.5);

	glVertex3f(1.25, -39.22, 5.5);
	glVertex3f(1.25, -37, 4.5);
	glVertex3f(-1.95, -37, 4.5);
	glVertex3f(-1.95, -39.22, 5.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.25, -39.22, 5.5);
	glVertex3f(1.25, -39.22, 4.5);
	glVertex3f(1.25, -37, 4.5);


	glVertex3f(-1.95, -39.22, 5.5);
	glVertex3f(-1.95, -39.22, 4.5);
	glVertex3f(-1.95, -37, 4.5);
	
	glEnd();

	glEnd();

	glEndList();


	cubeBody13 = glGenLists(1);
	glNewList(cubeBody13, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -39.22, -5.5);
	glVertex3f(1.25, -39.22, -4.5);
	glVertex3f(-1.95, -39.22, -4.5);
	glVertex3f(-1.95, -39.22, -5.5);

	glVertex3f(1.25, -39.22, -4.5);
	glVertex3f(1.25, -37, -4.5);
	glVertex3f(-1.95, -37, -4.5);
	glVertex3f(-1.95, -39.22, -4.5);

	glVertex3f(1.25, -39.22, -5.5);
	glVertex3f(1.25, -37, -4.5);
	glVertex3f(-1.95, -37, -4.5);
	glVertex3f(-1.95, -39.22, -5.5);
	glEnd();

	glBegin(GL_TRIANGLES);
	glVertex3f(1.25, -39.22, -5.5);
	glVertex3f(1.25, -39.22, -4.5);
	glVertex3f(1.25, -37, -4.5);


	glVertex3f(-1.95, -39.22, -5.5);
	glVertex3f(-1.95, -39.22, -4.5);
	glVertex3f(-1.95, -37,-4.5);

	glEnd();

	glEnd();

	glEndList();

	woodthing = glGenLists(1);
	glNewList(woodthing, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(1.25, -38.305, 1.83);
	glVertex3f(1.25, -38.305, 0);
	glVertex3f(3.995, -38.3, 0);
	glVertex3f(3.595, -38.3, 1.83);

	glVertex3f(1.25, -37.85, 1.83);
	glVertex3f(1.25, -37.85, 0);
	glVertex3f(3.995, -38.1, 0);
	glVertex3f(3.595, -38.1, 1.83);

	glVertex3f(1.25, -38.305, 0);
	glVertex3f(1.25, -38.305, -1.83);
	glVertex3f(3.359, -38.3, -1.83);
	glVertex3f(3.995, -38.3, 0);

	glVertex3f(1.25, -37.85, 0);
	glVertex3f(1.25, -37.85, -1.83);
	glVertex3f(3.359, -38.1, -1.83);
	glVertex3f(3.995, -38.1, 0);

	glVertex3f(1.25, -38.305, 1.83);
	glVertex3f(1.25, -38.305, 0);
	glVertex3f(1.25, -37.85, 0);
	glVertex3f(1.25, -37.85, 1.83);

	glVertex3f(1.25, -38.305, 1.83);
	glVertex3f(3.595, -38.3, 1.83);
	glVertex3f(3.595, -38.1, 1.83);
	glVertex3f(1.25, -37.85, 1.83);

	glVertex3f(3.595, -38.3, 1.83);
	glVertex3f(3.995, -38.3, 0);
	glVertex3f(3.995, -38.1, 0);
	glVertex3f(3.595, -38.1, 1.83);

	glVertex3f(3.359, -38.3, -1.83);
	glVertex3f(3.995, -38.3, 0);
	glVertex3f(3.995, -38.1, 0);
	glVertex3f(3.359, -38.1, -1.83);

	glVertex3f(1.25, -38.305, -1.83);
	glVertex3f(3.395, -38.3, -1.83);
	glVertex3f(3.395, -38.1, -1.83);
	glVertex3f(1.25, -37.85, -1.83);







	glEnd();
	glEndList();

	triangle = glGenLists(1);
	glNewList(triangle, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(2.165, -45.625, .686);
	glVertex3f(2.165, -45.625, -.686);
	glVertex3f(2.165, -41.05, -1.6);
	glVertex3f(2.165, -41.05, 1.6);

	glVertex3f(3.08, -45.625, .686);
	glVertex3f(3.08, -45.625, -.686);
	glVertex3f(3.08, -41.05, -1.6);
	glVertex3f(3.08, -41.05, 1.6);

	glVertex3f(2.165, -45.625, .686);
	glVertex3f(2.165, -45.625, -.686);
	glVertex3f(3.08, -45.625, -.686);
	glVertex3f(3.08, -45.625, .686);

	glVertex3f(2.165, -45.625, -.686);
	glVertex3f(2.165, -41.05, -1.6);
	glVertex3f(3.08, -41.05, -1.6);
	glVertex3f(3.08, -45.625, -.686);

	glVertex3f(2.165, -41.05, -1.6);
	glVertex3f(2.165, -41.05, 1.6);
	glVertex3f(3.08, -41.05, 1.6);
	glVertex3f(3.08, -41.05, -1.6);

	glVertex3f(2.165, -45.625, .686);
	glVertex3f(2.165, -41.05, 1.6);
	glVertex3f(3.08, -41.05, 1.6);
	glVertex3f(3.08, -45.625, .686);
	//
	glVertex3f(2.165, -45.625, .686);
	glVertex3f(2.165, -45.625, -.686);
	glVertex3f(1.5, -52, -.686);
	glVertex3f(1.5, -52, .686);

	glVertex3f(3.08, -45.625, .686);
	glVertex3f(3.08, -45.625, -.686);
	glVertex3f(2, -52, -.686);
	glVertex3f(2, -52, .686);

	glVertex3f(2.165, -45.625, .686);
	glVertex3f(2.165, -45.625, -.686);
	glVertex3f(3.08, -45.625, -.686);
	glVertex3f(3.08, -45.625, .686);

	glVertex3f(2.165, -45.625, -.686);
	glVertex3f(1.5, -52, -.686);
	glVertex3f(2, -52, -.686);
	glVertex3f(3.08, -45.625, -.686);

	glVertex3f(1.5, -52, -.686);
	glVertex3f(1.5, -52, .686);
	glVertex3f(2, -52, .686);
	glVertex3f(2, -52, -.686);

	glVertex3f(2.165, -45.625, .686);
	glVertex3f(1.5, -52, .686);
	glVertex3f(2, -52, .686);
	glVertex3f(3.08, -45.625, .686);

	glEnd();
	glEndList();


	bowTop = glGenLists(1);
	glNewList(bowTop, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(6, -35.331, 25.85);
	glVertex3f(6, -35.217, -25.85);
	glVertex3f(6, -35.903, -25.85);
	glVertex3f(6, -35.789, 25.85);

	glVertex3f(5.542, -35.331, 25.85);
	glVertex3f(5.314, -35.217, -25.85);
	glVertex3f(5.314, -35.903, -25.85);
	glVertex3f(5.542, -35.789, 25.85);

	glVertex3f(6, -35.331, 25.85);
	glVertex3f(6, -35.217, -25.85);
	glVertex3f(5.314, -35.217, -25.85);
	glVertex3f(5.542, -35.331, 25.85);

	glVertex3f(6, -35.217, -25.85);
	glVertex3f(6, -35.903, -25.85);
	glVertex3f(5.314, -35.903, -25.85);
	glVertex3f(5.314, -35.217, -25.85);

	glVertex3f(6, -35.903, -25.85);
	glVertex3f(6, -35.789, 25.85);
	glVertex3f(5.542, -35.789, 25.85);
	glVertex3f(5.314, -35.903, -25.85);

	glVertex3f(6, -35.331, 25.85);
	glVertex3f(6, -35.789, 25.85);
	glVertex3f(5.542, -35.789, 25.85);
	glVertex3f(5.542, -35.331, 25.85);

	glEnd();
	glEndList();

	bowCube1 = glGenLists(1);
	glNewList(bowCube1, GL_COMPILE);
	glBegin(GL_QUADS);

	glVertex3f(5.514, -35.903, -20.82);
	glVertex3f(5.514, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -20.82);

	glVertex3f(5.514, -35.217, -20.82);
	glVertex3f(5.514, -35.217, -24.02);
	glVertex3f(5.06, -35.217, -24.02);
	glVertex3f(5.06, -35.217, -20.82);

	glVertex3f(5.514, -35.903, -20.82);
	glVertex3f(5.514, -35.903, -24.02);
	glVertex3f(5.514, -35.217, -24.02);
	glVertex3f(5.514, -35.217, -20.82);

	glVertex3f(5.514, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -24.02);
	glVertex3f(5.06, -35.217, -24.02);
	glVertex3f(5.514, -35.217, -24.02);

	glVertex3f(5.06, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -20.82);
	glVertex3f(5.06, -35.217, -20.82);
	glVertex3f(5.06, -35.217, -24.02);

	glVertex3f(5.514, -35.903, -20.82);
	glVertex3f(5.06, -35.903, -20.82);
	glVertex3f(5.06, -35.217, -20.82);
	glVertex3f(5.514, -35.217, -20.82);
	//smaller cube
	glVertex3f(5.514, -35.903, -21.735);
	glVertex3f(5.514, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -21.735);

	glVertex3f(5.514, -35.217, -21.735);
	glVertex3f(5.514, -35.217, -24.02);
	glVertex3f(5.06, -35.217, -24.02);
	glVertex3f(5.06, -35.217, -21.735);

	glVertex3f(5.514, -35.903, -21.735);
	glVertex3f(5.514, -35.903, -24.02);
	glVertex3f(5.514, -35.217, -24.02);
	glVertex3f(5.514, -35.217, -21.735);

	glVertex3f(5.514, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -24.02);
	glVertex3f(5.06, -35.217, -24.02);
	glVertex3f(5.514, -35.217, -24.02);

	glVertex3f(5.06, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -21.735);
	glVertex3f(5.06, -35.217, -21.735);
	glVertex3f(5.06, -35.217, -24.02);

	glVertex3f(5.514, -35.903, -21.735);
	glVertex3f(5.06, -35.903, -21.735);
	glVertex3f(5.06, -35.217, -21.735);
	glVertex3f(5.514, -35.217, -21.735);

	glEnd();
	glEndList();

	bowCube2 = glGenLists(1);
	glNewList(bowCube2, GL_COMPILE);
	glBegin(GL_QUADS);

	
	//smaller cube
	glVertex3f(5.514, -35.903, -21.735);
	glVertex3f(5.514, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -21.735);

	glVertex3f(5.514, -35.217, -21.735);
	glVertex3f(5.514, -35.217, -24.02);
	glVertex3f(5.06, -35.217, -24.02);
	glVertex3f(5.06, -35.217, -21.735);

	glVertex3f(5.514, -35.903, -21.735);
	glVertex3f(5.514, -35.903, -24.02);
	glVertex3f(5.514, -35.217, -24.02);
	glVertex3f(5.514, -35.217, -21.735);

	glVertex3f(5.514, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -24.02);
	glVertex3f(5.06, -35.217, -24.02);
	glVertex3f(5.514, -35.217, -24.02);

	glVertex3f(5.06, -35.903, -24.02);
	glVertex3f(5.06, -35.903, -21.735);
	glVertex3f(5.06, -35.217, -21.735);
	glVertex3f(5.06, -35.217, -24.02);

	glVertex3f(5.514, -35.903, -21.735);
	glVertex3f(5.06, -35.903, -21.735);
	glVertex3f(5.06, -35.217, -21.735);
	glVertex3f(5.514, -35.217, -21.735);

	glEnd();
	glEndList();

	bowCube3 = glGenLists(1);
	glNewList(bowCube3, GL_COMPILE);


	glBegin(GL_TRIANGLES);

	glVertex3f(6, -35.331, 25.85);
	glVertex3f(6, -35.789, 25.85);
	glVertex3f(6, -35.56, 26.765);

	glVertex3f(6, -35.56, 26.765);
	glVertex3f(4.402, -35.9, 27.22);
	glVertex3f(4.402, -35.19, 27.22);

	glEnd();

	glBegin(GL_QUADS);

	glVertex3f(4.402, -35.19, 25.85);
	glVertex3f(4.402, -35.9, 25.85);
	glVertex3f(4.402, -35.9, 27.22);
	glVertex3f(4.402, -35.19, 27.22);

	glVertex3f(6, -35.331, 25.85);
	glVertex3f(6, -35.789, 25.85);
	glVertex3f(4.402, -35.9, 25.85);
	glVertex3f(4.402, -35.19, 25.85);

	glVertex3f(6, -35.789, 25.85);
	glVertex3f(6, -35.56, 26.765);
	glVertex3f(4.402, -35.9, 27.22);
	glVertex3f(4.402, -35.9, 25.85);

	glVertex3f(4.402, -35.9, 25.85);
	glVertex3f(4.402, -35.9, 27.22);
	glVertex3f(4.402, -35.19, 27.22);
	glVertex3f(4.402, -35.19, 25.85);
	glEnd();
	
	glEndList();


	bowCube4 = glGenLists(1);
	glNewList(bowCube4, GL_COMPILE);


	glBegin(GL_TRIANGLES);

	glVertex3f(4.4, -35.19, 27.22);
	glVertex3f(4.4, -35.9, 27.22);
	glVertex3f(4.4, -35.545, 28.135);

	glVertex3f(4.45, -35.19, 27.22);
	glVertex3f(4.45, -35.9, 27.22);
	glVertex3f(4.45, -35.545, 28.135);

	glEnd();

	glBegin(GL_QUADS);

	glVertex3f(4.4, -35.19, 27.22);
	glVertex3f(4.4, -35.9, 27.22);
	glVertex3f(4.45, -35.9, 27.22);
	glVertex3f(4.45, -35.19, 27.22);

	glVertex3f(4.4, -35.9, 27.22);
	glVertex3f(4.4, -35.545, 28.135);
	glVertex3f(4.45, -35.545, 28.135);
	glVertex3f(4.45, -35.9, 27.22);

	glVertex3f(4.4, -35.19, 27.22);
	glVertex3f(4.4, -35.545, 28.135);
	glVertex3f(4.45, -35.545, 28.135);
	glVertex3f(4.45, -35.19, 27.22);

	
	glEnd();

	glEndList();


	hair = glGenLists(1);
	glNewList(hair, GL_COMPILE);
	glBegin(GL_QUADS);


	glVertex3f(4.402, -35.19, 25.85);
	glVertex3f(4.402, -35.9, 25.85);
	glVertex3f(4.152, -35.903, -20.82);
	glVertex3f(4.152, -35.217, -20.82);

	glVertex3f(4.405, -35.19, 25.85);
	glVertex3f(4.405, -35.9, 25.85);
	glVertex3f(4.155, -35.903, -20.82);
	glVertex3f(4.155, -35.217, -20.82);

	glVertex3f(4.402, -35.19, 25.85);
	glVertex3f(4.402, -35.9, 25.85);
	glVertex3f(4.405, -35.9, 25.85);
	glVertex3f(4.405, -35.19, 25.85);

	glVertex3f(4.402, -35.9, 25.85);
	glVertex3f(4.152, -35.903, -20.82);
	glVertex3f(4.155, -35.903, -20.82);
	glVertex3f(4.405, -35.9, 25.85);

	glVertex3f(4.152, -35.903, -20.82);
	glVertex3f(4.152, -35.217, -20.82);
	glVertex3f(4.155, -35.217, -20.82);
	glVertex3f(4.155, -35.903, -20.82);

	glVertex3f(4.402, -35.19, 25.85);
	glVertex3f(4.152, -35.217, -20.82);
	glVertex3f(4.155, -35.217, -20.82);
	glVertex3f(4.405, -35.19, 25.85);

	glEnd();
	glEndList();

	// create the axes:

	AxesList = glGenLists( 1 );
	glNewList( AxesList, GL_COMPILE );
		glLineWidth( AXES_WIDTH );
			Axes( 5 );
		glLineWidth( 1. );
	glEndList( );
}


// the keyboard callback:

void
Keyboard( unsigned char c, int x, int y )
{
	if( DebugOn != 0 )
		fprintf( stderr, "Keyboard: '%c' (0x%0x)\n", c, c );

	switch( c )
	{
		case 'o':
		case 'O':
			WhichProjection = ORTHO;
			break;
		case 'A': 
			rotateA += 5;
			if (rotateA == 360) {
				rotateA = 0;
			}
			break;
		case 'D':
			rotateD += 5;
			if (rotateD == 360) {
				rotateD = 0;
			}
			break;
		case 'G':
			rotateG += 5;
			if (rotateG == 360) {
				rotateG = 0;
			}
			break;
		case 'C':
			rotateC += 5;
			if (rotateC == 360) {
				rotateC = 0;
			}
			break;
		case 'a':
		
			playing = !playing;
			if (playing) {
				bowSpeed = .2;
			}
			playA = !playA;
			if (playD)
				playD = false;
			if (playG)
				playG = false;
			if (playC)
				playC = false;
			break;
		case 'd':
			playing = !playing;
			if (playing) {
				bowSpeed = .2;
			}
			playD = !playD;
			if (playA)
				playA = false;
			if (playG)
				playG = false;
			if (playC)
				playC = false;
			break;
		case 'g':
		
			playing = !playing;
			if (playing) {
				bowSpeed = .2;
			}
			playG = !playG;
			if (playD)
				playD = false;
			if (playA)
				playA = false;
			if (playC)
				playC = false;
			break;

		case 'c':
		
			playing = !playing;
			if (playing) {
				bowSpeed = .2;
			}
			playC = !playC;
			if (playD)
				playD = false;
			if (playG)
				playG = false;
			if (playA)
				playA = false;
			break;

		case '1':
			if (bowSpeed > .05) {
				playString = true;
				bowSpeed -= .05;
			} 
			else playString = false;
			break;
		case '2':
			if (bowSpeed < 2) {
				bowSpeed += .05;
				playString = true;
			}
			break;
		case 'p':
		case 'P':
			WhichProjection = PERSP;
			break;

		case 'q':
		case 'Q':
		case ESCAPE:
			DoMainMenu( QUIT );	// will not return here
			break;				// happy compiler

		default:
			fprintf( stderr, "Don't know what to do with keyboard hit: '%c' (0x%0x)\n", c, c );
	}

	// force a call to Display( ):

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// called when the mouse button transitions down or up:

void
MouseButton( int button, int state, int x, int y )
{
	int b = 0;			// LEFT, MIDDLE, or RIGHT

	if( DebugOn != 0 )
		fprintf( stderr, "MouseButton: %d, %d, %d, %d\n", button, state, x, y );

	
	// get the proper button bit mask:

	switch( button )
	{
		case GLUT_LEFT_BUTTON:
			b = LEFT;		break;

		case GLUT_MIDDLE_BUTTON:
			b = MIDDLE;		break;

		case GLUT_RIGHT_BUTTON:
			b = RIGHT;		break;

		default:
			b = 0;
			fprintf( stderr, "Unknown mouse button: %d\n", button );
	}


	// button down sets the bit, up clears the bit:

	if( state == GLUT_DOWN )
	{
		Xmouse = x;
		Ymouse = y;
		ActiveButton |= b;		// set the proper bit
	}
	else
	{
		ActiveButton &= ~b;		// clear the proper bit
	}
}


// called when the mouse moves while a button is down:

void
MouseMotion( int x, int y )
{
	if( DebugOn != 0 )
		fprintf( stderr, "MouseMotion: %d, %d\n", x, y );


	int dx = x - Xmouse;		// change in mouse coords
	int dy = y - Ymouse;

	if( ( ActiveButton & LEFT ) != 0 )
	{
		Xrot += ( ANGFACT*dy );
		Yrot += ( ANGFACT*dx );
	}


	if( ( ActiveButton & MIDDLE ) != 0 )
	{
		Scale += SCLFACT * (float) ( dx - dy );

		// keep object from turning inside-out or disappearing:

		if( Scale < MINSCALE )
			Scale = MINSCALE;
	}

	Xmouse = x;			// new current position
	Ymouse = y;

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// reset the transformations and the colors:
// this only sets the global variables --
// the glut main loop is responsible for redrawing the scene

void
Reset( )
{
	ActiveButton = 0;
	AxesOn = 1;
	DebugOn = 0;
	DepthCueOn = 0;
	Scale  = 1.0;
	WhichColor = WHITE;
	WhichProjection = PERSP;
	Xrot = Yrot = 0.;
}


// called when user resizes the window:

void
Resize( int width, int height )
{
	if( DebugOn != 0 )
		fprintf( stderr, "ReSize: %d, %d\n", width, height );

	// don't really need to do anything since window size is
	// checked each time in Display( ):

	glutSetWindow( MainWindow );
	glutPostRedisplay( );
}


// handle a change to the window's visibility:

void
Visibility ( int state )
{
	if( DebugOn != 0 )
		fprintf( stderr, "Visibility: %d\n", state );

	if( state == GLUT_VISIBLE )
	{
		glutSetWindow( MainWindow );
		glutPostRedisplay( );
	}
	else
	{
		// could optimize by keeping track of the fact
		// that the window is not visible and avoid
		// animating or redrawing it ...
	}
}



///////////////////////////////////////   HANDY UTILITIES:  //////////////////////////


// the stroke characters 'X' 'Y' 'Z' :

static float xx[ ] = {
		0.f, 1.f, 0.f, 1.f
	      };

static float xy[ ] = {
		-.5f, .5f, .5f, -.5f
	      };

static int xorder[ ] = {
		1, 2, -3, 4
		};

static float yx[ ] = {
		0.f, 0.f, -.5f, .5f
	      };

static float yy[ ] = {
		0.f, .6f, 1.f, 1.f
	      };

static int yorder[ ] = {
		1, 2, 3, -2, 4
		};

static float zx[ ] = {
		1.f, 0.f, 1.f, 0.f, .25f, .75f
	      };

static float zy[ ] = {
		.5f, .5f, -.5f, -.5f, 0.f, 0.f
	      };

static int zorder[ ] = {
		1, 2, 3, 4, -5, 6
		};

// fraction of the length to use as height of the characters:
const float LENFRAC = 0.10f;

// fraction of length to use as start location of the characters:
const float BASEFRAC = 1.10f;

//	Draw a set of 3D axes:
//	(length is the axis length in world coordinates)

void
Axes( float length )
{
	glBegin( GL_LINE_STRIP );
		glVertex3f( length, 0., 0. );
		glVertex3f( 0., 0., 0. );
		glVertex3f( 0., length, 0. );
	glEnd( );
	glBegin( GL_LINE_STRIP );
		glVertex3f( 0., 0., 0. );
		glVertex3f( 0., 0., length );
	glEnd( );

	float fact = LENFRAC * length;
	float base = BASEFRAC * length;

	glBegin( GL_LINE_STRIP );
		for( int i = 0; i < 4; i++ )
		{
			int j = xorder[i];
			if( j < 0 )
			{
				
				glEnd( );
				glBegin( GL_LINE_STRIP );
				j = -j;
			}
			j--;
			glVertex3f( base + fact*xx[j], fact*xy[j], 0.0 );
		}
	glEnd( );

	glBegin( GL_LINE_STRIP );
		for( int i = 0; i < 5; i++ )
		{
			int j = yorder[i];
			if( j < 0 )
			{
				
				glEnd( );
				glBegin( GL_LINE_STRIP );
				j = -j;
			}
			j--;
			glVertex3f( fact*yx[j], base + fact*yy[j], 0.0 );
		}
	glEnd( );

	glBegin( GL_LINE_STRIP );
		for( int i = 0; i < 6; i++ )
		{
			int j = zorder[i];
			if( j < 0 )
			{
				
				glEnd( );
				glBegin( GL_LINE_STRIP );
				j = -j;
			}
			j--;
			glVertex3f( 0.0, fact*zy[j], base + fact*zx[j] );
		}
	glEnd( );

}


// function to convert HSV to RGB
// 0.  <=  s, v, r, g, b  <=  1.
// 0.  <= h  <=  360.
// when this returns, call:
//		glColor3fv( rgb );

void
HsvRgb( float hsv[3], float rgb[3] )
{
	// guarantee valid input:

	float h = hsv[0] / 60.f;
	while( h >= 6. )	h -= 6.;
	while( h <  0. ) 	h += 6.;

	float s = hsv[1];
	if( s < 0. )
		s = 0.;
	if( s > 1. )
		s = 1.;

	float v = hsv[2];
	if( v < 0. )
		v = 0.;
	if( v > 1. )
		v = 1.;

	// if sat==0, then is a gray:

	if( s == 0.0 )
	{
		rgb[0] = rgb[1] = rgb[2] = v;
		return;
	}

	// get an rgb from the hue itself:
	
	float i = floor( h );
	float f = h - i;
	float p = v * ( 1.f - s );
	float q = v * ( 1.f - s*f );
	float t = v * ( 1.f - ( s * (1.f-f) ) );

	float r, g, b;			// red, green, blue
	switch( (int) i )
	{
		case 0:
			r = v;	g = t;	b = p;
			break;
	
		case 1:
			r = q;	g = v;	b = p;
			break;
	
		case 2:
			r = p;	g = v;	b = t;
			break;
	
		case 3:
			r = p;	g = q;	b = v;
			break;
	
		case 4:
			r = t;	g = p;	b = v;
			break;
	
		case 5:
			r = v;	g = p;	b = q;
			break;
	}


	rgb[0] = r;
	rgb[1] = g;
	rgb[2] = b;
}
