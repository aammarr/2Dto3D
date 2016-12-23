#include "GLRendering.h"

void GLRendering::DrawGrid(int size) {
	glBegin(GL_LINES);
	glColor3f(0, 0.75, 1);
	for (int i = -size; i <= size; i++) {
		glVertex3f(-size, 0, i);
		glVertex3f(size, 0, i);

		glVertex3f(i, 0, -size);
		glVertex3f(i, 0, size);
	}
	glEnd();
}

void GLRendering::DrawRoom(int size) {
	float hsize = size / 2.0f;
	//float newSize = hsize*1.5;
	glBegin(GL_QUADS);

	// Floor  
	glColor3f(0, 0, 0);
	glVertex3f(-hsize, -hsize, -hsize);
	glVertex3f(-hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, -hsize);

	//Ceiling 
	glColor3f(0, 0, 1);
	glVertex3f(-hsize, hsize, -hsize);
	glVertex3f(-hsize, hsize, hsize);
	glVertex3f(hsize, hsize, hsize);
	glVertex3f(hsize, hsize, -hsize);

	// Walls 
	glColor3f(1, 1, 0);
	glVertex3f(-hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, hsize);
	glVertex3f(hsize, hsize, hsize);
	glVertex3f(-hsize, hsize, hsize);

	glVertex3f(hsize, -hsize, -hsize);
	glVertex3f(-hsize, -hsize, -hsize);
	glVertex3f(-hsize, hsize, -hsize);
	glVertex3f(hsize, hsize, -hsize);

	glVertex3f(hsize, hsize, hsize);
	glVertex3f(hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, -hsize);
	glVertex3f(hsize, hsize, -hsize);

	glVertex3f(-hsize, hsize, hsize);
	glVertex3f(-hsize, hsize, -hsize);
	glVertex3f(-hsize, -hsize, -hsize);
	glVertex3f(-hsize, -hsize, hsize);

	glEnd();
}

void GLRendering::readfile()
{
	// reading a text file

	std::string line;
	std::ifstream myfile("coordinates.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{

			std::cout << line << '\n';
			std::istringstream str(line);
			do
			{
				std::string s;
				str >> s;
				std::cout << s << std::endl;
			} while (str);


		}
		myfile.close();
	}

	else std::cout << "Unable to open file";

}

void GLRendering::DrawRoom1(int size) {

	float hsize = (size / 2.0f) * 2;


	glTranslated(hsize + 3, hsize + 3, hsize + 3);
	glScalef(8, 8, 8);



	//float newSize = hsize*1.5;
	glBegin(GL_QUADS);

	// Floor
	glColor3f(0.545, 0, 0);
	glVertex3f(-hsize, -hsize, -hsize);
	glVertex3f(-hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, -hsize);

	//Ceiling 
	glColor3f(0, 0, 0);
	glVertex3f(-hsize, hsize, -hsize);
	glVertex3f(-hsize, hsize, hsize);
	glVertex3f(hsize, hsize, hsize);
	glVertex3f(hsize, hsize, -hsize);

	// Walls 

	//left wall
	glColor3f(1, 0, 0);
	glVertex3f(-hsize * 5, -hsize * 5, hsize * 5);
	glVertex3f(hsize * 5, -hsize * 5, hsize * 5);
	glVertex3f(hsize * 5, hsize * 5, hsize * 5);
	glVertex3f(-hsize * 5, hsize * 5, hsize * 5);


	//right wall
	glVertex3f(hsize * 5, -hsize * 5, -hsize * 5);
	glVertex3f(-hsize * 5, -hsize * 5, -hsize * 5);
	glVertex3f(-hsize * 5, hsize * 5, -hsize * 5);
	glVertex3f(hsize * 5, hsize * 5, -hsize * 5);


	//front wall
	glVertex3f(hsize, hsize, hsize);
	glVertex3f(hsize, -hsize, hsize);
	glVertex3f(hsize, -hsize, -hsize);
	glVertex3f(hsize, hsize, -hsize);

	//back wall
	glVertex3f(-hsize * 5, hsize * 5, hsize * 5);
	glVertex3f(-hsize * 5, hsize * 5, -hsize * 5);
	glVertex3f(-hsize * 5, -hsize * 5, -hsize * 5);
	glVertex3f(-hsize * 5, -hsize * 5, hsize * 5);

	glEnd();
}



void GLRendering::DrawPoints() {
	glScalef(0.5, 0.5, 0.5);

	glBegin(GL_POINTS);
	for (int z = -N; z <= N; ++z) {
		for (int x = -N; x <= N; ++x) {
			float r = (x + N) / (2.0f*N);
			float b = (z + N) / (2.0f*N);
			glColor3f(0, 1, b);
			float y = sinf(x + t);
			//float y = sinf(z + t);
			//float y = sinf(x + z + t);
			//float y = sinf(10*sqrtf(x*x + z*z)+t);
			glVertex3f(x, y, z);
		}
	}
	glEnd();
}


void GLRendering::OnRender() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//gluLookAt(5, 5, N, 0, 0, 0, 0, 1, 0);
	MV = glm::lookAt(glm::vec3(10, 5, 0), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	glLoadMatrixf(glm::value_ptr(MV));

	DrawGrid();

	/*glBegin(GL_TRIANGLES);
	glVertex3f(-2, 0, -2);
	glVertex3f(0, 2, 2);
	glVertex3f(2, 0, -2);*/
	glEnd();

	DrawRoom(4);
	DrawRoom1(1);

	//	DrawPoints();

	glutSwapBuffers();
}

void GLRendering::OnInit() {
	glClearColor(1, 1, 1, 1);
	glPointSize(51);

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_BACK, GL_LINE);

	/*glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::mat4 view;
	view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);*/

}



void GLRendering::OnResize(int nw, int nh) {
	glViewport(0, 0, nw, nh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, float(nw) / nh, 0.1f, 100);

	glMatrixMode(GL_MODELVIEW);
}


void GLRendering::OnIdle() {
	t += 0.1f;
	glutPostRedisplay();
}
