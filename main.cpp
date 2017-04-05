#include<windows.h>
#include <GL/glut.h>
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <cstring>

int checkTest=0;
const int xMax = 9, xMin = 0, yMax = 9, yMin = 0;
bool checkSolve=true, checkPressNumber=true, checkDemo=true;
unsigned char s[9][9],test_s[9][9], keyboardPress;
int posClick_x, posClick_y;

void Initialize();
void drawSquare(GLint x1, GLint y1, GLint x2, GLint y2, GLint x3, GLint y3, GLint x4, GLint y4);
void keyboard(unsigned char key, int x, int y);
void mouseClick(int button, int state, int x, int y);
void preDraw();
void test();
void clearBoard();
void display();
void printText(int x, int y, char *str);
void printText2(int x, int y, char *str);
void printNumber(unsigned char s, GLint x, GLint y);
void printNumber2(unsigned char s, GLint x, GLint y);
void inputBoard();
void solveBoard(int x, int y);
bool checkBoard(int x, int y, unsigned char check);

int main(int agrc, char ** argv)
{
    glutInit(&agrc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowPosition(200, 100);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Solve Sudoku using OpenGL in C++");
    Initialize();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
}

void Initialize()
{
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 800, 0,600);
    for(int i=0; i<xMax; i++)
    for(int j=0; j<yMax; j++)
    {
        s[i][j]='0';
        test_s[i][j]='0';
    }

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
    switch(key)
    {
    case '1':
        {
            keyboardPress=key;
            break;
        }
    case '2':
        {
            keyboardPress=key;
            break;
        }
    case '3':
        {
            keyboardPress=key;
            break;
        }
    case '4':
        {
            keyboardPress=key;
            break;
        }
    case '5':
        {
            keyboardPress=key;
            break;
        }
    case '6':
        {
            keyboardPress=key;
            break;
        }
    case '7':
        {
            keyboardPress=key;
            break;
        }
    case '8':
        {
            keyboardPress=key;
            break;
        }
    case '9':
        {
            keyboardPress=key;
            break;
        }
    default:
        {
            break;
        }
    }
}

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {

        posClick_x = x;
        posClick_y = 600-y;
    }
    glutPostRedisplay();
}

void preDraw()
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

        //draw square of "Load"
        glBegin(GL_LINE_LOOP);
            glVertex2i(765, 570);
            glVertex2i(765, 470);
            glVertex2i(600, 470);
            glVertex2i(600, 570);
        glEnd();

        //draw square of "Check"
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

    printText(650,515,"LOAD");
    if(checkTest ==0 )
        printText2(125,583,"Click on \"Load\" to open Sudoku board or input number from keyboard");
    else if (checkTest == 1)
        printText2(225,583,"Congratulations! You did it");
    else if(checkTest == -1)
        printText2(225,583,"Try again. That's wrong!!!");
    else printText2(225,583,"Get number from your keyboard");
    printText(640,370,"CHECK");
    printText(642,220,"SOLVE");
    printText(640,70,"CLEAR");

    //Slipt Sudoku Board into 9 parts
    glPushAttrib(GL_CURRENT_BIT);
        glColor3d(255,255,0);
        glLineWidth(10);

        glBegin(GL_LINE_LOOP);
            glVertex2i(30, 570);
            glVertex2i(570, 570);
            glVertex2i(570,30);
            glVertex2i(30,30);
        glEnd();

        glBegin(GL_LINES);
            glVertex2i(210, 572);
            glVertex2i(210, 29);
        glEnd();

        glBegin(GL_LINES);
            glVertex2i(390, 572);
            glVertex2i(390, 29);
        glEnd();

        glBegin(GL_LINES);
            glVertex2i(30, 390);
            glVertex2i(570, 390);
        glEnd();

        glBegin(GL_LINES);
            glVertex2i(30, 210);
            glVertex2i(570, 210);
        glEnd();

    glPopAttrib();
}

void test()
{
    //set all value of s[9][9] to equal 0 to get input from keyboard and we also can solve it
    if(checkPressNumber==true)
    {
        for(int i=0; i<xMax; i++)
            for(int j=0; j<yMax; j++)
                if (checkBoard(i,j,s[i][j])==false)
                {
                    checkTest = -1;
                    return;
                }
    }
    checkTest =1;
}

void clearBoard()
{
    checkTest = 0;
    //if s[i][j] = 0, it isn't display on the screen, so we set all value to 0
    for(int i=0; i<xMax; i++)
        for(int j=0; j<yMax; j++)
        {
            s[i][j]='0';
            test_s[i][j]='0';
        }
}

