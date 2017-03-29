#include <iostream>
#include <windows.h>
#include <fstream>
#include <GL/glut.h>
using namespace std;

const int xMax = 9;
const int xMin = 0;
const int yMax = 9;
const int yMin = 0;
bool check_solve=false;
bool check_press_number=false;
bool check_clear_board=false;
bool check_test=false;
unsigned char s[9][9];
unsigned char keyboardPress;

int pos_click_x;
int pos_click_y;
int pos_press_x;
int pos_press_y;

void inputBoard();
void solveBoard(int x, int y);
bool checkBoard(int x, int y, int check);
void init();
void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4);
void draw();
void drawBoard();
void printNumber(unsigned char s, int x, int y);
void keyboard(unsigned char key, int x, int y);
void mouseClick(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void printText(int x, int y, char *str);
void printText2(int x, int y, char *str);
void pressNumber();

int main(int agrc, char ** argv)
{
    glutInit(&agrc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Sudoku using OpenGL in C++");
    init();
    glutDisplayFunc(draw);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboard);
//    glutPassiveMotionFunc(mouseMotion);
    glutMainLoop();
}

void init()
{
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0,600);
}

void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4)
{
    // Draw Square
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glVertex2i(x3, y3);
    glVertex2i(x4, y4);
    glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case '1':
        keyboardPress=key;
        break;
    case '2':
        keyboardPress=key;
        break;
    case '3':
        keyboardPress=key;
        break;
    case '4':
        keyboardPress=key;
        break;
    case '5':
        glutKeyboardFunc(keyboard);
        keyboardPress=key;
        break;
    case '6':
        keyboardPress=key;
        break;
    case '7':
        keyboardPress=key;
        break;
    case '8':
        keyboardPress=key;
        break;
    case '9':
        keyboardPress=key;
        break;
    default:
        break;
    }
}

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        pos_click_x = x;
        cout << pos_click_x << endl;
        pos_click_y = 600-y;
        cout << pos_click_y << endl;
    }
    glutPostRedisplay();
}

//void mouseMotion(int x, int y)
//{
//    glutPostRedisplay();
//}

void drawBoard()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(255,255,255);
    GLint x, y;
    for (y = 510; y >= 30; y -= 60)
    {
        for (x = 510; x >= 30; x -= 60)
        {
            drawSquare(x, y + 60, x + 60, y + 60, x + 60, y, x, y);
        }
    }
    glLineWidth(4);
    glBegin(GL_LINE_LOOP);
    glVertex2i(765, 560);
    glVertex2i(765, 460);
    glVertex2i(600, 460);
    glVertex2i(600, 560);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2i(765, 420);
    glVertex2i(765, 320);
    glVertex2i(600, 320);
    glVertex2i(600, 420);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2i(765, 270);
    glVertex2i(765, 170);
    glVertex2i(600, 170);
    glVertex2i(600, 270);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glVertex2i(765, 130);
    glVertex2i(765, 30);
    glVertex2i(600, 30);
    glVertex2i(600, 130);
    glEnd();

    printText(645,505,"DEMO");
    printText2(605,480,"Press on Sudoku Map or Watch Demo");
    printText(610,360,"Press Number");
    printText(642,210,"SOLVE");
    printText(620,70,"Clear Board");
}

void pressNumber()
{
    GLint x, y;
    if(check_press_number==false)
    {
        for(int i=0; i<xMax; i++)
            for(int j=0; j<yMax; j++)
                s[i][j]='0';
        check_press_number=true;
        check_clear_board=false;
    }
}

void clearBoard()
{
    if(check_clear_board==false)
    {
        for(int i=0; i<xMax; i++)
            for(int j=0; j<yMax; j++)
                s[i][j]='0';
        check_solve=false;
        check_clear_board=true;
    }
}

void draw()
{
    if(pos_click_x>=600&&pos_click_x<=765&&pos_click_y<=560&&pos_click_y>=460)
    {
        inputBoard();
        check_clear_board=false;
        check_press_number=false;
        check_solve=false;
    }
    if(pos_click_x>=600&&pos_click_x<=765&&pos_click_y<=270&&pos_click_y>=170)
    {
        solveBoard(0,0);
        check_press_number=false;
        check_test=true;
    }
    if(pos_click_x>=600&&pos_click_x<=765&&pos_click_y<=420&&pos_click_y>=320)
    {
        pressNumber();
        check_press_number=false;
        check_clear_board=false;
        check_solve=false;
    }
    if(check_press_number==false&&check_test==false)
    {
        int j = 8-(pos_click_x-30)/60;
        int i = (pos_click_y-30)/60;
        s[i][j]=keyboardPress;
        cout << i << endl << j << endl << s[i][j];
    }
    if(pos_click_x>=600&&pos_click_x<=765&&pos_click_y<=130&&pos_click_y>=30)
        clearBoard();
    GLint x, y;
    drawBoard();
    for (y = 510; y >= 30; y -= 60)
    {
        for (x = 510; x >= 30; x -= 60)
        {
            if(s[y/60][8-x/60]!='0')printNumber(s[y/60][8-x/60],x+25, y+20);
            keyboardPress='0';
            pos_click_x=0;
            pos_click_y=0;
        }
    }
    glFlush();
}

void printText(int x, int y, char *str)
{
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1,1,1);
    glRasterPos2f(x,y);
    int n = (int) strlen(str);
    for (int i = 0; i < n; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,str[i]);
    }
    glPopAttrib();
}

void printText2(int x, int y, char *str)
{
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1,1,1);
// Draw your text
    glRasterPos2f(x,y);
    int n = (int) strlen(str);
    for (int i = 0; i < n; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10,str[i]);
    }
    glPopAttrib();
}

void printNumber(unsigned char s, int x, int y)
{
    glPushAttrib(GL_CURRENT_BIT);
    glColor3f(1,1,1);
    glRasterPos2d(x,y);
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s);
    glPopAttrib();
}

void inputBoard()
{
    ifstream file ("input.txt");
    if(file.is_open())
        while(!file.eof())
        {
            for(int i=xMax-1; i>=xMin; i--)
                for(int j=yMax-1; j>=yMin; j--)
                {
                    file >> s[i][j];
                }
        }
    else cout << "Unable to open file";
    file.close();
}

void solveBoard(int x, int y)
{
    if(y==yMax)
    {
        if(x==xMax-1)
        {
            check_solve = true;
            return;
        }
        else solveBoard(x+1,yMin);
    }
    else if(s[x][y]=='0')
    {
        for(int check = 1; check <= yMax; check++)
        {
            if(checkBoard(x,y,check)==true)
            {
                s[x][y]=check+'0';
                solveBoard(x,y+1);
                if(check_solve==false)s[x][y]='0';
            }
        }
    }
    else solveBoard(x,y+1);
}
bool checkBoard(int x, int y, int check)
{
    char c_check=check+'0';
    for(int i=0; i<yMax; i++)
    {
        if(s[x][i]==c_check) return false;
    }
    for(int i=0; i<xMax; i++)
    {
        if(s[i][y]==c_check) return false;
    }
    int a=x/3, b=y/3;
    for(int i=3*a; i<3*a+3; i++)
        for(int j=3*b; j<3*b+3; j++)
            if(s[i][j]==c_check) return false;
    return true;
}
