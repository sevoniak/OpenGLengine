//OpenGLEngine by Sebastian Evoniak
//Copyright 2015

// INCLUDES
#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <glew.h>
#include <glut.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include <time.h>
#include "Defs.h"
#include "Camera.h"
#include "InputManager.h"
#include "Shader.h"
#include "ShapeMaker.h"
#include "GameObject.h"


// FORWARD DECS
bool initAppObjects();
bool initShaders();
bool initShapes();
bool initGameObjects();
void cleanup();
void resizeWin(int w, int h);
void display();
void timer(int id);
void renderWin();
void normalKeyDown(unsigned char key, int x, int y);
void specialKeyDown(int key, int x, int y);
void normalKeyUp(unsigned char key, int x, int y);
void specialKeyUp(int key, int x, int y);
void handleInput();
void updateGameState();
void calcFPS();
using std::vector;


// GLOBAL VARS
bool CAP_FRAMES = true;
WindowInfo winfo = {};
InputManager* input;
Camera* cam;
Shader** shaders;
Shape** shapes;
ShapeMaker* shapeMaker;
Matrix4 perspectiveProjectionMatrix;
Matrix4 orthographicProjectionMatrix;
vector<GameObject*> objects;

// SOURCE

int main(int argc, char* argv[])
{
	//basic values for window
	winfo.width = 1280;
	winfo.height = 720;
	winfo.FoV_Y = 50.0f;
	winfo.zNear = 0.1f;
	winfo.zFar = 1000.0f;
	winfo.title = "OpenGLEngine";
	winfo.aspectRatio = ((float) winfo.width) / ((float) winfo.height);

	//initialize glut
	glutInit(&argc, argv);
    glutInitWindowPosition(100, 100);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(winfo.width, winfo.height);
    
	//create window and register callback functions 
	winfo.windowID = glutCreateWindow(winfo.title.c_str());
    glutReshapeFunc(resizeWin);
	if (CAP_FRAMES)
		glutDisplayFunc(display);
	else
	{
		glutDisplayFunc(renderWin);
		glutIdleFunc(renderWin);
	}
	glutKeyboardFunc(normalKeyDown);
	glutSpecialFunc(specialKeyDown);
	glutKeyboardUpFunc(normalKeyUp);
	glutSpecialUpFunc(specialKeyUp);

	//initialize render options
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(0.0f, 1.0f);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
/*
	glPointSize(5);
	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
*/
/*
	glLineWidth(2);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
*/
	//initialize objects, shaders, geometry, etc...
	glewInit();
	if (!initAppObjects())
		cerr << "error initializing the application";
	if (!initShaders())
		cerr << "error initializing the shaders";
	if (!initShapes())
		cerr << "error initializing the shapes";
	if (!initGameObjects())
		cerr << "error initializing the objects";

	glutMainLoop();
    
	cleanup();
    return 0;
}

bool initAppObjects()
{
	input = new InputManager();
	cam = new Camera();
	shapeMaker = new ShapeMaker();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	perspectiveProjectionMatrix = createPerspectiveProjectionMatrix(winfo.FoV_Y, winfo.aspectRatio, winfo.zNear, winfo.zFar);
	orthographicProjectionMatrix = createOrthographicProjectionMatrix((float)winfo.width, (float)winfo.height, winfo.zNear, winfo.zFar);

	return true;
}

bool initShaders()
{
	shaders = new Shader*[NUMSHADERS];
	for (int i = 0; i < NUMSHADERS; i++)
		shaders[i] = nullptr;

	//load shaders
	shaders[0] = new Shader("BasicShader");
	shaders[1] = new Shader("ColorShader");
	shaders[2] = new Shader("GouraudShader");
	shaders[3] = new Shader("PhongShader");

	//validate shaders
	for (int i = 0; i < NUMSHADERS; i++)
		if (!shaders[i]->isValid())
			return false;
	return true;
}

