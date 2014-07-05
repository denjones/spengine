////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.11.1
// SpsShow 0.11.1 演示脚本
// Sicily 零与一的幻想 预览版
//
// Author: Ken.J
// Date: 2014-07-05
////////////////////////////////////////////////////////////////////////////

// 起始标记
$tag('一般主菜单');

////////////////////////////////////////////////////////////////////////////

// 创建屏幕
var mainMenuScreen = ss.createScreen({id: '主菜单'});

var soundTrack = ss.createTrack({id: '音效'});

// 初始化组件
var mainMenu = {
	
	/*********************** 组件 Begin ***********************/
	
	background1: mainMenuScreen.createComponent({
		id: '背景',
		width: 1280,
		height: 720,
		x: 0,
		y: 0,
		opacity: 0,
		backgroundImage: 'data/images/bg_classroom_02.png',
		depth: 0
	}),
	
	background2: mainMenuScreen.createComponent({
		id: '背景2',
		width: 1280,
		height: 720,
		x: 0,
		y: 0,
		opacity: 0,
		backgroundImage: 'data/images/bg_menu.png',
		depth: 1
	}),
	
	title: mainMenuScreen.createComponent({
		id: '标题',
		width: 1000,
		height: 300,
		x: 0,
		y: 50,
		opacity: 0,
		backgroundImage: 'data/images/logo_sicily_02.png',
		backgroundColor: 0x00FFFFFF,
		depth: 2
	}),
	
	copyright: mainMenuScreen.createComponent({
		id: 'copyright',
		width: 256,
		height: 20,
		x: 287,
		y: 700,
		opacity: 0,
		backgroundImage: 'data/images/copyright.png',
		backgroundColor: 0x00FFFFFF,
		depth: 2,
		onClick: function(){
			var proc = spawn('explorer', ['http://www.sprabbit.com']);
		}
	}),
	
	round: mainMenuScreen.createComponent({
		id: '转盘',
		width: 700,
		height: 700,
		x: 930,
		y: 370,
		opacity: 0,
		backgroundImage: 'data/images/round_menu.png',
		depth: 4,
		rotation: 0,
		rotationCenterX: 1280,
		rotationCenterY: 720
	}),
	
	button1: mainMenuScreen.createComponent({
		id: '按钮1',
		width: 350,
		height: 80,
		x: -150,
		y: 280,
		opacity: 0,
		backgroundImage: 'data/images/button_restart.png',
		backgroundColor: 0x00FFFFFF,
		depth: 3,
		onMouseIn: function(){
			soundTrack.src = 'data/sounds/select.wav';
			soundTrack.play();
			mainMenu.button1.backgroundY = -80;
			mainMenu.round.addAnimation({
				opacity: 1,
				rotation: 0,
				time: 0.3,
				addMode: 'Merge'
			});
			mainMenu.underline1.addAnimation({
				x: 0,
				time: 0.3,
				addMode: 'Merge'
			});
		},
		onMouseOut: function(){
			mainMenu.button1.backgroundY = 0;
			mainMenu.round.addAnimation({
				opacity: 0,
				time: 0.3,
				addMode: 'Merge'
			});
			mainMenu.underline1.addAnimation({
				x: -500,
				time: 0.3,
				addMode: 'Merge'
			});		
		},
		onClick: function(){
			soundTrack.src = 'data/sounds/confirm.wav';
			soundTrack.play();
			//@include{file:"script/main_menu_out.ks"} 
			//@include{file:"script/sicily_init.ks"}
			//// 跳转到主要内容
			//@goTo{ file:"script/sicily_01.ks" }
		}
	}),
	
	button2: mainMenuScreen.createComponent({
		id: '按钮2',
		width: 350,
		height: 80,
		x: -120,
		y: 360,
		opacity: 0,
		backgroundImage: 'data/images/button_continue.png',
		backgroundColor: 0x00FFFFFF,
		depth: 3,
		onMouseIn: function(){
			soundTrack.src = 'data/sounds/select.wav';
			soundTrack.play();
			mainMenu.button2.backgroundY = -80;
			mainMenu.round.addAnimation({
				opacity: 1,
				rotation: -PI / 2,
				time: 0.3,
				addMode: 'Merge'
			});
			mainMenu.underline2.addAnimation({
				x: 0,
				time: 0.3,
				addMode: 'Merge'
			});
		},
		onMouseOut: function(){
			mainMenu.button2.backgroundY = 0;
			mainMenu.round.addAnimation({
				opacity: 0,
				time: 0.3,
				addMode: 'Merge'
			});
			mainMenu.underline2.addAnimation({
				x: -500,
				time: 0.3,
				addMode: 'Merge'
			});		
		},
		onClick: function(){
			soundTrack.src = 'data/sounds/confirm.wav';
			soundTrack.play();
			//@include{file:"script/main_menu_out.ks"} 
			//@include{file:"script/sicily_init.ks"}
			//@loadGameData{ file:"data/savedata/qsave.sav" } 
		}
	}),
	
	button3: mainMenuScreen.createComponent({
		id: '按钮3',
		width: 350,
		height: 80,
		x: -120,
		y: 440,
		opacity: 0,
		backgroundImage: 'data/images/button_configure.png',
		backgroundColor: 0x00FFFFFF,
		depth: 3,
		onMouseIn: function(){
			soundTrack.src = 'data/sounds/select.wav';
			soundTrack.play();
			mainMenu.button3.backgroundY = -80;
			mainMenu.round.addAnimation({
				opacity: 1,
				rotation: -PI,
				time: 0.3,
				addMode: 'Merge'
			});
			mainMenu.underline3.addAnimation({
				x: 0,
				time: 0.3,
				addMode: 'Merge'
			});
		},
		onMouseOut: function(){
			mainMenu.button3.backgroundY = 0;
			mainMenu.round.addAnimation({
				opacity: 0,
				time: 0.3,
				addMode: 'Merge'
			});
			mainMenu.underline3.addAnimation({
				x: -500,
				time: 0.3,
				addMode: 'Merge'
			});		
		},
		onClick: function(){
			soundTrack.src = 'data/sounds/confirm.wav';
			soundTrack.play();
			//@include{file:"script/main_menu_out.ks"} 
			//@include{file:"script/sicily_config_on.ks"}
			//@execute{file:"http://www.sprabbit.com/spengine/tutorial.html"}
		}
	}),
	
	button4: mainMenuScreen.createComponent({
		id: '按钮4',
		width: 350,
		height: 80,
		x: -100,
		y: 520,
		opacity: 0,
		backgroundImage: 'data/images/button_shutdown.png',
		backgroundColor: 0x00FFFFFF,
		depth: 3,
		onMouseIn: function(){
			soundTrack.src = 'data/sounds/select.wav';
			soundTrack.play();
			mainMenu.button4.backgroundY = -80;
			mainMenu.round.addAnimation({
				opacity: 1,
				rotation: PI / 2,
				time: 0.3,
				addMode: 'Merge'
			});
			mainMenu.underline4.addAnimation({
				x: 0,
				time: 0.3,
				addMode: 'Merge'
			});
		},
		onMouseOut: function(){
			mainMenu.button4.backgroundY = 0;
			mainMenu.round.addAnimation({
				opacity: 0,
				time: 0.3,
				addMode: 'Merge'
			});
			mainMenu.underline4.addAnimation({
				x: -500,
				time: 0.3,
				addMode: 'Merge'
			});		
		},
		onClick: function(){
			soundTrack.src = 'data/sounds/confirm.wav';
			soundTrack.play();
			// 退出游戏			
			mainMenu.hide();
			setTimeout(function(){
				process.exit(0);
			}, 2000);
		}
	}),
	
	underline1: mainMenuScreen.createComponent({
		id: '按钮1下划线',
		width: 500,
		height: 20,
		x: -500,
		y: 340,
		backgroundImage: 'data/images/menu_button_line.png',
		backgroundColor: 0x00FFFFFF,
		depth: 2
	}),
	
	underline2: mainMenuScreen.createComponent({
		id: '按钮2下划线',
		width: 500,
		height: 20,
		x: -500,
		y: 420,
		backgroundImage: 'data/images/menu_button_line.png',
		backgroundColor: 0x00FFFFFF,
		depth: 2
	}),
	
	underline3: mainMenuScreen.createComponent({
		id: '按钮3下划线',
		width: 500,
		height: 20,
		x: -500,
		y: 500,
		backgroundImage: 'data/images/menu_button_line.png',
		backgroundColor: 0x00FFFFFF,
		depth: 2
	}),
	
	underline4: mainMenuScreen.createComponent({
		id: '按钮4下划线',
		width: 500,
		height: 20,
		x: -500,
		y: 580,
		backgroundImage: 'data/images/menu_button_line.png',
		backgroundColor: 0x00FFFFFF,
		depth: 2
	}),
	
	/*********************** 组件 End ***********************/
	
	/**
	 * 初始化父子关系
	 */
	init: function(){
		mainMenuScreen.root.appendChild(mainMenu.background1);
		mainMenuScreen.root.appendChild(mainMenu.background2);
		mainMenuScreen.root.appendChild(mainMenu.title);
		mainMenuScreen.root.appendChild(mainMenu.copyright);
		mainMenuScreen.root.appendChild(mainMenu.round);
		mainMenuScreen.root.appendChild(mainMenu.button1);
		mainMenuScreen.root.appendChild(mainMenu.button2);
		mainMenuScreen.root.appendChild(mainMenu.button3);
		mainMenuScreen.root.appendChild(mainMenu.button4);
		mainMenuScreen.root.appendChild(mainMenu.underline1);
		mainMenuScreen.root.appendChild(mainMenu.underline2);
		mainMenuScreen.root.appendChild(mainMenu.underline3);
		mainMenuScreen.root.appendChild(mainMenu.underline4);
	},
	
	/**
	 * 菜单出现动画
	 */
	show: function(){
		
		// 开启事件点击
		mainMenuScreen.root.catchClick = undefined;
		
		mainMenu.background1.addAnimation({
			time: 1,
			opacity: 1
		});
		
		mainMenu.background2.addAnimation({
			time: 1,
			opacity: 1
		});
		
		mainMenu.title.addAnimation({
			opacity: 1,
			time: 1,
			x: -100,
			replay: 'FastIn',
			canSkip: false
		});
		
		mainMenu.copyright.addAnimation({
			depth: 1,
			opacity: 1,
			time: 1,
			replay: 'FastIn',
			canSkip: false
		});
		
		mainMenu.button1.addAnimation({
			x: 50,
			opacity: 1,
			time: 1,
			replay: 'FastIn',
			canSkip: false
		});
		
		setTimeout(function(){
			mainMenu.button2.addAnimation({
				x: 80,
				opacity: 1,
				time: 1,
				replay: 'FastIn',
				canSkip: false
			});
		}, 200);
		
		setTimeout(function(){
			mainMenu.button3.addAnimation({
				x: 110,
				opacity: 1,
				time: 1,
				replay: 'FastIn',
				canSkip: false
			});
		}, 400);
		
		setTimeout(function(){
			mainMenu.button4.addAnimation({
				x: 80,
				opacity: 1,
				time: 1,
				replay: 'FastIn',
				canSkip: false
			});
		}, 600);
		
	},
	
	/**
	 * 菜单退出动画
	 */
	hide: function(){
		
		// 拦截事件点击
		mainMenuScreen.root.catchClick = function(){return false;};
		
		mainMenu.title.addAnimation({
			opacity: 0,
			time: 1,
			x: 0,
			replay: 'FastOut',
			canSkip: false
		});
		
		mainMenu.copyright.addAnimation({
			opacity: 0,
			time: 1,
			replay: 'FastOut',
			canSkip: false
		});
		
		mainMenu.round.addAnimation({
			opacity: 0,
			time:1,
			replay: 'FastOut',
			canSkip: false
		});
		
		mainMenu.underline1.addAnimation({
			x: -500,
			time: 0.3,
			addMode: 'Merge'
		});
		
		mainMenu.underline2.addAnimation({
			x: -500,
			time: 0.3,
			addMode: 'Merge'
		});
		
		mainMenu.underline3.addAnimation({
			x: -500,
			time: 0.3,
			addMode: 'Merge'
		});
		
		mainMenu.underline4.addAnimation({
			x: -500,
			time: 0.3,
			addMode: 'Merge'
		});
		
		mainMenu.button1.addAnimation({
			x: 80,
			opacity: 0,
			time: 1,
			replay: 'FastOut',
			canSkip: false
		});
		
		setTimeout(function(){
			mainMenu.button2.addAnimation({
				x: 110,
				opacity: 0,
				time: 1,
				replay: 'FastOut',
				canSkip: false
			});
		}, 200);
		
		setTimeout(function(){
			mainMenu.button3.addAnimation({
				x: 140,
				opacity: 0,
				time: 1,
				replay: 'FastOut',
				canSkip: false
			});
		}, 400);
		
		setTimeout(function(){
			mainMenu.button4.addAnimation({
				x: 110,
				opacity: 0,
				time: 1,
				replay: 'FastOut',
				canSkip: false
			});
		}, 600);
		
	}
};

mainMenu.init();
mainMenuScreen.focus();

// 进入菜单
mainMenu.show();