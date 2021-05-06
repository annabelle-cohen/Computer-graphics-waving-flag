#include "glut.h"
#include <math.h>

const int W = 600;
const int H = 600;

unsigned char pix[H][W][3] = { 0 }; // kind of frame buffer (RGB) for each pixel
double offset=0;
double offestGray = 0;



typedef struct {
	int x;
	int y;
}POINT2D;

POINT2D first;
POINT2D second;

void init()
{
	int i,j;
	double d,intensity;
	glClearColor(0.8, 0.7, 0.5, 0);// color of window background



	//magen david

}


void display()
{
	glClear(GL_COLOR_BUFFER_BIT); // clean frame buffer

	glDrawPixels(W, H, GL_RGB, GL_UNSIGNED_BYTE, pix);

	
	

	glutSwapBuffers(); // show all
}



void DrawLine(POINT2D pt1, POINT2D pt2)
{
	double a, b;
	int i, j, tmp;

	if (pt1.x != pt2.x)
	{
		a = ((double)pt2.y - pt1.y) / (pt2.x - pt1.x);
		b = pt1.y - a * pt1.x;

		if (fabs(a) < 1)
		{
			// if x1>x2 exchange them
			if (pt1.x > pt2.x)
			{
				tmp = pt1.x;
				pt1.x = pt2.x;
				pt2.x = tmp;
			}

			for (j = pt1.x; j <= pt2.x; j++)
			{
				i = a * j + b;
				pix[i][j][0] = 0;
				pix[i][j][1] = 0;
				pix[i][j][2] = 255;
			}
		}
		else // |a|>1
		{
			// recalculate a and b
			b = -b / a;
			a = 1 / a;

			if (pt1.y > pt2.y)
			{
				tmp = pt1.y;
				pt1.y = pt2.y;
				pt2.y = tmp;
			}
			for (i = pt1.y; i <= pt2.y; i++)
			{
				j = a * i + b;
				pix[i][j][0] = 0;
				pix[i][j][1] = 0;
				pix[i][j][2] = 255;
			}
		}
	}
}
void idle()
{
	int i, j;
	double dist,dist1;

	offset -= 0.1;

	
	for (i = 0; i < H; i++)
		for (j = 0; j < W; j++)
		{
			dist = sqrt(abs((i - W / 2) * (i - W / 2) + (j) * (j)));

			pix[i][j][0] = 200+55*(1+sin(dist/50 + offset))/2 ; // red
			pix[i][j][1] = 200+55*(1+sin(dist/50 + offset))/2; // green
			pix[i][j][2] = 200+55*(1+sin(dist/50 +offset))/2 ; // blue

			if (i >= 50 && i <= 120 ||i>=480 && i<=550) {
				pix[i][j][0] =  75* (1 + sin(dist / 30 + offset)) / 2;
				pix[i][j][1] =  75* (1 + sin(dist / 30 + offset)) / 2;
				pix[i][j][2] = 255;

			}

		}
		
	first.x = 250;
	first.y = 250;
	second.x = 350;
	second.y = 250;
	DrawLine(first, second);
	
	
	first.x = 300;
	first.y = 340;
	second.x = 250;
	second.y = 250;
	DrawLine(first, second);

	first.x = 300;
	first.y = 340;
	second.x = 350;
	second.y = 250;
	DrawLine(first, second);

	first.x = 250;
	first.y = 320;
	second.x = 350;
	second.y = 320;
	DrawLine(first, second);

	first.x = 250;
	first.y = 320;
	second.x = 300;
	second.y = 230;
	DrawLine(first, second);

	first.x = 350;
	first.y = 320;
	second.x = 300;
	second.y = 230;
	DrawLine(first, second);


	
	glutPostRedisplay();// indirect call to display
}


void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(W, H);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("First Example");

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	init();

	glutMainLoop();
}