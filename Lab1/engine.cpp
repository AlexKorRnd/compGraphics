#include "engine.h"

GLvoid Engine::SetProjectionMatrix(GLvoid){
	glMatrixMode(GL_PROJECTION);											// �������� ����� ������������� � �������� ��������
	glLoadIdentity();														// ������� ������� (��������) ������������ �� ���������
	glOrtho (-1 * double(Width) / Height, 1 * double(Width) / Height,	// ��������������� ������������� ��������
		-1, 1, -10.0, 10.0);												
}

GLvoid Engine::SetModelviewMatrix(GLvoid){
	glMatrixMode(GL_MODELVIEW);					// �������� ����� ������������� � �������� ������
	glLoadIdentity();							// ������� ������� (������) ������������ �� ���������
}

GLvoid Engine::Resize(GLsizei width, GLsizei height){
	if (height == 0)									
	{
		height = 1;										
	}

	glViewport(0, 0, width, height);			// ��������������� ������� ���������

	Height = height;
	Width = width;

	SetProjectionMatrix();
	SetModelviewMatrix();
}

GLvoid Engine::Init(GLvoid){
	glClearColor(216.0f / 255.0f, 216.0f / 255.0f, 247.0f / 255.0f, 1.0f);	// ��������������� ����� ���
	
	angle = 0;
}

void DrawCube(GLfloat center, GLfloat size)
{
	glBegin(GL_QUADS);
	// ����� �����
	glColor3f(0.0, 0.0, 0.0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	// ������ �����
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(size / 2, -size / 2, -size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	// ������ �����
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
	glVertex3f(-size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, size / 2);
	glVertex3f(size / 2, -size / 2, -size / 2);
	// ������� �����
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	glVertex3f(-size / 2, size / 2, size / 2);
	glVertex3f(size / 2, size / 2, size / 2);
	glVertex3f(size / 2, size / 2, -size / 2);
	// ������ �����
	glColor3f(1.0, 1.0, 0.0);
	glVertex3f(-size / 2, -size / 2, -size / 2);
//	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(size / 2, -size / 2, -size / 2);
//	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(size / 2, size / 2, -size / 2);
//	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(-size / 2, size / 2, -size / 2);
	// �������� �����
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
	glClear(GL_COLOR_BUFFER_BIT);				// ��������� ����� �����
	//angle += _angle;
	glPushMatrix();								// ������������ ��������� ������� ���������
	glRotatef(angle, 0.0f, 0.1f, 1.0f);			// ������� �� 30 �������� ������ ������� (1, 1, 1)
//	glColor3f(0.7f, 0.25f, 0.55f);				// �������� ������� ���� ����������
	DrawCube(1.0f, 1.0f);							// �������� ����������� ��� �� �������� 2
	glPopMatrix();								// ����������������� ��������� ������� ���������


	glClear(GL_COLOR_BUFFER_BIT);				// ��������� ����� �����
												//angle += _angle;
	glPushMatrix();								// ������������ ��������� ������� ���������
	glRotatef(angle, 0.0f, 0.1f, 1.0f);			// ������� �� 30 �������� ������ ������� (1, 1, 1)
												//	glColor3f(0.7f, 0.25f, 0.55f);				// �������� ������� ���� ����������
	DrawCube(0.5f, 1.0f);							// �������� ����������� ��� �� �������� 2
	glPopMatrix();								// ����������������� ��������� ������� ���������
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




