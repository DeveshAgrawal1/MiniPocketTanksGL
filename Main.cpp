#include <gl\GL.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <GL\freeglut.h>
#include <stdlib.h>
#include <cmath>
#include <Windows.h>
#include <dos.h>
#include <process.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <cstring>
#include <iostream>
#include <vector>
using namespace std;
#define PI_OVER180 3.14159265359 / 180 

//player 1 variables
int tankdirx=1;
float angl = 0;
float tankx = 90, tanky = 100 ;
float bulletx , bullety;
bool btrue = false;
float bxv = 0, byv = 0, vx = 0, vy = 0; 
float vdp = 0,vdpd = 1;  //velocity decider pointer (vdp) and velocity decider pointer direction (vdpd) 
bool vdtrue = false;  
int life = 500;
float bulletxfreezer,bulletyfreezer;

int choice=1,ochoice=1;int screen=0;
bool gameover=false;

//player 2 variables
int otankdirx=1;
float oangl = 180;
float otankx = 550, otanky = 100 ;
float obulletx , obullety  ; 
bool obtrue = false;
float obxv = 0, obyv = 0, ovx = 0, ovy = 0;
float ovdp = 0,ovdpd = 1;  //velocity decider pointer (vdp) and velocity decider pointer direction (vdpd) 
bool ovdtrue = false ;
int olife = 500;
float obulletxfreezer,obulletyfreezer;

float pchance = 1; //player1 plays first
float gravity = 0.025 ;  //gravity 

bool keystates[256];
char buffer[100]; //used to display text 

void init()
{
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	glOrtho (0, 640, 0, 480, -1, 1);
	glMatrixMode (GL_MODELVIEW);
}

void drawbombs()
{
	glLoadIdentity();
	glColor4f(0.6, 0.4, 0.12,1);
	glBegin(GL_QUADS);
		glVertex2f(210,350);
		glVertex2f(220,350);
		glVertex2f(220,340);
		glVertex2f(210,340);
	glEnd();
	 glColor4f(0.6, 0, 0.12,1);
	glBegin(GL_QUADS);
		glVertex2f(210,330);
		glVertex2f(220,330);
		glVertex2f(220,320);
		glVertex2f(210,320);
	glEnd();
	glLoadIdentity();
}

void drawtank()
{ 
    glLoadIdentity ();

	//tankx+=0.2*tankdirx;

    glTranslatef (tankx, tanky, 0);
    glColor3f (0.9,0.5,0);
    glBegin (GL_QUADS);
        glVertex2f (-12, 2) ;
        glVertex2f (-12, -10);
        glVertex2f (12, -10);
        glVertex2f (12, 2);
    glEnd () ;
	glColor3f (1,1,0);
	glBegin (GL_LINE_STRIP);
        glVertex2f (-2, 2) ;
        glVertex2f (-2, -6);
        glVertex2f (2, -6);
        glVertex2f (2, 2);
    glEnd () ;
    glLoadIdentity();
    glTranslatef(tankx, tanky, 0);
    glRotatef (angl, 0, 0, 1);
	glColor3f (0.9,0.5,0);
    glBegin (GL_QUADS);
        glVertex2f (-2, 2); 
        glVertex2f (-2, -2);
        glVertex2f (18, -2);
        glVertex2f (18, 2);
    glEnd();
    glLoadIdentity () ;       
}     



void drawotank()
{ 
    glLoadIdentity ();
    glTranslatef (otankx, otanky, 0);
    glColor3f (0,0.9,0.8);
    glBegin (GL_QUADS);
        glVertex2f (-12, 2); 
        glVertex2f (-12, -10);
        glVertex2f (12, -10);
        glVertex2f (12, 2);
    glEnd () ;
	glColor3f (0,0,1);
	glBegin (GL_LINE_STRIP);
        glVertex2f (-2, 2) ;
        glVertex2f (-2, -6);
        glVertex2f (2, -6);
        glVertex2f (2, 2);
    glEnd () ;
    glLoadIdentity();
    glTranslatef(otankx, otanky, 0);
    glRotatef (oangl, 0, 0, 1);
	glColor3f (0,0.9,0.8);
    glBegin (GL_QUADS);
        glVertex2f (-2, 2) ;
        glVertex2f (-2, -2);
        glVertex2f (18, -2);
        glVertex2f (18, 2);
    glEnd();
    glLoadIdentity () ;       
}

