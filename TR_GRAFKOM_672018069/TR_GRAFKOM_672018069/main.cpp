#include <windows.h>
#include <GL/freeglut.h>

float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
int is_depth;

bool mouseDown = false;

void initGL() {
	glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	glClearDepth(5.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	is_depth = 1;
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);
	glPushMatrix();

	glBegin(GL_POLYGON);
	//lantai
	glColor3f(0, 0, 0);
	glVertex3f(-10, 0, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(15, 0, -8);
	glVertex3f(8, 0, -14);
	glVertex3f(-8, 0, -16);

	glEnd();

	glBegin(GL_QUADS);
	//dinding depan
	glColor3f(1, 1, 1);
	glVertex3f(-10, 0, 0);
	glVertex3f(10, 0, 0);
	glVertex3f(10, 2, 0);
	glVertex3f(-10, 2, 0);

	glBegin(GL_QUADS);
	//dinding kanan 1
	glColor3f(1, 1, 1);
	glVertex3f(10, 0, 0);
	glVertex3f(15, 0, -8);
	glVertex3f(15, 2, -8);
	glVertex3f(10, 2, 0);

	glBegin(GL_QUADS);
	//dinding kanan 2
	glColor3f(1, 1, 1);
	glVertex3f(15, 0, -8);
	glVertex3f(8, 0, -14);
	glVertex3f(8, 2, -14);
	glVertex3f(15, 2, -8);
	
	glBegin(GL_QUADS);
	//dinding belakang
	glColor3f(1, 1, 1);
	glVertex3f(15, 0, -8);
	glVertex3f(8, 0, -14);
	glVertex3f(8, 2, -14);
	glVertex3f(15, 2, -8);
	
	glEnd();



	glutSwapBuffers();
}

void idle() {
	if (!mouseDown) {
		xrot += 0.3f;
		yrot += 0.4f;
	}
	glutPostRedisplay();
}

void mouse(int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON) {
		mouseDown = true;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else
		mouseDown = false;
}

void mouseMotion(int x, int y) {
	if (mouseDown) {
		yrot = x - xdiff;
		xrot = y + ydiff;
		glutPostRedisplay();
	}
}

void setting(GLsizei width, GLsizei height) {
	if (height == 0) height = 1;
	GLfloat aspect = (GLfloat)width / (GLfloat)height;
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}

void tombol(unsigned char key, int x, int y) {
	switch (key) {
		//geser ke kiri
	case 'a':
	case 'A':
		glTranslatef(-1.0, 0.0, 0.0);
		break;

		//geser ke kanan
	case 'd':
	case 'D':
		glTranslatef(1.0, 0.0, 0.0);
		break;

		//maju ke depan
	case 'w':
	case 'W':
		glTranslatef(0.0, 0.0, 1.0);
		break;

		//maju ke belakang
	case 's':
	case 'S':
		glTranslatef(0.0, 0.0, -1.0);
		break;

		//gerak ke atas
	case 'q':
	case 'Q':
		glTranslatef(0.0, 1.0, 0.0);
		break;

		//gerak ke bawah
	case 'e':
	case 'E':
		glTranslatef(0.0, -1.0, 0.0);
		break;

		//rotate ke kiri
	case 'j':
	case 'J':
		glRotatef(1.0, 0.0, -5.0, 0.0);
		break;

		//rotate ke kanan
	case 'l':
	case 'L':
		glRotatef(1.0, 0.0, 5.0, 0.0);
		break;

		//rotate ke samping kanan
	case 'o':
	case 'O':
		glRotatef(1.0, 0.0, 0.0, -5.0);
		break;

		//rotate ke samping kiri
	case 'u':
	case 'U':
		glRotatef(1.0, 0.0, 0.0, 5.0);
		break;

		//rotate ke atas
	case 'i':
	case 'I':
		glRotatef(1.0, -5.0, 0.0, 0.0);
		break;

		//rotate ke bawah
	case 'k':
	case 'K':
		glRotatef(1.0, 5.0, 0.0, 0.0);
		break;

		//exit
	case 27:
		exit(0);
	}
	myDisplay();
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("Gabriel Gracia Salindeho - 672018069");
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(setting);
	glutKeyboardFunc(tombol);
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	initGL();
	glutMainLoop();
	return 0;
}