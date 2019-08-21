#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <stdio.h>
#define PI 3.1415926
float standard_x = -100.0, standard_y = -130.0;
float width = 200.0, height = 200.0, Width = 500.0, Height = 500.0;
float xp = 0.0, yp = -130 + 13, side_block = 0.0, cx = 0.0, cy = 0.0, radius = 4.0;
float delta, block_y, block_delta_y = 0.0, xp_1 = 0.0, yp_1 = -130 + 13;
float  delta_x_1 = -0.93, delta_y_1 = 0.97, bonus_speed = 0.99, delta_x = 0.97, delta_y = 1.0, bullet_speed = 1.2; //속도
int collide_count = 0, num = 30, start = 0;
int shootx = 13, shooty = 8;
int total = 4, score = 0, active = -1, restartnumber = 0;
char buffer[50];//글자
int score_top[10];
GLfloat shooter[4][2] = { {-shootx,standard_y - shooty},{-shootx,standard_y + shooty},{shootx,standard_y + shooty},{shootx,standard_y - shooty} };//밑에판
GLfloat colorarray[5][3] = { {0.8,1.0,1.0},{1.0,1.0,1.0},{1.0,0.8,1.0},{1.0,0.0,0.0},{0.8,0.7,0.7} };
GLfloat bonusarray[4][3] = { {0.8,1.0,1.0},{1.0,1.0,1.0},{1.0,0.8,1.0},{1.0,0.0,0.0} };
GLfloat bonus_radius[5] = { 6.0,4.0,2.0,14.0 };
int lenthx = 16 / 2, heighty = 10;
int success = 0;
typedef struct //블록
{
	float x1, y1, x2, y2;
	int color, collision, bonus;
}blockbreak;
blockbreak block[8][4];
typedef struct {
	int collision = 0;
	float  x = -180, y;
}  Bullet;
Bullet bullet[14]; //총알
typedef struct {
	int collision, select;
	float  x, y;
}  Bonus;
Bonus bonus[8][4]; //보너스
int block_X1 = -8, block_Y1 = 35, block_X2 = 8, block_Y2 = 25, r;
void drawString(void * font, char *s, float x, float y) { //글자
	unsigned int i;
	glRasterPos2f(x, y);
	for (i = 0; i < strlen(s); i++)
		glutBitmapCharacter(font, s[i]);
}
void Init_Block(void) {
	for (int i = 0; i < 14; i++) {
		bullet[i].collision = 0;
	}
	for (int i = 0; i < 8; i++) {
		for (int r = 0; r < 4; r++) {
			bonus[i][r].collision = rand() % 5; //block[i][r].bonus가 4라면 보너스 점수가 없다
			bonus[i][r].select = 0;
			block[i][r].x1 = 0;
			block[i][r].y1 = 0;
			block[i][r].x2 = 0;
			block[i][r].y2 = 0;
		}
	}
	for (int i = 0; i < 1; i++) {
		for (int r = 0; r < 1; r++) {
			success++;
			if (r % 2 == 0)
				block[i][r].color = 0;
			else
				block[i][r].color = 1;

			block[i][r].collision = 1;
			block[i][r].x1 = block_X1;
			block[i][r].y1 = block_Y1;
			block[i][r].x2 = block_X2;
			block[i][r].y2 = block_Y2;

			bonus[i][r].x = block[i][r].x1 + 8;
			bonus[i][r].y = block[i][r].y1 - radius;
		}
	}
	block_Y1 -= 10;
	block_Y2 -= 10;
	block_X1 = -16;
	block_X2 = 0;
	for (int i = 1; i < 2; i++) {
		for (int r = 0; r < 2; r++) {
			success++;
			if (r % 2 == 0)
				block[i][r].color = 4;
			else
				block[i][r].color = 1;

			block[i][r].collision = 1;
			block[i][r].x1 = block_X1;
			block[i][r].y1 = block_Y1;
			block[i][r].x2 = block_X2;
			block[i][r].y2 = block_Y2;

			bonus[i][r].x = block[i][r].x1 + 8;
			bonus[i][r].y = block[i][r].y1 - radius;

			block_X1 += 16;
			block_X2 += 16;
		}
	}
	block_Y1 -= 10;
	block_Y2 -= 10;
	block_X1 = -24;
	block_X2 = -8;
	for (int i = 2; i < 3; i++) {
		for (int r = 0; r < 3; r++) {
			success++;
			if (r % 2 == 0)
				block[i][r].color = 0;
			else
				block[i][r].color = 1;

			block[i][r].collision = 1;
			block[i][r].x1 = block_X1;
			block[i][r].y1 = block_Y1;
			block[i][r].x2 = block_X2;
			block[i][r].y2 = block_Y2;

			bonus[i][r].x = block[i][r].x1 + 8;
			bonus[i][r].y = block[i][r].y1 - radius;

			block_X1 += 16;
			block_X2 += 16;
		}
	}
	block_Y1 -= 10;
	block_Y2 -= 10;
	block_X1 = -16;
	block_X2 = 0;
	for (int i = 3; i < 4; i++) {
		for (int r = 0; r < 2; r++) {
			success++;
			if (r % 2 == 0)
				block[i][r].color = 4;
			else
				block[i][r].color = 1;

			block[i][r].collision = 1;
			block[i][r].x1 = block_X1;
			block[i][r].y1 = block_Y1;
			block[i][r].x2 = block_X2;
			block[i][r].y2 = block_Y2;

			bonus[i][r].x = block[i][r].x1 + 8;
			bonus[i][r].y = block[i][r].y1 - radius;

			block_X1 += 16;
			block_X2 += 16;
		}
	}
	block_X1 = -8;
	block_X2 = 8;
	block_Y1 -= 10;
	block_Y2 -= 10;
	for (int i = 4; i < 5; i++) {
		for (int r = 0; r < 1; r++) {
			success++;
			if (r % 2 == 0)
				block[i][r].color = 0;
			else
				block[i][r].color = 1;

			block[i][r].collision = 1;
			block[i][r].x1 = block_X1;
			block[i][r].y1 = block_Y1;
			block[i][r].x2 = block_X2;
			block[i][r].y2 = block_Y2;

			bonus[i][r].x = block[i][r].x1 + 8;
			bonus[i][r].y = block[i][r].y1 - radius;

		}
	}

	int e = -70, f = -54, g = 52, h = 42;
	for (int i = 5; i < 7; i++) {
		for (int r = 0; r < 4; r++) {
			success++;
			block[i][r].collision = 1;
			block[i][r].color = 2;
			block[i][r].x1 = e;
			block[i][r].y1 = g;
			block[i][r].x2 = f;
			block[i][r].y2 = h;

			bonus[i][r].x = block[i][r].x1 + 8;
			bonus[i][r].y = block[i][r].y1 - radius;

			if (i == 5 && r == 3) {//block[5][3].color.red
				block[i][r].color = 3;
			}

			e += 40;
			f += 40;
			if (r % 2 == 0) {
				g -= 4;
				h -= 4;
			}
			else {
				g += 2;
				h += 2;
			}
		}
		e = -60;
		f = -44;
		g -= 80;
		h -= 80;
	}
	e = -70, f = -54, g = 5, h = -5;
	for (int i = 7; i < 8; i++) {
		for (int r = 0; r < 2; r++) {
			success++;
			block[i][r].collision = 1;
			block[i][r].color = 2;
			block[i][r].x1 = e;
			block[i][r].y1 = g;
			block[i][r].x2 = f;
			block[i][r].y2 = h;

			bonus[i][r].x = block[i][r].x1 + 8;
			bonus[i][r].y = block[i][r].y1 - radius;

			e += 130;
			f += 130;
		}
	}
}
void Check_Blocks(void) {//벽돌 충돌체크
	for (int i = 0; i < 8; i++) {
		for (int r = 0; r < 4; r++) {
			if (block[i][r].collision == 1 && block[i][r].x1 - radius <= xp && block[i][r].x2 + radius >= xp && block[i][r].y1 + radius >= yp && block[i][r].y2 - radius <= yp) {
				block[i][r].collision += 1;
				bonus[i][r].select += 1;
				success--;
				score += 10;
				if (i == 5 && r == 3) {//빨간벽돌
					collide_count++;
				}
				delta_x *= (-1.0);
				delta_y *= (-1.0);
				break;
			}
		}
	}
	if (collide_count == 1) { //빨간공 벽돌 충돌체크
		for (int i = 0; i < 8; i++) {
			for (int r = 0; r < 4; r++) {
				if (block[i][r].collision == 1 && block[i][r].x1 - radius <= xp_1 && block[i][r].x2 + radius >= xp_1 && block[i][r].y1 + radius >= yp_1 && block[i][r].y2 - radius <= yp_1) {
					block[i][r].collision += 1;
					bonus[i][r].select += 1;
					success--;
					score += 10;
					delta_x_1 *= (-1.0);
					delta_y_1 *= (-1.0);
					break;
				}
			}
		}
	}
	for (int i = 0; i < 8; i++) {
		for (int r = 0; r < 4; r++) {
			for (int j = 0; j < active; j++) {
				if (block[i][r].collision == 1 && bullet[j].collision == 0 && block[i][r].x1 - radius <= bullet[j].x && block[i][r].x2 + radius >= bullet[j].x && block[i][r].y1 + radius >= bullet[j].y && block[i][r].y2 - radius <= bullet[j].y) {
					block[i][r].collision += 1;
					bonus[i][r].select += 1;
					bullet[j].collision += 1;
					if (i == 5 && r == 3) {//빨간벽돌
						collide_count++;
					}
					success--;
					score += 10;
					break;
				}
			}
		}
	}

}


