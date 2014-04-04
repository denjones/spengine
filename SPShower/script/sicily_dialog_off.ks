////////////////////////////////////////////////////////////////////////////
// Demo script of SPEShow Beta 0.82
// SPEShow 0.82 演示脚本之二
// 将演示一个简易的AVG场景脚本
//
// Author: Ken.J
// Date: 2012-10-02
////////////////////////////////////////////////////////////////////////////


// 对话框消失
// 替代对话框用于在对话框正在消失时拦截对话框消息
@component{ 
	name:"替代对话框" 
	display:"unhidden"
	layer:31 
	catch_click:[
		// 不作任何事情
	]
	catch_rclick:[ 
		// 不作任何事情
	]
}
@component{ 
	name:"对话框" 
	transparency:1 
	catch_click:null
	catch_rclick:null
	catch_scroll_up:null
	on_key_down_LCONTROL:null
	on_key_up_LCONTROL:null
}
@component{ name:"功能按钮"	transparency:1 }
@animation{ component:"对话框" transparency:0 time:0.3}
@animation{ component:"功能按钮" transparency:0 time:0.3}
@waitTime{ time:0.3 }
@component{ name:"功能按钮"	display:"hidden" }
@component{ name:"对话框" display:"hidden" }
@component{ 
	name:"替代对话框" 
	catch_click:[
		// 不作任何事情
	]
	catch_rclick:[ 
		@include{file:"script/sicily_dialog_on.ks"}
	]
}
 