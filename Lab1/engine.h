#include "api.h"

#ifndef __ENGINE
#define __ENGINE

class Engine {
	GLsizei Height, Width;
	GLfloat angle;
	GLvoid SetProjectionMatrix(GLvoid);						// ������� ������������ ��������������
	GLvoid SetModelviewMatrix(GLvoid);						// ������� �������������� ������-����
public:
	GLvoid Resize(GLsizei width, GLsizei height);			// �������, ���������� ��� ��������� �������� ����
	GLvoid Init(GLvoid);									// �������, ��� ������� ��������� ����������
	GLvoid Draw(GLvoid);									// ��������� (render) �����
	GLvoid RotateDraw(GLfloat angle, GLfloat x, GLfloat y, GLfloat z);
};

#endif