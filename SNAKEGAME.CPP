#include<stdio.h>
#include<graphics.h>
#include<stdlib.h>
#include<dos.h>
#include<conio.h>
#include<string.h>
#include<time.h>

//Variables
int x = 640 / 2 , y = 480 / 2 -20 ;
int xfood , yfood ;
int xPoints[10000] , yPoints[10000] ;
int xr , yr ;
int gameEnd , restart , endType ;
int score = 0 , tailCount = 0 ;
char choise = 'd' ;
char * string ;

//Functions
char * intToStr(int) ;
void pattern() ;
void initialiseTail(int) ;
int getFoodX() ;
int getFoodY() ;
void drawFood() ;
void drawNewFood() ;
void drawSnake() ;
void moveSnake() ;
void clearAll() ;
void foodEaten() ;
void endGame() ;
void drawString(int , int , int ,int ,int , int ,char[] ) ;

//Main Function
void main(){
     clrscr() ;
     srand(time(NULL)) ;
     int gd = DETECT , gm ;
     initgraph(&gd , &gm , "C:\\tc\\bgi") ;
     xPoints[xr] = x ;
     yPoints[yr] = y ;
     xr++ ; yr++ ;
     pattern() ;
     initialiseTail(3) ;
     drawSnake() ;
     drawNewFood() ;
     clearAll() ;
     //loop staring
     while(1){
       if(kbhit()){
	 char ch = getch() ;
	 if(ch == 'q')
	 exit(0) ;
	 else choise = ch ;
       }
       moveSnake() ;
       endGame() ;
       drawSnake() ;
       foodEaten() ;
       pattern() ;
       delay(100) ;
     }
     getch() ;
     closegraph() ;
}

void clearAll(){
     cleardevice() ;
}

void initialiseTail(int count){
     tailCount = count-1 ;
     xr = count+2 ; yr = count+2 ;
     for(int i = 0 ; i <= count + 2 ; i++){
       xPoints[i] = x ;
       yPoints[i] = y ;
     }
}

char * intToStr(int val){
    char * arr = (char*)malloc(sizeof(char)*10) ;
    int num[10] ;
    int x = 0 , y = 0 , mod = 0 , placeholder = 0 ;

    if(val == 0){
      arr[0] = '0' ; arr[1] = '\0' ;
      return arr ;
    }

    while(val != 0){
      mod = val % 10 ;
      val = val / 10 ;
      num[x] = mod ;
      x++ ;
    }

    x-- ;

    while(x != -1){
       placeholder = num[x] ;
       placeholder+= 48 ;
       arr[y] = (char)placeholder ;
       y++ ; x-- ;
    }
    arr[y] = '\0' ;
    return arr ;
}

void drawString(int type , int pos , int size , int color , int x , int y , char arr[]){
     settextstyle(type,pos,size) ;
     setcolor(color) ;
     outtextxy(x,y,arr) ;
}

int getFoodX(){
    int x = rand() % 620 ;
    x = x / 20 ;
    x = x * 20 ;
    if(x <= 40 || x >= 600)
    x = getFoodX() ;

    return x ;
}

int getFoodY(){
    int y = rand() % 460 ;
    y = y / 20 ;
    y = y * 20 ;
    if(y <= 40 || y >= 440)
    y = getFoodY() ;

    return y ;
}

void drawFood(){
     setcolor(rand() % 15) ;
     for(int i = 0 ; i < 10 ; i++){
	 circle(xfood+10,yfood+10,i) ;
     }
}

void drawNewFood(){
     xfood = getFoodX() ;
     yfood = getFoodY() ;
     for(int i = xr ; i >= xr - tailCount ; i--){
       if(xPoints[i] == xfood && yPoints[i] == yfood)
       drawNewFood() ;
     }
     drawFood() ;
}

void foodEaten(){
     if(x == xfood && y == yfood){
	string = intToStr(score) ;
	drawString(0,0,2,0,140,0,string) ;
	free(string) ; string = "" ;
	score++ ;
	tailCount++ ;
	drawNewFood() ;
     }
}

void drawSnake(){
     setcolor(0) ;
     int points[] = {x,y,x+20,y,x+20,y,x+20,y+20,x,y+20,x,y} ;
     setfillstyle(1,15) ;
     fillpoly(6,points) ;
     if(tailCount == 0){
       int m = xPoints[xr-2] , n = yPoints[yr-2] ;
       int points[] = {m,n,m+20,n,m+20,n,m+20,n+20,m,n+20,m,n} ;
       setfillstyle(1,0) ;
       setcolor(0) ;
       fillpoly(6,points) ;
     }
     else{
       int val = tailCount , o = 2 ;
       while(val != -2){
       if(val > 0){
       int m = xPoints[xr-o] , n = yPoints[yr-o] ;
       int points[] = {m,n,m+20,n,m+20,n,m+20,n+20,m,n+20,m,n} ;
       setfillstyle(1,10) ;
       fillpoly(6,points) ;
       }
       else{
       //painting black
       int m = xPoints[xr-o] , n = yPoints[yr-o] ;
       int points[] = {m,n,m+20,n,m+20,n,m+20,n+20,m,n+20,m,n} ;
       setfillstyle(1,0) ;
       fillpoly(6,points) ;
       drawpoly(6,points) ;
	 }
       val-- ; o++ ;
       }
     }
}

