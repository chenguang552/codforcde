/*
版本:SDL_UI FOR ANDROID  v3.1
编写者：小鱼儿
百度id:简单aaaaaa
功能:SDL的常用封装函数
SDL_UI交流群:165486113
增加Triangle按钮 ：绘制三角形
建立日期:2015-09-24
更新日期:2017-12-18
*/
#include <time.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_events.h>
#include <GLES/gl.h>
#define SDL_UI
const char*LOG_FILE="SDL_UI_log.txt";
 struct Triangle
{
	int triax[3];
	int triay[3];
};

typedef struct Triangle Triangle;

 struct EVE_FINGER
{
	int id;
	int x;
	int y;
	int state;
	Uint32 time;
};
typedef struct EVE_FINGER EVE_FINGER;

struct EVE_POS
{
	int x;
	int y;
	
};
typedef struct EVE_POS EVE_POS;

struct LIST//list结构体
{
	int n;
	char str[500][256];
};
typedef struct LIST LIST;


//SDL_UI定义的函数
double angel(double a,double b,double x,double y);//求线段角度
double angel (double a,double b,double x,double y,double c,double d);
char *strtoa(char *str, int n, int r);

			
int thread_fps(void*ptr);//记录程序运行状态
int eventState();//获取Event事件
	
SDL_Rect reSite(int x,int y,int w,int h);//还原屏幕自适应坐标	
SDL_Rect site(int x,int y,int w,int h);
//获得屏幕自适应后的坐标
Triangle site(int x,int y,int w,int h,int a,int b);//三角形坐标屏幕自适应
int Logout(const char*text);
	int Quit();//退出SDL,释放内存
int Init(const char *titel ,int aw,int ah);//初始化SDL引擎
	int  ttf_Init(int size);//字库加载
	int mixInit(int i);
int quitAudio();
SDL_Surface*loadSurface(SDL_Rect rect ,const char*str);
	SDL_Texture*loadTexture(SDL_Rect rect ,const char*str);
int txtTexture(char*str,unsigned long int  a);//文字Text图层
	int drawLine(SDL_Rect rect);//画线
		int drawFillRect(SDL_Rect rect);//画填充式的矩形
	int drawRect(SDL_Rect rect);//画矩形
	int drawTriangle(Triangle tria);
		 int drawCircle(int x,int y,float r,float R,float a,float b);//画圆
	int drawPolygon(int x,int y,int l,int rr,int R,int o,int b,double r);//多边形
SDL_Surface*catSurface(SDL_Surface*s1,SDL_Surface*s2,int x,int y);
int displaySurface(SDL_Rect pos,SDL_Surface*sur,double angel);
	int displayTexture(SDL_Rect pos,SDL_Texture*tex,double angel);
  	int displayTxt(SDL_Rect pos,char*str,unsigned long int a,double angel);
  	 int displayText(SDL_Rect rect,char*str,unsigned long int a,double angel);
	int loopTexture(SDL_Rect rect,SDL_Texture**tex,int n,int time);
		SDL_Surface* discolor(SDL_Surface*sur);
int INF_box();
 int Button(SDL_Rect rect,unsigned long int a,char*str,unsigned long int c,int size,int align);
  int imgButton(SDL_Rect rect,SDL_Texture*tex,char*str,unsigned long int c,int size,int align);
 int circleButton(SDL_Texture*tex,int x,int y ,int r,char*str,unsigned long int c);
int triangleButton(Triangle tria,unsigned long int a);
int slideBar(SDL_Rect rect,unsigned long int a,double* z);
int pointer(SDL_Rect rect,unsigned long int a,double*f);
int selectBox(SDL_Rect rect,unsigned long int a,int *i);
int glint(SDL_Rect rect,int time);//闪烁的指针
int txtBox(SDL_Rect rect,char*str,unsigned long int a,int h);
int listView(SDL_Rect rect,unsigned long int a,LIST li,
char*title,unsigned long int c,int size,int align);
int slideList(SDL_Rect rect,unsigned long int a,LIST li,int h,int size,int align);
int slideText(SDL_Rect rect,unsigned long int b,char*str,unsigned long int a,int h);
int inputBox(SDL_Rect rect,char*str,unsigned long int a);
int slideInput(SDL_Rect rect,unsigned long int b,char*str,unsigned long int a,int h);

//SDL_UI定义的变量

//窗口和渲染器
SDL_Window*win=NULL;//SDL窗口指针
SDL_Renderer*ren=NULL;//SDL渲染器指针，
//bool QUIT=false;
//自适应屏幕比
int S_w,S_h;//屏幕宽度和高度
int W_w,W_h;
double S_x,S_y;//屏幕自适应比例

//event事件
SDL_Event event;//SDL事件结构体
int Ex=0;
int Ey=0;
int EVEx=0;
int EVEy=0;
EVE_POS EVE_pos[20];
SDL_TouchID device;
SDL_Finger*finger;
int EVE_fingernum=0;
int FINGERDOWN=1;
int FINGERUP=2;
int FINGERMOTION=3;
int KEYDOWN=4;
int KEYUP=5;
int TEXTINPUT=6;
int state=0;//event的状态
int laststate=0;


int lastfingernum=0;

//文字
TTF_Font*TXT_font;
double  TXT_size=0;
double TXT_w=0.44;
double TXT_dw=1.6;
int TXT_max=0;//
int TXT_id=0;//文字图层id值
char  TXT_strtemp[1000][100];
unsigned long int TXT_color[1000];
SDL_Texture*TXT_texture[1000];

//底部信息提示
char INF_str[50];//INF_box待发送的信息
SDL_Rect INF_pos;//INF_box的位置
int INF_time=1500;//INF_box的显示时间
Uint32 INF_start;
float INF_site=0.9;
//INF_box计时器初值(SDL_GetTicks()提供
//按钮
Uint32 Button_time=0;//按下的时间
int Button_longtime=500;
int Button_flag=0;
int Button_Static_id=0;
int Button_Trends_id=0;
int Button_id=0;//按钮id
int Button_Temp_id=0;
SDL_Rect Button_rect;//对Button区域的检测
Triangle Button_tria;


//输入框
int INP_x;//记录输入框的坐标
int INP_y;//记录输入框的坐标
int INP_site[100]={0};//光标坐标
char INP_str[100][256]={""};
int INP_kb=1; //是否启动键盘
//滑动输入框
int INP_n[100]={0};//光标所在字节
int INP_k[100]={0};//光标开关
int INP_state[100]={0};
int INP_al[100]={0};
int INP_fu[100]={0};
int INP_id=0;


//滑动文本框
int TXTBOX_i[100]={0};//保存数据起点
int TXTBOX_flag[100]={0};//标志
int TXTBOX_slide[100]={0};//滑动惯性
int TXTBOX_fu[100]={0};//文本框滑动距离
SDL_Rect TXTBOX_rect;//保存当前输入框坐标
int TXTBOX_id=0;



//滑动列表
int LIST_n[100]={0};//滑动列表的id
int LIST_h[100]={0};//滑动列表的顶部高度
int LIST_inertia[100]={0};//滑动惯性
int LIST_id=0;

int SLIDEBAR_state=0;

//动画
int LOOP_n[100]={0};
int LOOP_a[100]={0};//
int LOOP_id=0;


//FPS线程
SDL_Thread*FPS_thread;
char FPS_str[100]="";//
int FPS_fps=0;
int FPS_num;
char FPS_mem[30]="";
FILE*FPS_p=NULL;

//SDL_Thread*event_thread;




/*
void TTF_SetFontStyle(TTF_Font *font, int style);
	TTF_STYLE_BOLD
2
TTF_STYLE_ITALIC
3
TTF_STYLE_UNDERLINE
4
TTF_STYLE_STRIKETHROUGH
5
TTF_STYLE_NORMAL
这些参数支持掩码(bitmask)，也就

int TTF_GetFontStyle(TTF_Font *font);

void TTF_SetFontOutline(TTF_Font *font, int outline);
2
int TTF_GetFontOutline(TTF_Font *font);

*/


double angel(double a,double b,double x,double y)//求线段角度
{
double angel=atan((y-b)/(x-a))/3.141592653*180;
if(x>=a&&y<b)//第四象限
angel=360+angel;
else
if(x<a&&y>=b)//第二象限
angel=180+angel;
else
if(x<a&&y<b)//第三象限
angel=180+angel;

return angel;
}
double angel (double a,double b,double x,double y,double c,double d)
{
	double e=fabs(angel(x,y,a,b)-angel(x,y,c,d));

	if(e>180)e=360-e;

	return e;
}

char *strtoa(char *str, int n, int r)
{
	int i = 0;
	char s[1000] ="";
	char *p=(char*)malloc(1000);
	strcpy(p,"");
	for (; n <= r; n++, i++)
		s[i] = str[n];
	s[i + 1] = '\0';
	strcpy(p, s);
	return p;
}
char*strde(char*a,int b,int c)
{

		char *p=(char*)malloc(1000);
strcpy(p,"");
char*s=strtoa(a,0,b-1);
strcat(p,s);
free(s);
s=strtoa(a,c,strlen(a));
strcat(p,s);
free(s);
strcpy(a,p);
return p;
}
char *strin(char*a,int b,const char*c)
{
	char *p=(char*)malloc(1000);
strcpy(p,"");
char*s=strtoa(a,0,b-1);
strcat(p,s);
free(s);
strcat(p,c);
s=strtoa(a,b,strlen(a));
strcat(p,s);
free(s);
//strcpy(a,p);
return p;
}

int strflush(char*str)//初始化字符串
{
for(int i=strlen(str);i>=0;i--)
str[i]='\0';
return 0;
}


int thread_fps(void*ptr)//记录程序运行状态
{
while(1){
FPS_fps=0;

SDL_Delay(1000);	
sprintf(FPS_str,"w:%d\nh:%d\nfps:%d \nid:%d\neve:%d\nT:%d\nmem:%s\nstate=%d",	S_w,S_h,FPS_fps,TXT_max,state,SDL_GetTicks(),FPS_mem,SLIDEBAR_state);

	}
	return 0;
}


