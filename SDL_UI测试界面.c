#include <SDL2/SDL.h>
#include <../../SDL_UI.h>
int txttest();
int buttontest();
int test2d();
int victortest();
int soundtest();
int screentest();
int main()
{
	//定义
	char abc[1000]="";
	int i,j;
int a=0;
    //图片texture图层
	SDL_Texture*tcircle=NULL;
	SDL_Texture*timgbutton=NULL;
    //列表结构体
	LIST li;
	//保存输入框文字
	char str[2][100]={""};
	//多行文字
	char poem[500]={"    水调歌头\n            --苏轼\n明月几时有？\n把酒问青天。\n不知天上宫阙，\n今夕是何年。\n我欲乘风归去，\n又恐琼楼玉宇，\n高处不胜寒。\n起舞弄清影，\n何似在人间？\n转朱阁，\n低绮户，\n照无眠。\n不应有恨，\n何事长向别时圆？\n人有悲欢离合，\n月有阴晴圆缺，\n此事古难全。\n但愿人长久，\n千里共婵娟。"};
	//选框键值
     int selectbox_n=0;
     //滑杆值
     double slidebar_x=0.36;
//初始化创建窗口.

 init("窗口标题",2080,1020);
ttf_init(80);//加载系统字库
//加载图片资源
tcircle=IMG_LoadTexture(ren,"circlebutton.png");
timgbutton=IMG_LoadTexture(ren,"imgbutton.png");
//列表结构体赋值
li.n=50;
for(i=0;i<50;i++)
sprintf(li.str[i],"%d",i);

//主循环
while(1)
{	

eventstate();


TTF_SetFontOutline(TXT_font,2);
displaytext(site(170,10,0,50),"SDL_UI V3.0测试界面",0x0,0);//显示标题8
TTF_SetFontOutline(TXT_font,0);
/*if(circlebutton(tcircle,50,100,40,"",0x0))//显示圆形按钮
quit();*/
i=button(site(120,70,120,70),0xaaaaaa,"按钮",0x0,100,0);//显示普通按钮
if(i==1)
{sprintf(INF_str,"矩形按钮按下");
INF_start=SDL_GetTicks();
//SDL_SetClipboardText("abdygvv");
SDL_Delay(100);
//strcpy(abc,SDL_GetClipboardText());
//SDL_free(abc);
}if(i==2)
{sprintf(INF_str,"矩形按钮长按中");
INF_start=SDL_GetTicks();
}if(i==3)
{sprintf(INF_str,"矩形按钮长按");
INF_start=SDL_GetTicks();
}
i=imgbutton(site(260,70,150,70),timgbutton,"按钮",0x0,100,0);
if(i==1)
{sprintf(INF_str,"图片按钮按下");
INF_start=SDL_GetTicks();
}if(i==2)
{sprintf(INF_str,"图片按钮长按中");
INF_start=SDL_GetTicks();
}if(i==3)
{sprintf(INF_str,"图片按钮长按");
INF_start=SDL_GetTicks();
}


displaytext(site(10,250,0,50),abc,0xff,0);

selectbox(site(450,80,50,50),0xaaaaaa,&selectbox_n);
if(selectbox_n)//创建选框
displaytext(site(520,80,0,50),"开启",0x0,0);else
displaytext(site(520,80,0,50),"关闭",0x0,0);

SDL_SetRenderDrawColor(ren,255,0,0,255);
drawPolygon(650,100,5,10,12,
18,54,30);//画五角星


displaytext(site(1,150,0,40),"圆形按钮   普通按钮   背景按钮        选框        五角星",0x0,0);//单行文本

displaytext(site(10,220,0,40),"帐号:",0x0,0);
displaytext(site(10,300,0,40),"密码:",0x0,0);

displayTexture(site(450,200,150,150),tcircle,a++);

slidetxtbox(site(10,380,250,300),0xffffffff,poem,0x0,40);//滑动文本框


//滑动列表，返回列表的id值
i=slidelist(site(300,430,300,250),0xaaaaaa,li,50,100,0);
SDL_SetRenderDrawColor(ren,0,0,0,255);
//画矩形不填充
drawRect(site(80,220,300,50));
inputbox(site(80,220,300,50),str[0],0xff0000);//输入框
SDL_SetRenderDrawColor(ren,0,0,0,255);
//画矩形不填充
drawRect(site(80,300,300,50));
inputbox(site(80,300,300,50),str[1],0xff0000);//输入框
SDL_SetRenderDrawColor(ren,0,0,0,255);

button(site(300,380,300,50),0xaaaaff,"滑动列表",0x0,100,0);
button(site(300,680,300,50),0xffffffff,"",0x0,100,0);


if(i>0)

{
	sprintf(INF_str,"%d被按下",i-1);
	INF_start=SDL_GetTicks();
}

for(i=0;i<10;i++)
{displaytext(site(20,850,0,100),"SDL_UI测试",(i+1)*255555,a+i);
}

if(button(site(400,730,300,50),0xaaaaff,"文本渲染测试",0x0,100,0))
{reflush(0xffffffff);txttest();}
if(button(site(400,800,300,50),0xaaaaff,"按钮响应测试",0x0,100,0))
{reflush(0xffffffff);buttontest();}
if(button(site(400,870,300,50),0xaaaaff,"2D贴图测试",0x0,100,0))
{reflush(0xffffffff);test2d();}
if(button(site(400,940,300,50),0xaaaaff,"矢量绘图测试",0x0,100,0))
{reflush(0xffffffff);victortest();}
button(site(400,1010,300,50),0xaaaaff,"音效测试",0x0,100,0);

displaytext(site(0,1180,0,50),"屏幕比例:",0,0);
slidebar(site(180,1180,500,30),0xaaaaaa,&slidebar_x);//滑杆
W_w=slidebar_x*2000;
W_h=W_w/0.5625;
txtbox(site(0,0,300,0),FPS_str,0xff0000,30);//显示FPS
reflush(0xffffffff);//显示并刷新

 }
quit();//退出
return 0;
}