void veldecide()
{
    glLoadIdentity ();
    glTranslatef (tankx, tanky + 20, 0);
    glColor3f(1, 1, 1);
    glBegin (GL_QUADS);
        glVertex2f (-17, 2) ;
        glVertex2f (-17, -2);
        glVertex2f (17, -2);
        glVertex2f (17, 2);
    glEnd () ;  
    glColor3f(0, 1, 0);
    glBegin (GL_QUADS);
        glVertex2f (-1, 3) ;
        glVertex2f (-1, -3);
        glVertex2f (1, -3);
        glVertex2f (1, 3);
    glEnd ()  ;
        

	glTranslatef (vdp , 0, 0); 
    glColor3f(0, 0, 1);
    glBegin (GL_QUADS);
        glVertex2f (-1, 4) ;
        glVertex2f (-1, -4);
        glVertex2f (1, -4);
        glVertex2f (1, 4) ; 
        
      glEnd ();
} 

void oveldecide()
{
    glLoadIdentity ();
    glTranslatef (otankx, otanky + 20, 0);
    glColor3f(1, 1, 1);
    glBegin (GL_QUADS);
        glVertex2f (-17, 2) ;
        glVertex2f (-17, -2);
        glVertex2f (17, -2);
        glVertex2f (17, 2);
    glEnd ()   ;
    glColor3f(0, 1, 0);
    glBegin (GL_QUADS);
        glVertex2f (-1, 3) ;
        glVertex2f (-1, -3);
        glVertex2f (1, -3);
        glVertex2f (1, 3);
    glEnd ()  ;
        
	glTranslatef (ovdp , 0, 0); 
    glColor3f(0, 0, 1);
    glBegin (GL_QUADS);
        glVertex2f (-1, 4); 
        glVertex2f (-1, -4);
        glVertex2f (1, -4);
        glVertex2f (1, 4) ;
        
	glEnd ();
}

void blast(int bulletxblast,int bulletyblast)
{
	glLoadIdentity ();
    
    glColor4f(0.6, 0.4, 0.12,1);
	glBegin (GL_QUADS);
	glVertex2f (bulletxblast+60,bulletyblast+60 ); 
        glVertex2f (bulletxblast+60,bulletyblast);
        glVertex2f (bulletxblast-60,bulletyblast);
        glVertex2f (bulletxblast-60,bulletyblast+60);
    glEnd() ;

	if(otankx<=bulletxblast+60)
	{
		olife-=10;
		if(olife<=0)
		{
			gameover=true;
			
		}
		//btrue=false;
	}
	if(bulletxblast>otankx&&bulletxblast-60>=otankx)
	{
		olife-=10;
		if(olife<=0)
		gameover=true;
		
		//false;
	}
	if(tankx>=bulletxblast-60)
	{
		life-=10;
		if(life<=0)
		{
			gameover=true;
			
		}
		
		//btrue=false;
	}
	if(bulletxblast<tankx&&bulletxblast+60>=tankx)
	{
		life-=10;
		if(life<=0)
		{
			gameover=true;
			
		}
		
		//btrue=false;
	}
  
}