/*
int eventstate()
{
int i=0;

while(SDL_PollEvent(&event))
{
device=SDL_GetTouchDevice(0);	EVE_fingernum=SDL_GetNumTouchFingers(device);
if(event.type==SDL_FINGERDOWN||
event.type==SDL_FINGERUP||
event.type==SDL_FINGERMOTION
){
for(i=0;i<EVE_fingernum;i++)
{
finger=SDL_GetTouchFinger(device,i);
if(finger!=NULL)
{
EVE_finger[i].id=finger->id;
EVE_finger[i].x=finger->x*S_w;
EVE_finger[i].y=finger->y*S_h;
//EVE_pos[i].state=event.tfinger.type;
//获得多触点坐标
if(event.type==SDL_FINGERDOWN)
{
if(EVE_finger[i].id==event.tfinger.fingerId)
{
EVE_finger[event.tfinger.fingerId].state=1;
EVE_finger[event.tfinger.fingerId].time=
event.tfinger.timestamp;
state=FINGERDOWN;
}
}
if(event.type==SDL_FINGERUP)
{if(EVE_finger[i].id==event.tfinger.fingerId){
EVE_finger[event.tfinger.fingerId].state=3;
EVE_finger[event.tfinger.fingerId].time=
event.tfinger.timestamp;
state=FINGERUP;
}
}
if(event.type==SDL_FINGERMOTION)
{
state=FINGERMOTION;	if(EVE_finger[i].id==event.tfinger.fingerId){
if(EVE_finger[i].x!=(int)Ex||EVE_finger[i].y!=(int)Ey);
//EVE_finger[event.tfinger.fingerId].state=2;
}


}


}
}


}




else {device=SDL_GetTouchDevice(0);
EVE_fingernum=SDL_GetNumTouchFingers(device)+1;}


if(event.type==SDL_KEYDOWN)
state=KEYDOWN;
if(event.type==SDL_KEYUP)state=KEYUP; if(event.type==SDL_TEXTINPUT)
state=TEXTINPUT;

if(event.type==SDL_DOLLARGESTURE);
if(event.type == SDL_DOLLARRECORD);
if(event.type == SDL_MULTIGESTURE);




}


return 0;
}

*/

int eventState()//获取Event事件
{
	int i;
SDL_TouchID device=SDL_GetTouchDevice(0);
SDL_Finger*finger;
	while(SDL_PollEvent(&event))
	{
	if(event.type==SDL_FINGERDOWN)
	state=FINGERDOWN;

if(event.type==SDL_FINGERUP)state=FINGERUP; 
if(event.type==SDL_FINGERMOTION)state=FINGERMOTION;
if(event.type==SDL_KEYDOWN)state=KEYDOWN;
if(event.type==SDL_KEYUP)state=KEYUP; 
if(event.type==SDL_TEXTINPUT)state=TEXTINPUT;
if(event.type==SDL_DOLLARGESTURE){};
if(event.type == SDL_DOLLARRECORD){};
if(event.type == SDL_MULTIGESTURE){};
//if(event.type==SDL_APP_WILLENTERBACKGROUND){QUIT=true;}
//if(event.type==SDL_APP_WILLENTERFOREGROUND){QUIT=true;}
//if(event.type==SDL_APP_DIDENTERBACKGROUND){QUIT=true;}
//if(event.type==SDL_APP_DIDENTERFOREGROUND){QUIT=true;}
}
Ex=event.tfinger.x*S_w;
Ey=event.tfinger.y*S_h;
EVEx=event.tfinger.x*W_w;
EVEy=event.tfinger.y*W_h;
//获得多触点坐标
EVE_fingernum=SDL_GetNumTouchFingers(device);
for(i=0;i<EVE_fingernum;i++)
{
finger=SDL_GetTouchFinger(device,i);
if(finger!=NULL)
{EVE_pos[i].x=finger->x*S_w;
EVE_pos[i].y=finger->y*S_h;
}}

	return 0;
}

SDL_Rect reSite(int x,int y,int w,int h)//还原屏幕自适应坐标
{
SDL_Rect site;
site.x=round(x/S_x);site.y=round(y/S_y);
site.w=round(w/S_x);site.h=round(h/S_y);
return site;
}
SDL_Rect site(int x,int y,int w,int h)
//获得屏幕自适应后的坐标
{
SDL_Rect site;
site.x=round(x*S_x);site.y=round(y*S_y);
site.w=round(w*S_x);site.h=round(h*S_y);
return site;
}
Triangle site(int x, int y, int w, int h, int a, int b) //三角形坐标屏幕自适应
{
	Triangle tria;
	tria.triax[0] = round(x * S_x);
	tria.triay[0] = round(y * S_y);
	tria.triax[1] = round(w * S_x);
	tria.triay[1] = round(h * S_y);
	tria.triax[2] = round(a * S_x);
	tria.triay[2] = round(b * S_y);
	return tria;
}
int Logout(const char*text)
//输出程序运行的log日志
{
	struct timeval tms;
	FILE*fp=NULL;
fp=fopen(LOG_FILE,"a+");
fclose(fp);	if((fp=fopen(LOG_FILE,"r+"))!=NULL)
	{
	char str[1000]="";
	gettimeofday(&tms, NULL);
	strftime(str, 100, "%F %w %X",localtime(&tms.tv_sec));
	strcat(str,text);
		strcat(str,"\n");
fseek(fp,0,2);
fwrite(str,1,strlen(str),fp);
	fclose(fp);
		}
		return 0;
	
}

	
	int Quit()//退出SDL,释放内存
{
int i;	
	for(i=0;i<100;i++)	SDL_DestroyTexture(TXT_texture[i]);	
    TTF_CloseFont(TXT_font);
	TTF_Quit();
	SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
	SDL_Quit();
	return 0;
}


int Init(const char *titel ,int aw,int ah)//初始化SDL引擎
{

	W_w=aw;W_h=ah;
if(SDL_Init(SDL_INIT_EVERYTHING)!=0)
{
Logout(SDL_GetError());	
Logout("SDL_INIT_EVERYTHING初始化失败");
if(SDL_Init(SDL_INIT_VIDEO)!=0)
{
Logout(SDL_GetError());	
Logout("SDL_INIT_VIDEO初始化失败");
return -1;
}

}

Logout("SDL初始化成功");


win=SDL_CreateWindow(titel,0,0,W_w,W_h,SDL_WINDOW_OPENGL);
Logout(SDL_GetError());
if(win==NULL)
{Logout("SDL窗口创建失败");return -1;}
Logout("SDL窗口创建成功");
SDL_GetWindowSize(win,&S_w,&S_h);
S_x=(double)S_w/W_w;
S_y=(double)S_h/W_h;
ren=SDL_CreateRenderer(win, -1,
SDL_RENDERER_ACCELERATED
|SDL_RENDERER_PRESENTVSYNC
|SDL_RENDERER_TARGETTEXTURE
);
if(ren==NULL)
{
Logout(SDL_GetError());	
Logout("创建Renderer失败");
SDL_Surface*ws= SDL_GetWindowSurface(win);
SDL_FillRect(ws, NULL, SDL_MapRGB(ws->format, 0xFF, 0x00, 0x00));
SDL_UpdateWindowSurface(win);
    SDL_Delay(3000);
Quit();
	return -3;
}
Logout("创建Renderer成功");

if(SDL_SetRenderDrawBlendMode(ren,SDL_BLENDMODE_BLEND)!=0)
{Logout(SDL_GetError());
Logout("设置渲染器矢量绘图BLEND模式失败");return -4;}
//SDL_SetHint(SDL_HINT_RENDER_DRIVER,"opengl");
if(SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")!=SDL_TRUE)
{Logout(SDL_GetError());
Logout("设置渲染器坑钜齿失败");return -5;
}
//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,1);
FPS_thread=SDL_CreateThread(thread_fps,"fps_Thread",(void*)NULL);
if(FPS_thread==NULL)
{Logout("创建fps线程失败");return -6;}
//event_thread=SDL_CreateThread(eventstate,"eventstate",(void*)NULL);
return 0;
}


		
int  ttf_Init(int size)//字库加载
{
if(TTF_Init()!=0)
{
Logout(SDL_GetError());	
Logout("TTF文字引擎初始化失败");
return -1;
}
Logout("TTF文字引擎初始化成功");

TXT_font=TTF_OpenFont("/storage/sdcard0/Android/DroidSansFallback.ttf",size);
if(TXT_font==NULL)
{
Logout("未找到/storage/sdcard0/Android/DroidSansFallback.ttf");	TXT_font=TTF_OpenFont("/storage/sdcard1/DroidSansFallback.ttf",size);
}
if(TXT_font==NULL)
{
Logout("未找到/storage/sdcard1/DroidSansFallback.ttf");	TXT_font=TTF_OpenFont("/mnt/sdcard/DroidSansFallback.ttf",size);
}
if(TXT_font==NULL)
{
Logout("未找到/mnt/sdcard/DroidSansFallback.ttf");	TXT_font=TTF_OpenFont("/system/fonts/DroidSansFallback.ttf",size);
}
if(TXT_font==NULL)
{
Logout("未找到/system/fonts/DroidSansFallback.ttf");	TXT_font=TTF_OpenFont("/system/fonts/DroidSansChinese.ttf",size);
}
if(TXT_font==NULL)
{
Logout("未找到/system/fonts/DroidSansChinese.ttf");	TXT_font=TTF_OpenFont("/system/fonts/NotoSansHans-Regular.otf",size);
}
if(TXT_font==NULL)
{	Logout("未找到/system/fonts/NotoSansHans-Regular.otf");	TXT_font=TTF_OpenFont("/system/fonts/Miui-Regular.ttf",size);
}
//搜索
/*
	unsigned long long blocksize ;	//每个block里包含的字节数
	unsigned long long totalsize;
			if(access("/storage/sdcard0/",0)!=-1)
	{
statfs("/storage/sdcard0/", &diskInfo);//获取目录信息
blocksize = diskInfo.f_bsize;	//每个block里包含的字节数
 totalsize = blocksize * diskInfo.f_blocks; 	//总的字节数，f_blocks为block的数目
	mem_inf.mem0=diskInfo.f_bsize* diskInfo.f_blocks; 
	mem_inf.memfree0=diskInfo.f_bfree * blocksize;
	*/
if(TXT_font==NULL)
{
Logout("未找到/system/fonts/Miui-Regular.ttf");	SDL_SetRenderDrawColor(ren,255,0,0,255);
	SDL_RenderClear(ren);
	SDL_RenderPresent(ren);
	SDL_Delay(3000);
	return -2;
}

Logout("字体加载成功");
TXT_size=size*132.0/100;
//TTF_SetFontStyle(fontz,6);
// TTF_SetFontOutline(fontz,1);
//TTF_SetFontKerning(TXT_font,0);
//TTF_SetFontKerning(fontz,0);
return 0;
	}	

	
	
	
int mixInit(int i)
{
Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,4096); 
Mix_AllocateChannels (i); 
return 0;
} 


    
    
