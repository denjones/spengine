////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.9
// SpsShow 0.9 演示脚本
// Sicily 零与一的幻想 预览版
//
// Author: Ken.J
// Date: 2013-10-07
////////////////////////////////////////////////////////////////////////////

// 设置演示屏幕
@screen{ name:"Sicily剧情" }

// 隐藏粒子系统
@pictureBox{ name:"光点" display:"unhidden" }

// #1 布局背景组件
@component{ name:"背景" width:1280 height:720 layer:10}
@component{ father:"背景" name:"背景后" width:1280 height:720 layer:1}
@component{ father:"背景" name:"背景前" width:1280 height:720 layer:2}

// #2 布局立绘组件
@component{  name:"立绘" width:1280 height:720 layer:20 }
@component{ father:"立绘" name:"立绘前1" width:720 height:720 layer:2 background_image:null}
@component{ father:"立绘" name:"立绘后1" width:720 height:720 layer:1 background_image:null}
@component{ father:"立绘" name:"立绘前2" width:720 height:720 layer:2 x:300 background_image:null}
@component{ father:"立绘" name:"立绘后2" width:720 height:720 layer:1 x:300 background_image:null}
@component{ father:"立绘" name:"立绘前3" width:720 height:720 layer:2 background_image:null}
@component{ father:"立绘" name:"立绘后3" width:720 height:720 layer:1 background_image:null}

// #3 布局对话框组件
@component{ name:"对话框" width:1280 height:180 y:540 layer:30 }
@component{ father:"对话框" name:"对话框背景" width:1220 height:166 layer:0 x:30 y:0 }
@dialogBox{ father:"对话框" name:"对话框文字" width:1120 height:126 layer:1 x:80 y:40 padding:10}
@component{ father:"对话框" name:"对话框角色背景" width:200 height:40 layer:2}
@textBox{ 	father:"对话框" name:"对话框角色" width:200 height:40 layer:3 x:30 padding:5 }

// #4 布局选项框
@component{ name:"选项框" width:500 height:200 x:390 y:200 layer:40 display:"hidden"}
@textBox{ 	father:"选项框" name:"选项1" width:500 height:40 y:0 layer:1 padding:5 }
@textBox{ 	father:"选项框" name:"选项2" width:500 height:40 y:50 layer:1 padding:5 }
@textBox{ 	father:"选项框" name:"选项3" width:500 height:40 y:100 layer:1 padding:5 }

// #5 布局功能按钮
@component{ name:"功能按钮" width:450 height:30 x:871 y:545 layer:50 }
@component{ father:"功能按钮" name:"播放声音按钮" width:26 height:26 layer:4 x:0 y:2 }
@component{ father:"功能按钮" name:"快进按钮" width:26 height:26 layer:4 x:26 y:2 }
@component{ father:"功能按钮" name:"自动按钮" width:26 height:26 layer:4 x:52 y:2 }
@component{ father:"功能按钮" name:"保存按钮" width:40 height:26 layer:4 x:87 y:2 }
@component{ father:"功能按钮" name:"读取按钮" width:40 height:26 layer:4 x:131 y:2 }
@component{ father:"功能按钮" name:"快速保存按钮" width:58 height:26 layer:4 x:177 y:2 }
@component{ father:"功能按钮" name:"快速读取按钮" width:58 height:26 layer:4 x:238 y:2 }
@component{ father:"功能按钮" name:"履历按钮" width:26 height:26 layer:4 x:308 y:2 }
@component{ father:"功能按钮" name:"退出按钮" width:26 height:26 layer:4 x:346 y:2 }

// #6 布局履历
@component{ name:"履历" width:1240 height:680 x:20 y:20 layer:60 display:"hidden"}
@textBox{ 	father:"履历" name:"履历标题" width:200 height:40 padding:5 layer:2}
@list{ 		father:"履历" name:"履历列表" width:1240 height:660 x:20 y:50 layer:1 max_item:20}
@component{ father:"履历" name:"履历背景" width:1240 height:660 layer:0 y:20 }

