#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

int FlatShaded = 0;	int Wireframed = 0;
	//flatshading과 Wireframe을 토글링하기 위한 부울 변수

int ViewX = 0, ViewY = 0;
	// 마우스 움직임에 따라 시점을 바꾸기 위한 변수 

float cameraDistance = 4.0f; // 카메라와 물체 사이의 거리
float cameraAngleX = 0.0f; // 카메라의 X축 회전 각도
float cameraAngleY = 0.0f; // 카메라의 Y축 회전 각도

void InitLight() {
	GLfloat mat_diffuse[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.5, 0.4, 0.3, 1.0 };
	GLfloat mat_shininess[] = { 15.0 };

	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
	GLfloat light_ambient[] = { 0.3, 0.3, 0.3, 1.0 };
	GLfloat light_position[] = { 0.0, 6.0, 0.0, 0.0 }; //조명의 위치를 알맞게 수정함.

	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}

void MyMouseMove(GLint X, GLint Y) {
	static GLint lastX = -1, lastY = -1; // 마지막 마우스 위치 초기화

	// 초기화된 lastX, lastY가 -1인 경우, 현재 마우스 위치로 초기화
	if (lastX == -1 && lastY == -1) {
		lastX = X;
		lastY = Y;
	}
	int dx = X - lastX;
	int dy = Y - lastY;

	cameraAngleX += dy * 0.5f; // Y축 회전 각도 조정
	cameraAngleY += dx * 0.5f; // X축 회전 각도 조정
	
	lastX = X;
	lastY = Y;

	glutPostRedisplay();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
		case 'q' : case 'Q' : case '\033' :
			exit(0);
			break;
		case 's' : case 'S' :
			if (FlatShaded) {
				FlatShaded = 0;
				glShadeModel(GL_SMOOTH);
			}
			else {
				FlatShaded = 1;
				glShadeModel(GL_FLAT);
			}
			glutPostRedisplay();
			break;
		case 'w' : case 'W' :
			if (Wireframed) {
				Wireframed = 0;
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			}
			else {
				Wireframed = 1;
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			}
			glutPostRedisplay();
			break;
			//와이어 프레임 토글링 코드 작성!
		// 위의 전역 변수 Wireframed를 사용할 것 
	}
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// 카메라 위치 설정
	float cameraX = cameraDistance * sin(cameraAngleY * 3.14f / 180.0f);
	float cameraZ = cameraDistance * cos(cameraAngleY * 3.14f / 180.0f);
	float cameraY = cameraDistance * sin(cameraAngleX * 3.14f / 180.0f);

	gluLookAt(cameraX, cameraY, cameraZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	// 아래에 필요한 물체 드로잉 명령을 삽입할 것 
	//탁자와 탁자다리, 구체, 도넛, 주전자 드로잉 명령함!
	glPushMatrix();
	glTranslatef(0.0f, -0.5f, 0.0f);
	glScalef(1.5f, 0.1f, 1.0f);
	glutSolidCube(1.0); //탁자 상판
	glPopMatrix();

	// 탁자 다리 1 (왼쪽 앞)
	glPushMatrix();
	glTranslatef(-0.7f, -1.0f, 0.4f); // 위치 설정
	glScalef(0.1f, 1.0f, 0.1f);       // 크기 조정
	glutSolidCube(1.0);               // 탁자 다리
	glPopMatrix();

	// 탁자 다리 2 (오른쪽 앞)
	glPushMatrix();
	glTranslatef(0.7f, -1.0f, 0.4f);  // 위치 설정
	glScalef(0.1f, 1.0f, 0.1f);       // 크기 조정
	glutSolidCube(1.0);               // 탁자 다리
	glPopMatrix();

	// 탁자 다리 3 (왼쪽 뒤)
	glPushMatrix();
	glTranslatef(-0.7f, -1.0f, -0.4f); // 위치 설정
	glScalef(0.1f, 1.0f, 0.1f);        // 크기 조정
	glutSolidCube(1.0);                // 탁자 다리
	glPopMatrix();

	// 탁자 다리 4 (오른쪽 뒤)
	glPushMatrix();
	glTranslatef(0.7f, -1.0f, -0.4f);  // 위치 설정
	glScalef(0.1f, 1.0f, 0.1f);        // 크기 조정
	glutSolidCube(1.0);                // 탁자 다리
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-0.5f, -0.25f, 0.0f);
	glutSolidSphere(0.2, 20, 16); // 구체
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.5f, -0.25f, 0.0f);
	glutSolidTeapot(0.2); // 주전자
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0f, -0.25f, -0.1f);
	glutSolidTorus(0.05, 0.15, 20, 20); //도넛 물체
	glPopMatrix();

	glFlush();
}

void MyReshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 1.0, 10.0);
}

int main(int argc, char* argv[]) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Chapt 5 Modeling Project 1");

	glClearColor(0.4, 0.4, 0.4, 0.0);
	InitLight();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMotionFunc(MyMouseMove);
	glutReshapeFunc(MyReshape);
	glutMainLoop();
}


