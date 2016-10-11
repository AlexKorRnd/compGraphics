
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
#  include <GL/glut.h>

const double pi = 4 * atan(1.0);
//const double g = 9.8;
const double L = 10.0;     // physical region: -L < x < L and 0 < y < L
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;

class Ball {

public:

	double x, y, vx, vy;

	Ball(double x, double y, double vx, double vy) {
		this->x = x;
		this->vx = vx;
		this->y = y;
		this->vy = vy;
	}

	void step() {
		x += vx;
		y += vy;

		if (x >  SCREEN_WIDTH) vx = -abs(vx);      // bounce off right wall
		if (x < 0) vx = abs(vx);        // bounce off left wall
		if (y <  0) vy = abs(vy);        // bounce off floor
		if (y > SCREEN_HEIGHT) vy = -abs(vy);
	}
};

int N = 10;            // number of balls
int vMax = 20;     // maximum initial speed
double dt = 0.001;     
double t = 0;             // simulation time
int step_number = 0;      // time step number

/*void get_input() {
	cout << "Bouncing balls simulation" << endl;
	cout << "-------------------------" << endl;
	cout << "Enter number of balls: " << flush;
	cin >> N;
	if (N < 1) N = 2;
	cout << "Enter maximum speed: " << flush;
	cin >> vMax;
	if (vMax < 0) vMax = -vMax;
	cout << "Enter time step dt: " << flush;
	cin >> dt;
	t = 0;
	step_number = 0;
}*/

double generateV()
{
	int v = 0;
	while (v == 0)
	{
		v = rand() % vMax;
	};
	return v;
}

Ball **balls;    // pointer to and array of ball pointers

void create_balls() {
	balls = new Ball*[N];
	srand(time(NULL));
	for (int i = 0; i < N; i++) {
		//double theta = pi * rand() / double(RAND_MAX);
		int x = rand() % SCREEN_WIDTH;
		int y = rand() % SCREEN_HEIGHT;
		double vx = generateV();
		double vy = generateV();
		balls[i] = new Ball(x, y, vx, vy);
	}
}



// move each ball by one time step dt
void step() {
	for (int i = 0; i < N; i++)
		balls[i]->step();
	t += dt;
	++step_number;
}

double frames_per_second = 24;   // for animation in real time

void animation_step() {
	double start = t;
	clock_t start_time = clock();
	step();
	/*double tau = 1.0 / frames_per_second;
	while (t - start < tau)
		step();
	while ((double(clock()) - start_time) / CLOCKS_PER_SEC < tau)
		;*/
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
	os << "Step No: " << step_number << "   Time t = " << t << ends;
	drawText(os.str(), -L + L / 50, L / 20);
	os.seekp(0);

	glutSwapBuffers();
}

// Glut callback function to reset the viewing transformation
void reshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-L, L, 0, L / w*(2.0*h));
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

bool running = true;   // is the animation running

						// Glut mouse callback function
/*void mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			if (running) {
				glutIdleFunc(NULL);
				running = false;
			}
			else {
				glutIdleFunc(animation_step);
				running = true;
			}
		}
	}
}*/

int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	//get_input();
	create_balls();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Bouncing Balls Animation");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	glutIdleFunc(animation_step);
	glutMainLoop();
}