// #7 布局视频组件
@pictureBox{  name:"视频" width:1280 height:720 layer:70 display:"hidden"}

// #8 布局全屏遮挡组件
@component{  name:"全屏遮挡" width:1280 height:720 layer:254  display:"hidden"}

///////////////////////////////////////////////////////////////////////////////////////

// 填充背景
@component{ name:"背景前" background_image:"data/images/bg_black.png" }
@component{ name:"背景后" background_image:"data/images/bg_black.png" }

///////////////////////////////////////////////////////////////////////////////////////

// 填充对话框
@component{ 
	name:"对话框" 
	background_color:0x00FFFFFF
	on_key_down_LCONTROL:[ 
		@include{ file:"script/sicily_auto_off.ks" }
		@skip{ set_on:true mode:"All" auto_time:0.01 } 
	]
	on_key_up_LCONTROL:[ 
		@include{ file:"script/sicily_auto_off.ks" }
		@skip{ set_on:false mode:"All" auto_time:0.01 } 
	]
	catch_click:[ 
		@next{ box:"对话框文字" } 
	] 
	on_key_down_SPACE:[
		@next{ box:"对话框文字" } 
	]
	catch_rclick:[
		@include{ file:"script/sicily_auto_off.ks" }
		@include{file:"script/sicily_dialog_off.ks"} 
	]
	catch_scroll_up: [
		@include{ file:"script/sicily_auto_off.ks" }
		@include{ file:"script/sicily_dialog_off.ks" }
		@include{ file:"script/sicily_backlog_on.ks" }
	]
}
@font{ name:"文字框字体" font:"微软雅黑" size:30 weight:6 }
@component{ name:"对话框背景" background_image:"data/images/dialog_bg.png" }
@dialogBox{ 
	name:"对话框文字" 
	font:"文字框字体" 
	content:" "
	speed:textSpeed
	background_color:0x00FFFFFF
	next_line_src:"data/images/dialog_next_line.png" 
	next_line_row:2 
	next_line_col:4 
	next_line_fps:14
	next_page_src:"data/images/dialog_next_page.png" 
	next_page_row:2 
	next_page_col:4 
	next_page_fps:14
	text_effect_front:"TextShadow"
	text_effect_front_tex:"data/images/dialog_text.png"
	text_effect_front_level:0
	text_effect_front_quality:0
	text_effect_front_opacity:1
	text_effect_back:"TextShadow"
	text_effect_back_tex:"data/images/dialog_shadow.png"
	text_effect_back_level:2
	text_effect_back_quality:10
	text_effect_back_opacity:2
}
@component{ 
	name:"对话框角色背景" 
	//background_color:0xDD334455  
}
@textBox{ 	
	name:"对话框角色" 
	font:"文字框字体" 
	content:" "
	text_effect_front:"TextStroke"
	text_effect_front_tex:"data/images/dialog_shadow.png"
	text_effect_front_level:2
	text_effect_front_quality:4
	text_effect_front_opacity:1
	text_effect_back:"TextShadow"
	text_effect_back_tex:"data/images/dialog_shadow.png"
	text_effect_back_level:1.5
	text_effect_back_quality:4
	text_effect_back_opacity:0.9
}

///////////////////////////////////////////////////////////////////////////////////////

// 填充功能按钮
@component{ 
	name:"功能按钮"
	background_color:0x00FFFFFF
}

@component{ 
	name:"播放声音按钮" 
	background_y:-26
	background_image:"data/images/dialog_button_sound.png" 
	background_color:0x00FFFFFF
	on_mouse_in:[ 
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
		@component{ name:"播放声音按钮" background_y:0 } 
	]
	on_mouse_out:[ @component{ name:"播放声音按钮" background_y:-26 } ]
}