void pattern(){
     drawString(0,0,2,5,20,0,"Score : ") ;
     string = intToStr(score) ;
     drawString(0,0,2,5,140,0,string) ;
     free(string) ; string = "" ;
     setcolor(15) ;
     rectangle(19,19,621,441) ;
     drawFood() ;
}

void moveSnake(){
     lab :
     switch(choise){
	case 'd' :    //right
	  x+=20 ;
	  break ;
	case 'a' :    //left
	  x-=20 ;
	  break ;
	case 'w':      //top
	  y-=20 ;
	  break ;
	case 's' :
	  y+=20 ;
	  break ;
	default :
	  while(1){
	   drawString(0,0,3,rand()%15,80,170,"Game has been Paused") ;
	   drawString(0,0,2,rand()%15,25,220,"Press 'w' , 'a' , 's' or 'd'to resume") ;
	    if(kbhit()){
	      choise = getch() ;
	      if(choise == 'w' || choise == 'a' || choise == 's' || choise == 'd'){
	      clearAll() ;
	      goto lab ;
	      }
	      else if(choise == 'q')
	      exit(0) ;
	    }
	  }
     }
     xPoints[xr] = x ; yPoints[yr] = y ;
     xr++ ; yr++ ;
}

void endGame(){
     if(x < 20 || y >= 440 || x >= 620 || y < 20){
       clearAll() ;
       gameEnd = 1 ;
       endType = 1 ;
     }
     else {
       for(int i = xr-2 ; i >= (xr-tailCount)-1 ; i--){
	  if(x == xPoints[i] && y == yPoints[i]){
	    clearAll() ;
	    gameEnd = 1 ;
	    endType = 2 ;
	  }
       }
     }

     if(gameEnd == 1){
	if(endType == 1){
	   while(1){
	    if(kbhit()){
	      char ch = getch() ;
	      if(ch == 'q'){
	      exit(0) ;
	      }
	      else if( ch == 'r'){
		x = 640 / 2 ; y = 480 / 2 -20 ;
		tailCount = 0 ; gameEnd = 0 ;
		xr = 1 ; yr = 1 ;
		score = 0 ; choise = 'd';
		clearAll() ;
		return ;
	      }
	      else if( ch == 'x'){
		choise = 'x' ;
		x = xPoints[xr-3] ; y = yPoints[yr-3] ;
		xr-=2 ; yr-= 2;
		gameEnd = 0 ; endType = 0 ;
		clearAll() ;
		return ;
	      }
	    }
	      drawString(0,0,3,(rand()%14)+1,0,20,"Score : ") ;
	      string = intToStr(score) ;
	      drawString(0,0,3,(rand()%14)+1,180,20,string) ;
	      free(string) ; string = "" ;
	      drawString(0,0,2,(rand()%14)+1,0,60,"Game Ended by collapsing with walls ...") ;
	      drawString(0,0,2,(rand()%14)+1,0,100,"Press 'x' to recontinue the game ...") ;
	      drawString(0,0,2,(rand()%14)+1,0,140,"Press 'r' to restart the game ...") ;
	      drawString(0,0,2,(rand()%14)+1,0,190,"Press 'q' to exit the game ...") ;
	     }
	}
	else{
	    //start
	     while(1){
	    if(kbhit()){
	      char ch = getch() ;
	      if(ch == 'q'){
	      exit(0) ;
	      }
	      else if( ch == 'r'){
		x = 640 / 2 ; y = 480 / 2 -20 ;
		tailCount = 0 ; gameEnd = 0 ;
		xr = 1 ; yr = 1 ;
		score = 0 ; choise = 'd';
		clearAll() ;
		return ;
	      }
	      else if( ch == 'x'){
		choise = 'x' ;
		x = xPoints[xr-3] ; y = yPoints[yr-3] ;
		xr-=2 ; yr-= 2;
		gameEnd = 0 ; endType = 0 ;
		clearAll() ;
		return ;
	      }
	    }
	      drawString(0,0,3,(rand()%14)+1,0,20,"Score : ") ;
	      string = intToStr(score) ;
	      drawString(0,0,3,(rand()%14)+1,180,20,string) ;
	      free(string) ; string = "" ;
	      drawString(0,0,2,(rand()%14)+1,0,60,"Game Ended by walking Over the Body ...") ;
	      drawString(0,0,2,(rand()%14)+1,0,100,"Press 'x' to recontinue the game ...") ;
	      drawString(0,0,2,(rand()%14)+1,0,140,"Press 'r' to restart the game ...") ;
	      drawString(0,0,2,(rand()%14)+1,0,190,"Press 'q' to exit the game ...") ;
	     }
	    //finish
	}
     }
}