void display()
{
    preDraw();
    //Click on "Load"
    if(posClick_x>=600&&posClick_x<=765&&posClick_y<=570&&posClick_y>=470)
    {
        inputBoard();
        checkPressNumber=true;
        checkSolve=true;
        checkTest=-2;
    }

    //Click on "Solve"
    if(posClick_x>=600&&posClick_x<=765&&posClick_y<=280&&posClick_y>=180)
    {
        solveBoard(0,0);
        checkPressNumber=false;
        checkDemo=false;
        for(int i=0; i<xMax; i++)
            for(int j=0; j<yMax; j++)
                if (s[i][j]=='0')
                {
                    printText2(620,200,"Can't solve. Try again!");
                    break;
                }
    }

    //Click on "Test"
    if(posClick_x>=600&&posClick_x<=765&&posClick_y<=430&&posClick_y>=330)
    {
        checkSolve=true;
        test();
        checkDemo=false;
    }

    //Click on "Clear Board"
    if(posClick_x>=600&&posClick_x<=765&&posClick_y<=130&&posClick_y>=30)
    {
        clearBoard();
        checkSolve=true;
        checkPressNumber=true;
    }

    if(30<=posClick_x&&570>=posClick_x&&30<=posClick_y&&570>=posClick_y)
    {
        checkTest=-2;
        int j = 8-(posClick_x-30)/60;
        int i = (posClick_y-30)/60;
        if(test_s[i][j]=='0')s[i][j]=keyboardPress;
        keyboardPress=test_s[i][j];
        posClick_x=0;
        posClick_y=0;
    }

    GLint x, y;
    for (y = 510; y >= 30; y -= 60)
    {
        for (x = 510; x >= 30; x -= 60)
        {
            if(s[y/60][8-x/60]!='0')
            {
                glPushAttrib(GL_CURRENT_BIT);
                    if(test_s[y/60][8-x/60]=='0')
                    printNumber(s[y/60][8-x/60],x+25, y+20);
                    else printNumber2(s[y/60][8-x/60],x+25, y+20);
                glPopAttrib();
            }
        }
    }
    glFlush();
}

void printText(int x, int y, char *str)
{
    glPushAttrib(GL_CURRENT_BIT);
        glColor3f(229, 236, 234);
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
        glColor3f(229, 236, 234);
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
        glColor3f(229, 236, 234);
        glRasterPos2i(x,y);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,s);
    glPopAttrib();
}

void printNumber2(unsigned char s, GLint x, GLint y)
{
    glPushAttrib(GL_CURRENT_BIT);
        glColor3f(0, 255, 255);
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
            std::ifstream file ("input1.txt");
            if(file.is_open())
                while(!file.eof())
                {
                    for(int i=xMax-1; i>=xMin; i--)
                        for(int j=yMax-1; j>=yMin; j--)
                        {
                            file >> s[i][j];
                            test_s[i][j]=s[i][j];
                        }
                }
            else std::cout << "Unable to open file";
            file.close();
            break;
        }

        case 2:
        {
            std::ifstream file ("input2.txt");
            if(file.is_open())
                while(!file.eof())
                {
                    for(int i=xMax-1; i>=xMin; i--)
                        for(int j=yMax-1; j>=yMin; j--)
                        {
                            file >> s[i][j];
                            test_s[i][j]=s[i][j];
                        }
                }
            else std::cout << "Unable to open file";
            file.close();
            break;
        }

        case 3:
        {
            std::ifstream file ("input3.txt");
            if(file.is_open())
                while(!file.eof())
                {
                    for(int i=xMax-1; i>=xMin; i--)
                        for(int j=yMax-1; j>=yMin; j--)
                        {
                            file >> s[i][j];
                            test_s[i][j]=s[i][j];
                        }
                }
            else std::cout << "Unable to open file";
            file.close();
            break;
        }

        case 4:
        {
            std::ifstream file ("input4.txt");
            if(file.is_open())
                while(!file.eof())
                {
                    for(int i=xMax-1; i>=xMin; i--)
                        for(int j=yMax-1; j>=yMin; j--)
                        {
                            file >> s[i][j];
                            test_s[i][j]=s[i][j];
                        }
                }
            else std::cout << "Unable to open file";
            file.close();
            break;
        }

        case 5:
        {
            std::ifstream file ("input5.txt");
            if(file.is_open())
                while(!file.eof())
                {
                    for(int i=xMax-1; i>=xMin; i--)
                        for(int j=yMax-1; j>=yMin; j--)
                        {
                            file >> s[i][j];
                            test_s[i][j]=s[i][j];
                        }
                }
            else std::cout << "Unable to open file";
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
            checkSolve = false;
            return;
        }
        else solveBoard(x+1,yMin);
    }
    else if(s[x][y]=='0')
    {
        for(int check = 1; check <= yMax; check++)
        {
            if(checkBoard(x,y,check+'0')==true)
            {
                s[x][y]=check+'0';
                solveBoard(x,y+1);
                if(checkSolve==true)s[x][y]='0';
            }
        }
    }
    else solveBoard(x,y+1);
}

bool checkBoard(int x, int y, unsigned char c_check)
{
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