bool initShapes()
{
	shapes = new Shape*[NUMSHAPES];
	for (int i = 0; i < NUMSHAPES; i++)
		shapes[i] = nullptr;

	//define shapes
	shapes[SHAPE_QUAD] = shapeMaker->genQuad();
	shapes[SHAPE_CUBE] = shapeMaker->genCube();
	shapes[SHAPE_PRISM] = shapeMaker->genPrism(15);
	shapes[SHAPE_CONE] = shapeMaker->genCone(10);
	shapes[SHAPE_SPHERE] = shapeMaker->genSphere(25,25);
	shapes[SHAPE_TORUS] = shapeMaker->genTorus(30,50,0.6f,0.3f);
	return true;
}

bool initGameObjects()
{
	int nv = shapes[SHAPE_QUAD]->getNumVerts();
	Vector4* cols = new Vector4[nv];
	for (int i = 0; i < nv; i++)
		cols[i] = Vector4(0.4f, 0.4f, 0.4f, 1.0f);//(float)(rand()%2), (float)(rand()%2), (float)(rand()%2), 1);
	GameObject* obj = new GameObject(shapes[SHAPE_QUAD], shaders[SHADER_COLOR], cols);
	obj->rotateX(90);
	obj->translateAbs(Vector3(0,-2,0));
	obj->scale(Vector3(10,10,1));
	objects.push_back(obj);

	nv = shapes[SHAPE_CONE]->getNumVerts();
	obj = new GameObject(shapes[SHAPE_CONE], shaders[SHADER_BASIC], 0);
	obj->translateAbs(Vector3(0,2,0));
	obj->scale(Vector3(2,2,2));
	objects.push_back(obj);

	nv = shapes[SHAPE_CUBE]->getNumVerts();
	obj = new GameObject(shapes[SHAPE_CUBE], shaders[SHADER_BASIC], 0);
	obj->scale(Vector3(2,2,2));
	obj->translateAbs(Vector3(-3,2,0));
	objects.push_back(obj);

	nv = shapes[SHAPE_PRISM]->getNumVerts();
	obj = new GameObject(shapes[SHAPE_PRISM], shaders[SHADER_BASIC], 0);
	obj->scale(Vector3(2,2,2));
	obj->rotateX(90.0f);
	obj->translateAbs(Vector3(3,2,0));
	objects.push_back(obj);

	nv = shapes[SHAPE_TORUS]->getNumVerts();
	cols = new Vector4[nv];
	for (int i = 0; i < nv; i++)
		cols[i] = Vector4((float)(rand()%2), (float)(rand()%2), (float)(rand()%2), 1);
	obj = new GameObject(shapes[SHAPE_TORUS], shaders[SHADER_COLOR], cols);
	objects.push_back(obj);

	obj = new GameObject(shapes[SHAPE_TORUS], shaders[SHADER_PHONG], 0);
	objects.push_back(obj);
	obj->translateAbs(Vector3(-3,0,0));

	obj = new GameObject(shapes[SHAPE_CONE], shaders[SHADER_PHONG], 0);
	obj->rotateX(90);
	obj->translateAbs(Vector3(3,0,0));
	objects.push_back(obj);
	return true;
}

void cleanup ()
{
	if (input) delete input;
	if (cam) delete cam;
	if (shaders)
	{
		for (int i = 0; i < NUMSHADERS; i++)
			if (shaders[i]) 
				delete shaders[i];
		delete[] shaders;
	}
	if (shapes)
	{
		for (int i = 0; i < NUMSHAPES; i++)
			if (shapes[i]) 
				delete shapes[i];
		delete[] shapes;
	}
	if (shapeMaker) delete shapeMaker;
	for (unsigned int i = 0; i < objects.size(); i++)
	{
		if (objects[i])
			delete objects[i];
	}
}

void resizeWin(int w, int h)
{
	winfo.width =  w;
	winfo.height =  h;
    glViewport(0, 0, (GLsizei) winfo.width, (GLsizei) winfo.height);
}

