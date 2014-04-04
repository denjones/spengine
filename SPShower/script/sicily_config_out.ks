////////////////////////////////////////////////////////////////////////////
// Demo script of SPEShow Beta 0.82
// SPEShow 0.82 演示脚本之二
// 将演示一个简易的AVG场景脚本
//
// Author: Ken.J
// Date: 2012-10-02
////////////////////////////////////////////////////////////////////////////

@component{
	name:"返回按钮"
	on_mouse:null
	on_mouse_in:null
	on_mouse_out:null
	on_click:null
}

// 选项退出
@animation{component:"返回按钮" y_delta:10 time:0.3 transparency:0 replay:"FastOut"}
@wait{time:0.1}
@animation{component:"跳过" y_delta:30 time:0.4 transparency:0 replay:"FastOut"}
@wait{time:0.1}
@animation{component:"分辨" y_delta:70 time:0.5 transparency:0 replay:"FastOut"}
@wait{time:0.1}
@animation{component:"屏幕" y_delta:50 time:0.5 transparency:0 replay:"FastOut"}
@wait{time:0.1}
@animation{component:"文字" y_delta:90 time:0.6 transparency:0 replay:"FastOut"}
@wait{time:0.1}
@animation{component:"音乐" y_delta:110 time:0.6 transparency:0 replay:"FastOut"}
@wait{time:0.1}
@animation{component:"声效" y_delta:130 time:0.6 transparency:0 replay:"FastOut"}
@wait{time:1}

@component{name:"返回按钮" display:"hidden"}
@component{name:"跳过" display:"hidden"}
@component{name:"屏幕" display:"hidden"}
@component{name:"分辨" display:"hidden"}
@component{name:"文字" display:"hidden"}
@component{name:"音乐" display:"hidden"}
@component{name:"声效" display:"hidden"}