void shostopper(int bulletxblast,int bulletyblast)
{
	bulletxfreezer=bulletx;bulletyfreezer=bullety;
	glLoadIdentity ();
    
    glColor4f(0.6, 0, 0.12,1);
	glBegin (GL_QUADS);
	glVertex2f (bulletxblast+10,bulletyblast+40 ); 
        glVertex2f (bulletxblast+10,bulletyblast);
        glVertex2f (bulletxblast-10,bulletyblast);
        glVertex2f (bulletxblast-10,bulletyblast+40);
    glEnd() ;
	int freezers=6,freezerdirx=1;
	float freezerx=bulletxblast,freezery=bulletyblast;
	
	glColor4f(1, 0, 0.12,1);
	for(float i=bulletxfreezer;i<bulletxfreezer+100;i++)
	{
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glVertex2f(i+20,bulletyfreezer+15);
	glVertex2f(i+10,bulletyfreezer+15);
	glVertex2f(i+20,bulletyfreezer+20);
	glVertex2f(i+10,bulletyfreezer+20);
	glVertex2f(i+20,bulletyfreezer+30);
	glVertex2f(i+10,bulletyfreezer+30);
	glVertex2f(i+20,bulletyfreezer+10);
	glVertex2f(i+10,bulletyfreezer+10);
	glVertex2f(i+20,bulletyfreezer+25);
	glVertex2f(i+10,bulletyfreezer+25);
	glVertex2f(i+20,bulletyfreezer+5);
	glVertex2f(i+10,bulletyfreezer+5);
	glEnd();
	}
	for(float i=bulletxfreezer;i>bulletxfreezer-100;i--)
	{
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glVertex2f(i-20,bulletyfreezer+15);
	glVertex2f(i-10,bulletyfreezer+15);
	glVertex2f(i-20,bulletyfreezer+20);
	glVertex2f(i-10,bulletyfreezer+20);
	glVertex2f(i-20,bulletyfreezer+30);
	glVertex2f(i-10,bulletyfreezer+30);
	glVertex2f(i-20,bulletyfreezer+10);
	glVertex2f(i-10,bulletyfreezer+10);
	glVertex2f(i-20,bulletyfreezer+25);
	glVertex2f(i-10,bulletyfreezer+25);
	glVertex2f(i-20,bulletyfreezer+5);
	glVertex2f(i-10,bulletyfreezer+5);
	glEnd();

	}

	if(bulletxfreezer+100>=otankx&&bulletyfreezer+5<=otanky&&bulletyfreezer+30>=otanky)
	{
		olife-=10;
		if(olife<=0)
		{
			gameover=true;
			
		}
		//btrue=false;
	}
	if(bulletxfreezer>otankx&&bulletxfreezer-100<=otankx&&bulletyfreezer+5<=otanky&&bulletyfreezer+30>=otanky)
	{
		olife-=10;
		if(olife<=0)
		{
			gameover=true;
			
		}
		//btrue=false;
	}
	if(bulletxfreezer-100<=tankx&&bulletyfreezer+5<=tanky&&bulletyfreezer+30>=tanky)
	{
		life-=10;
		if(life<=0)
		{
			gameover=true;
			
		}
		
		//btrue=false;
	}
	if(bulletxfreezer<tankx&&bulletxfreezer+100>=tankx&&bulletyfreezer+5<=tanky&&bulletyfreezer+30>=tanky)
	{
		life-=10;
		if(life<=0)
		{
			gameover=true;
			
		}
	
		//btrue=false;
	}
	
}

void oblast(int bulletxblast,int bulletyblast)
{
	glLoadIdentity ();
    
    glColor4f(0.6, 0.4, 0.12,1);
	glBegin (GL_QUADS);
	glVertex2f (bulletxblast+60,bulletyblast+60 ); 
        glVertex2f (bulletxblast+60,bulletyblast);
        glVertex2f (bulletxblast-60,bulletyblast);
        glVertex2f (bulletxblast-60,bulletyblast+60);
    glEnd() ;

	if(otankx<=bulletxblast+60)
	{
		olife-=10;
		if(olife<=0)
		{
			gameover=true;
			
		}
		
		//obtrue=false;
	}
	if(bulletxblast>otankx&&bulletxblast-60<=otankx)
	{
		olife-=10;
		if(olife<=0)
		{
			gameover=true;
			
		}
		
		//obtrue=false;
	}
	if(tankx>=bulletxblast-60)
	{
		life-=10;
		if(life<=0)
		{
			gameover=true;
			
		}
		//obtrue=false;
	}
	if(bulletxblast<tankx&&bulletxblast+60>=tankx)
	{
		life-=10;
		if(life<=0)
		{
			gameover=true;
			
		}
		//obtrue=false;
	}
	//obtrue=false;
}

