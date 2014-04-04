////////////////////////////////////////////////////////////////////////////
// Demo script of SPShower Beta 0.82
//
// Author: Ken.J
// Date: 2012-09-25
////////////////////////////////////////////////////////////////////////////

// 起始标记
@tag{ name:"进入Logo画面"}

// 设置Logo画面
@screen{ name:"Logo画面"}

///////////////////////////////////////////////////////////////////////////
// 设置社团Logo
///////////////////////////////////////////////////////////////////////////

@component{
	name:"logo"
	background_image:"data/images/logo_sprabbit.png"
	width:400
	height:400
	x:440
	y:150
	transparency:0
}

// Logo出现消失动画
@animation{
	component:"logo"
	transparency:1
	time:1
	replay:"FastIn"
}

@wait{ time:3 click:true}

@animation{
	component:"logo"
	transparency:0
	time:1
	replay:"FastOut"
}

@wait{ time:1.5 click:true}

///////////////////////////////////////////////////////////////////////////
// 设置引擎Logo
///////////////////////////////////////////////////////////////////////////

@component{
	name:"logo"
	background_image:"data/images/logo_speshow.jpg"
	width:583
	height:194
	x:350
	y:200
	transparency:0
}

// Logo出现消失动画
@animation{
	component:"logo"
	transparency:1
	time:1
	replay:"FastIn"
}

@wait{ time:3 click:true}

@animation{
	component:"logo"
	transparency:0
	time:1
	replay:"FastOut"
}

@wait{ time:1.5 click:true}

@goTo{ file:"script/main_menu.ks" }
