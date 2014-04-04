////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.8.6
// SpsShow 0.8.6 演示脚本
// Sicily 零与一的幻想 预览版
//
// Author: Ken.J
// Date: 2013-06-07
////////////////////////////////////////////////////////////////////////////

// 起始标记
@tag{ name:"显示主菜单" }

////////////////////////////////////////////////////////////////////////////

// 播放菜单音乐
@track{ 
	name:"背景音乐" 
	src:"data/sounds/bgm01.ogg" 
	loop:-1 control:"Play" 
}

@track{
	name:"音效"
	loop:0
}

// 设置主菜单
@screen{ name:"主菜单"}

// 初始化背景
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


// 背景动画
@animation{
	component:"背景"
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

@animation{
	component:"背景2"
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

@goTo{file:"script/main_menu_in.ks"}