void display()
{
	glutTimerFunc(17, timer, 1);

	renderWin();
}

void timer(int id)
{
	glutPostRedisplay();
}

void renderWin()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	calcFPS();
	handleInput();

	updateGameState();

	Matrix4 viewMatrix = cam->getViewMatrix();

	//render models
	for (unsigned int i = 0; i < objects.size(); i++)
		objects.at(i)->render(viewMatrix, perspectiveProjectionMatrix);
	
	glutSwapBuffers();
}

void normalKeyDown(unsigned char key, int x, int y)
{
	input->keyDown(key);
}

void specialKeyDown(int key, int x, int y)
{
	input->keyDown(key+INPUTOFFSET);
}

void normalKeyUp(unsigned char key, int x, int y)
{
	input->keyUp(key);
}

void specialKeyUp(int key, int x, int y)
{
	input->keyUp(key+INPUTOFFSET);
}

void handleInput()
{
	// camera control keys - translations
	if(input->isKeyDown('a'))
		cam->strafe(-SPEED_STRAFE);
	if(input->isKeyDown('d'))
		cam->strafe(SPEED_STRAFE);
	if(input->isKeyDown('w'))
		cam->moveForward(SPEED_STRAFE);
	if(input->isKeyDown('s'))
		cam->moveForward(-SPEED_STRAFE);
	if(input->isKeyDown('r'))
		cam->crane(SPEED_STRAFE);
	if(input->isKeyDown('f'))
		cam->crane(-SPEED_STRAFE);

	// camera control keys - rotations
	if(input->isKeyDown('q'))
		cam->roll(-SPEED_ROTATE);
	if(input->isKeyDown('e'))
		cam->roll(SPEED_ROTATE);
	if(input->isKeyDown(GLUT_KEY_UP+INPUTOFFSET))
		cam->pitch(SPEED_ROTATE);
	if(input->isKeyDown(GLUT_KEY_DOWN+INPUTOFFSET))
		cam->pitch(-SPEED_ROTATE);
	if(input->isKeyDown(GLUT_KEY_RIGHT+INPUTOFFSET))
		cam->yaw(-SPEED_ROTATE);
	if(input->isKeyDown(GLUT_KEY_LEFT+INPUTOFFSET))
		cam->yaw(SPEED_ROTATE);

	//general keys
	if (input->isKeyDown(27))	//escape
		exit(0);
}

void calcFPS()
{
	static float t = 0.0f;
	static float previous_t = 0.0f;
	static int sampleCount = 0;
	static float sampleStartTime = 0.0f;

    static DWORD dwTimeStart = 0;

    DWORD dwTimeCur = GetTickCount();
    if( dwTimeStart == 0 ) dwTimeStart = dwTimeCur;
	previous_t = t;
	t = ( dwTimeCur - dwTimeStart ) / 1000.0f; //elapsed time in seconds
	if(t -sampleStartTime > 1.0){
		//produce FPS stats every second
		sampleCount++;
		float averageFramePeriod = (t-sampleStartTime)/sampleCount;
		sampleCount = 0;
		sampleStartTime = t;

		std::stringstream captionStrm;
		int ms = (int)averageFramePeriod;
		int mss = (int)(10*averageFramePeriod) - 10*ms;
		captionStrm << "OpenGLEngine. FPS: " << (int)(1.0f/averageFramePeriod) << ", frame time: " << ms << "." << mss << "ms";
		string str = captionStrm.str();
		const char* c = str.c_str();
        glutSetWindowTitle(c); //use FPS stats as title caption to windows window.

	}
	else{
		sampleCount++;
	}
}

void updateGameState()
{
	if (CAP_FRAMES)
	{
		for (unsigned int i = 1; i < objects.size(); i++)
			objects[i]->rotateY(1.0f);
	}
	else
	{
		for (unsigned int i = 1; i < objects.size(); i++)
			objects[i]->rotateY(0.01f);
	}
	
}