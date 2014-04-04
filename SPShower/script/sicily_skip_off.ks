////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.8.6
// SpsShow 0.8.6 演示脚本
// Sicily 零与一的幻想 预览版
//
// Author: Ken.J
// Date: 2013-06-07
////////////////////////////////////////////////////////////////////////////

// 关闭自动模式
@skip{ set_on:false }

@component{ 
	name:"快进按钮" 
	background_y:-26
	background_image:"data/images/dialog_button_skip.png" 
	on_click:[ 
		快进模式开启 = false; 
		@include{ file:"script/sicily_skip_on.ks" }
	]
}