int quitAudio()
{
	Mix_CloseAudio(); 
	return 0;
}

 /*
 Mix_CloseAudio(); //关闭音乐播放器
Mix_VolumeMusic(audio_volume); //设置音量
Mix_FreeMusic(music); //关闭打开音频文件
Mix_ResumeMusic();
Mix_PausedMusic();
Mix_PlayingMusic();
分配多个音轨(Channels);
Mix_AllocateChannels ();
Mix_PlayChannel();
 Mix_FreeChunk( scratch ); 
 Mix_PlayChannel( -1, scratch, 0 ) 
  Mix_PlayChannelTimed( -1, scratch, 0,tickets )   
*/
  
    


//***********************

SDL_Surface*loadSurface(SDL_Rect rect ,const char*str)
{
	//rect为截取尺寸
SDL_Surface*s2=SDL_CreateRGBSurface(SDL_SWSURFACE,rect.w,rect.h,32,0xFF000000,0X00FF0000,0x0000FF00,0x000000FF);
	SDL_Rect size;
	SDL_Surface*sur=IMG_Load(str);
	size.x=0;
	size.y=0;
	size.w=sur->w;
	size.h=sur->h;
	SDL_BlitSurface(sur,&rect,s2,NULL);
		SDL_FreeSurface(sur);
	
	return s2;
}

SDL_Texture*loadTexture(SDL_Rect rect ,const char*str)
{

	//rect为截取尺寸
SDL_Surface*s2=SDL_CreateRGBSurface(SDL_SWSURFACE,rect.w,rect.h,32,0xFF000000,0X00FF0000,0x0000FF00,0x000000FF);
	SDL_Rect size;
	SDL_Surface*sur=IMG_Load(str);
	size.x=0;
	size.y=0;
	size.w=sur->w;
	size.h=sur->h;

	SDL_BlitSurface(sur,&rect,s2,NULL);
		SDL_FreeSurface(sur);
	SDL_Texture*tex=SDL_CreateTextureFromSurface(ren,s2);
//	SDL_FreeSurface(sur);
	SDL_FreeSurface(s2);
	return tex;
}



//***********************

int txtTexture(char*str,unsigned long int  a)//文字Text图层
{
//
int i=0;

for(;i<TXT_max;i++)
{
if(!strcmp(str,TXT_strtemp[i])&&a==TXT_color[i])//如果文字相同
{TXT_id++;return i;}
}
//如果没有相同的字符串


SDL_Color color = {(Uint8)(a % 16777216 / 65536), (Uint8)(a % 65536 / 256),
				   (Uint8)(a % 256)};

SDL_Surface *txt = TTF_RenderUTF8_Blended(TXT_font, str, color);

SDL_DestroyTexture(TXT_texture[TXT_id]);
TXT_texture[TXT_id]=SDL_CreateTextureFromSurface(ren,txt);
strflush(TXT_strtemp[TXT_id]);
strcpy(TXT_strtemp[TXT_id],str);
TXT_color[TXT_id] = a;
SDL_FreeSurface(txt);

TXT_id++;
return TXT_id-1;
	}
	
	//*********************

	
	

//***********************	
//***矢量绘制函数

int drawLine(SDL_Rect rect)//画线
{	SDL_RenderDrawLine(ren,rect.x,rect.y,rect.w,rect.h);
return 0;
}

//****************
	int drawFillRect(SDL_Rect rect)//画填充式的矩形
	{
	SDL_RenderFillRect(ren,&rect);
	return 0;
}
		//***********************
int drawRect(SDL_Rect rect)//画矩形
{	SDL_RenderDrawRect(ren,&rect);
return 0;
}
	
	//*********************
	


int drawTriangle(Triangle tria)//画三角形
{
int i,max=0,min=0,mid=0;
if(tria.triay[0]>tria.triay[1]){
	if(tria.triay[0]>tria.triay[2]){
		max=0;
		if(tria.triay[1]>tria.triay[2])min=2;
		 else min=1;}
		 else {max=2; min=1;}//i求最大值 k最小值
	}else{
		if(tria.triay[1]<tria.triay[2])max=2,min=0;
		else {
		max=1;
		if(tria.triay[0]<tria.triay[2])min=0;
		else min=2;
		}
		}
	if((max==0&&min==1)||(max==1&&min==0))mid=2;
		else if((max==0&&min==2)||(max==2&&min==0))mid=1;
		else if((max==1&&min==2)||(max==2&&min==1))mid=0;
//132
for(i=tria.triay[min];i<tria.triay[max];i++)
{
if(i<tria.triay[mid])	SDL_RenderDrawLine(ren,tria.triax[min]+(double)(tria.triax[max]-tria.triax[min])/(tria.triay[max]-tria.triay[min])*(i-tria.triay[min]),i,tria.triax[min]+(double)(tria.triax[mid]-tria.triax[min])/(tria.triay[mid]-tria.triay[min])*(i-tria.triay[min]),i);else
SDL_RenderDrawLine(ren,tria.triax[min]+(double)(tria.triax[max]-tria.triax[min])/(tria.triay[max]-tria.triay[min])*(i-tria.triay[min]),i,tria.triax[mid]+(double)(tria.triax[max]-tria.triax[mid])/(tria.triay[max]-tria.triay[mid])*(i-tria.triay[mid]),i);
}
//a+(b-a)/(c-d)*(e-d)
//a+(be-ae-bd+ad)/(c-d)
return 0;

}
	
	
	//***********************

 int drawCircle(int x,int y,float r,float R,float a,float b)//画圆
//画圆
{float i,j,u,v,e=0,c,d;
	x*=S_x;y*=S_y;
		r*=sqrt(S_x*S_y);
	R*=sqrt(S_x*S_y);
if(a>b){c=a;a=b;b=c;}
if(r>R){c=r;r=R;R=c;}
//glLineWidth(2.0);
for(;r<R;r+=1)
{
e=0;
c=i=r*cos(a/180*3.14159);
d=j=r*sin(a/180*3.14159);
while(e<=b-a)
{
u=i*cos(e/180*3.14159)-j*sin(e/180*3.14159);
v=j*cos(e/180*3.14159)+i*sin(e/180*3.14159);
SDL_RenderDrawLine(ren,u+x,y-v,c+x,y-d);
c=u;d=v;
e+=1.0;
}
}
return 0;
}
//***********************

int drawPolygon(int x,int y,int l,int rr,int R,int o,int b,double r)//多边形
{
	x*=S_x;y*=S_y;
	rr*=sqrt(S_x*S_y);
	R*=sqrt(S_x*S_y);
int out[1000][2]={0};
int i=0;
double e=360.0/l;
//glLineWidth(2.0);
if(R>rr){i=R;R=rr;rr=i;}i=0;
for(;R<rr;R++)
{
for(i=0;i<l;i++)
{out[i*2][0]=(int)(R*cos(3.14159/180*(e*i+o)));
out[i*2][1]=(int)(R*sin(3.14159/180*(e*i+o)));
out[i*2+1][0]=(int)(r*cos(3.14159/180*(e*i)+3.14159/180*b));
out[i*2+1][1]=(int)(r*sin(3.14159/180*(e*i)+3.14159/180*b));
}
for(i=0;i<2*l-1;i++)
{
SDL_RenderDrawLine(ren,out[i][0]+x,out[i][1]+y,out[i+1][0]+x,out[i+1][1]+y);
}
SDL_RenderDrawLine(ren,out[2*l-1][0]+x,out[2*l-1][1]+y,out[0][0]+x,out[0][1]+y);
r+=r/R;
}
return 0;
}





//***********************
//纹理处理

//***********************
//拼接两个Surface


SDL_Surface*catSurface(SDL_Surface*s1,SDL_Surface*s2,int x,int y)
{SDL_Rect rect,pos1,pos2;
SDL_Surface*sur;
int w,h;
rect.x=0;
rect.y=0;
if(x<0)
{
 if(s1->w<=-x+s2->w)//相交并覆盖
w=-x+s2->w;
	else w=-x+s1->w;
	pos1.x=0;
	pos2.x=-x;
}
else 
{
	if(x+s1->w<=s2->w)//s1在s2内
	w=s2->w;
	else w=x+s1->w;
	pos1.x=x;
	pos2.x=0;
	
	}
	if(y<0)
{
 if(s1->h<=-y+s2->h)//相交并覆盖
	h=-y+s2->h;
	else h=-y+s1->h;
	pos1.y=0;
	pos2.y=-y;
}
else 
{
	if(y+s1->h<=s2->h)//s2在s2内
	h=s2->h;
	else h=y+s1->h;
		pos1.y=y;
	pos2.y=0;
	}
sur=SDL_CreateRGBSurface(SDL_SWSURFACE,w,h,32,0xFF000000,0X00FF0000,0x0000FF00,0x000000FF);
rect.w=s2->w;
rect.h=s2->h;
SDL_BlitSurface(s2,&rect,sur,&pos2);rect.w=s1->w;
rect.h=s1->h;
SDL_BlitSurface(s1,&rect,sur,&pos1);
return sur;
}

