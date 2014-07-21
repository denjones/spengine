////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.11
//
// Author: Ken.J
// Date: 2014-05-05
////////////////////////////////////////////////////////////////////////////

// 获取SpeShow对象
var ss = process.binding('speshow');
var spawn = require('child_process').spawn;

// 读取系统变量以及已读函数
ss.loadSystemData();

// 窗口标题
ss.window.title = 'Sicily - 零与一的幻想 序章 (with SpeShow.JS 0.11)';

// 注册字体
ss.registerFont('font/msyh.ttf');

// 设置鼠标指针
ss.window.cursor = 'cursor/3.cur';

// 隐藏帧率
ss.window.fps.display = false;

// 退出前验证
ss.window.onExit = function () {
	ss.saveSystemData();
    return true;
}

// 跳过模式
ss.sysVar.skipMode = 'read';

// 音轨
var soundTrack = ss.createTrack({
	id: '音效'
});
var musicTrack = ss.createTrack({
	id: '背景音乐',
	loop: -1
});

////////////////////////////////////////////////////////////////////////////
// 常量
////////////////////////////////////////////////////////////////////////////

var PI = 3.1415926;

////////////////////////////////////////////////////////////////////////////
// 以下定义相关函数
////////////////////////////////////////////////////////////////////////////

// 绑定$为队列函数
var $ = ss.addCommand;
var $tag = ss.addTag;

// 阻塞变量
var _isClick = false;
var _isTimesUp = false;
var _waitTimeHandle = null;
var stopWaitingClick = function () {
    _isClick = true;
}
var _resetWaiting = function () {
    _isClick = false;
    _isTimesUp = false;
};

// 定义定等待点击队列函数
var waitClick = function (e) {
    if (!_isClick) {
        e.repeat = true;
    }
    _resetWaiting();
};

// 定义等待时间队列函数
var waitTime = function (timeMs, e) {
    if (!_waitTimeHandle) {
        _waitTimeHandle = setTimeout(function () {
            _isTimesUp = true;
        }, timeMs);
    }
    if (_isTimesUp) {
        clearTimeout(_waitTimeHandle);
        _waitTimeHandle = null;
    } else {
        e.repeat = true;
    }
    _resetWaiting();
};

// 定义等待时间或点击队列函数
var waitTimeOrClick = function (timeMs, e) {
    if (!_waitTimeHandle) {
        _waitTimeHandle = setTimeout(function () {
            _isTimesUp = true;
        }, timeMs);
    }
    if (_isTimesUp || _isClick) {
        clearTimeout(_waitTimeHandle);
        _waitTimeHandle = null;
    } else {
        e.repeat = true;
    }
    _resetWaiting();
};

////////////////////////////////////////////////////////////////////////////
// 进入起始脚本
////////////////////////////////////////////////////////////////////////////

// 跳转
//$(function (e) {
//    ss.goto({ file: 'script/logo.js' });
//});

$(function (e) {
	ss.include('script/sicily_init.js');
	storyScreen.focus();
    ss.goto({ file: 'script/sicily_01.js' });
});

//PI = 3.1415926;

//ss.window.resize(800, 600);

//ss.createScreen({
//    id: 'testScreen',
//    backgroundColor: 0xff000000
//}).focus();

//ss.screen.root.backgroundColor = 0xaaffffff;

//var newCom = ss.screen.createComponent({
//    id: 'testCom',
//    backgroundColor: 0xff000000,
//    width: 100,
//    height: 200,
//    x: 0,
//    y: 0
//});

//ss.registerFont({
//    file: 'data/fonts/DFPShaoNvW5-GB.ttf'
//});

//var textBox = ss.screen.createComponent({
//    type: 'dialogBox',
//    id: 'textBox',
//    backgroundColor: 0x00ffffff,
//    width: 400,
//    height: 200,
//    x: 100,
//    y: 50,
//    paddingTop: 10,
//    paddingRight: 10,
//    paddingLeft: 10,
//    paddingBottom: 10,
//    color: 0xffffffff,
//    letterSpace: 1,
//    autoHeight: true,
//    font: {
//        size: 20,
//        weight: 500,
//        font: '华康少女文字W5(P)'
//    },
//    textEffectFront: {
//        type: 'TextShadow',
//	    texture: 'data/images/dialog_text.png',
//	    level: 0,
//        quality: 0,
//	    opacity: 1,
//        control: 'play'
//    },
//    textEffectBack: {
//        type: 'TextShadow',
//        texture: 'data/images/dialog_shadow.png',
//        level: 2,
//        quality: 10,
//        opacity: 1,
//        control: 'play'
//    }
//});

//var pictureBox = ss.screen.createComponent({
//    type: 'pictureBox',
//    id: 'pictureBox',
//    backgroundColor: 0xdd000000,
//    width: 1280,
//    height: 720
//});

//var scroll = ss.screen.createComponent({
//    type: 'scroll',
//    id: 'scroll',
//    backgroundColor: 0x22eeffdd,
//    depth: 10,
//    width: 1280,
//    height: 720,
//    onClick: function(e) {
//        console.log(JSON.stringify(e));
//        this.backgroundColor += 0x11; 
//    }
//});

//scroll.addEffect({
//    type:'Mask',
//    texture: 'mask/mask_123.png',
//    level:2,
//    time:3,
//    addMode:"Skip"
//});

//scroll.addAnimation({
//    xDelta: 200,
//    yDelta: 100,
//    time: 5
//});

//var video = ss.createVideo({
//    id: 'video',
//    src: 'data/videos/openning.mp4'
//});

//var particleSystem = ss.createParticleSystem({
//    id: 'ps',
//    tex: { src: 'data/images/snow.png' },
//    bornXMin: 0,
//    bornXMax: 1280,
//    bornYMin: 721,
//    bornYMax: 722,
//    liveXMin: -2,
//    liveYMin: -2,
//    liveXMax: 1282,
//    liveYMax: 722,
//    liveTime: 5,
//    shootVelocityMin: 100,
//    shootVelocityMax: 200,
//    shootAngleMin: PI + PI / 6 * 2,
//    shootAngleMax: PI + PI / 6 * 5,
//    shootRate: 20,
//    accelerationX: 0,
//    accelerationY: 0,
//    fadeTime: 1,
//    scaleMax: 1,
//    scaleMin: 0.5,
//    scaleRateMin: -0.5,
//    scaleRateMax: 0,
//    countMax: 300,
//    color: 0xf9ffffff,
//    width: 1280,
//    height: 720,
//    specialRotation: true,
//    rotateMax: 0,
//    rotateMin: 0,
//    rotateRateMin: 0,
//    rotateRateMax: 0
//});

//pictureBox.setPicture({
//    particleSystem: particleSystem
//});

//for (var i = 0; i < 100; i++) {
//    scroll.appendChild(ss.screen.createComponent({
//        type: 'textBox',
//        backgroundColor: 0xffeeffdd,
//        autoHeight: true,
//        width: 300,
//        color: 0xff000000,
//        text: '测试' + i
//    }));
//}

//ss.screen.root.appendChild(ss.screen.getComponentById('testCom'));
//ss.screen.root.appendChild(pictureBox);
//ss.screen.root.appendChild(textBox);
//ss.screen.root.appendChild(scroll);

//var track = ss.createTrack({
//    id: 'track',
//    src: 'data/sounds/bgm01.ogg'
//});



//textBox.text = '哈哈哈哈哈哈，测试下';

//track.play();
//video.play();
//particleSystem.play();

//ss.include('first.js');