void oshostopper(int bulletxblast,int bulletyblast)
{
	obulletxfreezer=obulletx;obulletyfreezer=obullety;
	glLoadIdentity ();
    
    glColor4f(0.6, 0, 0.12,1);
	glBegin (GL_QUADS);
		glVertex2f (bulletxblast+10,bulletyblast+40 ); 
        glVertex2f (bulletxblast+10,bulletyblast);
        glVertex2f (bulletxblast-10,bulletyblast);
        glVertex2f (bulletxblast-10,bulletyblast+40);
    glEnd() ;
	int freezers=6,freezerdirx=1;
	float freezerx=bulletxblast,freezery=bulletyblast;
	
	glColor4f(1, 0, 0.12,1);
	for(float i=obulletxfreezer;i<obulletxfreezer+100;i++)
	{
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glVertex2f(i+20,obulletyfreezer+15);
	glVertex2f(i+10,obulletyfreezer+15);
	glVertex2f(i+20,obulletyfreezer+20);
	glVertex2f(i+10,obulletyfreezer+20);
	glVertex2f(i+20,obulletyfreezer+30);
	glVertex2f(i+10,obulletyfreezer+30);
	glVertex2f(i+20,obulletyfreezer+10);
	glVertex2f(i+10,obulletyfreezer+10);
	glVertex2f(i+20,obulletyfreezer+25);
	glVertex2f(i+10,obulletyfreezer+25);
	glVertex2f(i+20,obulletyfreezer+5);
	glVertex2f(i+10,obulletyfreezer+5);
	glEnd();
	}
	for(float i=obulletxfreezer;i>obulletxfreezer-100;i--)
	{
	glLineWidth(1.0);
	glBegin(GL_LINES);
	glVertex2f(i-20,obulletyfreezer+15);
	glVertex2f(i-10,obulletyfreezer+15);
	glVertex2f(i-20,obulletyfreezer+20);
	glVertex2f(i-10,obulletyfreezer+20);
	glVertex2f(i-20,obulletyfreezer+30);
	glVertex2f(i-10,obulletyfreezer+30);
	glVertex2f(i-20,obulletyfreezer+10);
	glVertex2f(i-10,obulletyfreezer+10);
	glVertex2f(i-20,obulletyfreezer+25);
	glVertex2f(i-10,obulletyfreezer+25);
	glVertex2f(i-20,obulletyfreezer+5);
	glVertex2f(i-10,obulletyfreezer+5);
	glEnd();

	}

	if(obulletxfreezer-100<=tankx&&obulletyfreezer+5<=tanky&&obulletyfreezer+30>=tanky)
	{
		life-=10;
		if(life<=0)
		{
			gameover=true;
			
		}
	}
	if(obulletxfreezer<tankx&&(obulletxfreezer+100>=tankx&&obulletyfreezer+5<=tanky&&obulletyfreezer+30>=tanky))
	{
		life-=10;
		if(life<=0)
		{
			gameover=true;
			
		}
		//obtrue=false;
	}
	if(obulletxfreezer<otankx&&obulletxfreezer+100>=otankx&&obulletyfreezer+5<=otanky&&obulletyfreezer+30>=otanky)
	{
		olife-=10;
		if(olife<=0)
		{
			gameover=true;
			
		}
		
		//obtrue=false;
	}
	if(obulletxfreezer>otankx&&(obulletxfreezer-100>=otankx&&obulletyfreezer+5<=otanky&&obulletyfreezer+30>=otanky))
	{
		olife-=10;
		if(olife<=0)
		{
			gameover=true;
			
		}
		
		//obtrue=false;
	}
	
}

void checkbhit()
{ 
	
	if(bulletx+2>10&&bullety-2<90&&choice==2&&gameover==false)
	{Sleep(500);shostopper(bulletx,bullety);
	
	}
	else if(bulletx+2>10&&bullety-2<90&&choice==1&&gameover==false)
	{Sleep(500);blast(bulletx,bullety);
	
	}

     if(bulletx + 2 >  otankx - 12 && bulletx + 2 <  otankx + 12 && bullety - 2 >  otanky - 10 && bullety - 2 <  otanky + 2)
	 {
		 
		olife = olife - 100;
		if(olife != 0)
			pchance = 2;
		btrue = false;
	 } 
	 
}