//*********


int displaySurface(SDL_Rect pos,SDL_Surface*sur,double angel)
 {
 	SDL_Rect rect;
 	SDL_Point p;
 	p.x=pos.w/2;
 	p.y=pos.h/2;
 	rect.x=0,rect.y=0;
 	rect.w=sur->w,rect.h=sur->h;
 	SDL_Texture*tex=SDL_CreateTextureFromSurface(ren,sur);
SDL_RenderCopyEx(ren,tex,&rect,&pos,angel,&p,SDL_FLIP_NONE);
SDL_DestroyTexture(tex);
//SDL_FreeSurface(sur);
return 0;
 	}
  	//***********************
  
int displayTexture(SDL_Rect pos,SDL_Texture*tex,double angel)
{
	//	SDL_Texture*tex;
	SDL_Rect rect;
 	SDL_Point p;
 	p.x=pos.w/2;
 	p.y=pos.h/2; SDL_QueryTexture(tex,NULL,NULL,&rect.x,&rect.y);
	//查询Texture
 rect.w=rect.x;rect.h=rect.y;
 rect.x=rect.y=0;
SDL_RenderCopyEx(ren,tex,&rect,&pos,angel,&p,SDL_FLIP_NONE);
//SDL_DestroyTexture(tex);
return 0;
 	}
 	//***********************

int displayTxt(SDL_Rect pos,char*str,unsigned long int a,double angel)
 {
     SDL_Rect rect;
 	SDL_Point p;
 	p.x=pos.w/2;
 	p.y=pos.h/2;
 	rect.x=0,rect.y=0;
 	int i=txtTexture(str,a); SDL_QueryTexture(TXT_texture[i],NULL,NULL,&rect.w,&rect.h);
 
	//查询Texture

SDL_RenderCopyEx(ren,TXT_texture[i],&rect,&pos,angel,&p,SDL_FLIP_NONE);
return 0;
 	}
 	

 int displayText(SDL_Rect rect,char*str,unsigned long int a,double angel)
//显示不变形的文本
{
	int w,h;
	SDL_Color color={(Uint8)(a%16777216/65536),(Uint8)(a%65536/256),(Uint8)(a%256),50};
	int i;
	rect.w=0;
//TTF_SizeUTF8(fontz,str,&rect.w,&rect.h);
TTF_SizeUTF8(TXT_font,str,&w,&h);
rect.w=w*rect.h/TXT_size;
rect.h=h*rect.h/TXT_size;
displayTxt(rect,str,a,angel);
return 0;
}
		
	
	//********************
int loopTexture(SDL_Rect rect,SDL_Texture**tex,int n,int time)
//闪烁的指针
{	
//Loop_n超出检测
if((SDL_GetTicks()/time)%2!=LOOP_a[LOOP_id])
{LOOP_n[LOOP_id]++;}
displayTexture(rect,tex[LOOP_n[LOOP_id]%n],0);
LOOP_a[LOOP_id]=(SDL_GetTicks()/time)%2;
LOOP_id++;
return 0;
}
	

//**************
SDL_Surface* discolor(SDL_Surface*sur)
{	
SDL_Surface *s=SDL_CreateRGBSurface(SDL_SWSURFACE,sur->w,sur->h,32,0xFF000000,0X00FF0000,0x0000FF00,0x000000FF); 
Uint32*p=(Uint32*)sur->pixels;
Uint32*ss=(Uint32*)s->pixels;
int i=0,j=0;
for(i=0;i<sur->w*sur->h;i++)
{	j=(p[i]/16777216*299+(p[i]%16777216)/65536*587+(p[i]%65536)/256*114)/1000;
ss[i]=j*16777216+j*65536+j*256+j;
} 

	return s;
} 


//***************

 

int INF_box()
{
			INF_pos.y=S_h*INF_site;	
			INF_pos.h=S_h*0.04;
	if(strlen(INF_str)>0)
	{	
	int j=0;

TTF_SizeUTF8(TXT_font,INF_str,&j,NULL);
j=j*INF_pos.h/TXT_size;
INF_pos.w=j;
INF_pos.x=(S_w-j)/2;	displayText(INF_pos,INF_str,0xff0000,0);//默认红色
}
	if(SDL_GetTicks()-INF_start>INF_time)
	strcpy(INF_str,"");
		return 0;
}


 		int reFlush(unsigned long int a)
	{	
	SDL_GetWindowSize(win,&S_w,&S_h);
S_x=(double)S_w/W_w;
S_y=(double)S_h/W_h;	 
	INF_box();//底部迅息框
	if(state)
	laststate=state;
	lastfingernum=SDL_GetNumTouchFingers(device);
     state=0;
     Button_id=0;
	TXT_max=TXT_id;
	TXT_id=0;
	 Button_id=0;
	TXTBOX_id=0;
	INP_id=0;
	LIST_id=0;
	LOOP_id=0;
	SDL_RenderPresent(ren);
SDL_SetRenderDrawColor(ren,a/16777216,(a%16777216)/65536,(a%65536)/256,a%256);
SDL_RenderClear(ren);
FPS_fps++;
return 0;
		}
		
		
 //***********************	

		
		
 //***********************	

int Button(SDL_Rect rect,unsigned long int a,char*str,unsigned long int c,int size,int align)
{
int w=0,i;
if(a)
{
SDL_SetRenderDrawColor(ren,a/16777216,(a%16777216)/65536,(a%65536)/256,a%256);
drawFillRect(rect);
}

rect.y+=(float)rect.h*(100-size)*0.005;
rect.h=(float)rect.h*size*0.01;

//size为按钮文字高度百分比
TTF_SizeUTF8(TXT_font,str,&w,NULL);
w=w*rect.h/TXT_size;
i=rect.x;
if(align==0)//居中对齐
rect.x+=(rect.w-w)/2;
else
if(align<0);//左对齐
else //右对齐
rect.x=rect.x+rect.w-w;
displayText(rect,str,c,0);//显示文字
rect.x=i;
if(state==FINGERDOWN)//如果按了按钮
{
if(Ex>rect.x&&Ex<(rect.x+rect.w)&&Ey>rect.y&&Ey<(rect.y+rect.h))
{//如果在按钮区
//初始化数据
	Button_time=0;
Button_flag=1;
Button_Temp_id=0;
Button_rect=rect;
//按下时id设为静态
Button_Static_id=Button_id;
Button_time=SDL_GetTicks();
}
}
else
if(Button_flag==1&&state!=FINGERUP)
{//如果一直长按中
	if(Button_rect.x==rect.x&&
Button_rect.y==rect.y&&
Button_rect.h==rect.h&&
Button_rect.w==rect.w)
{//如果是当前Button
if(Ex>rect.x&&Ex<(rect.x+rect.w)&&Ey>rect.y&&Ey<(rect.y+
rect.h))//如果在按钮区
{
if(Button_Static_id>=Button_Temp_id)
//如果static大于等于当前图层id
if(SDL_GetTicks()-Button_time>Button_longtime)
{state=0;return 2;}
}
else//移出按钮区
{
Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
return 0;
}
}
else//如果不在按钮图层中(可能在重叠按钮上)
{	if(Ex>rect.x&&Ex<(rect.x+rect.w)&&Ey>rect.y&&Ey<(rect.y+
rect.h))//Button_rect改变但还在按钮上
{
if(Button_Static_id<=Button_Temp_id)
{//如果移到了上面的图层按钮
	Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
Button_Static_id=0;
Button_Temp_id=0;
return 0;
}
//保存滑动时当前id
Button_Temp_id=Button_id;
}
}
}
else
if(state==FINGERUP&&Button_flag==1)
{//如果抬起按钮
	if(Button_rect.x==rect.x&&
Button_rect.y==rect.y&&
Button_rect.h==rect.h&&
Button_rect.w==rect.w)	if(Ex>Button_rect.x&&Ex<(Button_rect.x+Button_rect.w)&&Ey>Button_rect.y&&Ey<(Button_rect.y+Button_rect.h))
{
	if(SDL_GetTicks()-Button_time<=Button_longtime)
{
Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
Button_Static_id=0;
Button_Temp_id=0;
return 1;
}
else
{
Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
Button_Static_id=0;
Button_Temp_id=0;
return 3;
}
}
}
Button_id++;
return 0;
}

 //***********************	

