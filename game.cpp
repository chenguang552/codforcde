#include <SDL_UI.h>
#include <SDL2/SDL.h>
#include <math.h>
#include <sys/time.h>
#include <stdio.h>
#include <thread>
#include <iostream>
#include <unistd.h>//调用sleep函数
#define pi 3.1415926

using namespace std;
bool stage_1(int x, int y,int HandW,int pyl);
void gameover();
void drawcircle_(int x, int y, int r,float R);
bool PZpanding(int x, int y, int r, int xx, int yy, int HandW);
bool Zacir(int x, int y, int r, float R, int xx, int yy, int HandW);
//函数声明
int main(int argc, char **args) {
beg:
    Init("hello world!", 1080, 1920);
    ttf_Init(50);
  float site_w_h = 20;
  int site_x = site_w_h, site_y = site_w_h;

  SDL_Texture *bir[3] = {NULL};
  bir[0] = IMG_LoadTexture(ren, "redbird-upflap.png");
  bir[1] = IMG_LoadTexture(ren, "redbird-midflap.png");
  bir[2] = IMG_LoadTexture(ren, "redbird-downflap.png");
  
  
  int pyl = 0;
{
  /* Logout("辅助文件读取失败!");
    Quit();*/
  int site_x = 0, site_y = 0, site_w_h = 20;
  unsigned int col[2] = {0xffffffff, 0x11111fff};
  int col_i = 0;
  while (1) {/***********循环开始*************/
    reFlush(0x0);
    eventState();
    site_y ++;
    if (site_y == 1920)
      site_y = 0;
               
    Button(site(0, 0, 540, 1920), 0x0, (char *)"", 0x0, 80, 0);
    Button(site(540, 0, 540, 1920), 0xffffffff, (char *)"", 0x0, 80, 0);

    /*生成随机点  
       Button(site(site_x, site_y, site_w_h, site_w_h), col[col_i], (char *)"",
           0x0, 80, 0);
   */
    int level_1[13][96] = {0};
    int level_2[13][96] = {0};
    int level_3[13][96] = {0};

    for (int i = 0; i < 13;i++) {
      for (int j = 0; j < 96; j++) {//生成1或0随机数
        level_1[i][j] = rand();
        /*
        
        *
        未完待续。。。。。
        *
        
        */
      }
    }
        if (site_x < 540-(site_w_h/2)) {
      col_i = 0;
    } else {
      col_i = 1;
    } 
    int Zbutton = Button(site(0, 0, 540, 1920), 0x0, (char *)"",
                       0x0, 80, 0);
    int Ybutton = Button(site(540, 0,540, 1920), 0x0, (char *)"",
                       0x0, 80, 0);


    if (Zbutton) {
      Logout("左边");
      site_x+=5;
      if(site_x>1080)
        site_x = 0;
    }
    if (Ybutton) {
      Logout("右边");
      site_x -= 5;
      if (site_x < 0)
        site_x = 1080;
    }

    Button(site(site_x, site_y, site_w_h, site_w_h), col[col_i], (char *)"",
           0x0, 80, 0);
  }
}
  return 0;
}
//@@@@@@@@@@@@@@   函数    @@@@@@@@@@@@
bool stage_1(int x,int y,int HandW,int pyl) {
  int nx[6] = {150, 600, 700, 380, 800, 200},
      ny[6] = {800, 200, 400, 1500, 700, 1200},
      banj[6] = {80, 130, 170, 140, 200, 100};
  for(int i=0;i<6;i++){
   // drawcircle_(nx[i], ny[i], banj[i], 0.1);
   if (Zacir(nx[i], ny[i], banj[i], 0.1, x, y, HandW)) {
     return true;
   }
   }
   return false;
}
//%%%**********              *画圆
  void drawcircle_(int x,int y,int r,float R) {
    if (x < 540 - r) {
      SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); //左圆
      drawCircle(x, y, r, r-R, 0, 360);
    } else {
      if (x < 540+ r) {
        float JD =(acos((540.0 - x) / r))*180/pi;
   //     char a[16];
    //    sprintf(a, "%f",JD);
      //  Logout(a);
        SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); //右半圆
        drawCircle(x, y, r, r-R, -JD, JD);
        SDL_SetRenderDrawColor(ren, 255, 255, 255, 255); //左半圆
        drawCircle(x, y, r, r-R, JD, 360-JD);
      }else{
               SDL_SetRenderDrawColor(ren, 0, 0, 0, 255); //右圆
               drawCircle(x, y, r, r -R, 0,360);
      }
    }
    
 }
 //             碰撞判定
 bool PZpanding(int x,int y,int r,int xx,int yy,int HandW) {
   if (((xx - x) * (xx - x) + (yy - y) * (yy - y)) >
       ((r + HandW) * (r + HandW))) {
     return false;
   } else {
     return true;
   }
 }
 //障碍
 bool Zacir(int x, int y, int r, float R, int xx, int yy, int HandW) {
   drawcircle_(x, y, r, R);
   return PZpanding(x, y, r, xx, yy, HandW);
 }