int txttest()
{
	char str[10000];
	int i;
	double a=0.5,b=0.5,c=0.5;
int	w=100,h=100,size=10;

	for(i=0;i<10000;i++)
	{
	str[i]=48+i%60;
	}
	while(1)
	{

		eventstate();		
slidetxtbox(site(10,60,w,h),0xffffffff,str,0x0,size);
displaytext(site(0,1060,0,50),"宽度:",0,0);
slidebar(site(120,1060,500,30),0xaaaaaa,&a);//滑杆
w=S_w*a;
displaytext(site(0,1120,0,50),"高度:",0,0);
slidebar(site(120,1120,500,30),0xaaaaaa,&b);//滑杆
h=S_h*b;
displaytext(site(0,1180,0,50),"尺寸:",0,0);
slidebar(site(120,1180,500,30),0xaaaaaa,&c);//滑杆
size=200*c;
if(button(site(0,0,S_w,50),0xaaaaff,"back",0x0,100,0))
return 0;
txtbox(site(0,0,300,0),FPS_str,0xff0000,30);//显示FPS
	reflush(0xffffffff);
		}
	return 0;
}

int buttontest()
{
		int i,j;
	Uint64 n=0;
	double a=0.1,b=0.1;
int	w=1,h=1;
SDL_Texture*timgbutton=IMG_LoadTexture(ren,"imgbutton.png");

	while(1)
	{
		eventstate();		
displaytext(site(0,1120,0,50),"x轴数量:",0,0);
slidebar(site(150,1120,500,30),0xaaaaaa,&a);//滑杆
w=100*a;
displaytext(site(0,1180,0,50),"y轴数量:",0,0);
slidebar(site(150,1180,500,30),0xaaaaaa,&b);//滑杆
h=100*b;

if(button(site(0,0,S_w,50),0xaaaaff,"back",0x0,100,0))
return 0;

for(i=0;i<w;i++)
{
for(j=0;j<h;j++)
if(imgbutton(site((S_w/w)*i,60+j*S_w/w,S_w/w,S_w/w),timgbutton,"",0,100,0))
{
	sprintf(INF_str,"%d被按下",w*j+i);
	INF_start=SDL_GetTicks();
}
}

txtbox(site(0,0,300,0),FPS_str,0xff0000,30);//显示FPS
	reflush(0xffffffff);
		}
	return 0;
	
}
int test2d()
{
	int i,j;
	Uint64 n=0;
	double a=0.1,b=0.1;
int	w=1,h=1;
SDL_Texture*tcircle=IMG_LoadTexture(ren,"circlebutton.png");

	while(1)
	{
		eventstate();		

for(i=0;i<w;i++)
{
	for(j=0;j<h;j++)
displayTexture(site((S_w/w)*i,60+j*S_w/w,S_w/w,S_w/w),tcircle,n++);
}


displaytext(site(0,1120,0,50),"x轴数量:",0,0);
slidebar(site(150,1120,500,30),0xaaaaaa,&a);//滑杆
w=100*a;
displaytext(site(0,1180,0,50),"y轴数量:",0,0);
slidebar(site(150,1180,500,30),0xaaaaaa,&b);//滑杆
h=100*b;

if(button(site(0,0,S_w,50),0xaaaaff,"back",0x0,100,0))
return 0;
txtbox(site(0,0,300,0),FPS_str,0xff0000,30);//显示FPS
	reflush(0xffffffff);
		}
	return 0;
}
int victortest()
{
	
	double a=0.5,b=0.5,c=0.49,d=0.5,e=0.5,f=0.5;
int a1=5,b1=10,c1=12,d1=18,e1=54,f1=30;
	
		while(1)
	{
		eventstate();		
SDL_SetRenderDrawColor(ren,255,0,0,255);


displaytext(site(0,880,0,50),"边数:",0,0);
slidebar(site(120,880,500,30),0xaaaaaa,&a);//滑杆
a1=100*a;
displaytext(site(0,940,0,50),"外径:",0,0);
slidebar(site(120,940,500,30),0xaaaaaa,&b);//滑杆
b1=S_w/2*b;
displaytext(site(0,1000,0,50),"内径:",0,0);
slidebar(site(120,1000,500,30),0xaaaaaa,&c);//滑杆
c1=S_w/2*c;

displaytext(site(0,1060,0,50),"主旋角:",0,0);
slidebar(site(120,1060,500,30),0xaaaaaa,&d);//滑杆
d1=360*d;
displaytext(site(0,1120,0,50),"副旋角:",0,0);
slidebar(site(120,1120,500,30),0xaaaaaa,&e);//滑杆
e1=360*e;
displaytext(site(0,1180,0,50),"张角:",0,0);
slidebar(site(120,1180,500,30),0xaaaaaa,&f);//滑杆
f1=200*f;
drawPolygon(S_w/2,400,a1,b1,c1,d1,e1,f1);
if(button(site(0,0,S_w,50),0xaaaaff,"back",0x0,100,0))
return 0;
txtbox(site(0,0,300,0),FPS_str,0xff0000,30);//显示FPS
	reflush(0xffffffff);
		}
	return 0;
	
}