void checkobhit()
{ 
	if(obulletx-2>10&&obullety-2<90&&ochoice==2&&gameover==false)
	{Sleep(500);oshostopper(obulletx,obullety);
	
	}
	else if(obulletx-2>10&&obullety-2<90&&ochoice==1&&gameover==false)
	{Sleep(500);oblast(obulletx,obullety);
	
	}

     if(obulletx - 2 >  tankx - 12 && obulletx - 2 <  tankx + 12 && obullety - 2 >  tanky - 10 && obullety - 2 <  tanky + 2)
	 {
		life = life - 100;
		if(life != 0)
			pchance = 1;
		obtrue = false;
	 } 
}

void drawbullet()
{ 
    glLoadIdentity ();
    glTranslatef (bulletx, bullety, 0);
    glColor3f(0, 0, 1);
    glBegin (GL_QUADS);
        glVertex2f (-2, 2) ;
        glVertex2f (-2, -2);
        glVertex2f (2, -2);
        glVertex2f (2, 2);
    glEnd() ;
    if(btrue)
	{
        if(bulletx > 640 || bulletx < 0 || bullety > 480 || bullety - 2 < 86 )
		{
			btrue = false; 
			pchance = 2;
		} 
	} 
    checkbhit();
}

void drawobullet()
{ 
    glLoadIdentity ();
    glTranslatef (obulletx, obullety, 0);
    glColor3f(0, 0, 1);
    glBegin (GL_QUADS);
        glVertex2f (-2, 2); 
        glVertex2f (-2, -2);
        glVertex2f (2, -2);
        glVertex2f (2, 2);
    glEnd() ;
     if(obtrue)
	{
        if(obulletx > 640 || obulletx < 0 || obullety > 480 || obullety - 2 < 86)
		{
        obtrue = false; 
        pchance = 1;
		} 
	} 
    checkobhit();
} 



//This function is used to draw text on the screen
void drawString (void * font, char *s, float x, float y){
     unsigned int i;
     glRasterPos2f(x, y);
     for (i = 0; i < strlen (s); i++)
          glutBitmapCharacter (font, s[i]);
}

void KeyUpPress(unsigned char key, int x, int y ){
    switch(key){
	case 'a':
        keystates['a'] = false;
     
	break;

	case 'b':
        {keystates['b'] = false;
			
		break;}

	case 'm':
        keystates['m'] = false;
     
	break;

	case 'w':
		keystates['w']=false;
		break;

	case 's':
		keystates['s']=false;
		break;
	case 'd':
        keystates['d'] = false;
		break;

	case 'i':
		keystates['i']=false;
		break;
	case 'k':
		keystates['k']=false;
		break;
	case 'j':
	    keystates['j'] = false;
		break;
	
	case 'l':
        keystates['l'] = false;
		break;

	case 'r':
	    keystates['r'] = false;
		break;
	
	case ' ':
        keystates[' '] = false;
		break;

	case 'c':
		break;
		if(screen==0)
		{
	case 'p':
		{screen=1;
		break;}}
	case 27:
		exit(0);
 
	} 
}
 
void KeyDownPress(unsigned char key, int x, int y ){
    switch(key){
	case 'a':
        keystates['a'] = true;
     
	break;

	case 'b':
	{	keystates['b'] = true;choice=2;ochoice=2;
     
	break;}
	case 'm':
		{keystates['m'] = true;choice=1;ochoice=1;
     
		break;}

	case 'w':
		keystates['w']=true;
		break;
	case 's':
		keystates['s']=true;
		break;
	case 'd':
        keystates['d'] = true;
		break;
 
	case 'j':
	    keystates['j'] = true;
		break;
	
	case 'i':
		keystates['i']=true;
		break;
	case 'k':
		keystates['k']=true;
		break;
	case 'l':
        keystates['l'] = true;
		break;

	case 'r':
		{
	    keystates['r'] = true;
		
		break;
		}
	case ' ':
        keystates[' '] = true;
		break;

	case 'c':
		break;

	case 'y':
		if(life <= 0 || olife <= 0)
		{
			life = 500;
			olife = 500;

			angl = 0;
			oangl = 180;
			gameover=false;
			pchance = 1;
		}
		break;

	case 'n':
        if(life == 0 || olife == 0)
			exit(0);
		break;

		if(screen==0)
		{
	case 'p':
		{screen=1;
		break;}}
	case 27:
		exit(0);
 	}
      
}