void Keys(int key, int x1, int y1)
{
	int j;

	switch (key)
	{
	case GLUT_KEY_LEFT:
		if (shooter[0][0] >= -100)
		{
			for (j = 0; j < 4; j++)
				shooter[j][0] -= 3.0;
			bullet[active].x = shooter[0][0] + 14;
			glutPostRedisplay();
		}
		break;
	case GLUT_KEY_RIGHT:

		if (shooter[0][0] <= 73)
		{
			for (j = 0; j < 4; j++)
				shooter[j][0] += 3.0;
			bullet[active].x = shooter[0][0] + 14;
			glutPostRedisplay();
		}
		break;
	}
}
void restartmember() {
	//shooter[4][2] = { {-shootx,standard_y - shooty},{-shootx,standard_y + shooty},{shootx,standard_y + shooty},{shootx,standard_y - shooty} };//밑에판
	delta_x_1 = -0.93;
	delta_y_1 = 0.97;
	delta_x = 0.97;
	delta_y = 1.0;
	block_X1 = -8, block_Y1 = 35, block_X2 = 8, block_Y2 = 25;
	score = 0;
	active = -1;
	success = 0;
	collide_count = 0;
	start = 0;
	xp_1 = 0.0;
	yp_1 = -130 + 13;
	xp = 0.0;
	yp = -130 + 13;
	Init_Block();

}
void Mykey(unsigned char key, int x, int y)
{
	switch (key) {
	case 'a':
		if (start == 1) {
			if (active < 12)
				active += 1;
			bullet[active].x = shooter[0][0] + 14;
			bullet[active].y = -118;
		}
		break;
	case 's':
		start = 1;
		break;
	case '1':
		restartnumber += 1;
		restartmember();
		break;

	default:						break;
	}
	glutPostRedisplay();
}
void Draw_Block(void) {//그냥 벽돌 그리기
	for (int j = 0; j < 5; j++)
	{
		for (int i = 0; i < 4; i++) {
			if (block[j][i].collision == 1) {
				glColor3fv(colorarray[block[j][i].color]);
				glBegin(GL_POLYGON);
				glVertex2f(block[j][i].x1, block[j][i].y1);
				glVertex2f(block[j][i].x2, block[j][i].y1);
				glVertex2f(block[j][i].x2, block[j][i].y2);
				glVertex2f(block[j][i].x1, block[j][i].y2);
				glEnd();
			}
		}
	}
}
void block1(void) {//움직이는 벽돌 그리기
	for (int j = 5; j < 8; j++)
	{
		for (int i = 0; i < 4; i++) {
			block[j][i].y1 += block_delta_y;
			block[j][i].y2 += block_delta_y;
			bonus[j][i].y += block_delta_y;

			if (block[j][i].collision == 1) {
				glColor3fv(colorarray[block[j][i].color]);
				glBegin(GL_POLYGON);
				glVertex2f(block[j][i].x1, block[j][i].y1);
				glVertex2f(block[j][i].x2, block[j][i].y1);
				glVertex2f(block[j][i].x2, block[j][i].y2);
				glVertex2f(block[j][i].x1, block[j][i].y2);
				glEnd();
			}
		}
	}
}
void init(void) {
	Init_Block();
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
}
void MyReshape(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(standard_x, standard_x + width, standard_y, standard_y + height);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void Draw_miniball(float x, float y, float radius, float start) {
	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++)
		glVertex2f(x + radius * cos(start + delta * i), y + radius * sin(start + delta * i));
	glEnd();
}
void Draw_bonusball(float x, float y, float radius, float start) {
	glBegin(GL_POLYGON);
	//glBegin(GL_LINE_LOOP);
	for (int i = 0; i < num; i++)
		glVertex2f(x + radius * cos(start + delta * i), y + radius * sin(start + delta * i));
	glEnd();
}
void DrawCircle_1(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(standard_x, standard_x + width, standard_y, standard_y + height);

	//start_delta_1 += 0.02;
	if (xp_1 + radius >= standard_x + width || xp_1 - radius <= standard_x) {
		delta_x_1 *= (-1.0);
	}
	if (yp_1 + radius >= standard_y + height || yp_1 - radius <= standard_y) {
		delta_y_1 *= (-1.0);
	}
	if ((-118 >= yp_1 && -116 >= yp_1) && (shooter[3][0] + radius >= xp_1 && shooter[0][0] - radius <= xp_1)) {
		delta_x_1 *= (-1.0);
		delta_y_1 *= (-1.0);
	}
}
void Draw_shooter() {
	glBegin(GL_POLYGON);
	glVertex2f(shooter[0][0], shooter[0][1]);
	glVertex2f(shooter[1][0], shooter[1][1]);
	glVertex2f(shooter[2][0], shooter[2][1]);
	glVertex2f(shooter[3][0], shooter[3][1]);
	glEnd();
}
void DrawCircle(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(standard_x, standard_x + width, standard_y, standard_y + height);

	if (block[6][3].y2 < -75) {
		block_y = 0.001;
	}
	block_delta_y += block_y;
	if (block[0][0].y1 >= standard_y) {
		block_y = -0.001;

	}
	if (xp + radius >= standard_x + width || xp - radius <= standard_x) {
		delta_x *= (-1.0);
	}
	if (yp + radius >= standard_y + height || yp - radius <= standard_y) {
		delta_y *= (-1.0);
	}

	if ((-118 >= yp && -116 >= yp) && (shooter[3][0] + radius >= xp && shooter[0][0] - radius <= xp)) {
		delta_x *= (-1.0);
		delta_y *= (-1.0);
	}


	DrawCircle_1();//공 빨간공
	Check_Blocks();//블록 체크
	for (int i = 0; i < 8; i++) {
		for (int r = 0; r < 4; r++) {
			if (bonus[i][r].select == 1) {
				if ((-118 >= bonus[i][r].y && -116 >= bonus[i][r].y) && (shooter[3][0] + radius >= bonus[i][r].x && shooter[0][0] - radius <= bonus[i][r].x)) {
					bonus[i][r].select -= 1;
					score += (bonus[i][r].collision + 1) * 10;
				}
				else if (bonus[i][r].y - radius <= standard_y)
					bonus[i][r].select -= 1;
			}

		}
	}
	for (int i = 0; i < 8; i++) {
		for (int r = 0; r < 4; r++) {
			if (bonus[i][r].select == 1) {
				bonus[i][r].y -= bonus_speed;
			}

		}
	}
	if (yp <= -125) {
		xp;
		yp;
	}
	else {
		if (start == 1) {
			xp += delta_x;
			yp += delta_y;
		}
	}
	if (collide_count == 1) {
		if (yp_1 <= -125) {
			xp_1;
			yp_1;
		}
		else {
			xp_1 += delta_x_1;
			yp_1 += delta_y_1;
		}
	}
	for (int i = 0; i < active; i++)
		bullet[i].y += bullet_speed;
	delta = 2.0 * PI / num;

}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	if ((yp <= -125 && yp_1 <= -125) || (yp <= -125 && collide_count == 0)) {
		glClearColor(0.8, 0.8, 0.8, 0.0);
		score_top[restartnumber] = score - 100;
		glColor3f(0, 0, 0);
		snprintf(buffer, 20, "My score: %d", score - 100);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, buffer, -60, -10);//점수계산

		glColor3f(1, 0, 0);
		snprintf(buffer, 10, "game over");
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, buffer, -22, 20);

		glColor3f(0, 0, 0);
		snprintf(buffer, 20, "1. Restart");
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, buffer, -60, -35);//점수계산
		int score_top_y = -10;
		for (int i = 0; i < restartnumber + 1; i++) {
			glColor3f(0, 0, 0);
			snprintf(buffer, 20, "%d.score: %d", i + 1, score_top[i]);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, buffer, 10, score_top_y);//점수출력
			score_top_y -= 20;
		}
	}
	else if (success <= 0) {
		glClearColor(0.8, 0.8, 0.8, 0.0);
		score_top[restartnumber] = score;
		glColor3f(0, 0, 0);
		snprintf(buffer, 20, "My score: %d", score);
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, buffer, -60, -10);//점수계산

		glColor3f(1, 0, 0);
		snprintf(buffer, 10, "success");
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, buffer, -18, 20);

		glColor3f(0, 0, 0);
		snprintf(buffer, 20, "1. Restart");
		drawString(GLUT_BITMAP_TIMES_ROMAN_24, buffer, -60, -35);//점수계산

		int score_top_y = -10;
		for (int i = 0; i < restartnumber + 1; i++) {
			glColor3f(0, 0, 0);
			snprintf(buffer, 20, "%d. score: %d", i + 1, score_top[i]);
			drawString(GLUT_BITMAP_TIMES_ROMAN_24, buffer, 10, score_top_y);//점수계산
			score_top_y -= 20;
		}
	}
	else {
		glClearColor(0.8, 0.8, 0.8, 0.0);
		DrawCircle();//작은공 움직이는 값 계산
		Draw_Block();
		block1(); //움직이는 벽돌

		glColor3f(0.0, 1.0, 0.0);//밑에 바
		Draw_shooter();

		glColor3f(1.0, 1.0, 0.0);//밑에 바 노란작은공
		Draw_miniball(xp, yp, radius, -2.0);

		if (collide_count == 1) {
			glColor3f(1.0, 0.0, 0.0); //밑에 바 빨간작은공
			Draw_miniball(xp_1, yp_1, radius, -2.0);
		}
		////총알
		for (int i = 0; i < active; i++) {
			if (bullet[i].collision == 0) {
				glColor3f(0.0, 1.0, 0.0); //총알 //glColor3f(0.0, 1.0, 0.0);//밑에 바
				Draw_miniball(bullet[i].x, bullet[i].y, radius, -2.0);
			}
		}
		for (int i = 0; i < 8; i++) {
			for (int r = 0; r < 4; r++) {
				if (bonus[i][r].collision <= 2 && bonus[i][r].select == 1) {
					glColor3fv(bonusarray[bonus[i][r].collision]);
					Draw_bonusball(bonus[i][r].x, bonus[i][r].y, bonus_radius[bonus[i][r].collision], -2.0);

					glColor3f(0, 0, 0);
					snprintf(buffer, 40, "%d", (bonus[i][r].collision + 1) * 10);
					drawString(GLUT_BITMAP_HELVETICA_10, buffer, bonus[i][r].x - 2, bonus[i][r].y - 1);//총알 남은 수

				}

			}
		}
		glColor3f(0, 0, 0);
		snprintf(buffer, 10, "%d", score);
		drawString(GLUT_BITMAP_HELVETICA_18, buffer, standard_x + 10, 60);//점수계산
		int b = 12;
		if (active >= 1) {
			b = 12 - active;
		}
		glColor3f(0, 0, 0);
		snprintf(buffer, 40, "bullets num: %d", b);
		drawString(GLUT_BITMAP_HELVETICA_18, buffer, standard_x + 150, 60);//총알 남은 수
	}
	glFlush();
	glutSwapBuffers();
}
void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("벽돌");
	init();
	glutDisplayFunc(RenderScene);
	glutSpecialFunc(Keys);
	glutKeyboardFunc(Mykey);
	glutReshapeFunc(MyReshape);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}