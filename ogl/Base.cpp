/*
 *		This Code Was Created By Lionel Brits & Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing The Base Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */

#include <windows.h>
#include <stdlib.h>			// Header File For Standard Library
#include "ColVector.h"
#include "Output.h"
#include "Collision.h"
#include <math.h>			// Math Library Header File
#include <stdio.h>			// Header File For Standard Input/Output
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include "bmp.h"			// Header File For The Glaux Library
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "GLlists.h"
#include "model.h"
#include "polygon.h"
#include "door.h"
#include "gui.h"
#include "texLoad.h"
#include "menu.h"
#include "ModelControl.h"
#include "lighting.h"

using namespace std;

typedef struct
{
	float X, Y, Z;
	float U, V;
} VERT;

const double PI = 3.1415926535897;
const double space = 10;
const int VertexCount = (90 / space) * (360 / space) * 4;
VERT *VERTICES;
gui display;
HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default
bool	blend;				// Blending ON/OFF
bool	bp;					// B Pressed?
bool	fp;					// F Pressed?
bool	sel;				// E Pressed?
bool	menu;				
bool	dead = false;


const float piover180 = 0.0174532925f;
float heading;
float xpos = 0;
float zpos = 2;
float ypos = 0;
float rotateX;
float doorAngle;
float time;
float falling = 0;
GLfloat	yrot;				// Y Rotation
GLfloat walkbias = 0;
GLfloat walkbiasangle = 0;
GLfloat lookupdown = 0.0f;
GLfloat	z=0.0f;				// Depth Into The Screen

GLuint	filter;				// Which Filter To Use
GLuint	texture[6];			// Storage For 3 Textures
GLUquadricObj* quadratic;

fstream myfile;
GLlists modelList;
Output ot;
LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc
vector<model*> models;
ModelControl interactModels;
lighting lighter;

bool startsWith(std::string& src, std::string& token){	return src.substr(0,token.length()) == token ;}

void floorColl() {
	Collision floor(models,false);
	ColVector fstart(xpos,ypos,zpos);
	ColVector fdirection(0,-0.05,0);
	bool detect = floor.collisionTest(fstart.getVector(),fdirection.getVector());
	if(detect != true) {
		falling += 1;
		if(falling > 80) {
			//dead = true;
		}
		ypos =ypos-0.05;
	}
	else {
		falling = 0;
	}
}
void readstr(FILE *f,char *string)
{
	do
	{
		fgets(string, 255, f);
	} while ((string[0] == '/') || (string[0] == '\n'));
	return;
}

void SetupWorld()
{
	freopen("Data/file.txt", "w", stdout);
	float x, y, z, u, v;
	float xangle,yangle,zangle;
	vector<float> angles;
	int numtriangles;
	string totalVert = "           ";
	bool init = true;
	FILE *filein;
	char oneline[255];
	filein = fopen("data/world.txt", "rt");				// File To Load World Data From
	readstr(filein,oneline);
	sscanf(oneline, "NUMPOLLIES %d\n", &numtriangles);
	int totalHeight;
	string location = "empty";
	model* newModel = NULL;
	string *curLoc;

	for (int loop = 0; loop < numtriangles; loop++)
	{
		string polyType;
		totalHeight = 0;
		readstr(filein,oneline);
		sscanf_s(oneline, "%s",&totalVert);
		if(newModel != NULL) {
			models.back()->display.newPoly();
		}
		if(startsWith(totalVert,string("cylinder"))) {
			readstr(filein,oneline);
			sscanf(oneline, "%f %f %f %f %f %s", &x, &y, &z, &u, &v, &location);
			newModel = new  model(location);
			newModel->setPolyType(totalVert);
			newModel->setDisplayType(true);
			newModel->display.newPoly();
			newModel->display.addVertex(x,y,z,u,v);
			readstr(filein,oneline);
			sscanf(oneline, "%f %f %f %f %f %s", &x, &y, &z, &u, &v);
			newModel->display.addVertex(x,y,z,u,v);
			readstr(filein,oneline);
			sscanf(oneline, "%f %f %f", &xangle, &yangle, &zangle);
			newModel->setDisplayList(modelList.buildCylinder(newModel->display.getPolys()[0]->getVertex(0),x,y,z,u,v,quadratic,xangle,yangle,zangle));
			angles.push_back(sin(xangle*PI/180));
			angles.push_back(sin(yangle*PI/180));
			angles.push_back(cos(zangle*PI/180));
			newModel->setOVector(angles);
			models.push_back(newModel);

			
		}
		else {
			for (int vert = 0; vert <atoi(totalVert.c_str()); vert++)
			{
				readstr(filein,oneline);
				sscanf(oneline, "%f %f %f %f %f %s", &x, &y, &z, &u, &v, &location);
				if(location != "empty") {
					if(location == "door1") {
						newModel = new door(location);
					}
					else {
						newModel = new model(location);
					}
					newModel->setPolyType(totalVert);
					models.push_back(newModel);
					models.back()->display.newPoly();
					models.back()->setDisplayType(false);
					models.back()->display.addVertex(x,y,z,u,v);
				
				}
				else if(x != 10101010010010101){
					models.back()->display.addVertex(x,y,z,u,v);
				}

				curLoc = &location;

				location = "empty";
				x = 10101010010010101;
			}	
		}
	}

	interactModels.spawnSprite("player",-2,0,0);
	fclose(filein);
	for(int a=0;a<models.size();a++) {
		models[a]->calculateMath();
	}
	return;
}

