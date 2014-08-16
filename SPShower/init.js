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

// 初始化系统变量
if(ss.sysVar.skipMode === undefined) {
	ss.sysVar.skipMode = 0; // 跳过已读
	//ss.sysVar.skipMode = 1; // 跳过全部
}
if(ss.sysVar.soundVolume === undefined) {
	ss.sysVar.soundVolume = 10;
}
if(ss.sysVar.musicVolume === undefined) {
	ss.sysVar.musicVolume = 10;
}
if(ss.sysVar.textSpeed === undefined) {
	ss.sysVar.textSpeed = 10;
}

// 音轨
var soundTrack = ss.createTrack({
	id: '音效',
	volume: ss.sysVar.soundVolume / 10
});
var musicTrack = ss.createTrack({
	id: '背景音乐',
	loop: -1,
	volume: ss.sysVar.musicVolume / 10
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
    ss.goto({ file: 'script/main_menu.js' });
});
