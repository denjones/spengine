////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.8.6
// SpsShow 0.8.6 演示脚本
// Sicily 零与一的幻想 预览版
//
// Author: Ken.J
// Date: 2013-06-07
////////////////////////////////////////////////////////////////////////////

// 起始标记
@tag{ name:"进入主菜单" }

////////////////////////////////////////////////////////////////////////////

// 设置主菜单
@screen{ name:"主菜单"}

// 标题动画
@animation{
	component:"标题"
	transparency:1
	time:1
	x:-100
	replay:"FastIn"
	can_skip:false
}

// LOGO动画
@animation{
	component:"copyright"
	layer:1
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

// 按钮1飞出动画
@animation{
	component:"按钮1"
	x:50
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

@waitTime{ time:0.2 }

// 按钮2飞出动画
@animation{
	component:"按钮2"
	x:80
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

@waitTime{ time:0.2 }

// 按钮3飞出动画
@animation{
	component:"按钮3"
	x:110
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}

@waitTime{ time:0.2 }

// 按钮4飞出动画
@animation{
	component:"按钮4"
	x:80
	transparency:1
	time:1
	replay:"FastIn"
	can_skip:false
}
