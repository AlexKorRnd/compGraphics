#include <cmath>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#  include <GL/glut.h>

const double pi = 4 * atan(1.0);
const int DEFAULT_SCREEN_WIDTH = 800;
const int DEFAULT_SCREEN_HEIGHT = 400;
int screenWidth = DEFAULT_SCREEN_WIDTH;
int screenHeight = DEFAULT_SCREEN_HEIGHT;
const int MAX_SPEED = 10;
const int BALL_RADIUS = 25;
double frames_per_second = 60;
const int COUNT_BALLS = 6;

double dt = 0.03;
double curTime = 0;
int step_number = 0;

class Ball
{
public:

	double x, vx, y, vy;
	double r;
	bool isDamagedMode;
	bool isNearWallMode[4];

	Ball(double x, double vx, double y, double vy, double r)
	{
		this->x = x;
		this->vx = vx;
		this->y = y;
		this->vy = vy;
		this->r = r;
	}

	void step(double dt)
	{
		x += vx;
		y += vy;


		if (x >= screenWidth - r)
		{
			if (!isNearWallMode[2])
			{
				vx *= -1;
				isNearWallMode[2] = true;
			}
		} else
		{
			isNearWallMode[2] = false;
		}

		if (x <= r) {
			if (!isNearWallMode[0])
			{
				vx *= -1;
				isNearWallMode[0] = true;
			}
		} else
		{
			isNearWallMode[0] = false;
		}

		if (y <= r) {
			if (!isNearWallMode[3])
			{
				vy *= -1;
				isNearWallMode[3] = true;
			}
		} else
		{
			isNearWallMode[3] = false;
		}

		if (y >= screenHeight - r) {
			if (!isNearWallMode[1])
			{
				vy *= -1;
				isNearWallMode[1] = true;
			}
		} else
		{
			isNearWallMode[1] = false;
		}
	}
};


Ball** balls; // pointer to and array of ball pointers

void create_balls()
{
	balls = new Ball*[COUNT_BALLS];
	srand(time(NULL));
	for (int i = 0; i < COUNT_BALLS; i++)
	{
		double vx = 1 + rand() % (MAX_SPEED - 1);
		double vy = 1 + rand() % (MAX_SPEED - 1);
		int r = 5 + rand() % (BALL_RADIUS -5);
		// min + rand() % (max - min);
		int x = r + rand() % (DEFAULT_SCREEN_WIDTH - r);
		int y = r + rand() % (DEFAULT_SCREEN_HEIGHT - r);
		balls[i] = new Ball(x, vx, y, vy, r);
		cout << "balls[i]: vx = " << vx << "  vy = " << vy << "  x = " << x << "  y = " << y << endl;
	}
}

void checkDamages()
{
	for (int i = 0; i < COUNT_BALLS; i++)
	{
		Ball* ball = balls[i];
		for (int j = i + 1; j < COUNT_BALLS; j++)
		{
			Ball* ball2 = balls[j];
			int length = sqrt(pow(ball->x - ball2->x, 2) + (pow(ball->y - ball2->y, 2)));
			if (length <= (ball->r + ball2->r))
			{
				if (!ball->isDamagedMode)
				{
					ball->vx *= -1;
					ball->vy *= -1;
					ball->isDamagedMode = true;
				}
				if (!ball2->isDamagedMode)
				{
					ball2->vx *= -1;
					ball2->vy *= -1;
					ball2->isDamagedMode = true;
				}
			}
			else
			{
				ball->isDamagedMode = false;
				ball2->isDamagedMode = false;
			}
		}
	}
}

// move each ball by one time step dt
void step()
{
	for (int i = 0; i < COUNT_BALLS; i++)
		balls[i]->step(dt);
	checkDamages();

	curTime += dt;
	++step_number;
}


void animation_step()
{
	double start = curTime;
	clock_t start_time = clock();
	step();
	double tau = 1.0 / frames_per_second;
	while (curTime - start < tau)
		step();
	while ((double(clock()) - start_time) / CLOCKS_PER_SEC < tau);
	glutPostRedisplay();
}

void drawFilledCircle(GLfloat x, GLfloat y, GLfloat radius)
{
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	//GLfloat radius = 0.8f; //radius
	GLfloat twicePi = 2.0f * pi;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++)
	{
		glVertex2f(
			x + (radius * cos(i * twicePi / triangleAmount)),
			y + (radius * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();
}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT);

	static GLubyte color_table[6][3] =
	{{255, 0, 0},{0, 255, 0},{0, 0, 255},
		{0, 255, 255},{255, 0, 255},{255, 255, 0}};
	for (int i = 0; i < COUNT_BALLS; i++)
	{
		glColor3ubv(color_table[i % 6]);
		drawFilledCircle(balls[i]->x, balls[i]->y, balls[i]->r);
	}
	glutSwapBuffers();
}


void reshape(int w, int h)
{
	double changedWeight = (double) w / screenWidth;
	double changedHeight = (double) h / screenHeight;
	double part = (double)(w * h) / (screenWidth * screenHeight);
	cout << "screenWidth = " << screenWidth << "  screenHeight = " << screenHeight;
	cout << "  w = " << w << "  h = " << h;
	cout << "  changedWeight = " << changedWeight << "  changedHeight = " << changedHeight;
	cout << "  part = " << part << endl;
	for (int i = 0; i < COUNT_BALLS; i++)
	{
		balls[i]->x = round(balls[i]->x * changedWeight);
		balls[i]->y = round(balls[i]->y * changedHeight);
		balls[i]->r = balls[i]->r * part;
		cout << "balls[" << i << "]->r = " << balls[i]->r << "  ";
	}
	cout << endl;
	screenWidth = w;
	screenHeight = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	create_balls();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(DEFAULT_SCREEN_WIDTH, DEFAULT_SCREEN_HEIGHT);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Computer graphics lab1");
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_FLAT);
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutIdleFunc(animation_step);
	glutMainLoop();
}
