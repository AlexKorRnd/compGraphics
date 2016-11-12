#include "engine.h"


const int DEFAULT_SCREEN_WIDTH = 800;
const int DEFAULT_SCREEN_HEIGHT = 480;


Engine *engine;

GLvoid display(GLvoid)
{
	engine->Draw();
	glutSwapBuffers();
}

GLvoid reshape(GLsizei width, GLsizei height)
{
	engine->Resize(width, height);
}

void processSpecialKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		engine->RotateDraw(5.0f, 1.0f, 1.0f, 0.0f);
		break;
	case GLUT_KEY_DOWN:
		engine->RotateDraw(-5.0f, 1.0f, 1.0f, 0.0f);
		break;
	}
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("2.2. Моделирование трехмерной сцены в OpenGL.");
	engine = new Engine();
	engine->Init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(processSpecialKeys);
	glutMainLoop();
}
