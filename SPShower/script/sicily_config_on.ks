////////////////////////////////////////////////////////////////////////////
// Demo script of SPEShow Beta 0.82
// SpsShow 0.8.6 演示脚本
// Sicily 零与一的幻想 预览版
//
// Author: Ken.J
// Date: 2013-07-20
////////////////////////////////////////////////////////////////////////////

// 初始化配置组件
@component{name:"声效" width:1000 height:60 x:20 y:10 layer:2 transparency:0 display:"unhidden"}
@component{name:"声效文字" father:"声效"  width:400 height:60 x:0 y:0 background_image:"data/images/tag_sound.png" layer:1}
@component{name:"声效选项" father:"声效"  width:600 height:60 x:400 y:0 layer:1}
onNum = soundVolume * 10 - 1;
for i = 0 to 9 {
	@component{
		name:"声效选项" + i
		father:"声效选项"  
		width:50 
		height:60 
		x:20 + i * 50 
		y:0 
		layer:1
		background_image:"data/images/slider_0" + i + (i <= onNum ? "_on.png":".png")
		on_mouse:' @component{name:"声效选项' + i + '"  background_y:-60} '
		on_mouse_out:' @component{name:"声效选项' + i + '" background_y:0} '
		on_mouse_in:[ @track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" } ]
		on_click:' 	soundVolume = ' + (i + 1) / 10.0 + '; @track{name:"音效" volume:soundVolume}
					for j = 0 to ' + i + ' {
						@component{name:"声效选项" + j  background_image:"data/images/slider_0" + j + "_on.png"}
					}
					
					if (' + i + ' < 9){
						for j = ' + (i + 1) + ' to 9 {
							@component{name:"声效选项" + j  background_image:"data/images/slider_0" + j + ".png"}
						}
					}
				'
	}
}


@component{name:"音乐" width:1000 height:60 x:50 y:40 layer:2 transparency:0 display:"unhidden"}
@component{name:"音乐文字" father:"音乐"  width:400 height:60 x:0 y:0 background_image:"data/images/tag_music.png" layer:1}
@component{name:"音乐选项" father:"音乐"  width:600 height:60 x:400 y:0 layer:1}
onNum = musicVolume * 10 - 1;
for i = 0 to 9 {
	@component{
		name:"音乐选项" + i
		father:"音乐选项"  
		width:50 
		height:60 
		x:20 + i * 50 
		y:0 
		layer:1
		background_image:"data/images/slider_0" + i + (i <= onNum ? "_on.png":".png")
		on_mouse:' @component{name:"音乐选项' + i + '"  background_y:-60} '
		on_mouse_out:' @component{name:"音乐选项' + i + '" background_y:0} '
		on_mouse_in:[ @track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" } ]
		on_click:' 	musicVolume = ' + (i + 1) / 10.0 + '; @track{name:"背景音乐" volume:musicVolume}
					for j = 0 to ' + i + ' {
						@component{name:"音乐选项" + j  background_image:"data/images/slider_0" + j + "_on.png"}
					}
					if (' + i + ' < 9){
						for j = ' + (i + 1) + ' to 9 {
							@component{name:"音乐选项" + j  background_image:"data/images/slider_0" + j + ".png"}
						}
					}
				'
	}
}

@component{name:"文字" width:1000 height:60 x:80 y:70 layer:2 transparency:0 display:"unhidden"}
@component{name:"文字文字" father:"文字"  width:400 height:60 x:0 y:0 background_image:"data/images/tag_speed.png" layer:1}
@component{name:"文字选项" father:"文字"  width:600 height:60 x:400 y:0 layer:1}
onNum = 10 - 100.0 / textSpeed;
for i = 0 to 9 {
	@component{
		name:"文字选项" + i
		father:"文字选项"  
		width:50 
		height:60 
		x:20 + i * 50 
		y:0 
		layer:1
		background_image:"data/images/slider_0" + i + (i <= onNum ? "_on.png":".png")
		on_mouse:' @component{name:"文字选项' + i + '"  background_y:-60} '
		on_mouse_out:' @component{name:"文字选项' + i + '" background_y:0} '
		on_mouse_in:[ @track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" } ]
		on_click:' 	textSpeed = ' + (100.0 / (10 - i)) + ';
					for j = 0 to ' + i + ' {
						@component{name:"文字选项" + j  background_image:"data/images/slider_0" + j + "_on.png"}
					}
					if (' + i + ' < 9){
						for j = ' + (i + 1) + ' to 9 {
							@component{name:"文字选项" + j  background_image:"data/images/slider_0" + j + ".png"}
						}
					}
				'
	}
}

@component{name:"屏幕" width:1000 height:60 x:110 y:100 layer:2 transparency:0 display:"unhidden"}
@component{name:"屏幕文字" father:"屏幕"  width:400 height:60 x:0 y:0 background_image:"data/images/tag_screen.png" layer:1}
@component{name:"屏幕选项" father:"屏幕"  width:600 height:60 x:400 y:0 layer:1}
@component{
	name:"屏幕选项1" 
	father:"屏幕选项" 
	x: 0
	width:300 
	height:60 
	background_image:"data/images/tag_screen_windowed.png"
	on_mouse:[ 
		@component{name:"屏幕选项1" background_y:-60} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"屏幕选项1" background_y:0} 
	]
	on_click:[ 
		@display{fullscreen:false}
	]
}
@component{
	name:"屏幕选项2" 
	father:"屏幕选项" 
	x: 300
	width:300 
	height:60 
	background_image:"data/images/tag_screen_fullscreen.png"
	on_mouse:[ 
		@component{name:"屏幕选项2" background_y:-60} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"屏幕选项2" background_y:0} 
	]
	on_click:[ 
		@display{fullscreen:true}
	]
}

@component{name:"分辨" width:1000 height:60 x:140 y:130 layer:2 transparency:0 display:"unhidden"}
@component{name:"分辨文字" father:"分辨"  width:400 height:60 x:0 y:0 background_image:"data/images/tag_resolution.png" layer:1}
@component{name:"分辨选项" father:"分辨" width:600 height:60 x:400 y:0 layer:1}
@component{
	name:"分辨选项1" 
	father:"分辨选项" 
	x: 0
	width:300 
	height:60 
	background_image:"data/images/tag_resolution_01.png"
	on_mouse:[ 
		@component{name:"分辨选项1" background_y:-60} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"分辨选项1" background_y:0} 
	]
	on_click:[ 
		@display{resolution_width:960 resolution_height:540}
	]
}
@component{
	name:"分辨选项2" 
	father:"分辨选项" 
	x: 300
	width:300 
	height:60 
	background_image:"data/images/tag_resolution_02.png"
	on_mouse:[ 
		@component{name:"分辨选项2" background_y:-60} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"分辨选项2" background_y:0} 
	]
	on_click:[ 
		@display{resolution_width:1280 resolution_height:720}
	]
}

