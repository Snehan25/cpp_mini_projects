#include<iostream>
#include<conio.h>
//#include<windows.h> for sleep function
using namespace std;
bool gameOver;
const int width= 20;
const int height= 20;
int x,y,fruitX,fruitY,score;
int tailX[100], tailY[100];//array for x and y coord of the tail
int nTail;//for length of tail
enum eDirection{STOP=0, LEFT, RIGHT, UP, DOWN};//user defined data type
eDirection dir;// variable

void setup()
{
 gameOver=false;
 dir = STOP;
 x = width/2;
 y = height/2;
 fruitX  = rand() % width;// rand() generates random values so fruit can pop at random places on the console
 fruitY = rand() % height;// modulus is used so that the value will fall within the range of 0 and width-1
 score=0;
}
void draw()
{
system("cls");//to clear the console window
for(int i=0;i<width+2;i++)// display top border of our map wall
cout<<"#";
cout<<endl;

for(int i=0;i<height;i++)//to print the map
{
for(int j = 0; j<width;j++)
{
    if(j==0){ cout<<"#";}
    if(i==y&&j==x)//for head
    cout<<"O";
    else if (i==fruitY && j==fruitX)//for fruit 
    cout<<"F";
        else {
            bool print = false;//keep track of the printing
            for(int k=0;k<nTail;k++)
            {
                
                if (tailX[k]==j && tailY[k]==i)//tailx equal to current x coord taily equal to current y coord
            {
                cout<<"o";
                print = true;
            }
            
            }
            if(!print)//print after every row 
            cout<<" ";
            
            }
        
        if(j== width-1){cout <<"#";}
        
    
}
cout<<endl;
}

for(int i=0;i<width+2;i++)//same for bottom wall
cout<<"#";
cout<<endl;
cout<<"Score:"<<score<<endl;
}

void input()
{
if(_kbhit)//keyboard hit checks if a key has been pressed or not if pressed returns non zero otherwise 0
{
    switch(_getch())//getch() also reads a single character from the keyboard. But it does not use any buffer, so the entered character is immediately returned without waiting for the enter key.
    {
case 'a': 
dir = LEFT;
break;
case 'd': 
dir = RIGHT;
break;
case 'w': 
dir = UP;
break;
case 's': 
dir = DOWN;
break;
case 'x': gameOver=true;
break;
    }
}
}
void logic()
{
    int prevX=tailX[0];
    int prevY=tailY[0];
int prev2X, prev2Y;
tailX[0]=x;//first element to follow the head
tailY[0]=y;
for(int i=1;i<nTail;i++)//i is 1 cuse we already have the first one in the abv lines
{
    prev2X= tailX[i];// to remember the current pos of the segment
    prev2Y= tailY[i];
    tailX[i]= prevX;//changing
    tailY[i]= prevY;
     prevX=prev2X;//updation
     prevY=prev2Y;
}
switch(dir)
{
    case LEFT:
    x--;//decreasing x coord of our snake
    break;
    case RIGHT:
    x++;
    break;
    case UP:
    y--;
    break;
    case DOWN:
    y++;
    break;
    default:
    break;

}
if(x>width || x<0 || y>height || y<0)// if head touches wall game terminates
{
    gameOver = true;
}
//if(x>=width) x=0; else if (x<0) x=width-1;//these two lines are for snake to pass the wall without getting terminated
//if(y>=height) y=0; else if (y<0) y=height-1;
for(int i=0;i<nTail;i++){
if(tailX[i]==x && tailY[i]==y)//for when the head touches the tail
     gameOver=true;
}
if(x==fruitX && y==fruitY)
{
    
    score+=10;
 fruitX = rand() % width;
 fruitY = rand() % height;
 nTail++;
}
}
int main()
{
    setup();
while(!gameOver)
{
    draw();
    input();
    logic();
    //Sleep(10);slows our game a lil bit
}


    return 0;
}