int imgButton(SDL_Rect rect,SDL_Texture*tex,char*str,unsigned long int c,int size,int align)
{
int w,h;
SDL_Rect r;
SDL_QueryTexture(tex,NULL,NULL,&w,&h);
r.x=0;r.y=0;
r.w=w;r.h=h;
SDL_RenderCopy(ren,tex,&r,&rect);
w=h=0;

TTF_SizeUTF8(TXT_font,str,&w,NULL);
w=w*rect.h/TXT_size;
rect.y+=(float)rect.h*(100-size)*0.005;
rect.h=(float)rect.h*size*0.01;

//size为按钮文字高度百分比
TTF_SizeUTF8(TXT_font,str,&w,NULL);
w=w*rect.h/TXT_size;
h=rect.x;
if(align==0)//居中对齐
rect.x+=(rect.w-w)/2;
else
if(align<0);//左对齐
else //右对齐
rect.x=rect.x+rect.w-w;
displayText(rect,str,c,0);//显示文字
rect.x=h;
h=0;



if(state==FINGERDOWN)//如果按了按钮
{
if(Ex>rect.x&&Ex<(rect.x+rect.w)&&Ey>rect.y&&Ey<(rect.y+rect.h))
{//如果在按钮区
//初始化数据
	Button_time=0;
Button_flag=1;
Button_Temp_id=0;
Button_rect=rect;
//按下时id设为静态
Button_Static_id=Button_id;
Button_time=SDL_GetTicks();
}
}
else
if(Button_flag==1&&state!=FINGERUP)
{//如果一直长按中
	if(Button_rect.x==rect.x&&
Button_rect.y==rect.y&&
Button_rect.h==rect.h&&
Button_rect.w==rect.w)
{//如果是当前Button
if(Ex>rect.x&&Ex<(rect.x+rect.w)&&Ey>rect.y&&Ey<(rect.y+
rect.h))//如果在按钮区
{
if(Button_Static_id>=Button_Temp_id)
//如果static大于等于当前图层id
if(SDL_GetTicks()-Button_time>Button_longtime)
{state=0;return 2;}
}
else//移出按钮区
{
Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
return 0;
}
}
else//如果不在按钮图层中(可能在重叠按钮上)
{	if(Ex>rect.x&&Ex<(rect.x+rect.w)&&Ey>rect.y&&Ey<(rect.y+
rect.h))//Button_rect改变但还在按钮上
{
if(Button_Static_id<=Button_Temp_id)
{//如果移到了上面的图层按钮
	Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
Button_Static_id=0;
Button_Temp_id=0;
return 0;
}
//保存滑动时当前id
Button_Temp_id=Button_id;
}
}
}
else
if(state==FINGERUP&&Button_flag==1)
{//如果抬起按钮
	if(Button_rect.x==rect.x&&
Button_rect.y==rect.y&&
Button_rect.h==rect.h&&
Button_rect.w==rect.w)	if(Ex>Button_rect.x&&Ex<(Button_rect.x+Button_rect.w)&&Ey>Button_rect.y&&Ey<(Button_rect.y+Button_rect.h))
{
	if(SDL_GetTicks()-Button_time<=Button_longtime)
{
Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
Button_Static_id=0;
Button_Temp_id=0;
return 1;
}
else
{
Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
Button_Static_id=0;
Button_Temp_id=0;
return 3;
}
}
}
Button_id++;
return 0;
}//imgbutton



int circleButton(SDL_Texture*tex,int x,int y ,int r,char*str,unsigned long int c)
{
int w,h;
x*=S_x;y*=S_y;
r*=sqrt(S_x*S_y);
SDL_Rect pos;
pos.x=x-r;pos.y=y-r;
pos.w=pos.h=2*r;
//SDL_QueryTexture(tex,NULL,NULL,&w,&h);

//SDL_RenderCopy(ren,tex,&rect,&pos);
displayTexture(pos,tex,0);
w=h=0;

TTF_SizeUTF8(TXT_font,str,&w,NULL);
w=w*pos.h/TXT_size;

pos.x+=(pos.w-w)/2;
displayText(pos,str,c,0);//显示文字
//rect.x-=(rect.w-w)/2;

if(state==FINGERDOWN)//如果按了按钮
{
if(sqrt((Ex-x)*(Ex-x)+(Ey-y)*(Ey-y))<=r)
{//如果在按钮区
//初始化数据
	Button_time=0;
Button_flag=1;
Button_Temp_id=0;
Button_rect.x=x;
Button_rect.y=y;
Button_rect.w=r;
//Button_rect=rect;
//按下时id设为静态
Button_Static_id=Button_id;
Button_time=SDL_GetTicks();
}
}
else
if(Button_flag==1&&state!=FINGERUP)
{//如果一直长按中
if(Button_rect.x==x&&
Button_rect.y==y&&
Button_rect.w==r)
{//如果是当前Button
if(sqrt((Ex-x)*(Ex-x)+(Ey-y)*(Ey-y))<=r)//如果在按钮区
{
if(Button_Static_id>=Button_Temp_id)
//如果static大于等于当前图层id
if(SDL_GetTicks()-Button_time>Button_longtime)
{state=0;return 2;}
}
else//移出按钮区
{
Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
return 0;
}
}
else//如果不在按钮图层中(可能在重叠按钮上)p
{	if(sqrt((Ex-x)*(Ex-x)+(Ey-y)*(Ey-y))<=r)//Button_rect改变但还在按钮上
{
if(Button_Static_id<=Button_Temp_id)
{//如果移到了上面的图层按钮
	Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
Button_Static_id=0;
Button_Temp_id=0;
return 0;
}
//保存滑动时当前id
Button_Temp_id=Button_id;
}
}
}
else
if(state==FINGERUP&&Button_flag==1)
{//如果抬起按钮
	if(Button_rect.x==x&&
Button_rect.y==y&&
Button_rect.w==r)	if(sqrt((Ex-Button_rect.x)*(Ex-Button_rect.x)+(Ey-Button_rect.y)*(Ey-Button_rect.y))<=Button_rect.w)
{
	if(SDL_GetTicks()-Button_time<=400)
{
Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
Button_Static_id=0;
Button_Temp_id=0;
return 1;
}
else
{
Button_time=0;
Button_flag=0;
Button_rect=(SDL_Rect){0};
Button_Static_id=0;
Button_Temp_id=0;
return 3;
}
}
}
Button_id++;
return 0;
}

int triangleButton(Triangle tria,unsigned long int a)
{
int w=0,i,max=0,mid=0,min=0;
if(a)
{
SDL_SetRenderDrawColor(ren,a/16777216,(a%16777216)/65536,(a%65536)/256,a%256);

if(tria.triay[0]>tria.triay[1]){
	if(tria.triay[0]>tria.triay[2]){
		max=0;
		if(tria.triay[1]>tria.triay[2])min=2;
		 else min=1;}
		 else {max=2; min=1;}//i求最大值 k最小值
	}else{
		if(tria.triay[1]<tria.triay[2])max=2,min=0;
		else {
		max=1;
		if(tria.triay[0]<tria.triay[2])min=0;
		else min=2;
		}
		}
	if((max==0&&min==1)||(max==1&&min==0))mid=2;
		else if((max==0&&min==2)||(max==2&&min==0))mid=1;
		else if((max==1&&min==2)||(max==2&&min==1))mid=0;
//132
for(i=tria.triay[min];i<tria.triay[max];i++)
{
if(i<tria.triay[mid])	SDL_RenderDrawLine(ren,tria.triax[min]+(double)(tria.triax[max]-tria.triax[min])/(tria.triay[max]-tria.triay[min])*(i-tria.triay[min]),i,tria.triax[min]+(double)(tria.triax[mid]-tria.triax[min])/(tria.triay[mid]-tria.triay[min])*(i-tria.triay[min]),i);else
SDL_RenderDrawLine(ren,tria.triax[min]+(double)(tria.triax[max]-tria.triax[min])/(tria.triay[max]-tria.triay[min])*(i-tria.triay[min]),i,tria.triax[mid]+(double)(tria.triax[max]-tria.triax[mid])/(tria.triay[max]-tria.triay[mid])*(i-tria.triay[mid]),i);
}
//a+(b-a)/(c-d)*(e-d)
//a+(be-ae-bd+ad)/(c-d)
}

if(state==FINGERDOWN)//如果按了按钮
{	if((int)round(angel(tria.triax[0],tria.triay[0],Ex,Ey,tria.triax[1],tria.triay[1])+angel(tria.triax[2],tria.triay[2],Ex,Ey,tria.triax[1],tria.triay[1])+angel(tria.triax[0],tria.triay[0],Ex,Ey,tria.triax[2],tria.triay[2]))==360)//如果在按钮区
{
//初始化数据
	Button_time=0;
Button_flag=1;
Button_Temp_id=0;
Button_tria.triax[0]=tria.triax[0];
Button_tria.triay[0]=tria.triay[0];
Button_tria.triax[1]=tria.triax[1];
Button_tria.triay[1]=tria.triay[1];
Button_tria.triax[2]=tria.triax[2];
Button_tria.triay[2]=tria.triay[2];
//按下时id设为静态
Button_Static_id=Button_id;
Button_time=SDL_GetTicks();
}
}
else
if(Button_flag==1&&state!=FINGERUP)
{//如果一直长按中
	if(Button_tria.triax[0]==tria.triax[0]&&
Button_tria.triay[0]==tria.triay[0]&&
Button_tria.triax[1]==tria.triax[1]&&
Button_tria.triay[1]==tria.triay[1]&&
Button_tria.triax[2]==tria.triax[2]&&
Button_tria.triay[2]==tria.triay[2]
)//Button区域的检测
{//如果是当前Button
if((int)round(angel(tria.triax[0],tria.triay[0],Ex,Ey,tria.triax[1],tria.triay[1])+angel(tria.triax[2],tria.triay[2],Ex,Ey,tria.triax[1],tria.triay[1])+angel(tria.triax[0],tria.triay[0],Ex,Ey,tria.triax[2],tria.triay[2]))==360)//如果在按钮区
{
if(Button_Static_id>=Button_Temp_id)
//如果static大于等于当前图层id
if(SDL_GetTicks()-Button_time>Button_longtime)
{state=0;return 2;}
}
else//移出按钮区
{
Button_time=0;
Button_flag=0;
Button_tria.triax[0]=0;
Button_tria.triay[0]=0;
Button_tria.triax[1]=0;
Button_tria.triay[1]=0;
Button_tria.triax[2]=0;
Button_tria.triay[2]=0;
return 0;
}
}
else//如果不在按钮图层中(可能在重叠按钮上)
{	if((int)round(angel(tria.triax[0],tria.triay[0],Ex,Ey,tria.triax[1],tria.triay[1])+angel(tria.triax[2],tria.triay[2],Ex,Ey,tria.triax[1],tria.triay[1])+angel(tria.triax[0],tria.triay[0],Ex,Ey,tria.triax[2],tria.triay[2]))==360)//Button_rect改变但还在按钮上
{
if(Button_Static_id<=Button_Temp_id)
{//如果移到了上面的图层按钮
	Button_time=0;
Button_flag=0;
Button_tria.triax[0]=0;
Button_tria.triay[0]=0;
Button_tria.triax[1]=0;
Button_tria.triay[1]=0;
Button_tria.triax[2]=0;
Button_tria.triay[2]=0;
Button_Static_id=0;
Button_Temp_id=0;
return 0;
}
//保存滑动时当前id
Button_Temp_id=Button_id;
}
}
}
else
if(state==FINGERUP&&Button_flag==1)
{//如果抬起按钮
	if(Button_tria.triax[0]==tria.triax[0]&&
Button_tria.triay[0]==tria.triay[0]&&
Button_tria.triax[1]==tria.triax[1]&&
Button_tria.triay[1]==tria.triay[1]&&
Button_tria.triax[2]==tria.triax[2]&&
Button_tria.triay[2]==tria.triay[2]
)//如果是当前Button区域
if((int)round(angel(tria.triax[0],tria.triay[0],Ex,Ey,tria.triax[1],tria.triay[1])+angel(tria.triax[2],tria.triay[2],Ex,Ey,tria.triax[1],tria.triay[1])+angel(tria.triax[0],tria.triay[0],Ex,Ey,tria.triax[2],tria.triay[2]))==360)
{	if(SDL_GetTicks()-Button_time<=Button_longtime)
{
Button_time=0;
Button_flag=0;
Button_tria.triax[0]=0;
Button_tria.triay[0]=0;
Button_tria.triax[1]=0;
Button_tria.triay[1]=0;
Button_tria.triax[2]=0;
Button_tria.triay[2]=0;
Button_Static_id=0;
Button_Temp_id=0;
return 1;
}
else
{
Button_time=0;
Button_flag=0;
Button_tria.triax[0]=0;
Button_tria.triay[0]=0;
Button_tria.triax[1]=0;
Button_tria.triay[1]=0;
Button_tria.triax[2]=0;
Button_tria.triay[2]=0;
Button_Static_id=0;
Button_Temp_id=0;
return 3;
}
}
}
Button_id++;
return 0;
}



