﻿////////////////////////////////////////////////////////////////////////////
// Demo script of SPShower Beta 0.11
//
// Author: Ken.J
// Date: 2014-04-02
////////////////////////////////////////////////////////////////////////////

// 设置Logo画面

var logoCom;
var ssCom;

$(function(e){

	// 创建屏幕

	ss.createScreen({
		id: 'Logo',
		backgroundColor: 0xff000000
	}).focus();

	ss.screen.root.onClick = function(e){
		if(e.key == 0){
			stopWaitingClick();
		}
	}

	// 设置社团Logo

	logoCom = ss.screen.createComponent({
		id: "logo",
		backgroundImage: "data/images/logo_sprabbit.png",
		width: 400,
		height: 400,
		x: 440,
		y: 150,
		opacity: 0
	});

	ss.screen.root.appendChild(logoCom);

	// 设置引擎Logo

	ssCom = ss.screen.createComponent({
		id: "sslogo",
		backgroundImage: "data/images/logo_speshow.jpg",
		width: 583,
		height: 194,
		x: 350,
		y: 200,
		opacity: 0
	});

	ss.screen.root.appendChild(ssCom);
});

////////////////////////////////////////////////////////////////

$tag('动画开始');

// 初始化
$(function(e){
	if(e.read){
		ss.window.title = 'read';
	}
	logoCom.opacity = 0;
	ssCom.opacity = 0;
});

// Logo出现消失动画
$(function(e){
	logoCom.addAnimation({
		opacity: 1,
		time: 1,
		replay: "FastIn"
	});
});

$(function(e){
	waitTimeOrClick(3000, e);
});

$(function(e){
	logoCom.addAnimation({
		opacity: 0,
		time: 1,
		replay: "FastOut"
	});
});

$(function(e){
	waitTimeOrClick(1500, e);
});

$(function(e){logoCom.skip()});

// Logo出现消失动画

$(function(e){
	ssCom.addAnimation({
		opacity: 1,
		time: 1,
		replay: "FastIn"
	});
});

$(function(e){
	waitTimeOrClick(3000, e);
});

$(function(e){
	ssCom.addAnimation({
		opacity: 0,
		time: 1,
		replay: "FastOut"
	});
});

$(function(e){
	waitTimeOrClick(1500, e);
});

$(function(e){
	ssCom.skip();
});

// 跳转
$(function (e) {
    ss.goto({file:'script/logo.js', tag:'动画开始'});
});

$(function(e){
	ss.include("script/main_menu.js");
});
