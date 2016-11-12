#include <windows.h>
#include <stdlib.h> 
#include <time.h>
#include <glut.h>
#include <math.h>

float width_win = 700;
float higth_win = 700;
float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
float pos[] = { width_win / 2, higth_win / 2, 250.0, 0.0 };
float pos2[] = { 0, 0, 500.0, 0.0 };
float angel = 0.0;
float rot = 0.0;
float scal = 0.0;
//float z_rot = 0.0;
float ambient[4] = { 0.5, 0.5, 0.5, 1 };
GLfloat front_color[] = { 0,1,0,1 };
GLfloat back_color[] = { 0,0,1,1 };

struct Coord {
	int x;
	int y;
	int z;
};

struct Color {
	double red;
	double green;
	double blue;
};

void drawParallelogram(Color color, Coord start, int heightX, int heightY, int heightZ) {
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(color.red, color.green, color.blue);

	//грань 1
	glBegin(GL_QUADS);
	glVertex3f(start.x, start.y, start.z);
	glVertex3f(start.x, start.y + heightY, start.z);
	glVertex3f(start.x + heightX, start.y + heightY, start.z);
	glVertex3f(start.x + heightX, start.y, start.z);
	glEnd();

	//грань 2
	glBegin(GL_QUADS);
	glVertex3f(start.x, start.y, start.z + heightZ);
	glVertex3f(start.x, start.y + heightY, start.z + heightZ);
	glVertex3f(start.x, start.y + heightY, start.z);
	glVertex3f(start.x, start.y, start.z);
	glEnd();
	
	//glColor3f(0, 0, 1);
	//грань 3
	glBegin(GL_QUADS);
	glVertex3f(start.x + heightX, start.y, start.z + heightZ);
	glVertex3f(start.x + heightX, start.y + heightY, start.z + heightZ);
	glVertex3f(start.x, start.y + heightY, start.z + heightZ);
	glVertex3f(start.x, start.y, start.z + heightZ);
	glEnd();

	//glColor3f(1, 1, 1);
	//грань 4
	glBegin(GL_QUADS);
	glVertex3f(start.x + heightX, start.y, start.z);
	glVertex3f(start.x + heightX, start.y + heightY, start.z);
	glVertex3f(start.x + heightX, start.y + heightY, start.z + heightZ);
	glVertex3f(start.x + heightX, start.y, heightZ);
	glEnd();

	//грань 5
	glBegin(GL_QUADS);
	glVertex3f(start.x + heightX, start.y + heightY, start.z);
	glVertex3f(start.x, start.y + heightY, start.z);
	glVertex3f(start.x, start.y + heightY, start.z + heightZ);
	glVertex3f(start.x + heightX, start.y + heightY, start.z + heightZ);
	glEnd();

	//грань 6
	glBegin(GL_QUADS);
	glVertex3f(start.x + heightX, start.y, start.z);
	glVertex3f(start.x + heightX, start.y, start.z + heightZ);
	glVertex3f(start.x, start.y, start.z + heightZ);
	glVertex3f(start.x, start.y, start.z);
	glEnd();

	glPopMatrix();
}

