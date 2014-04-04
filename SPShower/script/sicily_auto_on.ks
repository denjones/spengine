////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.8.6
// SpsShow 0.8.6 演示脚本
// Sicily 零与一的幻想 预览版
//
// Author: Ken.J
// Date: 2013-06-07
////////////////////////////////////////////////////////////////////////////

// 开启自动模式
@include{ file:"script/sicily_skip_off.ks" }

@skip{ set_on:true mode:"Auto" auto_time:等待时间 }

@component{ 
	name:"自动按钮" 
	background_y:0
	background_image:"data/images/dialog_button_auto_on.png" 
	on_click:[ 
		自动模式开启 = true; 
		@include{ file:"script/sicily_auto_off.ks" }
	]
}