@component{name:"跳过" width:1000 height:60 x:170 y:160 layer:2 transparency:0 display:"unhidden"}
@component{name:"跳过文字" father:"跳过"  width:400 height:60 x:0 y:0 background_image:"data/images/tag_skip.png" layer:1}
@component{name:"跳过选项" father:"跳过"  width:600 height:60 x:400 y:0 layer:1}
@component{
	name:"跳过选项1" 
	father:"跳过选项" 
	x: 0
	width:300 
	height:60 
	background_image: skipMode ? "data/images/tag_skip_all.png" : "data/images/tag_skip_all_on.png"
	on_mouse:[ 
		@component{name:"跳过选项1" background_y:-60} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"跳过选项1" background_y:0} 
	]
	on_click:[ 
		skipMode = 0;
		@component{	name:"跳过选项1" background_image:"data/images/tag_skip_all_on.png"}
		@component{	name:"跳过选项2" background_image:"data/images/tag_skip_read.png"}
	]
}
@component{
	name:"跳过选项2" 
	father:"跳过选项" 
	x: 300
	width:300 
	height:60 
	background_image: skipMode ? "data/images/tag_skip_read_on.png" : "data/images/tag_skip_read.png"
	on_mouse:[ 
		@component{name:"跳过选项2" background_y:-60} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"跳过选项2" background_y:0} 
	]
	on_click:[ 
		skipMode = 1;
		@component{	name:"跳过选项1" background_image:"data/images/tag_skip_all.png"}
		@component{	name:"跳过选项2" background_image:"data/images/tag_skip_read_on.png"}
	]
}

@component{
	name:"返回按钮"
	width:400
	height:60
	x:200
	transparency:1
	display:"unhidden"
	y:190
	layer:2
	background_y:0
	background_image:"data/images/button_return.png"
	background_color:0x00FFFFFF
	on_mouse:[ 
		@component{name:"返回按钮" background_y:-60} 
	]
	on_mouse_in:[
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
	]
	on_mouse_out:[ 
		@component{name:"返回按钮" background_y:0} 
	]
	on_click:[ 
		@track{ name:"音效" src:"data/sounds/confirm.wav" loop:0 control:"Play" }
		@include{file:"script/sicily_config_out.ks"}
		@include{file:"script/main_menu_init.ks"}
		@include{file:"script/main_menu_in.ks"}
	]
}

// 动画
@animation{component:"声效" y:100 time:0.8 transparency:1 replay:"FastIn"}
@animation{component:"音乐" y:180 time:0.7 transparency:1 replay:"FastIn"}
@animation{component:"文字" y:260 time:0.6 transparency:1 replay:"FastIn"}
@animation{component:"屏幕" y:340 time:0.5 transparency:1 replay:"FastIn"}
@animation{component:"分辨" y:420 time:0.4 transparency:1 replay:"FastIn"}
@animation{component:"跳过" y:500 time:0.3 transparency:1 replay:"FastIn"}
@animation{component:"返回按钮" y:580 time:0.2 transparency:1 replay:"FastIn"}
@wait{time:1}
