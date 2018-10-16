#include "SDL_UI.h"
#include <SDL2/SDL.h>
#include <fstream>
#include <stdio.h>
#include <regex>
/*
 displayText(site(500, 470, 0, 100),
 "文字", 0xffffff, 0); reFlush(c);
  Button(site(500, 1020, 200, 100),
 0xff, (char *)"test", 0xffffff, 100, 0)
*/
using namespace std;

//函数声明
bool checknm0(char *name);
bool checknm(char *name,char n2n[128][64]);
int  renamebat(string Name);
char renamestr[64] ;

int main(int argc, char **args) {
  Init("hello world!", 1080, 1920);
  ttf_Init(50);
  int countp;
  char displaytext[1024];
  
  LIST li;

   /*************读取辅助文件************/
  ifstream index("/sdcard/cide/index.txt", ios::in);
 if (!index) {
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


    if (Zbutton==2) {
      Logout("左边");
      site_x+=5;
      if(site_x>1080)
        site_x = 0;
    }
    if (Ybutton==2) {
      Logout("右边");
      site_x -= 5;
      if (site_x < 0)
        site_x = 1080;
    }


    Button(site(site_x, site_y, site_w_h, site_w_h), col[col_i], (char *)"",
           0x0, 80, 0);

    
  }
  }
  char n2n[128][64];
  for (int count_ = 0; index.getline(n2n[count_], 64); count_++) {
    countp = count_;
  }

  while (0) {
   
    reFlush(0x666666);
    eventState();
/***********************************/
    /*	按钮声明	*/
    int quit1 = Button(site(0, 0, 200, 100), 0x6666ff, (char*)"[quit]", 0x221111, 80, 0);

    int check = Button(site(600, 0, 400, 100), 0x6666ff,(char*)"[检查已有项目]", 0x999999, 80, 0);

/***********************************/
    /*	列表声明	*/

    slideList(site(10,200,500,1600),0x555555,li,80,100,-1);
    
    slideText(site(600,300,450,400),0x555555,displaytext,0xbbbbbb,80);//滑动文本框

  		 
/***********************************/
    /*	按钮事件	*/
    if (quit1) {
      Quit();
      return 0;
    }
    if (check) {
    system("cd /sdcard/tencent/QQfile_recv && ls>/sdcard/cide/zyindex.txt ");
   // system("cd /sdcard && ls>/sdcard/cide/zyindex.txt ");
   /******读取文件 写入列表 统计*******/
    ifstream out("/sdcard/cide/zyindex.txt", ios::in);
	if(!out)
  	 {
    	 sprintf(INF_str, "文件读取失败!");
    	 INF_start = SDL_GetTicks();
         Quit();
 	 }
 
 /****************读取目标文件**********/
     for (int nullinit = 0; nullinit<256; nullinit++) {
       sprintf(li.str[nullinit],"");
     }
     int  count_0 = 0;
     char tmp[128][64];
     while (out.getline(tmp[count_0], 64)) {
       count_0++;
     }
 /******************************/
     li.n = count_0;
     int pdcount = 0;
     for (int j = 0; j < count_0; j++) {
     	//文件名判断
        if (
       // checknm0(tmp[j])
        checknm(tmp[j],n2n)
        ) {
         // sprintf(li.str[pdcount], "%s", tmp[j]);
          string Name = tmp[j];
         // Name = li.str[pdcount];
          renamebat(Name);
          
          sprintf(li.str[pdcount], "%d: %s", pdcount + 1, renamestr);
          pdcount++;
          Logout(li.str[pdcount-1]);
        }
     }
     count_0 = pdcount;
     sprintf(displaytext,"检测到%d项\n有%d项缺失",count_0,countp-count_0+1);
     
/*************************************/
      sprintf(INF_str, "查询完毕");
      INF_start = SDL_GetTicks();
      out.close();
    }

/***********************************/
  }
  index.close();
}

int renamebat(string Name) //批量重命名
{
  regex NUMT("\\d{2,4}"),
  	  NAMT("[\u4e00-\u9fa5]+"),
  	  TYPT("[a-zA-Z]+");
  
  smatch snum,snam,styp;
  char res_num[32], res_nam[32], res_typ[32];

  regex_search(Name,snum,NUMT);
  regex_search(Name,snam,NAMT);
  regex_search(Name,styp,TYPT);
  sprintf(res_num,"%s",snum.str().c_str());
  sprintf(res_nam,"%s",snam.str().c_str());
  sprintf(res_typ,"%s",styp.str().c_str());
  Logout("重命名开始");
  Logout(res_num);
  Logout(res_nam);
  Logout(res_typ);
  sprintf(renamestr,"%s_%s.%s", res_num,res_nam,res_typ);

  char Linuxstr[256];
  sprintf(Linuxstr,"cd /sdcard/tencent/QQfile_recv && mv %s %s" , Name.c_str() ,renamestr);
  Logout(Name.c_str());
  Logout(Linuxstr);
  Logout("重命名结束");
  if (res_num[0]) {
    system(Linuxstr);
  }
  return 0;
	}



bool checknm0(char *name)  //使用正则进行文件名检查
{
   regex SDNM("\\d{2,4}.[\u4e00-\u9fa5]{0,}\\.[a-zA-Z]+"); //数字.任意加汉字

   //regex SDNM("[a-z]+\\.[a-z]+");

   bool  result = regex_match(name, SDNM);
   return result;
}

bool checknm(char *name,char n2n[128][64])  //使用正则进行文件名检查
{
  string name_ = name;
  regex NAMC("[\u4e00-\u9fa5]+");
  smatch RNAM;
  char   c_nam[64];
  regex_search(name_,RNAM,NAMC);
  sprintf(c_nam, "%s", RNAM.str().c_str());
  Logout(c_nam);
  bool isZY ;
  for (int c_j = 0; n2n[c_j][1]; c_j++) {
    isZY = true;
    for (int c_i = 0;n2n[c_j][c_i]||c_nam[c_i]; c_i++)      {
      if (c_nam[c_i] != n2n[c_j][c_i])
        isZY = false;
    }
    char istrue[64];
    sprintf(istrue, "%s:%d", n2n[c_j], isZY);
    Logout(istrue);
    if (isZY == 1)
      break;
  }
  
  Logout("文件名检测结束");
  return isZY;
}