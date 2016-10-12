/*
bouncing balls animation using OpenGL and Glut
*/

#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#  include <GL/glut.h>

const double pi = 4 * atan(1.0);
const double R = 15.0;   
const int DEFAULT_SCREEN_WIDTH = 800;
const int DEFAULT_SCREEN_HEIGHT = 400;
int screenWidth = DEFAULT_SCREEN_WIDTH;
int screenHeight = DEFAULT_SCREEN_HEIGHT;

class BouncingBall {

public:

	double x, vx, y, vy;

	BouncingBall(double x, double vx, double y, double vy) {
		this->x = x;
		this->vx = vx;
		this->y = y;
		this->vy = vy;
	}

	void step(double dt) {
		x += vx;
		y += vy;

		if (x >  R) vx = -abs(vx);      // bounce off right wall
		if (x < -R) vx = abs(vx);        // bounce off left wall
		if (y <  0) vy = abs(vy);        // bounce off floor
		if (y > R) vy = -abs(vy);
	}
};

int N = 1;            // number of balls
double v_max = 1;     // maximum initial speed
double dt = 0.01;     // time step for Euler method
double t = 0;             // simulation time
int step_number = 0;      // time step number


BouncingBall **balls;    // pointer to and array of ball pointers

void create_balls() {
	balls = new BouncingBall*[N];
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		int x = rand() % DEFAULT_SCREEN_WIDTH;
		int y = rand() % DEFAULT_SCREEN_HEIGHT;
		double vx = 0.02*(i+1);
		double vy = 0.1*(i+1);
		balls[i] = new BouncingBall(0, vx, 0, vy);
	}
}

// move each ball by one time step dt
void step() {
	for (int i = 0; i < N; i++)
		balls[i]->step(dt);
	t += dt;
	++step_number;
}

double frames_per_second = 30;   // for animation in real time

void animation_step() {
	double start = t;
	clock_t start_time = clock();
	step();
	double tau = 1.0 / frames_per_second;
	while (t - start < tau)
		step();
	while ((double(clock()) - start_time) / CLOCKS_PER_SEC < tau)
		;
	glutPostRedisplay();
}

void drawText(const string &str, double x, double y) {
	glRasterPos2d(x, y);
	int len = str.find('\0');
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, str[i]);
}

// Glut callback function to update the display
void display() {
	glClear(GL_COLOR_BUFFER_BIT);

	static GLubyte color_table[6][3] =
	{ { 255, 0, 0 },{ 0, 255, 0 },{ 0, 0, 255 },
	{ 0, 255, 255 },{ 255, 0, 255 },{ 255, 255, 0 } };
	for (int i = 0; i < N; i++) {
		glColor3ubv(color_table[i % 6]);
		glBegin(GL_TRIANGLE_FAN);
		glVertex2d(balls[i]->x, balls[i]->y);
		double phi = 2 * pi / 24;
		for (int j = 0; j < 25; j++)
			glVertex2d(balls[i]->x + 0.5 * cos(phi*j),
				balls[i]->y + 0.5 * sin(phi*j));
		glEnd();
	}
	glColor3ub(0, 0, 0);
	ostringstream os;
	//os << "Step No: " << step_number << "   Time t = " << t << ends;
	os << balls[0]->x << "; " << balls[0]->y << ends;
	//drawText(os.str(), -R + R / 50, R / 20);
	os.seekp(0);

	glutSwapBuffers();
}

// Glut callback function to reset the viewing transformation
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluOrtho2D(0, w, 0, h);
	glOrtho(-screenWidth / 2, screenWidth / 2 - 1, -screenHeight / 2, screenHeight / 2 - 1, -1, 1);
	//gluOrtho2D(-R-3, R-5, 0, R / w*(2.0*h));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	//get_input();
	create_balls();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Computer graphics lab1");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	glutIdleFunc(animation_step);
	glutMainLoop();
}