void updategame(int value)
{
	glutTimerFunc(10, updategame, 0);
	if(life > 0 && olife > 0)
	{
		if(pchance == 1)
		{

			if(keystates['w']==true)
			{
				tankx+=0.2*tankdirx;
			}
			if(keystates['s']==true)
			{
				tankx-=0.2*tankdirx;
			}
			if(keystates['a'] == true)
			{
				if(vdtrue == false)
				{
					angl = angl + 1;
				}
			}
			if(keystates['d'] == true)
			{
				if(vdtrue == false)
				{
					angl = angl - 1;  
				}
			}
			if(keystates['r'] == true)
			{
				
				if(btrue == false)
				{
			         
						btrue = true;
			            
						vdtrue = true;
						
				}
			}
			if(keystates[' '] == true)
			{
				if(vdtrue)
				{     
					vdtrue = false;
					bulletx = tankx + cos (angl * PI_OVER180) * 20; bullety = tanky + sin (angl * PI_OVER180) * 20;
					bxv = cos (angl * PI_OVER180) * vx; byv = sin (angl * PI_OVER180) * vy;   
				}
			}
			
			//decide the velocity of player1
			if( vdp >= 17 || vdp <= -17) {vdpd = -vdpd;} 
				vdp = vdp + vdpd; 

			vx = cos(vdp/17*90 * PI_OVER180)  * 3.5;
			vy = cos(vdp/17*90 * PI_OVER180)  * 3.5;
	   
			bulletx = bulletx + bxv;
			bullety = bullety + byv;
			byv = byv - gravity;
	    

			if(angl < 0){angl = 0; }
			if(angl > 180){angl = 180;}
	   }  
		else if(pchance == 2)
		{
			if(keystates['i']==true)
			{
				otankx+=0.2*otankdirx;
			}
			if(keystates['k']==true)
			{
				otankx-=0.2*otankdirx;
			}


			if(keystates['j'] == true)
			{
				
				if(ovdtrue == false)
				{
					oangl = oangl + 1; 
				}
			}
			if(keystates['l'] == true)
			{
				
				if(ovdtrue == false)
				{
					oangl = oangl - 1;  
				}
			}
			if(keystates['r'] == true)
			{

				if(obtrue == false)
				{  
						obtrue = true;
			            
						ovdtrue = true; 
						
				}
			}
			if(keystates[' '] == true)
			{
				if(ovdtrue)
				{    
					ovdtrue = false;
					obulletx = otankx + cos (oangl * PI_OVER180) * 20; obullety = otanky + sin (oangl * PI_OVER180) * 20;
					obxv = cos (oangl * PI_OVER180) * ovx; obyv = sin (oangl * PI_OVER180) * ovy;   
				}
			}

			//decide the velocity of player2
			 if( ovdp >= 17 || ovdp <= -17) {ovdpd = -ovdpd ;} 
				ovdp = ovdp + ovdpd; 

			 ovx = cos(ovdp/17*90 * PI_OVER180)  * 3.5;
			 ovy = cos(ovdp/17*90 * PI_OVER180)  * 3.5;
		    
			 obulletx = obulletx + obxv;
			obullety = obullety + obyv; 
			obyv = obyv - gravity;
		   

			if(oangl < 0){oangl = 0;} 
			if(oangl > 180){oangl = 180;}
	  }
	}
}

void drawground()
{
	glLoadIdentity();
	glColor3f(0,0.5,0);
	glBegin(GL_QUADS);
		glVertex2f(0, 0);
		glVertex2f(0, 90);
		glVertex2f(640, 90);
		glVertex2f(640, 0);
	glEnd();
}