int slideBar(SDL_Rect rect,unsigned long int a,double* z)
{
SDL_Rect pos;
pos=rect;
SDL_SetRenderDrawColor(ren,a/16777216,(a%16777216)/65536,(a%65536)/256,a%256);
drawFillRect(rect);
pos.x+=rect.w*(*z);
pos.y-=S_h*0.01;
pos.h+=S_h*0.02;
pos.w=S_w*0.03;
SDL_SetRenderDrawColor(ren,0,0,255,255);
rect.y=pos.y;
rect.h=pos.h;
drawFillRect(pos);
if(state==FINGERDOWN)
SLIDEBAR_state=1;
//else if(state==FINGERUP)SLIDEBAR_state=0;
if(state==FINGERMOTION&&SLIDEBAR_state)
{	if(Ey>=rect.y&&Ey<=rect.y+rect.h)
{
if(Ex>=rect.x&&Ex<=rect.x+rect.w)
{//如果在滑杆内
*z=(double)(Ex-rect.x)/rect.w;
}else if(Ex<rect.x)*z=0;
else * z=1;
}
//else SLIDEBAR_state=0;
}
	return 0;
}

int pointer(SDL_Rect rect,unsigned long int a,double*f)
{	SDL_SetRenderDrawColor(ren,a/16777216,(a%16777216)/65536,(a%65536)/256,a%256);	SDL_RenderDrawRect(ren,&rect);
	rect.w=rect.w*(*f);	SDL_SetRenderDrawColor(ren,a/16777216,(a%16777216)/65536,(a%65536)/256,a%256);
	drawFillRect(rect);
	return 0;
}

int selectBox(SDL_Rect rect,unsigned long int a,int *i)
{
	SDL_Rect pos=rect;
SDL_SetRenderDrawColor(ren,a/16777216,(a%16777216)/65536,(a%65536)/256,a%256);
drawFillRect(rect);
SDL_SetRenderDrawColor(ren,255,255,255,255);
rect.x+=rect.w/4;
rect.y+=rect.h/4;
rect.w/=2;
rect.h/=2;
drawFillRect(rect);
if(*i!=0)
{
rect.x+=rect.w/4;
rect.y+=rect.h/4;
rect.w/=2;
rect.h/=2;	SDL_SetRenderDrawColor(ren,a/16777216,(a%16777216)/65536,(a%65536)/256,a%256);
drawFillRect(rect);
}
if(state==FINGERDOWN)
{	if(Ex>=pos.x&&Ex<=pos.x+pos.w)	if(Ey>=pos.y&&Ey<=pos.y+pos.h)
*i=!(*i);
	}

return 0;
}

int glint(SDL_Rect rect,int time)//闪烁的指针
{	
if((SDL_GetTicks()/time)%2==0)	{SDL_SetRenderDrawColor(ren,255,0,0,255);
drawFillRect(rect);}
return 0;
}

int txtBox(SDL_Rect rect,char*str,unsigned long int a,int h)
{
	char*stt;
	h=h*S_y;
		int i,j=0,k=0,s=0;
		SDL_Rect pos;
		pos.x=rect.x;
		pos.y=rect.y;
		pos.w=0;
		pos.h=h;
for(i=0;i<strlen(str);i++)
{
	stt=strtoa(str,s,i);
TTF_SizeUTF8(TXT_font,stt,&j,NULL);
j=j*h/TXT_size;
free(stt);
if(str[i]==10)
{char* text=strtoa(str,s,i-1);
		displayText(pos,text,a,0);
		free(text);
s=i+1;
j-=pos.w;
pos.y+=h*1;//行距
}
pos.w=j;
if(str[i+1]<128||str[i+1]>191){
if(j>rect.w)
{
	char*cha=strtoa(str,s,i);
displayText(pos,cha,a,0);
s=i+1;
j-=pos.w;
pos.y+=h*1;//行距
}
}
}
char* cha=strtoa(str,s,i);
displayText(pos,cha,a,0);
free(cha);
return 0;
}



int listView(SDL_Rect rect,unsigned long int a,LIST li,
char*title,unsigned long int c,int size,int align)
{
	SDL_Rect pos=rect;
	int i,j=0;
SDL_SetRenderDrawColor(ren,a/16777216,(a%16777216)/65536,(a%65536)/256,a%256);
drawFillRect(rect);
displayText(rect,title,c,0);
for(i=1;i<=li.n;i++)
{	SDL_SetRenderDrawColor(ren,0,0,0,255);
pos.y=rect.y+2+(rect.h+2)*i;
if(Button(pos,a,li.str[i-1],c,size,align))
j=i;
}
		return j;
}

//slidelist
int slideList(SDL_Rect rect,unsigned long int a,LIST li,int h,int size,int align)
{
h*=S_y;
	rect.y-=h,rect.h+=h;
SDL_Rect pos=rect;
	int i,j=rect.y,k=-1;
	
if(state==FINGERMOTION)//如果滑动
{
if(Ex>rect.x&&Ex<rect.x+rect.w)
if(Ey>rect.y+h&&Ey<rect.y+rect.h)
{
if(event.tfinger.dy>0)
{LIST_inertia[LIST_id]=event.tfinger.dy*S_h;
	if(LIST_h[LIST_id]>0)	   
     LIST_h[LIST_id]-=LIST_inertia[LIST_id];
	else 	if(LIST_n[LIST_id]>0)
		LIST_h[LIST_id]=h,
		LIST_n[LIST_id]--;
}
else 
if(event.tfinger.dy<0)
{LIST_inertia[LIST_id]=event.tfinger.dy*S_h;
		if(LIST_h[LIST_id]<h)
		LIST_h[LIST_id]-=LIST_inertia[LIST_id];	
	else if(LIST_n[LIST_id]<li.n-rect.h/h)
		LIST_h[LIST_id]=0,
		LIST_n[LIST_id]++;
}}
}


if(LIST_inertia[LIST_id]>0)
{
		if(LIST_h[LIST_id]>0)	   
     LIST_h[LIST_id]-=LIST_inertia[LIST_id];
	else 	if(LIST_n[LIST_id]>0)
		LIST_h[LIST_id]=h,
		LIST_n[LIST_id]--;
		LIST_inertia[LIST_id]--;
}
else
if(LIST_inertia[LIST_id]<0)
{
	if(LIST_h[LIST_id]<h)
		LIST_h[LIST_id]-=LIST_inertia[LIST_id];	
	else if(LIST_n[LIST_id]<li.n-rect.h/h)
		LIST_h[LIST_id]=0,
		LIST_n[LIST_id]++;
		LIST_inertia[LIST_id]++;
}

if(state==FINGERUP&&laststate==FINGERMOTION)
{state=0;}
if(LIST_h[LIST_id]<0)LIST_h[LIST_id]=0;
if(LIST_h[LIST_id]>h)LIST_h[LIST_id]=h;
for(i=LIST_n[LIST_id];i<LIST_n[LIST_id]+(rect.h/h);i++)
{
pos.h=(h-1);
pos.y=j+(h-LIST_h[LIST_id]);
if(Button(pos,a,li.str[i],0xffffff,size,align))
k=i+1;
	j+=h;
}
rect.y-=h;
LIST_id++;
return k;
}



