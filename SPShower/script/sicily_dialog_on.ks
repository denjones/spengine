////////////////////////////////////////////////////////////////////////////
// Demo script of SPEShow Beta 0.82
// SPEShow 0.82 演示脚本之二
// 将演示一个简易的AVG场景脚本
//
// Author: Ken.J
// Date: 2012-10-02
////////////////////////////////////////////////////////////////////////////


// 对话框出现
@component{ name:"功能按钮"		display:"unhidden" }
@component{ name:"对话框" 		display:"unhidden" }
@component{ name:"替代对话框" 	display:"hidden" }
@component{ 
	name:"对话框" 
	transparency:0 
	on_key_down_LCONTROL:[ 
		@include{ file:"script/sicily_auto_off.ks" }
		@skip{ set_on:true mode:"All" auto_time:0.01 } 
	]
	on_key_up_LCONTROL:[ 
		@include{ file:"script/sicily_auto_off.ks" }
		@skip{ set_on:false mode:"All" auto_time:0.01 } 
	]
	catch_click:[ @next{ box:"对话框文字" } ] 
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
@component{ name:"功能按钮"	transparency:0 }
@animation{ component:"对话框" transparency:1 time:0.3}
@animation{ component:"功能按钮" transparency:1 time:0.3}
@waitTime{ time:0.3 }