void display()
{
    glClear (GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	//display player1 health point (HP)
	glColor3f(1, 1, 1);
	drawString(GLUT_BITMAP_HELVETICA_18, "Player1 HP:", 40, 450);	
	itoa(life, buffer, 10);
	drawString(GLUT_BITMAP_HELVETICA_18, buffer, 150, 450);	

	glColor4f(0, 0.6, 1,1);
	drawString(GLUT_BITMAP_HELVETICA_18, "Mud Ball: Choose M", 230, 340);	

	glColor4f(0, 0.6, 1,1);
	drawString(GLUT_BITMAP_HELVETICA_18, "Laser Bomb: Choose B", 230, 320);	

	glColor3f(1, 1, 1);
	drawString(GLUT_BITMAP_HELVETICA_18, "Player2 HP:", 450, 450);	
	itoa(olife, buffer, 10);
	drawString(GLUT_BITMAP_HELVETICA_18, buffer, 560, 450);

	drawground();
	drawbombs();
	if(pchance == 1) //player1's turn
	{
		glColor3f(1, 1, 1);
		drawString(GLUT_BITMAP_HELVETICA_18, "Player1's turn", 40, 410);
		drawString(GLUT_BITMAP_HELVETICA_18, "press a and d to adjust", 40, 390);
		drawString(GLUT_BITMAP_HELVETICA_18, "the tank gun r to ready ", 40, 370);
		drawString(GLUT_BITMAP_HELVETICA_18, "and space bar to fire ", 40, 350);
        if( vdtrue)
		{
            veldecide();
		}
        drawtank();
        drawotank();
        if(  btrue && vdtrue == false)
		{
            drawbullet();
		}
         
	}     
    else if(pchance == 2) //player2's turn
	{
		glColor3f(1, 1, 1);
		drawString(GLUT_BITMAP_HELVETICA_18, "Player2's turn", 410, 410);
		drawString(GLUT_BITMAP_HELVETICA_18, "press j and l to adjust ", 410, 390);
		drawString(GLUT_BITMAP_HELVETICA_18, "the tank gun r to ready ", 410, 370);
		drawString(GLUT_BITMAP_HELVETICA_18, "and space bar to fire ", 410, 350);
        if(ovdtrue)
		{
            oveldecide();
		}
        drawotank();
        drawtank();
        if(  obtrue && ovdtrue == false)
		{
            drawobullet();
		} 
         
	}
    
	if(gameover==true)
	{
		glColor3f(1, 1, 0);
		
		if(life <= 0&&gameover==true)
			drawString(GLUT_BITMAP_HELVETICA_18, "Player 2 Wins", 260, 300);
		 if(olife<=0&&gameover==true)
			drawString(GLUT_BITMAP_HELVETICA_18, "Player 1 Wins", 260, 300);

		drawString(GLUT_BITMAP_HELVETICA_18, "Game Over", 270, 280);
		drawString(GLUT_BITMAP_HELVETICA_18, "play again?(y/n)", 250, 260);	
	}

    glutSwapBuffers ();
}
int stars[500][2];
void drawstars()
{
	glLoadIdentity();
	glColor3f(0,0.5,0);
	glColor3f(1,1,1);
	for(int i = 0; i < 500; i++)
	{
		stars[i][0] = rand() % 640;
		stars[i][1] = rand() % 480+90;
	}
	for(int i=0;i<500;i++)
	{
		glPointSize(1.3);
		glBegin(GL_POINTS);
			glVertex2f(stars[i][0], stars[i][1]);
		glEnd();
	}
	
}

void cover()
{
	/*glLoadIdentity();*/
	glMatrixMode(GL_MODELVIEW);

	glOrtho(0,0,0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	
	glClearColor(0,0,0,1);
	drawground();
	drawtank();
	drawotank();
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "MINI POCKET TANKS", 200, 360);
	glColor3f(1,0,1);
	drawString(GLUT_BITMAP_TIMES_ROMAN_24, "To Play! Press P!!", 230, 260);
	drawstars();

	glFlush();
	glutSwapBuffers();
	
}


void menu()
{
	if(screen==0)
		cover();
	else if(screen==1)
		display();
}

void main(int argc, char **argv)
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(640,480);
	glutCreateWindow("tanks");
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); glEnable( GL_BLEND ); glClearColor(0.0,0.0,0.0,0.0);
	init();
	glutDisplayFunc(menu);
	glutKeyboardFunc(KeyDownPress);
	glutKeyboardUpFunc(KeyUpPress);
	glutIdleFunc(menu);
	glutTimerFunc(10, updategame, 0);
    glutMainLoop();
}