void Draw_sh() {



	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float size = 50;
	glEnable(GL_DEPTH_TEST);//проверка глубины
	GLUquadricObj *quadObj;
	quadObj = gluNewQuadric();

	// основание(фигура 2)
	Coord startFig2 = { 0, -200, 0 };
	Color color = { 0.3, 0.3, 0.3 };
	int lengthFig2X = 300, lengthFig2Y = 20, lengthFig2Z = 300;
	drawParallelogram(color, startFig2, lengthFig2X, lengthFig2Y, lengthFig2Z);

	// параллелограм над подставкой(фигура 3)
	color = {0.8, 0, 0};
	int marginRelativeFig2X = 50, marginRelativeFig2Z = 20;
	Coord startFig3 = { startFig2.x + marginRelativeFig2X, startFig2.y + lengthFig2Y + 1, startFig2.z + marginRelativeFig2Z };
	int lengthFig3X = lengthFig2X - 2 * marginRelativeFig2X;
	int lengthFig3Y = 150;
	int lengthFig3Z = lengthFig2Z - 2 * marginRelativeFig2Z;
	drawParallelogram(color, startFig3, lengthFig3X, lengthFig2Y, lengthFig3Z);
	
	// параллелограм над параллелограмом над подставкой(фигура 4)
	color = { 0.7, 0, 0 };
	int marginRelativeFig3X = 20;
	Coord startFig4 = { startFig3.x + marginRelativeFig3X, startFig3.y + lengthFig2Y + 1, startFig3.z};
	int lengthFig4X = lengthFig3X - marginRelativeFig3X;
	int lengthFig4Y = 125;
	int lengthFig4Z = lengthFig3Z;
	drawParallelogram(color, startFig4, lengthFig4X, lengthFig4Y, lengthFig4Z);

	// фигура 5
	color = { 0.6, 0, 0 };
	int marginRelativeFig4X = 20;
	Coord startFig5 = { startFig4.x + marginRelativeFig4X, startFig4.y + lengthFig4Y + 1, startFig4.z };
	int lengthFig5X = lengthFig4X - marginRelativeFig4X;
	int lengthFig5Y = 80;
	int lengthFig5Z = lengthFig3Z;
	drawParallelogram(color, startFig5, lengthFig5X, lengthFig5Y, lengthFig5Z);

	//фигура 6
	color = { 0.83,  0.83,  0.83 };
	int lengthFig6X = 100;
	int lengthFig6Y = 20;
	int lengthFig6Z = 50;
	int marginRelativeFig5Y = (lengthFig5Y - lengthFig6Y) / 2;
	int marginRelativeFig5Z = 40;
	Coord startFig6 = { startFig5.x - lengthFig6X + 1, startFig5.y + marginRelativeFig5Y,startFig5.z + marginRelativeFig5Z};
	drawParallelogram(color, startFig6, lengthFig6X, lengthFig6Y, lengthFig6Z);

	//фигура 7
	color = { 0, 0,  0 };
	int lengthFig7X = 130;
	int lengthFig7Y = 30;
	int lengthFig7Z = 50;
	int marginRelativeFig5Y_2 = (lengthFig5Y - lengthFig6Y) / 2;
	int marginRelativeFig5Z_2 = marginRelativeFig5Z + lengthFig6Z + 80;
	Coord startFig7 = { startFig5.x - lengthFig7X + 1, startFig5.y + marginRelativeFig5Y_2,startFig5.z + marginRelativeFig5Z_2 };
	drawParallelogram(color, startFig7, lengthFig7X, lengthFig7Y, lengthFig7Z);

	////оси
	glPushMatrix();	
	glTranslatef(0, 0, 0);

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(-600,0,0);
	glVertex3f(400,0,0);
	glEnd();
	glPopMatrix();

	glPushMatrix();	
	glTranslatef(0, 0, 0);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(0,-400,0);
	glVertex3f(0,400,0);
	glEnd();
	glPopMatrix();

	glPushMatrix();	
	glTranslatef(0, 0, 0);
	glBegin(GL_LINES);
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(0,0,-400);
	glVertex3f(0,0,400);
	glEnd();
	glPopMatrix();

	//glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();


}







void Keyboard(unsigned char key, int x, int y) {

	switch (key) {
		//вращение
	case 'd':
		angel = 0;
		angel++;
		glRotatef(angel, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case 'a':
		angel = 0;
		angel--;
		glRotatef(angel, 0.0, 1.0, 0.0);
		glutPostRedisplay();
		break;
	case 'w':
		angel = 0;
		angel--;
		glRotatef(angel, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case 's':
		angel = 0;
		angel++;
		glRotatef(angel, 1.0, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case 'x':
		angel = 0;
		angel--;
		glRotatef(angel, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
	case 'z':
		angel = 0;
		angel++;
		glRotatef(angel, 0.0, 0.0, 1.0);
		glutPostRedisplay();
		break;
		//движение по осям
	case '6':
		rot = 0;
		rot++;
		glTranslatef(rot, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case '4':
		rot = 0;
		rot--;
		glTranslatef(rot, 0.0, 0.0);
		glutPostRedisplay();
		break;
	case '8':
		rot = 0;
		rot++;
		glTranslatef(0.0, rot, 0.0);
		glutPostRedisplay();
		break;
	case '2':
		rot = 0;
		rot--;
		glTranslatef(0.0, rot, 0.00);
		glutPostRedisplay();
		break;
	case '9':
		rot = 0;
		rot--;
		glTranslatef(0.0, 0.0, rot);
		glutPostRedisplay();
		break;
	case '1':
		rot = 0;
		rot++;
		glTranslatef(0.0, 0.0, rot);
		glutPostRedisplay();
		break;

	}
}

void SKeyboard(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:

		scal = 1.0;
		scal += 0.05;
		glScalef(scal, scal, scal);
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:

		scal = 1.0;
		scal -= 0.05;
		glScalef(scal, scal, scal);
		glutPostRedisplay();
		break;
	}

}



void Init() {
	glClearColor(180.0 / 255.0, 243.0 / 255.0, 246.0 / 255.0, 1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-width_win / 2, width_win / 2, -higth_win / 2, higth_win / 2, -250, 250);
	glMatrixMode(GL_MODELVIEW);


}


int main(int argc, char**argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width_win, higth_win);

	glutCreateWindow("Лабораторная работа 2");
	glutDisplayFunc(Draw_sh);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, pos);
	glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
	glEnable(GL_COLOR_MATERIAL);
	Init();
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SKeyboard);
	glutMainLoop();
	return 0;

}