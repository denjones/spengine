////////////////////////////////////////////////////////////////////////////
// Demo script of SPShower Beta 0.82
//
// Author: Ken.J
// Date: 2012-09-25
////////////////////////////////////////////////////////////////////////////

// 起始标记
@tag{ name:"退出主菜单" }

// 设置主菜单
@screen{ name:"主菜单"}

// 空置按钮事件响应脚本
@component{
	name:"按钮1"
	on_mouse:null
	on_mouse_in:null
	on_mouse_out:null
	on_click:null
}

@component{
	name:"按钮2"
	on_mouse:null
	on_mouse_in:null
	on_mouse_out:null
	on_click:null
}

@component{
	name:"按钮3"
	on_mouse:null
	on_mouse_in:null
	on_mouse_out:null
	on_click:null
}

@component{
	name:"按钮4"
	on_mouse:null
	on_mouse_in:null
	on_mouse_out:null
	on_click:null
}

@animation{
	component:"标题"
	transparency:0
	time:1
	x:0
	replay:"FastOut"
	can_skip:false
}

// LOGO动画
@animation{
	component:"copyright"
	transparency:0
	time:1
	replay:"FastOut"
	can_skip:false
}

// 转盘动画
@animation{
	component:"转盘"
	transparency:0
	time:1
	replay:"FastOut"
	can_skip:false
}

@animation{ component:"按钮1下划线" x:-500 time:0.3 add_mode:"Merge"} 	
@animation{ component:"按钮2下划线" x:-500 time:0.3 add_mode:"Merge"} 	
@animation{ component:"按钮3下划线" x:-500 time:0.3 add_mode:"Merge"} 	
@animation{ component:"按钮4下划线" x:-500 time:0.3 add_mode:"Merge"} 	

// 按钮1飞出动画
@animation{
	component:"按钮1"
	x:80
	transparency:0
	time:1
	replay:"FastOut"
	can_skip:false
}

@waitTime{ time:0.2 }

// 按钮2飞出动画
@animation{
	component:"按钮2"
	x:110
	transparency:0
	time:1
	replay:"FastOut"
	can_skip:false
}

@waitTime{ time:0.2 }

// 按钮3飞出动画
@animation{
	component:"按钮3"
	x:140
	transparency:0
	time:1
	replay:"FastOut"
	can_skip:false
}

@waitTime{ time:0.2 }

// 按钮4飞出动画
@animation{
	component:"按钮4"
	x:110
	transparency:0
	time:1
	replay:"FastOut"
	can_skip:false
}

@waitTime{ time:1 }