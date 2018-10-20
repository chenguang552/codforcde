package com.chenguang.demo;

import android.app.*;
import android.hardware.*;
import android.opengl.*;
import android.os.*;
import android.view.*;
import android.widget.*;

public class MainActivity extends Activity 
{
	private GLSurfaceView glsurfaceView;//预览摄像头
  
    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
		
		requestWindowFeature(Window.FEATURE_NO_TITLE);//隐藏标题栏
		getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN
		,WindowManager.LayoutParams.FLAG_FULLSCREEN);//隐藏状态栏
		
        setContentView(R.layout.main);
		
		glsurfaceView=(GLSurfaceView)findViewById(R.id.glSurfaceView);
		CameraController.getInstance().openCamera(glsurfaceView);
    }
}
