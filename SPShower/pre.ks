////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.9
//
// Author: Ken.J
// Date: 2013-10-06
////////////////////////////////////////////////////////////////////////////

// 设置窗口标题
@windowText{ content:"Sicily - 零与一的幻想 序章 (with SpeShow 0.9)" }

// 设置鼠标指针
@cursor{ file:"cursor/3.cur" }

// 注册字体（雅黑）
@registerFont{ file:"font/msyh.ttf" }

// 隐藏帧率
@fps{ position:"RightTop" display:false lock:60}

// 初始化全局变量
@var{
	soundVolume:1
	musicVolume:1
	textSpeed:30
	skipMode:1
}

履历编号 = 0;

// 设置入口脚本
//@first{ file:"script/logo.ks" }
