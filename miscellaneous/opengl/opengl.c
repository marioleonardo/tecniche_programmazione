
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
/*  #include <libpng16/png.h> */

#define NUM_PTS 6
#define len(array) sizeof( array )/sizeof(array[0])

double * coeffMultiply(double a[], double b[], int lengthA, int lengthB);

double ptsList[NUM_PTS][2];

double pnx[NUM_PTS+1];

double functionMath(double x){
	double y;
	y=x*x*x *0.4;
	return y;
}

void interpolate(double ptsList[][2]){
	float result;
	float polinomio[NUM_PTS];
	for(int i=0; i<NUM_PTS; i++){
		
	};
	
}

void display(void)
{
	srand(time(NULL));
	double random;
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho( -6, 6, -6, 6, -1, 1);

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

	

	glBegin(GL_LINES);
		glColor3f(0.0f, 0.0f, 0.0f);
		glVertex2f(0.0, -6.00);
		glVertex2f(0.0, 6.00);
		glVertex2f(6.0, 0.00);
		glVertex2f(-6.0, 0.00);
	glEnd();

	glPointSize(4.0);
	glBegin(GL_POINTS);
		glColor3f(0.9f, 0.4f, 0.1f);
		for(int i=0; i<NUM_PTS; i++){
			ptsList[i][0]=(-5.0 + i * (10 / (NUM_PTS - 1)));
			random= -4.0 + 8.0 * ((double)rand() / (double)RAND_MAX);
			ptsList[i][1]=(double) (5.0*(random/(1 + abs(random))));
			glVertex2f(ptsList[i][0], ptsList[i][1]);
		}
	glEnd();
	
	
	glLineWidth(2.0f);
	glBegin(GL_LINE_STRIP);
		
		glColor3f(0.0f, 0.8f, 0.4f);
		double pointsFunction[100][2];
		for(int i=0; i<100; i++){
			pointsFunction[i][0]= -5.0 + 0.1*i ;
			interpolate(ptsList);
			pointsFunction[i][1] = functionMath(pointsFunction[i][0]);
			glVertex2f(pointsFunction[i][0], pointsFunction[i][1]);
		}
	glEnd();
	


	glFlush();
}

int main(int argc, char** argv)
{
	int random;
	
	random = rand();
	

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);	// Use single display buffer.
	glutInitWindowSize(1080, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Hello world");
	glutDisplayFunc(display);
	glutMainLoop();
	return 0;
}

/* gcc -lGL opengl.c -o cube -lglut -lGLU
./cube 
*/

double * coeffMultiply(double a[], double b[], int lengthA, int lengthB){
    int index=0;
    int nonZeroLast=0;
    while(index < lengthA ){
        if(a[index] != 0)
            nonZeroLast=index;
        index++;
    }
    lengthA=nonZeroLast;
    index=0;
    nonZeroLast=0;
    while(index < lengthB ){
        if(b[index] != 0)
            nonZeroLast=index;
        index++;
    }
    lengthB=nonZeroLast;
    double result[1 + lengthA + lengthB];
    
    for(int first=0; first<lengthA+1; first++){
        for(int second=0; second<lengthB+1; second++){
            result[first+second]+=a[first]*b[second];
        }
    }
    return result;
}