////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.8.6
// SpsShow 0.8.6 演示脚本
// Sicily 零与一的幻想 预览版
//
// Author: Ken.J
// Date: 2013-06-07
////////////////////////////////////////////////////////////////////////////

// 起始标记
@tag{ name:"主菜单" }

// 初始化
@track{name:"音效" volume:soundVolume}
@track{name:"背景音乐" volume:musicVolume}

////////////////////////////////////////////////////////////////////////////

// 设置主菜单
@screen{ name:"主菜单"}

@component{
	name:"标题"
	width:1000
	height:300
	x:0
	y:50
	transparency:0
	background_image:"data/images/logo_sicily_02.png"
	background_color:0x00FFFFFF
	layer:2
}

@component{
	name:"copyright"
	width:256
	height:20
	x:287
	y:700
	transparency:0
	background_image:"data/images/copyright.png"
	background_color:0x00FFFFFF
	on_click:[ @execute{file:"http://www.sprabbit.com"} ]
	layer:2
}

@component{
	name:"转盘"
	layer:4
	width:700
	height:700
	rotation_center_x:1280
	rotation_center_y:720
	x:930
	y:370
	rotation:0
	transparency:0
	background_image:"data/images/round_menu.png"
}

// 设置按钮初始位置
@component{
	name:"按钮1"
	width:350
	height:80
	x:-150
	transparency:0
	y:280
	layer:3
	background_y:0
	background_image:"data/images/button_restart.png"
	background_color:0x00FFFFFF
	on_mouse:[ 
		@component{name:"按钮1" background_y:-80} 
		@animation{ component:"转盘" transparency:1 rotation:0 time:0.3 add_mode:"Merge"} 
		@animation{ component:"按钮1下划线" x:0 time:0.3 add_mode:"Merge"} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"按钮1" background_y:0} 		
		@animation{ component:"转盘" transparency:0 time:0.3} 
		@animation{ component:"按钮1下划线" x:-500 time:0.3 add_mode:"Merge"} 		
	]
	on_click:[ 
		@track{ name:"音效" src:"data/sounds/confirm.wav" loop:0 control:"Play" }
		@include{file:"script/main_menu_out.ks"} 
		@include{file:"script/sicily_init.ks"}
		// 跳转到主要内容
		@goTo{ file:"script/sicily_01.ks" }
	]
}

@component{
	name:"按钮1下划线"
	width:500
	height:20
	x:-500
	y:340
	layer:2
	background_image:"data/images/menu_button_line.png"	
	background_color:0x00FFFFFF
}

PI = 3.1415926;

@component{
	name:"按钮2"
	width:350
	height:80
	x:-120
	transparency:0
	y:360
	layer:3
	background_y:0
	background_image:"data/images/button_continue.png"
	background_color:0x00FFFFFF
	on_mouse:[ 
		@component{name:"按钮2" background_y:-80} 
		@animation{ component:"转盘" transparency:1 rotation: -PI / 2 time:0.3 add_mode:"Merge"} 
		@animation{ component:"按钮2下划线" x:0 time:0.3 add_mode:"Merge"} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"按钮2" background_y:0} 
		@animation{ component:"转盘" transparency:0 time:0.3} 
		@animation{ component:"按钮2下划线" x:-500 time:0.3 add_mode:"Merge"} 
	]
	on_click:[ 
		@track{ name:"音效" src:"data/sounds/confirm.wav" loop:0 control:"Play" }
		@include{file:"script/main_menu_out.ks"} 
		@include{file:"script/sicily_init.ks"}
		@loadGameData{ file:"data/savedata/qsave.sav" } 
	]
}

@component{
	name:"按钮2下划线"
	width:500
	height:20
	x:-500
	y:420
	layer:2
	background_image:"data/images/menu_button_line.png"	
	background_color:0x00FFFFFF
}

@component{
	name:"按钮3"
	width:350
	height:80
	x:-120
	transparency:0
	y:440
	layer:3
	background_y:0
	background_image:"data/images/button_configure.png"
	background_color:0x00FFFFFF
	on_mouse:[ 
		@component{name:"按钮3" background_y:-80} 
		@animation{ component:"转盘" transparency:1 rotation: -PI time:0.3 add_mode:"Merge"} 
		@animation{ component:"按钮3下划线" x:0 time:0.3 add_mode:"Merge"} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"按钮3" background_y:0} 
		@animation{ component:"转盘" transparency:0 time:0.3}
		@animation{ component:"按钮3下划线" x:-500 time:0.3 add_mode:"Merge"}
	]
	on_click:[ 
		@track{ name:"音效" src:"data/sounds/confirm.wav" loop:0 control:"Play" }
		@include{file:"script/main_menu_out.ks"} 
		@include{file:"script/sicily_config_on.ks"}
		//@execute{file:"http://www.sprabbit.com/spengine/tutorial.html"}
	]
}

@component{
	name:"按钮3下划线"
	width:500
	height:20
	x:-500
	y:500
	layer:2
	background_image:"data/images/menu_button_line.png"	
	background_color:0x00FFFFFF
}

@component{
	name:"按钮4"
	width:350
	height:80
	x:-100
	transparency:0
	y:520
	layer:3
	background_y:0
	background_image:"data/images/button_shutdown.png"
	background_color:0x00FFFFFF
	on_mouse:[ 
		@component{name:"按钮4" background_y:-80} 
		@animation{ component:"转盘" transparency:1 rotation: PI / 2 time:0.3 add_mode:"Merge"}
		@animation{ component:"按钮4下划线" x:0 time:0.3 add_mode:"Merge"} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[
		@component{name:"按钮4" background_y:0} 
		@animation{ component:"转盘" transparency:0 time:0.3} 
		@animation{ component:"按钮4下划线" x:-500 time:0.3 add_mode:"Merge"}
	]
	on_click:[
		@track{ name:"音效" src:"data/sounds/confirm.wav" loop:0 control:"Play" }
		@include{file:"script/main_menu_out.ks"} 
		@exit; 
	]
}

@component{
	name:"按钮4下划线"
	width:500
	height:20
	x:-500
	y:580
	layer:2
	background_image:"data/images/menu_button_line.png"	
	background_color:0x00FFFFFF
}