int slideText(SDL_Rect rect,unsigned long int b,char*str,unsigned long int a,int h)
{
	h=h*S_y;
		int i=0,j=0,k=0,s;
		SDL_Rect pos;
		pos=rect;
	pos.h=h;
	char*st;
if(b)
{
SDL_SetRenderDrawColor(ren,b/16777216,(b%16777216)/65536,(b%65536)/256,b%256);
drawFillRect(rect);
}	
		
if(state==FINGERMOTION)
		{	if(Ex>rect.x&&Ex<rect.x+rect.w&&Ey>rect.y&&Ey<rect.y+rect.h)
	{	if(event.tfinger.dy>0&&!(TXTBOX_i[TXTBOX_id]==0&&TXTBOX_fu[TXTBOX_id]>=0))
			{
	TXTBOX_slide[TXTBOX_id]=event.tfinger.dy*S_h;
			}
			else if (event.tfinger.dy<0&&!TXTBOX_flag[TXTBOX_id])
		{	TXTBOX_slide[TXTBOX_id]=event.tfinger.dy*S_h;
		}
		
//TXTBOX_rect=rect;		
	}
		}//fingermotion
		if(state==FINGERDOWN)
		TXTBOX_slide[TXTBOX_id]=0;
		
if(TXTBOX_slide[TXTBOX_id]>0)
{
	TXTBOX_slide[TXTBOX_id]--;
	TXTBOX_fu[TXTBOX_id]+=TXTBOX_slide[TXTBOX_id];
}
if (TXTBOX_slide[TXTBOX_id] < 0) {
	TXTBOX_slide[TXTBOX_id]++;
	TXTBOX_fu[TXTBOX_id]+=TXTBOX_slide[TXTBOX_id];
}




if(TXTBOX_fu[TXTBOX_id]>0)//下滑
{
	if(TXTBOX_i[TXTBOX_id]>0)
i=--TXTBOX_i[TXTBOX_id];
if(TXTBOX_i[TXTBOX_id]==0)
TXTBOX_fu[TXTBOX_id]=0;
else
TXTBOX_fu[TXTBOX_id]=-h;
j=0;

for(;TXTBOX_i[TXTBOX_id]>0;TXTBOX_i[TXTBOX_id]--)
{
	st=strtoa(str,TXTBOX_i[TXTBOX_id],i);	TTF_SizeUTF8(TXT_font,st,&j,&k);
	free(st);
j=j*h/TXT_size;
if(str[TXTBOX_i[TXTBOX_id]]==10)
{
	//TXTBOX_i
//break;
}
if(j>rect.w){
	TXTBOX_i[TXTBOX_id]++;	while(str[TXTBOX_i[TXTBOX_id]]>127&&str[TXTBOX_i[TXTBOX_id]]
<192)TXTBOX_i[TXTBOX_id]++;
	i++;
	while(str[i]>127&&str[i]
<192)i++;
	st=strtoa(str,TXTBOX_i[TXTBOX_id],i);	TTF_SizeUTF8(TXT_font,st,&j,&k);
	free(st);
j=j*h/TXT_size;
if(j<rect.w)
{
	TXTBOX_i[TXTBOX_id]--;
	while (str[TXTBOX_i[TXTBOX_id]] > 127 && str[TXTBOX_i[TXTBOX_id]] < 192)
		TXTBOX_i[TXTBOX_id]--;
	break;
}

break;}
}
}
else if(TXTBOX_fu[TXTBOX_id]<-h)//上滑
{
	i=TXTBOX_i[TXTBOX_id];
	j=0;	for(;TXTBOX_i[TXTBOX_id]<strlen(str);TXTBOX_i[TXTBOX_id]++)
	{
st=strtoa(str,i,TXTBOX_i[TXTBOX_id]);
TTF_SizeUTF8(TXT_font,st,&j,&k);
free(st);
j=j*h/TXT_size;
if(str[TXTBOX_i[TXTBOX_id]]==10)
{
	TXTBOX_i[TXTBOX_id]++;
break;
}

if(j>rect.w){
	//TXTBOX_i++;
	break;}
	}
TXTBOX_fu[TXTBOX_id]=0;
}


pos.y+=TXTBOX_fu[TXTBOX_id];	
j=0;

s=TXTBOX_i[TXTBOX_id];
	
//	pos.h=0;

for(i=TXTBOX_i[TXTBOX_id];i<strlen(str);i++)
{//扫描并显示
	st=strtoa(str,s,i);
	TTF_SizeUTF8(TXT_font, st, &j, &k);
	j = j * h / TXT_size;
	free(st);
	if (str[i] == 10) {
		st = strtoa(str, s, i - 1);
		displayText(pos, st, a, 0);
		free(st);
		s = i + 1;
		j -= pos.w;
		j = 0;
		pos.y += h * 1; //行距
		if (pos.y - rect.y > rect.h)
			break;
}


pos.w=j;

if(str[i]<128||str[i]>191)
{
if(j>rect.w)//如果超出了行宽
{
	st=strtoa(str,s,i-1);
displayText(pos,st,a,0);
free(st);
s=i;
//j-=pos.w;
j=0;
pos.y+=h*1;//行距
if(pos.y-rect.y>rect.h)
break;
}

}
}//for

if(pos.y-rect.y<rect.h-h)
{
	TXTBOX_flag[TXTBOX_id]=1;
	TXTBOX_slide[TXTBOX_id]=0;
}
else {TXTBOX_flag[TXTBOX_id]=0;}
	st=strtoa(str,s,i-1);
displayText(pos,st,a,0);
free(st);
if(b)
{
s=rect.h;
rect.h=h;
rect.y-=h;
drawFillRect(rect);
rect.y+=s+h;
drawFillRect(rect);
}
TXTBOX_id++;

return 0;
}



int inputBox(SDL_Rect rect,char*str,unsigned long int a)
{
int i=0;
int p=0;
int pp=0;
int finger_flag=0;
int k;
char*stt;
SDL_Rect pos;

//获取字符串总长
TTF_SizeUTF8(TXT_font,str,&p,NULL);
p=p*rect.h/TXT_size;


if(state==FINGERUP)//按下
{
if(Ex>rect.x&&Ex<rect.x+rect.w&&Ey>rect.y&&Ey<rect.y+rect.h)
{//如果在输入框
	INP_x=rect.x;
INP_y=rect.y;
INP_k[INP_id]=1;
if(INP_kb)
  SDL_StartTextInput();
  else
  SDL_StopTextInput();
if(strlen(str)>0)
{
if(p>rect.w)//如果光标定位时，字幅大于框幅
i=INP_al[INP_id];
else 
i=0;

k=i;
	for(;i<strlen(str);i++)
{
stt=strtoa(str,k,i);
TTF_SizeUTF8(TXT_font,stt,&pp,NULL);
	free(stt);
pp=pp*rect.h/TXT_size;	if((double)(pp+rect.x)>=Ex)//光标插入
{//i++;
	while(str[i]>127&&str[i]<192)i--;
  break;
    }
}
INP_n[INP_id]=i;//保存了光标字符串所在下标
}
else {
	//INP_site=rect.x;
INP_n[INP_id]=0;
}

}

}//按下事件



 if(INP_x==rect.x&&INP_y==rect.y)
//如果是当前输入框
{
	
if(state==FINGERMOTION)
	{
		if(p>rect.w)
		{
if(Ex>rect.x&&Ex<(rect.x+rect.w)&&Ey>rect.y&&Ey<(rect.y+
rect.h))
{
if(event.tfinger.dx>0)
{
	if(INP_al[INP_id]>=0&&INP_site[INP_id]<rect.x+rect.w)//右滑
{
	if(INP_al[INP_id]==0&&INP_fu[INP_id]>0)
	{
		INP_fu[INP_id]=0;
	}
	else
	INP_fu[INP_id]+=event.tfinger.dx*S_w;
if(str[INP_al[INP_id]]<128)
{
if(INP_fu[INP_id]>rect.h*TXT_w&&INP_al[INP_id]>0)
{
INP_al[INP_id]--;
	while(str[INP_al[INP_id]]>127&&str[INP_al[INP_id]]<192)INP_al[INP_id]--;
	INP_fu[INP_id]-=rect.h*TXT_w;
	}
}
else
{
if(INP_fu[INP_id]>rect.h*TXT_w&&INP_al[INP_id]>1)
{

INP_al[INP_id]--;
	
while(str[INP_al[INP_id]]>127&&str[INP_al[INP_id]]<192)INP_al[INP_id]--;	
	INP_fu[INP_id]-=rect.h*TXT_w*TXT_dw;}
}
}
	
}
if(event.tfinger.dx<0)//左滑
finger_flag=1;
}
}//可以滑动
	}//滑动事件
		
	else
if(state==TEXTINPUT)//输入状态
{
char *strp=event.text.text;

TTF_SizeUTF8(TXT_font,strp,&pp,NULL);

pp=pp*rect.h/TXT_size;
//p+=pp;

if(INP_n[INP_id]!=strlen(str))//如果是插入而非末尾
{
//	if(p>rect.w)
	{
if(INP_site[INP_id]<rect.x+rect.w-pp)//文字输出不超边框
{
INP_site[INP_id]+=pp;
//if(p>rect.w)
char*cha=strin(str,INP_n[INP_id],strp);
strcpy(str,cha);
free(cha);
INP_n[INP_id]+=strlen(strp);
}
else //超出，//且在边框尾
{
//INP_site-=pp;
INP_al[INP_id]+=strlen(strp);
char*cha=strin(str,INP_n[INP_id],strp);
strcpy(str,cha);
free(cha);
INP_n[INP_id]+=strlen(strp);
if(str[INP_al[INP_id]]>127)
{while(str[INP_al[INP_id]]>127&&str[INP_al[INP_id]]<
192)INP_al[INP_id]++;
//INP_n++;
}

}

}
}

else//是末尾
{
char*cha=strin(str,INP_n[INP_id],strp);
strcpy(str,cha);free(cha);
INP_n[INP_id]+=strlen(strp);
}


}//如果是输入

else
if(state==KEYUP)//有按键9
{
if(event.key.keysym.sym==SDLK_RETURN)
{    
INP_x=INP_y=-1;
INP_k[INP_id]=0;
	SDL_StopTextInput();
}

else
if(event.key.keysym.sym==SDLK_BACKSPACE)//如果退格键
{
if(strlen(str)>0&&INP_n[INP_id]>0)
{
if(str[INP_n[INP_id]-1]<128)//如果是英文
{
	char*cha=strde(str,INP_n[INP_id]-1,INP_n[INP_id]);
strcpy(str,cha);
free(cha);
INP_n[INP_id]--;
if(INP_al[INP_id]>0)
{
	INP_al[INP_id]--;
 if(str[INP_al[INP_id]]>127)
{while(str[INP_al[INP_id]]>127&&str[INP_al[INP_id]]<192)INP_al[INP_id]--;INP_n[INP_id]--;
}
}


}
else if((str[INP_n[INP_id]-1]>127&&str[INP_n[INP_id]-1]<192)||INP_n[INP_id]==strlen(str))//如果是中文
{
i=INP_n[INP_id];
do
i--;
while(str[i]>127&&str[i]<
192);
char*cha=strde(str,i,INP_n[INP_id]);
strcpy(str,cha);
free(cha);
if(INP_al[INP_id]>0)
{
INP_al[INP_id]-=INP_n[INP_id]-i;
if(str[INP_al[INP_id]]>127)
while(str[INP_al[INP_id]]>127&&str[INP_al[INP_id]]<
192)
{INP_al[INP_id]--;INP_n[INP_id]--;}
INP_n[INP_id]-=INP_n[INP_id]-i;
}
else
{
INP_n[INP_id]-=INP_n[INP_id]-i;
}

}//else if chinese
}

}//backspace
}//有按键


//rect.x+=fu;

//计算INP_al
if(p>rect.w)//如果长度大于矩形宽度
{
if(INP_n[INP_id]==strlen(str))//如果光标在末尾
{
	pp=0;
for(i=0;pp<(p-(rect.w));i++)
{
			stt=strtoa(str,0,i);
TTF_SizeUTF8(TXT_font,stt,&pp,NULL);
	free(stt);
pp=pp*rect.h/TXT_size;		
}
while(str[i]>127&&str[i]<192)i++;
INP_al[INP_id]=i;
}
}
else		
 INP_al[INP_id]=0;
pp=0;
 if(p>rect.w)//计算i值
{
if(INP_n[INP_id]==strlen(str))
  i=strlen(str);
	else//插入状态
	{	for(i=INP_al[INP_id];pp<rect.w-rect.h*TXT_w&&i<strlen(str);i++)
	{
		stt=strtoa(str,INP_al[INP_id],i);
TTF_SizeUTF8(TXT_font,stt,&pp,NULL);
	free(stt);
pp=pp*rect.h/TXT_size;	

	}
	while(str[i]>127&&str[i]<192&&i<strlen(str))i++;
i--;
}
}
else i=strlen(str);
if(i<strlen(str)&&INP_site[INP_id]>rect.x&&finger_flag)//响应左滑动事件
{
	INP_fu[INP_id]+=event.tfinger.dx*S_w;
	if(str[INP_al[INP_id]]<128)
{
if(INP_fu[INP_id]<-rect.h*TXT_w)
{INP_al[INP_id]++;INP_fu[INP_id]+=rect.h*TXT_w;}
}
else
{
if(INP_fu[INP_id]<-rect.h*TXT_w)
{
	i=INP_al[INP_id]+1;
	while(str[i]>127&&str[i]<
192)i++;
	INP_al[INP_id]+=i-INP_al[INP_id];
	INP_fu[INP_id]+=rect.h*TXT_w;
}
}	
	
	
}

//Copy INP_str字符串
if(INP_al[INP_id]<0)INP_al[INP_id]=0;
strflush(INP_str[INP_id]);
stt=strtoa(str,INP_al[INP_id],i);
strcpy(INP_str[INP_id],stt);
free(stt);


pp=0;
for(i=INP_al[INP_id];i<INP_n[INP_id];i++)
{
	stt=strtoa(str,INP_al[INP_id],i);
TTF_SizeUTF8(TXT_font,stt,&pp,NULL);
	free(stt);
pp=pp*rect.h/TXT_size;		
}
INP_site[INP_id]=rect.x+pp;
//光标位置

}//如果是当前
else INP_k[INP_id]=0;

	if(INP_k[INP_id]>0)//光标开关
{
	pos.x=INP_site[INP_id];
	pos.y=rect.y;
	pos.w=2;
	pos.h=rect.h;
	glint(pos,500);
	}
displayText(rect,INP_str[INP_id],a,0);
INP_id++;

	return 0;
}


