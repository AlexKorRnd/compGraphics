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

void drawParallelogram(Coord start, int heightX, int heightY, int heightZ) {
	glPushMatrix();
	glTranslatef(0, 0, 0);
	glColor3f(0.3, 0.3, 0.3);

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

	// подставка
	struct Coord start = { 0, 0, 0 };
	drawParallelogram(start, 300, 20, 300);

	

	////нос кончик
	//glPushMatrix();
	//glColor3f(0.7, 0.7, 0.7);
	//glTranslatef(-160, 0, 0);
	//glRotated(-90, 0, 1, 0);
	//glScalef(1, 1, 3);
	//gluSphere(quadObj, 30, 50, 50);
	//glPopMatrix();


	////тело
	//glPushMatrix();
	//glColor3f(0.7, 0.7, 0.7);
	//glRotated(-90, 0, 1, 0);
	//gluCylinder(quadObj, 30, 30, 150, 50, 50);
	//glPopMatrix();

	////хвост 
	//glPushMatrix();
	//glColor3f(0.7, 0.7, 0.7);
	//glTranslatef(-5, 0, 0);
	//glRotated(-90, 0, 1, 0);
	//glRotated(190, 1, 0, 0);
	//gluCylinder(quadObj, 30, 10, 130, 50, 50);
	//glPopMatrix();

	//// жопка

	//glPushMatrix();
	//glColor3f(0.7, 0.7, 0.7);
	//glTranslatef(115, 22, 0);
	//glRotated(-90, 0, 1, 0);
	//glRotated(13, 1, 0, 1);
	//glScalef(1, 1, 3);
	//gluSphere(quadObj, 10, 50, 50);
	//glPopMatrix();


	////верхний треугольник 
	//glPushMatrix();
	//glTranslatef(0, 0, 0);
	//glColor3f(0.7, 0.7, 0.9);

	//glBegin(GL_QUADS);
	//glVertex3f(20, 28, -4);
	//glVertex3f(130, 125, -4);
	//glVertex3f(130, 125, 4);
	//glVertex3f(20, 28, 4);
	//glEnd();

	//glBegin(GL_QUADS);
	//glVertex3f(130, 125, -4);
	//glVertex3f(150, 130, -4);
	//glVertex3f(150, 130, 4);
	//glVertex3f(130, 125, 4);
	//glEnd();

	//glBegin(GL_QUADS);
	//glVertex3f(150, 130, -4);
	//glVertex3f(120, 30, -4);
	//glVertex3f(120, 30, 4);
	//glVertex3f(150, 130, 4);
	//glEnd();

	//glBegin(GL_POLYGON);
	//glVertex3f(20, 28, 4);
	//glVertex3f(130, 125, 4);
	//glVertex3f(150, 130, 4);
	//glVertex3f(120, 30, 4);
	//glVertex3f(20, 28, 4);
	//glEnd();

	//glBegin(GL_POLYGON);
	//glVertex3f(20, 28, -4);
	//glVertex3f(130, 125, -4);
	//glVertex3f(150, 130, -4);
	//glVertex3f(120, 30, -4);
	//glVertex3f(20, 28, -4);
	//glEnd();
	//glPopMatrix();

	////маленькие треугольники на хвосте 

	//glPushMatrix();
	//glTranslatef(0, 0, 0);
	//glColor3f(0.7, 0.7, 0.9);
	//glBegin(GL_POLYGON);
	//glVertex3f(110, 25, 50);
	//glVertex3f(70, 20, 0);
	//glVertex3f(110, 25, -50);
	//glEnd();

	//glBegin(GL_POLYGON);
	//glVertex3f(110, 20, 50);
	//glVertex3f(70, 15, 0);
	//glVertex3f(110, 20, -50);
	//glEnd();
	//glPopMatrix();

	//glBegin(GL_QUAD_STRIP);
	//glVertex3f(110, 25, 50);
	//glVertex3f(110, 20, 50);
	//glVertex3f(110, 25, -50);
	//glVertex3f(110, 20, -50);
	//glVertex3f(70, 20, 0);
	//glVertex3f(70, 15, 0);
	//glVertex3f(110, 25, 50);
	//glVertex3f(110, 20, 50);

	//glEnd();
	//glPopMatrix();

	////крылья

	//glPushMatrix();
	//glTranslatef(0, 0, 0);
	//glBegin(GL_POLYGON);

	//glPointSize(20);
	//glColor3f(0.7, 0.7, 0.7);

	//glVertex3f(-40, 3, 20);
	//glVertex3f(-15, 3, 170);
	//glVertex3f(20, 3, 200);
	//glVertex3f(10, 3, 20);

	//glVertex3f(10, 3, -20);
	//glVertex3f(20, 3, -200);
	//glVertex3f(-15, 3, -170);
	//glVertex3f(-40, 3, -20);

	//glVertex3f(-40, -3, 20);
	//glVertex3f(-15, -3, 170);
	//glVertex3f(20, -3, 200);
	//glVertex3f(10, -3, 20);

	//glVertex3f(10, -3, -20);
	//glVertex3f(20, -3, -200);
	//glVertex3f(-15, -3, -170);
	//glVertex3f(-40, -3, -20);

	//glEnd();

	////боковушки крыльев

	//glBegin(GL_QUAD_STRIP);
	//glVertex3f(-40, 3, 20);
	//glVertex3f(-40, -3, 20);
	//glVertex3f(-15, 3, 170);
	//glVertex3f(-15, -3, 170);
	//glVertex3f(20, 3, 200);
	//glVertex3f(20, -3, 200);
	//glVertex3f(10, 3, 20);
	//glVertex3f(10, -3, 20);

	//glVertex3f(-40, 3, -20);
	//glVertex3f(-40, -3, -20);
	//glVertex3f(-15, 3, -170);
	//glVertex3f(-15, -3, -170);
	//glVertex3f(20, 3, -200);
	//glVertex3f(20, -3, -200);
	//glVertex3f(10, 3, -20);
	//glVertex3f(10, -3, -20);
	//glEnd();
	//glPopMatrix();


	////турбины

	//glPushMatrix();
	//glColor3f(0.7, 0.7, 0.7);
	//glTranslatef(20, -15, 100);
	//glRotated(-90, 0, 1, 0);
	//gluCylinder(quadObj, 15, 15, 40, 50, 50);
	//glPopMatrix();

	//glPushMatrix();
	//glColor3f(0.6, 0.6, 0.6);
	//glTranslatef(15, -15, 100);
	//glRotated(-90, 0, 1, 0);
	//glScalef(1, 1, 2.5);
	//gluSphere(quadObj, 15, 50, 50);
	//glPopMatrix();

	//glPushMatrix();
	//glColor3f(0.7, 0.7, 0.7);
	//glTranslatef(20, -15, -100);
	//glRotated(-90, 0, 1, 0);
	//gluCylinder(quadObj, 15, 15, 40, 50, 50);
	//glPopMatrix();

	//glPushMatrix();
	//glColor3f(0.6, 0.6, 0.6);
	//glTranslatef(15, -15, -100);
	//glRotated(-90, 0, 1, 0);
	//glScalef(1, 1, 2.5);
	//gluSphere(quadObj, 15, 50, 50);
	//glPopMatrix();


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

	glDisable(GL_DEPTH_TEST);
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