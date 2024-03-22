#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <vector>
#include <stdio.h>
#include <cstdlib>
using namespace std;

struct {
    vector <vector<int>> m;
    vector <int> m1,m2;
    int d1=0;
    int d2=0;
    int p=1;
    int movesCounter=0;
    int x1,y1;
    int index;
    int n;
    int quit=0;
    int state=0;
} T;

void gameStateWriteInfo() {
    FILE *fptr;
    fptr = fopen("XOgameStateFile.bin","wb");

    if (fptr == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    fwrite(&T.n, sizeof(T.n), 1, fptr);
    fwrite(&T.state, sizeof(T.state), 1, fptr);

    for (int i = 0; i < T.n; i++) {
        for (int j = 0; j < T.n; j++) {
           int num = T.m[i][j];
           fwrite(&num, sizeof(num), 1, fptr);
        }
    }
    fclose(fptr);
}

void gameStateReadInfo() {
    FILE *fptr;
	fptr = fopen("XOgameStateFile.bin","rb");

	if (fptr == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    fread(&T.n, sizeof(T.n), 1, fptr);
    fread(&T.state, sizeof(T.state), 1, fptr);

    for (int i = 0; i < T.n; i++) {
        for (int j = 0; j < T.n; j++) {
           int num;
           fread(&num, sizeof(num), 1, fptr);
           T.m[i][j] = num;
        }
    }
    fclose(fptr);
}

void clearMatrix() {
    T.m = vector<vector<int>>(T.n, vector<int>(T.n, 0));
}

void clearArray(){
    T.m1= vector<int>(T.n,0);
    T.m2= vector<int>(T.n,0);
}

void exitImage() {
    setlinestyle(0,0,1);
    setcolor(LIGHTBLUE);
    rectangle(580,5,700,60);
    setbkcolor(BLACK);
    setcolor(YELLOW);
    settextstyle(8,0,4);
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    outtextxy(600,40,"menu");
}

void replayImage() {
    setlinestyle(0,0,1);
    setcolor(LIGHTBLUE);
    rectangle(7,5,147,60);
    setbkcolor(BLACK);
    setcolor(YELLOW);
    settextstyle(8,0,4);
    settextjustify(RIGHT_TEXT,CENTER_TEXT);
    outtextxy(138,40,"replay");
}

void table() {
    setfillstyle(SOLID_FILL,BLACK);
    bar(10,90,getmaxx()-10,getmaxy()-10);
    setlinestyle(0,0,1);
    setcolor(LIGHTBLUE);

    for (int i=1;i<T.n;i++) {
        line(10+(690/T.n)*i,90,10+(690/T.n)*i,780);
        line(10,90+(690/T.n)*i,700,90+(690/T.n)*i);
    }

    exitImage();
    replayImage();
}

void draw(int f,int color) {
    setbkcolor(BLACK);
    settextstyle(BOLD_FONT,0,6);
    settextjustify(LEFT_TEXT,CENTER_TEXT);
    setcolor(color);
    if (f==0) outtextxy(165,50,"IT'S A DRAW!");
    else {
            if (T.p==1) outtextxy(230,50,"O WON!!!");
            else outtextxy(230,50,"X WON!!!");
    }
}

void replay() {
    clearMatrix();
    T.state=0;
    gameStateWriteInfo();
    clearArray();
    T.d1=0;
    T.d2=0;
    table();
    draw(0,0);
    T.movesCounter=0;
    T.p=1;
}

void cross(int x,int y,int color,int linewidth) {
    int newX=690/T.n*x+(690/T.n/2)+10;
    int newY=690/T.n*y+(690/T.n/2)+90;
    int r=(690/T.n/2)-30;
    setlinestyle(0,0,linewidth);
    setcolor(color);
    line(newX-r,newY-r,newX+r,newY+r);
    line(newX+r,newY-r,newX-r,newY+r);
}

void zero(int x,int y,int color,int linewidth) {
    setlinestyle(0,0,linewidth);
    setcolor(color);
    circle(690/T.n*x+(690/T.n/2)+10,690/T.n*y+(690/T.n/2)+90,(690/T.n/2)-25);
}

void winnerLine() {

    if (T.index==1) {
        for(int i = 0; i < T.n; i++) {
            if (T.p==-1) cross(T.x1,i,14,5);
            else zero(T.x1,i,14,5);
        }
    }

    if (T.index==2) {
        for(int i = 0; i < T.n; i++) {
            if (T.p==-1) cross(i,T.y1,14,5);
            else zero(i,T.y1,14,5);
        }
    }

    if (T.index==3) {
        for(int i = 0; i < T.n; i++) {
           if (T.p==-1) cross(i,i,14,5);
           else zero(i,i,14,5);
        }
    }

    if (T.index==4) {
        for(int i = 0; i < T.n; i++) {
            for(int j = 0; j < T.n; j++) {
               if (i+j==T.n-1) {
                    if (T.p==-1) cross(i,j,14,5);
                    else zero(i,j,14,5);
                }
            }
        }
    }
}

void won() {
    T.state=0;
    gameStateWriteInfo();
    winnerLine();
    T.movesCounter=T.n*T.n;
    draw(0,0);
    draw(1,14);
}

void oneMove() {

    if (T.p==1) T.m[T.x1][T.y1]=1;
    else T.m[T.x1][T.y1]=-1;
    T.p*=-1;
    T.movesCounter++;
    T.state=T.n;
    gameStateWriteInfo();

    if (T.movesCounter==T.n*T.n) {
        draw(0,14);
        T.state=0;
        gameStateWriteInfo();
    }

    if (T.p==1) {
           T.m1[T.x1]++;
           T.m2[T.y1]++;
           if(T.x1==T.y1) T.d1++;
           if(T.x1+T.y1==T.n-1) T.d2++;

           if (T.m1[T.x1]==T.n) {
                T.index=1;
                won();
           }
           if (T.m2[T.y1]==T.n) {
                T.index=2;
                won();
           }
           if (T.d1==T.n) {
                T.index=3;
                won();
           }
           if (T.d2==T.n) {
                T.index=4;
                won();
           }
    }

    else {
           T.m1[T.x1]+=10;
           T.m2[T.y1]+=10;
           if(T.x1==T.y1) T.d1+=10;
           if(T.x1+T.y1==T.n-1) T.d2+=10;

           if (T.m1[T.x1]==T.n*10) {
                T.index=1;
                won();
           }
           if (T.m2[T.y1]==T.n*10) {
                T.index=2;
                won();
           }
           if (T.d1==T.n*10) {
                T.index=3;
                won();
           }
           if (T.d2==T.n*10) {
                T.index=4;
                won();
           }
    }
}

void inTheGame() {
    int x,y;
    while(1) {
        if(ismouseclick(WM_LBUTTONDOWN)) {
            x=mousex();
            y=mousey();

            if(x<700 && x>580 && y>5 && y<60){ //player clicked on the Menu button
                T.state=0;
                gameStateWriteInfo();
                closegraph();
                return;
            };
            if(x<160 && x>15 && y>5 && y<60) replay();//player clicked on the Replay button

            if (((x>10 && x<700 && x!=240 && x!=470) && (y>90 && y<780 && y!=220 && y!=550)) && T.movesCounter<T.n*T.n) {

                T.x1=(x-10)/(690/T.n);
                T.y1=(y-90)/(690/T.n);

                if (T.p==1 and abs(T.m[T.x1][T.y1])!=1) {
                    cross(T.x1,T.y1,15,3);
                    oneMove();
                }

                else if(T.p==-1 and abs(T.m[T.x1][T.y1])!=1) {
                    zero(T.x1,T.y1,15,3);
                    oneMove();
                }
            }
            delay(50);
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

void reconstructData() {

    for(int i = 0; i < T.n; i++) {
        for(int j = 0; j < T.n; j++) {

            if(T.m[i][j]==1) {
                T.m1[i]+=10;
                T.m2[j]+=10;
                if(i==j) T.d1+=10;
                if (i+j==T.n-1) {
                    T.d2+=10;
                }
                T.movesCounter++;
            }

            if(T.m[i][j]==-1) {
                T.m1[i]+=1;
                T.m2[j]+=1;
                if(i==j) T.d1+=1;
                if (i+j==T.n-1) {
                    T.d2+=1;
                }
                T.movesCounter++;
            }
        }
    }

    if (T.movesCounter%2==1)
        T.p=-1;
    else T.p=1;
}

void readTableSizeAndGameState() {
    FILE *fptr;
	fptr = fopen("XOgameStateFile.bin","rb");

	if (fptr == NULL) {
        printf("Error! opening file");
        exit(1);
    }

    fread(&T.n, sizeof(T.n), 1, fptr);
    fread(&T.state, sizeof(T.state), 1, fptr);
    fclose(fptr);
}

void oldGame() {

    readTableSizeAndGameState();

    if (T.state!=0) {
        clearMatrix();
        clearArray();
        gameStateReadInfo();

        initwindow(710,790,"XO",getmaxwidth()/2 - 710/2 ,getmaxheight()/2 - 790/2-20);
        table();
        for (int i = 0; i < T.n; i++) {
            for (int j = 0; j < T.n; j++) {
                if(T.m[i][j]==1) cross(i,j,15,3);
                if(T.m[i][j]==-1) zero(i,j,15,3);
            }
        }
        reconstructData();
        inTheGame();
    }
}

bool menu() {

    initwindow(710,790,"XO",getmaxwidth()/2 - 710/2 ,getmaxheight()/2 - 790/2-20);

    setfillstyle(1,BLACK);
    bar(0,0,getmaxx(),getmaxy());

    setbkcolor(BLACK);
    setcolor(LIGHTBLUE);
    settextstyle(8,0,9);
    outtextxy(20,0,"Tic-tac-toe");

    setbkcolor(LIGHTBLUE);
    setcolor(BLUE);
    settextstyle(8,0,6);
    outtextxy(267,170,"3 X 3");
    outtextxy(267,250,"4 O 4");
    outtextxy(267,330,"5 X 5");
    outtextxy(267,410,"6 O 6");
    outtextxy(267,490,"7 X 7");
    outtextxy(267,570,"8 O 8");

    setlinestyle(0,0,THICK_WIDTH);
    rectangle(266,169,433,224);
    rectangle(266,249,433,304);
    rectangle(266,329,433,384);
    rectangle(266,409,433,464);
    rectangle(266,489,433,544);
    rectangle(266,569,433,624);

    setbkcolor(BLACK);
    rectangle(266,650,433,710);
    outtextxy(283,655,"Exit");

    while(1) {
        if(ismouseclick(WM_LBUTTONDOWN)) {

            int x=mousex();
            int y=mousey();
            int q=0;

            if(x<433 && x>266 && y>650 && y<710){
                return 0;
            }

            for(int i=0;i<6;i++) {
                int a = 169+80*i;
                int b = 224+80*i;

                if(x<433 && x>266 && y>a && y<b){
                        T.n=i+3;
                        replay();
                        q=1;
                        break;
                }
            }

            if(q==1) {
              closegraph();
              initwindow(710,790,"XO",getmaxwidth()/2 - 710/2 ,getmaxheight()/2 - 790/2-20);
              table();
              inTheGame();
              return 1;
            }
            delay(50);
            clearmouseclick(WM_LBUTTONDOWN);
        }
    }
}

int main() {
    oldGame();
    while(menu());
    return 0;
}