//多行文本输入框
int slideInput(SDL_Rect rect,unsigned long int b,char*str,unsigned long int a,int h)
{
	h=h*S_y;
int i=0,j=0,s=0;
	int inpy=0;
char st[1000];
SDL_Rect pos=(SDL_Rect){0,0,0,0}; 
SDL_Rect temp=(SDL_Rect){0,0,0,0}; 
if(state==FINGERUP)//如果按下
{
TXTBOX_slide[TXTBOX_id]=0;
if(Ex>rect.x&&Ex<rect.x+rect.w&&Ey>rect.y&&Ey<rect.y+rect.h)
{
	INP_x=rect.x;
	INP_y=rect.y;
if(INP_kb)
  SDL_StartTextInput();
  else
  SDL_StopTextInput();
INP_k[INP_id]=1;//开启光标
//寻找字符下标
inpy=0;
s=TXTBOX_i[TXTBOX_id];


for(i=TXTBOX_i[TXTBOX_id];i<strlen(str);i++)
{//扫描并显示
char*cha=strtoa(str,s,i);
strcpy(st,cha);
free(cha);
TTF_SizeUTF8(TXT_font,st,&j,NULL);
j=j*h/TXT_size;
//free(st);

if(Ey-h-TXTBOX_fu[TXTBOX_id]<inpy+rect.y)
{

if(Ex<j+rect.x)
{
INP_n[INP_id]=i;//+TXTBOX_i[TXTBOX_id];
//if(Ex<rect.x+h/2)ab--;
 break;
}


}


if(str[i]==10)
{
char*cha=strtoa(str,s,i);
strcpy(st,cha);
free(cha);
TTF_SizeUTF8(TXT_font,st,&j,NULL);
j=j*h/TXT_size;

if(Ey-h-TXTBOX_fu[TXTBOX_id]<inpy+rect.y)
{

if(Ex>j+rect.x)
{
INP_n[INP_id]=i;
	break;
}
}


s=i+1;
j=0;
inpy+=h;

}
//pos.w=j;

if(str[i]<128||str[i]>191)
{

	
	
if(j>rect.w)//如果超出了行宽
{

s=i;
j=0;
inpy+=h;
if(pos.y-rect.y>rect.h)break;
}
}


}//for

if(i==strlen(str))
INP_n[INP_id]=strlen(str);

}
else {INP_k[INP_id]=0;//关闭光标
//SDL_StopTextInput();
}

}//如果是fingerDOWN



 if(INP_x==rect.x&&INP_y==rect.y)
//如果是当前输入框
{
if(state==TEXTINPUT)//输入状态
{
char *strp=event.text.text;
char*cha=strin(str,INP_n[INP_id],strp);
strcpy(str,cha);
free(cha);
INP_n[INP_id]+=strlen(strp);

}//输入，定位光标
if(state==KEYUP)//有按键9
{
if(event.key.keysym.sym==SDLK_RETURN)
{
char*cha=strin(str,INP_n[INP_id],"\n");
strcpy(str,cha);
free(cha);
INP_n[INP_id]++;
}
else
if(event.key.keysym.sym==SDLK_BACKSPACE)//如果退格键
{


if(str[INP_n[INP_id]-1]<128)//如果是英文
{
	char*cha=strde(str,INP_n[INP_id]-1,INP_n[INP_id]);
strcpy(str,cha);
free(cha);
INP_n[INP_id]--;

}
else if((str[INP_n[INP_id]-1]>127&&str[INP_n[INP_id]-1]<192))//如果是中文或其他
{
i=INP_n[INP_id];
do
i--;
while(str[i]>127&&str[i]<
192&&i>0);
char*cha=strde(str,i,INP_n[INP_id]);
strcpy(str,cha);
free(cha);
INP_n[INP_id]=i;

}//else if chinese
}


}

}//如果是当前输入框



//实时更新光标位置
s=TXTBOX_i[TXTBOX_id];
inpy=0;


for(i=TXTBOX_i[TXTBOX_id];i>=0&&i<INP_n[INP_id];i++)
{

if(str[i]==10)
{

s=i+1;
j=0;
inpy+=h*1;//行距
//if(pos.y-rect.y>rect.h)break;
}
//pos.w=j;
if(str[i]<128||str[i]>191)
{
	char*cha=strtoa(str,s,i);
strcpy(st,cha);
free(cha);
TTF_SizeUTF8(TXT_font,st,&j,NULL);
j=j*h/TXT_size;	

if(j>rect.w)//如果超出了行宽
{

s=i;
j=0;
inpy+=h*1;//行距
char*cha=strtoa(str,s,i);
strcpy(st,cha);
free(cha);
TTF_SizeUTF8(TXT_font,st,&j,NULL);
j=j*h/TXT_size;	


}
}
}

if(i>=0)
INP_n[INP_id]=i;//+TXTBOX_i[TXTBOX_id];

INP_site[INP_id]=j+rect.x;

slideText(rect,b,str,a,h/S_y);



if(INP_k[INP_id]>0)//光标开关
{
pos.x=INP_site[INP_id];
pos.y=rect.y+inpy+TXTBOX_fu[TXTBOX_id-1];
pos.w=2;
pos.h=h;
if(pos.y+h>rect.y&&pos.y<rect.y+rect.h)
if(pos.x>=rect.x&&pos.x<rect.x+rect.w)
glint(pos,500);
}
INP_id++;

return 0;
}


/*

int logo(int time)
{
int i=0;	SDL_Texture*text=IMG_LoadTexture(ren,"xiaoyuer.png");

	for(i=0;i<time;i++)
{
	
	reflush(0xffffffff);
displayTexture(site(250,400,200,100),text,0);

SDL_Delay(50);

displayText(site(310,500,0,60),"小鱼儿",0x0,0);

SDL_SetRenderDrawColor(ren,255,255,255,255-i*5);
FillRect(site(250,400,300,200));


}	
}
*/
/*int main()
{
	
			
	
	}*/
