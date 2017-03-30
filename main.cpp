#include <iostream>
#include <fstream>
#include <GL/glut.h>
#include <ctime>
#include <cstdlib>

using namespace std;

const int xMax = 9, xMin = 0, yMax = 9, yMin = 0;
bool check_solve=false, check_press_number=true, check_demo=true;
unsigned char s[9][9], keyboardPress;
int pos_click_x, pos_click_y, pos_press_x, pos_press_y;

void init();
void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4);
void keyboard(unsigned char key, int x, int y);
void mouseClick(int button, int state, int x, int y);
void drawBoard();
void pressNumber();
void clearBoard();
void draw();
void printText(int x, int y, char *str);
void printText2(int x, int y, char *str);
void printNumber(unsigned char s, GLint x, GLint y);
void inputBoard();
void solveBoard(int x, int y);
bool checkBoard(int x, int y, int check);

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
    glLineWidth(3);
    glBegin(GL_LINE_LOOP);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glVertex2i(x3, y3);
        glVertex2i(x4, y4);
    glEnd();
}

void keyboard(unsigned char key, int x, int y)
{
    keyboardPress=key;
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
    glLineWidth(5);
    glPushAttrib(GL_CURRENT_BIT);
        glColor3d(255, 255, 0);

        //draw square of "Demo"
        glBegin(GL_LINE_LOOP);
            glVertex2i(765, 570);
            glVertex2i(765, 470);
            glVertex2i(600, 470);
            glVertex2i(600, 570);
        glEnd();

        //draw square of "Press Number"
        glBegin(GL_LINE_LOOP);
            glVertex2i(765, 430);
            glVertex2i(765, 330);
            glVertex2i(600, 330);
            glVertex2i(600, 430);
        glEnd();

        //draw square of "Solve"
        glBegin(GL_LINE_LOOP);
            glVertex2i(765, 280);
            glVertex2i(765, 180);
            glVertex2i(600, 180);
            glVertex2i(600, 280);
        glEnd();

        //draw square of "Clear Board"
        glBegin(GL_LINE_LOOP);
            glVertex2i(765, 130);
            glVertex2i(765, 30);
            glVertex2i(600, 30);
            glVertex2i(600, 130);
        glEnd();


    glPopAttrib();

    printText(645,515,"DEMO");
    printText2(60,583,"Click on 'Press Number' to solve your board Sudoku or click on 'Demo' to watch demo");
    printText(610,370,"Press Number");
    printText(642,220,"SOLVE");
    printText(620,70,"Clear Board");

    glPushAttrib(GL_CURRENT_BIT);
        glColor3d(255,255,0);
        glLineWidth(10);

        glBegin(GL_LINES);
            glVertex2i(210, 572);
            glVertex2i(210, 29);
        glEnd();

        glColor3d(255,255,0);
        glLineWidth(10);
        glBegin(GL_LINES);
            glVertex2i(390, 572);
            glVertex2i(390, 29);
        glEnd();

        glColor3d(255,255,0);
        glLineWidth(10);
        glBegin(GL_LINES);
            glVertex2i(30, 390);
            glVertex2i(570, 390);
        glEnd();

        glColor3d(255,255,0);
        glLineWidth(10);
        glBegin(GL_LINES);
            glVertex2i(30, 210);
            glVertex2i(570, 210);
        glEnd();

        glColor3d(255,255,0);
        glLineWidth(10);
        glBegin(GL_LINE_LOOP);
            glVertex2i(30, 570);
            glVertex2i(570, 570);
            glVertex2i(570,30);
            glVertex2i(30,30);
        glEnd();
    glPopAttrib();
}

void pressNumber()
{
    if(check_press_number==true)
    {
        for(int i=0; i<xMax; i++)
            for(int j=0; j<yMax; j++)
                s[i][j]='0';
    }
}

void clearBoard()
{
    for(int i=0; i<xMax; i++)
        for(int j=0; j<yMax; j++)
            s[i][j]='0';
}

void draw()
{
    drawBoard();
    //Click on "Demo"
    if(pos_click_x>=600&&pos_click_x<=765&&pos_click_y<=570&&pos_click_y>=470)
    {
        inputBoard();
        check_press_number=false;
        check_solve=true;
    }

    //Click on "Solve"
    if(pos_click_x>=600&&pos_click_x<=765&&pos_click_y<=280&&pos_click_y>=180&&check_solve==true)
    {
        solveBoard(0,0);
        check_press_number=false;
        check_demo=false;
    }

    //Click on "Press Number"
    if(pos_click_x>=600&&pos_click_x<=765&&pos_click_y<=430&&pos_click_y>=330)
    {
        check_solve=true;
        pressNumber();
        check_solve=true;
        check_demo=false;
    }

    //Click on "Clear Board"
    if(pos_click_x>=600&&pos_click_x<=765&&pos_click_y<=130&&pos_click_y>=30)
    {
        clearBoard();
        check_solve=true;
        check_press_number=true;
    }

    if(check_press_number==true&&30<=pos_click_x&&570>=pos_click_x&&30<=pos_click_y&&570>=pos_click_y)
    {
        int j = 8-(pos_click_x-30)/60;
        int i = (pos_click_y-30)/60;
        s[i][j]=keyboardPress;
    }

    GLint x, y;
    for (y = 510; y >= 30; y -= 60)
    {
        for (x = 510; x >= 30; x -= 60)
        {
            if(s[y/60][8-x/60]!='0')
            {
                glPushAttrib(GL_CURRENT_BIT);
                    glColor3f(255,255,0);
                    printNumber(s[y/60][8-x/60],x+25, y+25);
                glPopAttrib();

                keyboardPress='0';
                pos_click_x=0;
                pos_click_y=0;
            }
        }
    }
    glFlush();
}

void printText(int x, int y, char *str)
{
    glPushAttrib(GL_CURRENT_BIT);
        glColor3b(229, 236, 234);
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
        glColor3b(229, 236, 234);
        // Draw your text
        glRasterPos2f(x,y);
        int n = (int) strlen(str);
        for (int i = 0; i < n; i++)
        {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12,str[i]);
        }
    glPopAttrib();
}

void printNumber(unsigned char s, GLint x, GLint y)
{
    glPushAttrib(GL_CURRENT_BIT);
        glColor3b(229, 236, 234);
        glRasterPos2i(x,y);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s);
    glPopAttrib();
}

void inputBoard()
{
    srand(time(NULL));
    int i = rand()%5+1;
    switch(i)
    {
        case 1:
        {
            ifstream file ("input1.txt");
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
            break;
        }

        case 2:
        {
            ifstream file ("input2.txt");
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
            break;
        }

        case 3:
        {
            ifstream file ("input3.txt");
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
            break;
        }

        case 4:
        {
            ifstream file ("input4.txt");
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
            break;
        }

        case 5:
        {
            ifstream file ("input5.txt");
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
            break;
        }
    }
}

void solveBoard(int x, int y)
{
    if(y==yMax)
    {
        if(x==xMax-1)
        {
            check_solve = false;
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
                if(check_solve==true)s[x][y]='0';
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
