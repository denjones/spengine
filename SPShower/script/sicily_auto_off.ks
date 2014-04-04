////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.8.6
// SpsShow 0.8.6 演示脚本
// Sicily 零与一的幻想 预览版
//
// Author: Ken.J
// Date: 2013-06-07
////////////////////////////////////////////////////////////////////////////

// 关闭自动模式
@skip{ set_on:false mode:"Auto" auto_time:等待时间 }

@component{ 
	name:"自动按钮" 
	background_y:-26
	background_image:"data/images/dialog_button_auto.png" 
	on_click:[ 
		自动模式开启 = false; 
		@include{ file:"script/sicily_auto_on.ks" }
	]
}