int LoadGLTextures() {
	texture[0] = texLoad::LoadGLTextures("Data/Dfloor.bmp",texture[0]);
	texture[1] = texLoad::LoadGLTextures("Data/greybrick.bmp",texture[1]);
	texture[2] = texLoad::LoadGLTextures("Data/carpet.bmp",texture[2]);
	texture[3] = texLoad::LoadGLTextures("Data/Rdoor.bmp",texture[3]);
	texture[4] = texLoad::LoadGLTextures("Data/floor2.bmp",texture[4]);
	texture[5] = texLoad::LoadGLTextures("Data/wall2.bmp",texture[5]);
	return TRUE;
}
int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	ot.erase();
	if (!LoadGLTextures())								// Jump To Texture Loading Routine
	{
		return FALSE;									// If Texture Didn't Load Return FALSE
	}
	rotateX = 0;
	doorAngle = 1;
	display.loadTextures();
	display.setMenu(false);
	glEnable(GL_TEXTURE_2D);							// Enable Texture Mapping
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);					// Set The Blending Function For Translucency
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// This Will Clear The Background Color To Black
	glClearDepth(1.0);									// Enables Clearing Of The Depth Buffer
	glDepthFunc(GL_LESS);								// The Type Of Depth Test To Do
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glShadeModel(GL_SMOOTH);							// Enables Smooth Color Shading
	quadratic=gluNewQuadric();			// Create A Pointer To The Quadric Object ( NEW )
	gluQuadricNormals(quadratic, GLU_SMOOTH);	// Create Smooth Normals ( NEW )
	gluQuadricTexture(quadratic, GL_TRUE);		// Create Texture Coords ( NEW )


	lighter.setupLighting();
	

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	//glFrontFace(GL_CW);
	SetupWorld();
	
	return TRUE;										// Initialization Went OK
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear The Screen And The Depth Buffer
	glLoadIdentity();									// Reset The View

	sel = false;
	int n = 0;
	double R = 0.1;
	double H = 0;
	double Z = 0;
	double K = 0;
	//floorColl();
	GLfloat x_m, y_m, z_m, u_m, v_m;
	GLfloat xtrans = -xpos;
	GLfloat ztrans = -zpos;
	GLfloat ytrans = -walkbias-0.25f - 0.5f - ypos;
	GLfloat sceneroty = 360.0f - yrot;
	
	// Move scene around camera position
	
	glRotatef(lookupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);
	glTranslatef(xtrans, ytrans, ztrans);
	glPushMatrix();
	glTranslatef(0.0f,0.0f,0.0f);	
	glRotatef(-90.0f,1.0f,0.0f,0.0f);	
	//gluCylinder(quadratic,1.0f,1.0f,3.0f,32,32);	// Draw Our Cylinder
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f,0.0f,10.0f);	
	glRotatef(-90.0f,1.0f,0.0f,0.0f);	
	//gluCylinder(quadratic,3.0f,3.0f,3.0f,32,32);	// Draw Our Cylinder
	glPopMatrix();
	//Position lights
	lighter.positionLights();

	// Colour check (can probably be removed
	//glColor3f(1.0, 1.0, 1.0);

	// Change texture for models, need to be moved to model class
	for (int loop_m = 0; loop_m < models.size(); loop_m++)
	{

		glPushMatrix();
		glMatrixMode(GL_MODELVIEW);
		if(models[loop_m]->getName()  == "ceili") {
			glBindTexture(GL_TEXTURE_2D, texture[2]);
		}
		else if(models[loop_m]->getName()  == "wall1") {
			glBindTexture(GL_TEXTURE_2D, texture[1]);
		}	
		else if(models[loop_m]->getName()  == "floor") {
			glBindTexture(GL_TEXTURE_2D, texture[0]);
		}
		else if(models[loop_m]->getName()  == "door1") {
			glBindTexture(GL_TEXTURE_2D, texture[3]);
		}
		else if(models[loop_m]->getName()  == "wall2") {
			glBindTexture(GL_TEXTURE_2D, texture[4]);
		}
		else if(models[loop_m]->getName()  == "flr02") {
			glBindTexture(GL_TEXTURE_2D, texture[5]);
		}
		models[loop_m]->build(lookupdown,sceneroty,xtrans, ytrans, ztrans);
		glPopMatrix();
		
	}
	//glColor3f(1.0, 0.0, 1.0);							// Random testing colour
	interactModels.checkCollision(models);					// Done here as needs current model list to check collision with


	//GLfloat LightPosition3[]= { 4.0,1.0,0.0, 1.0f };				 // Light Position ( NEW )
	//glLightfv(GL_LIGHT2, GL_POSITION,LightPosition2);			// Position The Light

	//GLfloat LightPosition4[]= { 4.0,1.0,0.0, 1.0f };				 // Light Position ( NEW )
	//glLightfv(GL_LIGHT2, GL_POSITION,LightPosition2);			// Position The Light

	// Builds and displays current interactive models

	glDisable(GL_LIGHTING);		// Disable Lighting
	interactModels.build(lookupdown,sceneroty,xtrans, ytrans, ztrans); 
	glEnable(GL_LIGHTING);		// Enable Lighting
	//display.showGui(0,0,0,0);							// Think this is pointless, test removal
	return TRUE;										// Everything Went OK
}



GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}
	display.setShape(width,height);
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop


	// Ask The User Which Screen Mode They Prefer
	if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Adam Spurrell Demo",640,480,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if ((active && !DrawGLScene()) || keys[VK_ESCAPE])	// Active?  Was There A Quit Received?
			{
				done=TRUE;							// ESC or DrawGLScene Signalled A Quit
			}
			else									// Not Time To Quit, Update Screen
			{
				SwapBuffers(hDC);					// Swap Buffers (Double Buffering)
				if (keys['B'] && !bp)
				{
					bp=TRUE;
					blend=!blend;
					if (!blend)
					{
						glDisable(GL_BLEND);
						glEnable(GL_DEPTH_TEST);
					}
					else
					{
						glEnable(GL_BLEND);
						glDisable(GL_DEPTH_TEST);
					}
				}
				if (!keys['B'])
				{
					bp=FALSE;
				}

				if (keys['F'] && !fp)
				{
					fp=TRUE;
					filter+=1;
					if (filter>2)
					{
						filter=0;
					}
				}
				if (keys[VK_F2]) {
					display.setMenu(true);
				}
				if (keys[VK_F3]) {
					display.setMenu(false);
				}

				// Interact with object e.g will open or close a door
				if(display.getMenu() == false && dead == false) {
					if (keys['E']) {
						if(time == 0) {
							Collision collisionSel(models,true);
							ColVector selStart(xpos,ypos,zpos);
							ColVector selDirection(-((float)sin(heading*piover180) * 0.60f),0,-((float)cos(heading*piover180) * 0.60f));
							bool detect = collisionSel.collisionTest(selStart.getVector(),selDirection.getVector());
							time = 10;
						}
					
					}
					if(time > 0) {
						time -= 1;
					}
					if (!keys['E'])
					{
						sel = false;
					}
					if (!keys['F'])
					{
						fp=FALSE;
					}

					if (keys[VK_PRIOR])
					{
						z-=0.02f;
					}

					if (keys[VK_NEXT])
					{
						z+=0.02f;
					}

					// Fire bullet from player, spawns bullet in ModelControl.
					if (keys[VK_SPACE]) {
						ot.out("HIT SPACE");
						interactModels.spawnBullet(xpos,0.3,zpos,-(float)sin(heading*piover180),(-(float)sin(lookupdown*piover180)),-(float)cos(heading*piover180));
						keys[VK_SPACE] = false;
					}

					// Determine if player is currently in midair and if so starts player falling.
					floorColl();

					// Move player forward
					if (keys[VK_UP])
					{
						// Calculate if player will collide if continuing on current vector
						Collision collision(models,sel);
						ColVector start(xpos,ypos,zpos);
						ColVector direction(-((float)sin(heading*piover180) * 0.55f),0,-((float)cos(heading*piover180) * 0.55f));
						bool detect = collision.collisionTest(start.getVector(),direction.getVector());
						if(detect == true) {
							// Determine if the collision detected was with a slope by checking if it collides at slightly higher y value.
							float height = 0.15;
							ColVector fstart(xpos,ypos+0.5,zpos);
							bool fDetect;
							fDetect = collision.collisionTest(fstart.getVector(),direction.getVector());
							// If it does not collide increase height (BAD REDO WITH MATH)
							if(fDetect == false) {
								ypos += height;
							}

							// Move player along a wall if moving diagonally into it

							// Determine if the collision was in the z direction, if no collision in z direction move player just in the z value
							ColVector zDirection(0,0,-((float)cos(heading*piover180) * 0.55f));
							bool zDetect;
							zDetect = collision.collisionTest(start.getVector(),zDirection.getVector());
							if(zDetect == false) {
								zpos -= (float)cos(heading*piover180) * 0.05f;
							}
							// Determine if the collision was in the y direction, if no collision in y direction move player just in the z value
							ColVector xDirection(-((float)sin(heading*piover180) * 0.55f),0,0);
							if(collision.collisionTest(start.getVector(),xDirection.getVector()) == false && zDetect == true) {
								xpos -= (float)sin(heading*piover180) * 0.05f;
							}
						}
						if(detect == false) {
							xpos -= (float)sin(heading*piover180) * 0.05f;
							zpos -= (float)cos(heading*piover180) * 0.05f;
						}

						if (walkbiasangle >= 359.0f)
						{
							walkbiasangle = 0.0f;
						}
						else
						{
							walkbiasangle+= 10;
						}
						walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
					}


					// Same as VK_UP except for moving backwards
					if (keys[VK_DOWN])
					{
						Collision collision(models,sel);
						ColVector start(xpos,ypos,zpos);
						ColVector direction(((float)sin(heading*piover180) * 0.55f),0,((float)cos(heading*piover180) * 0.55f));
						bool detect = collision.collisionTest(start.getVector(),direction.getVector());
						if(detect == true) {
							float height = 0.15;
							ColVector fstart(xpos,ypos+0.5,zpos);
							bool fDetect;
							fDetect = collision.collisionTest(fstart.getVector(),direction.getVector());
							if(fDetect == false) {
								ypos += height;
							}
							ColVector zDirection(0,0,((float)cos(heading*piover180) * 0.55f));
							if(collision.collisionTest(start.getVector(),zDirection.getVector()) == false) {
								zpos += (float)cos(heading*piover180) * 0.05f;
							}
							ColVector xDirection(((float)sin(heading*piover180) * 0.55f),0,0);
							if(collision.collisionTest(start.getVector(),xDirection.getVector()) == false) {
								xpos += (float)sin(heading*piover180) * 0.05f;
							}
						}
						if(detect == false) {
							xpos += (float)sin(heading*piover180) * 0.05f;
							zpos += (float)cos(heading*piover180) * 0.05f;
						}
						if (walkbiasangle <= 1.0f)
						{
							walkbiasangle = 359.0f;
						}
						else
						{
							walkbiasangle-= 10;
						}
						walkbias = (float)sin(walkbiasangle * piover180)/20.0f;
					}

					// Turn right, Collision same as VK_UP
					if (keys[VK_RIGHT])
					{
						Collision collision(models,false);
						ColVector start(xpos,ypos,zpos);
						ColVector direction(((float)sin((heading-2.0f)*piover180) * 0.02f),0,((float)cos((heading-2.0f)*piover180) * 0.02f));
						bool detect = collision.collisionTest(start.getVector(),direction.getVector());
						if(detect == false) {
							heading -= 2.0f;
							yrot = heading;
						}

					}

					// Turn left, Collision same as VK_UP
					if (keys[VK_LEFT])
					{
						Collision collision(models,false);
						ColVector start(xpos,ypos,zpos);
						ColVector direction(((float)sin((heading+2.0f)*piover180) * 0.02f),0,((float)cos((heading+2.0f)*piover180) * 0.02f));
						bool detect = collision.collisionTest(start.getVector(),direction.getVector());
						if(detect == false) {
							heading += 2.0f;	
							yrot = heading;
						}
					}

					if (keys[VK_PRIOR])
					{
						lookupdown-= 1.0f;
					}

					if (keys[VK_NEXT])
					{
						lookupdown+= 1.0f;
					}
				}
				if (keys[VK_F1])						// Is F1 Being Pressed?
				{
					keys[VK_F1]=FALSE;					// If So Make Key FALSE
					KillGLWindow();						// Kill Our Current Window
					fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
					// Recreate Our OpenGL Window
					if (!CreateGLWindow("Lionel Brits & NeHe's 3D World Tutorial",640,480,16,fullscreen))
					{
						return 0;						// Quit If Window Was Not Created
					}
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();										// Kill The Window
	//Output::close();
	return (msg.wParam);								// Exit The Program

}