快进模式开启 = false;
@component{ 
	name:"快进按钮" 
	background_y:-26
	background_image:"data/images/dialog_button_skip.png" 
	background_color:0x00FFFFFF
	on_mouse_in:[ 
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
		@component{ name:"快进按钮" background_y:0 } 
	]
	on_mouse_out:[ @component{ name:"快进按钮" background_y:-26 } ]
	on_click:[ 
		快进模式开启 = !快进模式开启; 
		if(快进模式开启){ 
			@include{ file:"script/sicily_auto_off.ks"}
			@include{ file:"script/sicily_skip_on.ks" }
		} 
		else{
			@include{ file:"script/sicily_skip_off.ks" }
		}
	]
}

自动模式开启 = false;
等待时间 = 1;
@component{ 
	name:"自动按钮" 
	background_y:-26
	background_image:"data/images/dialog_button_auto.png" 
	background_color:0x00FFFFFF
	on_mouse_in:[  
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
		@component{ name:"自动按钮" background_y:0 } 
	]
	on_mouse_out:[ @component{ name:"自动按钮" background_y:-26 } ]
	on_click:[ 
		自动模式开启 = !自动模式开启; 
		if(自动模式开启){ 
			@include{ file:"script/sicily_skip_off.ks"}
			@include{ file:"script/sicily_auto_on.ks" }
		} 
		else{
			@include{ file:"script/sicily_auto_off.ks" }
		}
	]
}

@component{ 
	name:"保存按钮" 
	background_image:"data/images/dialog_button_save.png" 
	background_color:0x00FFFFFF
	background_y:-26
	on_mouse_in:[ 
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
		@component{ name:"保存按钮" background_y:0 } 
	]
	on_mouse_out:[ @component{ name:"保存按钮" background_y:-26 } ]
	on_click:[ 
		@component{ name:"保存按钮" background_y:-26 }
		@include{ file:"script/sicily_auto_off.ks" }
		@saveGameData{ file:"data/savedata/qsave.sav" } 		
	]
}

@component{ 
	name:"读取按钮" 
	background_image:"data/images/dialog_button_load.png" 
	background_color:0x00FFFFFF
	background_y:-26
	on_mouse_in:[  
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
		@component{ name:"读取按钮" background_y:0 } 
	]
	on_mouse_out:[ @component{ name:"读取按钮" background_y:-26 } ]
	on_click:[ @loadGameData{ file:"data/savedata/qsave.sav" } ]
}

@component{ 
	name:"快速保存按钮" 
	background_image:"data/images/dialog_button_qsave.png" 
	background_color:0x00FFFFFF
	background_y:-26
	on_mouse_in:[  
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
		@component{ name:"快速保存按钮" background_y:0 } 
	]
	on_mouse_out:[ @component{ name:"快速保存按钮" background_y:-26 } ]
	on_click:[ 
		@component{ name:"快速保存按钮" background_y:-26 }
		@include{ file:"script/sicily_auto_off.ks" }
		@saveGameData{ file:"data/savedata/qsave.sav" } 		
	]
}

@component{ 
	name:"快速读取按钮" 
	background_image:"data/images/dialog_button_qload.png" 
	background_color:0x00FFFFFF
	background_y:-26
	on_mouse_in:[  
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
		@component{ name:"快速读取按钮" background_y:0 } 
	]
	on_mouse_out:[ @component{ name:"快速读取按钮" background_y:-26 } ]
	on_click:[ @loadGameData{ file:"data/savedata/qsave.sav" } ]
}

@component{ 
	name:"履历按钮" 
	background_image:"data/images/dialog_button_blog.png" 
	background_color:0x00FFFFFF
	background_y:-26
	on_mouse_in:[  
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
		@component{ name:"履历按钮" background_y:0 } 
	]
	on_mouse_out:[ @component{ name:"履历按钮" background_y:-26 } ]
	on_click:[
		@include{ file:"script/sicily_auto_off.ks" }
		@include{ file:"script/sicily_dialog_off.ks" }
		@include{ file:"script/sicily_backlog_on.ks" }
	]
}

