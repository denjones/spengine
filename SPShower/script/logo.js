////////////////////////////////////////////////////////////////////////////
// Demo script of SPShower Beta 0.11
//
// Author: Ken.J
// Date: 2014-04-02
////////////////////////////////////////////////////////////////////////////

// 设置Logo画面
ss.createScreen({
	id: 'Logo',
	backgroundColor: 0xff000000
}).focus();

ss.screen.root.onClick = function(e){
	if(e.key == 0){
		stopWaitingClick();
	}
}

///////////////////////////////////////////////////////////////////////////
// 设置社团Logo
///////////////////////////////////////////////////////////////////////////

var logoCom = ss.screen.createComponent({
	name: "logo",
	backgroundImage: "data/images/logo_sprabbit.png",
	width: 400,
	height: 400,
	x: 440,
	y: 150,
	opacity: 0
});

ss.screen.root.appendChild(logoCom);

// Logo出现消失动画
$(function(e){
	logoCom.addAnimation({
		opacity: 1,
		time: 1,
		replay: "FastIn"
	});
});

$(waitTimeOrClick(3000));

$(function(e){
	logoCom.addAnimation({
		opacity: 0,
		time: 1,
		replay: "FastOut"
	});
});

$(waitTimeOrClick(1500));

$(function(e){logoCom.skip()});

///////////////////////////////////////////////////////////////////////////
// 设置引擎Logo
///////////////////////////////////////////////////////////////////////////

var ssCom = ss.screen.createComponent({
	name: "sslogo",
	backgroundImage: "data/images/logo_speshow.jpg",
	width: 583,
	height: 194,
	x: 350,
	y: 200,
	opacity: 0
});

ss.screen.root.appendChild(ssCom);

// Logo出现消失动画

$(function(e){
	ssCom.addAnimation({
		opacity: 1,
		time: 1,
		replay: "FastIn"
	});
});

$(waitTimeOrClick(3000));

$(function(e){
	ssCom.addAnimation({
		opacity: 0,
		time: 1,
		replay: "FastOut"
	});
});

$(waitTimeOrClick(1500));

$(function(e){
	ss.include("script/main_menu.js");
});
