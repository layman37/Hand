#include<windows.h>
#include<math.h>
#include <gl/glut.h>
#ifndef M_PI
#define M_PI 3.14159
#endif

static float t = M_PI / 180.0f; //弧度角度转换参数
static int angle = 60, oldx = -1, oldy = -1; //angle为视点绕y轴角度
static float r = 9.0f, h = 8.0f; //r为视点到y轴距离，h为视点的y轴坐标
float xRot1 = 0, xRot2 = 0, xRot3 = 0, xRot4 = 0, xRot5 = 0;
float angle1 = -1.50, angle2 = -1.45, angle3 = -1.40, angle4 = -1.35, angle5 = -1.30;
int zRot = 0;

GLUquadricObj *hand=NULL;

void Initial(void)
{
	glClearColor(0.9f, 0.6f, 0.4f, 1.0f);      //设置窗口背景颜色
	hand = gluNewQuadric();
	glEnable(GL_DEPTH_TEST);
}

void ChangeSize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (float)w / h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
}

void MousePlot(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
	{
		oldx = x;
		oldy = y;
	}
}

void MouseMove(int x, int y)
{
	angle += x - oldx;
	h += y - oldy;
	if (h > 10.0f)
		h = 10.0f;
	else if (h < -10.0f)
		h = -10.0f;
	oldx = x;
	oldy = y;
}

void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);   //用当前背景色填充窗口

	glLoadIdentity();
	gluLookAt(r*cos(t*angle), h, r*sin(t*angle), 0, 0, 0, 0, 1, 0);

	//绘制手臂
	gluQuadricDrawStyle(hand, GLU_FILL);
	glColor3f(1.0f, 0.2f, 0.3f);
	glTranslatef(0, -3.5, 0);
	glRotatef(270, 1, 0, 0);
	gluCylinder(hand, 0.85, 0.65, 3.8, 100, 100);
	//绘制手掌
	glColor3f(0.5f, 0.5f, 1.0f);
	glScalef(1.3f, 0.8f, 0.8f);
	glTranslatef(0, 0, 5.5);
	glutSolidCube(1);
	glPushMatrix();

	//绘制手指

	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0);
	glRotatef(xRot3, 1, 0, 0);
	glTranslatef(0, 0, 0.8);
	gluCylinder(hand, 0.17, 0, 1.5, 10, 10); //中指

	glPopMatrix();
	glPushMatrix();
	glRotatef(xRot2, 1, 0, 0);
	glTranslatef(-0.47, 0, 0.7);
	glRotatef(345, 0, 1, 0);
	gluCylinder(hand, 0.10, 0, 1.3, 10, 10); //食指

	glPopMatrix();
	glPushMatrix();
	glRotatef(xRot1, 1, 0, 0);
	glTranslatef(-0.7, 0, 0.2);
	glRotatef(310, 0, 1, 0);
	gluCylinder(hand, 0.13, 0, 0.5, 10, 10); //拇指

	glPopMatrix();
	glPushMatrix();
	glRotatef(xRot4, 1, 0, 0);
	glTranslatef(0.45, 0, 0.7);
	glRotatef(15, 0, 1, 0);
	gluCylinder(hand, 0.14, 0, 1.2, 10, 10); //无名指

	glPopMatrix();
	glPushMatrix();
	glRotatef(xRot5, 1, 0, 0);
	glTranslatef(0.7, 0, 0.1);
	glRotatef(20, 0, 1, 0);
	gluCylinder(hand, 0.09, 0, 0.7, 10, 10); //小指

	glColor3f(0.0f, 0.0f, 0.06f);  //八面体
	glPopMatrix();
	glPushMatrix();
	glRotatef(zRot, 0, 0, 1);
	glTranslatef(-1.7, 0, -2.9);
	glScalef(0.8f, 0.2f, 0.2f);
	glutSolidOctahedron();

	glPopMatrix();  //八面体
	glPushMatrix();
	glRotatef(zRot, 0, 0, 1);
	glTranslatef(0, -2.8, -2.9);
	glScalef(0.2f, 1.6f, 0.2f);
	glutSolidOctahedron();

	glPopMatrix();  //八面体
	glPushMatrix();
	glRotatef(zRot, 0, 0, 1);
	glTranslatef(1.9, 0, -2.9);
	glScalef(1.0f, 0.2f, 0.2f);
	glutSolidOctahedron();

	glPopMatrix();  //八面体
	glPushMatrix();
	glRotatef(zRot, 0, 0, 1);
	glTranslatef(0, 2.8, -2.9);
	glScalef(0.2f, 1.2f, 0.2f);
	glutSolidOctahedron();

	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

void TimerFunc(int value)
{
	if (xRot1 > 40.0f || xRot1 < -40.0f)
		angle1 = -angle1;
	if (xRot2 > 40.0f || xRot2 < -40.0f)
		angle2 = -angle2;
	if (xRot3 > 40.0f || xRot3 < -40.0f)
		angle3 = -angle3;
	if (xRot4 > 40.0f || xRot4 < -40.0f)
		angle4 = -angle4;
	if (xRot5 > 40.0f || xRot5 < -40.0f)
		angle5 = -angle5;
	xRot1 += angle1;
	xRot2 += angle2;
	xRot3 += angle3;
	xRot4 += angle4;
	xRot5 += angle5;
	zRot += 2;
	glutPostRedisplay();
	glutSwapBuffers();
	glutTimerFunc(20, TimerFunc, 0);
}


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  //初始化窗口的显示模式
	glutInitWindowSize(800, 600);                  //设置窗口的尺寸
	glutInitWindowPosition(100, 120);               //设置窗口的位置
	glutCreateWindow("手");                    //创建一个名为矩形的窗口
	glutDisplayFunc(Display);                     //设置当前窗口的显示回调函数
	glutIdleFunc(Display);
	glutReshapeFunc(ChangeSize);
	glutTimerFunc(20, TimerFunc, 0);
	glutMouseFunc(MousePlot);
	glutMotionFunc(MouseMove);
	Initial();                                    //完成窗口初始化
	glutMainLoop();                             //启动主GLUT事件处理循环
	return 0;
}