@component{ 
	name:"退出按钮" 
	background_y:-26
	background_image:"data/images/dialog_button_close.png" 
	background_color:0x00FFFFFF
	on_mouse_in:[  
		@track{ name:"音效" src:"data/sounds/select.wav" loop:0 control:"Play" }
		@component{ name:"退出按钮" background_y:0 } 
	]
	on_mouse_out:[ @component{ name:"退出按钮" background_y:-26 } ]
	on_click:[ @goTo{ file:"script/main_menu.ks" } ]
}

///////////////////////////////////////////////////////////////////////////////////////

// 填充选项
@textBox{ 
	name:"选项1" 
	font:"文字框字体" 
	background_color:0xDD002244 
	on_mouse_in:[ @textBox{ name:"选项1" background_color:0xDD334455} ]
	on_mouse_out:[ @textBox{ name:"选项1" background_color:0xDD002244} ]
}
@textBox{ 
	name:"选项2" 
	font:"文字框字体" 
	background_color:0xDD002244 
	on_mouse_in:[ @textBox{ name:"选项2" background_color:0xDD334455}]
	on_mouse_out:[ @textBox{ name:"选项2" background_color:0xDD002244}]
}
@textBox{ 
	name:"选项3" 
	font:"文字框字体" 
	background_color:0xDD002244 
	on_mouse_in:[ @textBox{ name:"选项3" background_color:0xDD334455}]
	on_mouse_out:[ @textBox{ name:"选项3" background_color:0xDD002244}]
}

///////////////////////////////////////////////////////////////////////////////////////

// 填充履历
@font{ name:"履历字体" font:"微软雅黑" size:25 weight:"SemiBold" }
@component{ 
	name:"履历" 	 
	on_rclick: [ 
		@include{ file:"script/sicily_backlog_off.ks" } 
		@include{ file:"script/sicily_dialog_on.ks" }
	]
}
@list{ 
	name:"履历列表" 
	clear:true 
	on_scroll_up: [ @list{ name:"履历列表" scroll_delta:-50 } ]
	on_scroll_down: [ @list{ name:"履历列表" scroll_delta:50 } ]
	on_scroll_down_max: [
		@include{ file:"script/sicily_backlog_off.ks" }
		@include{ file:"script/sicily_dialog_on.ks" }
	]
}
@component{ name:"履历背景" background_color:0xDD002244 }
@textBox{ name:"履历标题" content:"   履 历" font:"文字框字体" background_color:0xDD334455}

///////////////////////////////////////////////////////////////////////////////////////

// 定义一个说话函数
继续说 = false;
@说(角色,内容,继续说){
	@clearText{ box:"对话框角色" content:角色 }
	@clearText{ box:"对话框文字" content:内容 }
	if(继续说){
		@waitDialog{ box:"对话框文字" has_text_to_add:true}
	}
	else{
		@waitDialog{ box:"对话框文字" has_text_to_clear:true}
	}
	// 将内容添加到履历
	履历编号++;
	@component{ 
		father:"履历列表" 
		name:"履历" + 履历编号 
		width:1200 
		height:100 
		layer:履历编号 
		background_color:0x00FFFFFF}
	@textBox{ 
		name:"履历角色" + 履历编号 
		father:"履历" + 履历编号 
		font:"履历字体" 
		width:140 
		height:90
		x:10 
		y:5 
		content:角色}
	@textBox{ 
		name:"履历内容" + 履历编号 
		father:"履历" + 履历编号 
		font:"履历字体" 
		width:1000
		height:90 
		x:160 
		y:5 
		content:内容}
	@wait{ component:"对话框" click:true key:"SPACE"}
}

