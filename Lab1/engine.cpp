#include "engine.h"

GLvoid Engine::SetProjectionMatrix(GLvoid){
	glMatrixMode(GL_PROJECTION);											// Действия будут производиться с матрицей проекции
	glLoadIdentity();														// Текущая матрица (проекции) сбрасывается на единичную
	glOrtho (-1 * double(Width) / Height, 1 * double(Width) / Height,	// Устанавливается ортогональная проекция
		-1, 1, -10.0, 10.0);												
}

GLvoid Engine::SetModelviewMatrix(GLvoid){
	glMatrixMode(GL_MODELVIEW);					// Действия будут производиться с матрицей модели
	glLoadIdentity();							// Текущая матрица (модели) сбрасывается на единичную
}

GLvoid Engine::Resize(GLsizei width, GLsizei height){
	if (height == 0)									
	{
		height = 1;										
	}

	glViewport(0, 0, width, height);			// Устанавливается область просмотра

	Height = height;
	Width = width;

	SetProjectionMatrix();
	SetModelviewMatrix();
}

GLvoid Engine::Init(GLvoid){
	glClearColor(216.0f / 255.0f, 216.0f / 255.0f, 247.0f / 255.0f, 1.0f);	// Устанавливается синий фон
	
	angle = 0;
}

void DrawCube(GLfloat center, GLfloat size)
{
	glBegin(GL_QUADS);
	// левая грань
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	// правая грань
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	// нижняя грань
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	// верхняя грань
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	// задняя грань
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
//	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(size / 2, -size / 2, -size / 2);
//	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(size / 2, size / 2, -size / 2);
//	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	// передняя грань
	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(center -size / 2, center -size / 2, center + size / 2);
	//glColor3f(1.0, 0.0, 0.0);
	glVertex3f(center + size / 2, center -size / 2, size / 2);
	//glColor3f(0.0, 1.0, 0.0);
	glVertex3f(center + size / 2, center + size / 2, size / 2);
	//glColor3f(0.0, 0.0, 1.0);
	glVertex3f(center -size / 2, center + size / 2, center + size / 2);
	glEnd();
}


GLvoid Engine::Draw(GLvoid)									
{
	glClear(GL_COLOR_BUFFER_BIT);				// Очищается буфер кадра
	//angle += _angle;
	glPushMatrix();								// Запоминается локальная система координат
	glRotatef(angle, 0.0f, 0.1f, 1.0f);			// Поворот на 30 градусов вокруг вектора (1, 1, 1)
//	glColor3f(0.7f, 0.25f, 0.55f);				// Задается текущий цвет примитивов
	DrawCube(1.0f, 1.0f);							// Рисуется проволочный куб со стороной 2
	glPopMatrix();								// Восстанавливается локальная система координат


	glClear(GL_COLOR_BUFFER_BIT);				// Очищается буфер кадра
												//angle += _angle;
	glPushMatrix();								// Запоминается локальная система координат
	glRotatef(angle, 0.0f, 0.1f, 1.0f);			// Поворот на 30 градусов вокруг вектора (1, 1, 1)
												//	glColor3f(0.7f, 0.25f, 0.55f);				// Задается текущий цвет примитивов
	DrawCube(0.5f, 1.0f);							// Рисуется проволочный куб со стороной 2
	glPopMatrix();								// Восстанавливается локальная система координат
}

GLvoid Engine::RotateDraw(GLfloat _angle, GLfloat x, GLfloat y, GLfloat z)
{
	angle += _angle;
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	glRotatef(angle, x, y, z);
	//DrawCube(1.0f);
	glPopMatrix();
	glutPostRedisplay();
}




