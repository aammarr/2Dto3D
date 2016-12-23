#include<GL/freeglut.h>
//#include<GL/freeglut_std.h>
#include <cmath>
#include <cassert>
//#include<GL/glut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include<sstream>

class GLRendering
{
	const int width = 512;
	const int height = 512;
	int angle = 0;
	const int N = 5;
	float t = 0;
	glm::mat4 MV;
	glm::mat4 P;

public:
	void OnResize(int nw, int nh);
	void OnIdle();
	void OnInit();
	void OnRender();
	void DrawPoints();
	void DrawRoom1(int size = 7);
	void readfile();
	void DrawRoom(int size = 7);
	void DrawGrid(int size = 21);
};