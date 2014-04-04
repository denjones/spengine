////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.8.6
// SpsShow 0.8.6 演示脚本
// Sicily 零与一的幻想 预览版
//
// Author: Ken.J
// Date: 2013-06-07
////////////////////////////////////////////////////////////////////////////

// 起始标记
@tag{ name:"一般主菜单" }

////////////////////////////////////////////////////////////////////////////

// 初始化背景
@screen{ name:"主菜单"}

@component{
	name:"背景"
	width:1280
	height:720
	x:0
	transparency:0
	y:0
	background_image:"data/images/bg_classroom_02.png"
	layer:0
}

@component{
	name:"背景2"
	width:1280
	height:720
	x:0
	transparency:0
	y:0
	background_image:"data/images/bg_menu.png"
	background_color:0x00888888
	layer:1
}

@include{ file:"script/main_menu_init.ks" }
@goTo{ file:"script/main_menu_on.ks" }