// 定义另一个说话函数
@继续说(内容,继续说){
	@addText{ box:"对话框文字" content:内容 }	
	if(继续说){
		@waitDialog{ box:"对话框文字" has_text_to_add:true}
	}
	else{
		@waitDialog{ box:"对话框文字" has_text_to_clear:true}
	}	
	// 将内容添加到履历
	履历编号++;
	@component{ 
		father:"履历列表" 
		name:"履历" + 履历编号 
		width:1200 
		height:100 
		layer:履历编号 
		background_color:0x00FFFFFF}
	@textBox{ 
		name:"履历内容" + 履历编号 
		father:"履历" + 履历编号 
		font:"履历字体" 
		width:1000
		height:90 
		x:160 
		y:5 
		content:内容}
	@wait{ component:"对话框" click:true key:"SPACE"}
}

// 定义一个背景切换函数
@换背景(目标图片,效果,效果图,时间,质量){
	@component{ name:"背景后" background_image:目标图片 }
	@effect{ component:"背景前" effect:效果 effect_tex:效果图 level:质量 time:时间 add_mode:"Skip"}
	@wait{time:时间 click:true}
	@component{ name:"背景前" background_image:目标图片 }
	@effect{ component:"背景前" effect:null add_mode:"Skip"}
}

// 定义一个显示选项函数
@选项(选项1,选项2,选项3,脚本1,脚本2,脚本3){
	关闭选项脚本 = " @component{ name:'选项框' display:'hidden' } ";
	@textBox{ name:"选项1" content:选项1 on_click:关闭选项脚本 + 脚本1 }
	@textBox{ name:"选项2" content:选项2 on_click:关闭选项脚本 + 脚本2 }
	@textBox{ name:"选项3" content:选项3 on_click:关闭选项脚本 + 脚本3 }
	@component{ name:"选项框" display:"unhidden" }
}

@换立绘(立绘编号,立绘,时间){
	@component{name:"立绘前"+立绘编号 background_image:立绘 transparency:0}
	@component{name:"立绘后"+立绘编号 transparency:1}
	@animation{component:"立绘后"+立绘编号 transparency:0 time:时间 add_mode:"Skip"}
	@animation{component:"立绘前"+立绘编号 transparency:1 time:时间 add_mode:"Skip"}
	@wait{time:时间}
	@component{name:"立绘前"+立绘编号 background_image:null transparency:0}
	@component{name:"立绘后"+立绘编号 background_image:立绘 transparency:1}
}

@换背景音乐(音乐){
	@track{ 
		name:"背景音乐" 
		src:音乐 
		loop:-1 control:"Play" 
	}
}

@全屏遮挡(图片,颜色,时间){
	@component{ name:"全屏遮挡" background_image:图片 background_color:颜色 display:"unhidden" transparency:0}
	@animation{component:"全屏遮挡" transparency:1 time:时间 add_mode:"Skip"}
	@wait{time:时间}
	@clearText{ box:"对话框角色" content:"" }
	@clearText{ box:"对话框文字" content:"" }
	@script{ content:[ @next{ box:"对话框文字"} ]}
}

@取消遮挡(时间){
	@animation{component:"全屏遮挡" transparency:0 time:时间 add_mode:"Skip"}
	@wait{time:时间}
	@component{ name:"全屏遮挡" display:"hidden" transparency:0}
}

@抖(组件名){
	@animation{component:组件名 x_delta:-25 y_delta:20 time:0.03}
	@animation{component:组件名 x_delta:25 y_delta:-10 time:0.03}
	@animation{component:组件名 x_delta:-15 y_delta:-15 time:0.03}
	@animation{component:组件名 x_delta:10 y_delta:20 time:0.03}
	@animation{component:组件名 x_delta:15 y_delta:5 time:0.03}
	@animation{component:组件名 x_delta:-10 y_delta:-20 time:0.03}
	@animation{component:组件名 x_delta:-25 y_delta:20 time:0.03}
	@animation{component:组件名 x_delta:25 y_delta:-10 time:0.03}
	@animation{component:组件名 x_delta:-15 y_delta:-15 time:0.03}
	@animation{component:组件名 x_delta:10 y_delta:20 time:0.03}
	@animation{component:组件名 x_delta:15 y_delta:5 time:0.03}
	@animation{component:组件名 x_delta:-10 y_delta:-20 time:0.03}
}
