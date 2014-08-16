/**
 * 主菜单
 * @file main_menu.js
 * @author Ken.J
 * @date 2014-07-05
 */

// 创建屏幕
var mainMenuScreen = ss.createScreen({
	id: '主菜单'
});


// 初始化组件
var mainMenu;
if (!mainMenu) {
	
	mainMenu = {

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
		
		mainMenuLayer: mainMenuScreen.createComponent({
			id: '菜单层',
			width: 1280,
			height: 720,
			x: 0,
			y: 0,
			opacity: 1,
			depth: 2
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
			onClick: function () {
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
			onMouseIn: function () {
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
			onMouseOut: function () {
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
			onClick: function () {
				soundTrack.src = 'data/sounds/confirm.wav';
				soundTrack.play();
				mainMenu.hide();
				setTimeout(function(){
					ss.include('script/sicily_init.js');
					storyScreen.focus();
					storyObj.reset();
					storyObj.maskEnd();
					ss.goto({file:'script/sicily_01.js'});
				}, 2000);
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
			onMouseIn: function () {
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
			onMouseOut: function () {
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
			onClick: function () {
				var fs = require('fs');
				if(!fs.existsSync('./state.dat')){
					return;
				}
				soundTrack.src = 'data/sounds/confirm.wav';
				soundTrack.play();
				mainMenu.hide();
				setTimeout(function(){
					ss.include('script/sicily_init.js');
					storyScreen.focus();
					storyObj.reset();
					storyObj.maskEnd();
					ss.loadState();
					storyObj.refresh();
				}, 2000);
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
			onMouseIn: function () {
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
			onMouseOut: function () {
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
			onClick: function () {
				soundTrack.src = 'data/sounds/confirm.wav';
				soundTrack.play();
				mainMenu.hide();
				setTimeout(function(){
					mainMenu.showConfig();
				}, 1000);
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
			onMouseIn: function () {
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
			onMouseOut: function () {
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
			onClick: function () {
				soundTrack.src = 'data/sounds/confirm.wav';
				soundTrack.play();
				// 退出游戏			
				mainMenu.hide();
				setTimeout(function () {
					ss.saveSystemData();
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
		
		configLayer: mainMenuScreen.createComponent({
			id: '选项层',
			width: 1280,
			height: 720,
			x: 0,
			y: 0,
			opacity: 1,
			depth: 3,
			display: false
		}),
		
		configSound: mainMenuScreen.createComponent({
			id: '声效',
			width: 1000,
			height: 60,
			x: 20,
			y: 10,
			depth: 2,
			opacity: 0
		}),
		
		configSoundText: mainMenuScreen.createComponent({
			id: '声效文字',
			width: 400,
			height: 60,
			x: 0,
			y: 0,
			backgroundImage: 'data/images/tag_sound.png',
			depth: 1
		}),
		
		configSoundSelection: mainMenuScreen.createComponent({
			id: '声效选项',
			width: 600,
			height: 60,
			x: 400,
			y: 0,
			depth: 1
		}),
		
		configMusic: mainMenuScreen.createComponent({
			id: '音乐',
			width: 1000,
			height: 60,
			x: 50,
			y: 40,
			depth: 2,
			opacity: 0
		}),
		
		configMusicText: mainMenuScreen.createComponent({
			id: '音乐文字',
			width: 400,
			height: 60,
			x: 0,
			y: 0,
			backgroundImage: 'data/images/tag_music.png',
			depth: 1
		}),
		
		configMusicSelection: mainMenuScreen.createComponent({
			id: '音乐选项',
			width: 600,
			height: 60,
			x: 400,
			y: 0,
			depth: 1
		}),
		
		configSpeed: mainMenuScreen.createComponent({
			id: '文字速度',
			width: 1000,
			height: 60,
			x: 80,
			y: 70,
			depth: 2,
			opacity: 0
		}),
		
		configSpeedText: mainMenuScreen.createComponent({
			id: '文字速度文字',
			width: 400,
			height: 60,
			x: 0,
			y: 0,
			backgroundImage: 'data/images/tag_speed.png',
			depth: 1
		}),
		
		configSpeedSelection: mainMenuScreen.createComponent({
			id: '文字速度选项',
			width: 600,
			height: 60,
			x: 400,
			y: 0,
			depth: 1
		}),
		
		configScreen: mainMenuScreen.createComponent({
			id: '屏幕模式',
			width: 1000,
			height: 60,
			x: 110,
			y: 100,
			depth: 2,
			opacity: 0
		}),
		
		configScreenText: mainMenuScreen.createComponent({
			id: '屏幕模式文字',
			width: 400,
			height: 60,
			x: 0,
			y: 0,
			backgroundImage: 'data/images/tag_screen.png',
			depth: 1
		}),
		
		configScreenSelection: mainMenuScreen.createComponent({
			id: '屏幕模式选项',
			width: 600,
			height: 60,
			x: 400,
			y: 0,
			depth: 1
		}),
		
		configScreenWindowed: mainMenuScreen.createComponent({
			id: '屏幕模式窗口',
			width: 300,
			height: 60,
			x: 0,
			y: 0,
			backgroundImage: 'data/images/tag_screen_windowed.png',
			onMouseIn: function(e){
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
				this.backgroundY = -60;
			},
			onMouseOut: function(e){
				this.backgroundY = 0;
			},
			onClick: function(e){
				if(ss.window.fullScreen){
					ss.window.fullScreen = false;
				}
			}
		}),
		
		configScreenFullscreen: mainMenuScreen.createComponent({
			id: '屏幕模式全屏',
			width: 300,
			height: 60,
			x: 300,
			y: 0,
			backgroundImage: 'data/images/tag_screen_fullscreen.png',
			onMouseIn: function(e){
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
				this.backgroundY = -60;
			},
			onMouseOut: function(e){
				this.backgroundY = 0;
			},
			onClick: function(e){
				if(!ss.window.fullScreen){
					ss.window.fullScreen = true;
				}
			}
		}),
		
		configResolution: mainMenuScreen.createComponent({
			id: '分辨率模式',
			width: 1000,
			height: 60,
			x: 140,
			y: 130,
			depth: 2,
			opacity: 0
		}),
		
		configResolutionText: mainMenuScreen.createComponent({
			id: '分辨率模式文字',
			width: 400,
			height: 60,
			x: 0,
			y: 0,
			backgroundImage: 'data/images/tag_resolution.png',
			depth: 1
		}),
		
		configResolutionSelection: mainMenuScreen.createComponent({
			id: '分辨率模式选项',
			width: 600,
			height: 60,
			x: 400,
			y: 0,
			depth: 1
		}),
		
		configResolution1: mainMenuScreen.createComponent({
			id: '分辨率模式1',
			width: 300,
			height: 60,
			x: 0,
			y: 0,
			backgroundImage: 'data/images/tag_resolution_01.png',
			onMouseIn: function(e){
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
				this.backgroundY = -60;
			},
			onMouseOut: function(e){
				this.backgroundY = 0;
			},
			onClick: function(e){
				ss.window.resize(960, 540);
			}
		}),
		
		configResolution2: mainMenuScreen.createComponent({
			id: '分辨率模式2',
			width: 300,
			height: 60,
			x: 300,
			y: 0,
			backgroundImage: 'data/images/tag_resolution_02.png',
			onMouseIn: function(e){
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
				this.backgroundY = -60;
			},
			onMouseOut: function(e){
				this.backgroundY = 0;
			},
			onClick: function(e){
				ss.window.resize(1280, 720);
			}
		}),
		
		configSkip: mainMenuScreen.createComponent({
			id: '跳过模式',
			width: 1000,
			height: 60,
			x: 170,
			y: 160,
			depth: 2,
			opacity: 0
		}),
		
		configSkipText: mainMenuScreen.createComponent({
			id: '跳过模式文字',
			width: 400,
			height: 60,
			x: 0,
			y: 0,
			backgroundImage: 'data/images/tag_skip.png',
			depth: 1
		}),
		
		configSkipSelection: mainMenuScreen.createComponent({
			id: '跳过模式选项',
			width: 600,
			height: 60,
			x: 400,
			y: 0,
			depth: 1
		}),
		
		configSkip1: mainMenuScreen.createComponent({
			id: '跳过模式1',
			width: 300,
			height: 60,
			x: 0,
			y: 0,
			backgroundImage: ss.sysVar.skipMode == 1 ? 'data/images/tag_skip_all_on.png' : 'data/images/tag_skip_all.png',
			onMouseIn: function(e){
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
				this.backgroundY = -60;
			},
			onMouseOut: function(e){
				this.backgroundY = 0;
			},
			onClick: function(e){
				if(ss.sysVar.skipMode == 1){
					ss.sysVar.skipMode = 0;
				} else {
					ss.sysVar.skipMode = 1;
					this.backgroundImage = 'data/images/tag_skip_all_on.png';
					mainMenu.configSkip2.backgroundImage = 'data/images/tag_skip_read.png';
				}
			}
		}),
		
		configSkip2: mainMenuScreen.createComponent({
			id: '跳过模式2',
			width: 300,
			height: 60,
			x: 300,
			y: 0,
			backgroundImage: ss.sysVar.skipMode == 0 ? 'data/images/tag_skip_read_on.png' : 'data/images/tag_skip_read.png',
			onMouseIn: function(e){
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
				this.backgroundY = -60;
			},
			onMouseOut: function(e){
				this.backgroundY = 0;
			},
			onClick: function(e){
				if(ss.sysVar.skipMode == 1){
					ss.sysVar.skipMode = 0;
					this.backgroundImage = 'data/images/tag_skip_read_on.png';
					mainMenu.configSkip1.backgroundImage = 'data/images/tag_skip_all.png';
				} else {
					ss.sysVar.skipMode = 1;
				}
			}
		}),
		
		configReturn: mainMenuScreen.createComponent({
			id: '返回按钮',
			width: 400,
			height: 60,
			x: 200,
			y: 190,
			backgroundImage: 'data/images/button_return.png',
			onMouseIn: function(e){
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
				this.backgroundY = -60;
			},
			onMouseOut: function(e){
				this.backgroundY = 0;
			},
			onClick: function(e){
				soundTrack.src = 'data/sounds/confirm.wav';
				soundTrack.play();
				mainMenu.hideConfig();
				setTimeout(function(){
					mainMenu.show();
				}, 1000);
			}
		}),

		/*********************** 组件 End ***********************/

		/**
		 * 初始化父子关系
		 */
		init: function () {
			mainMenuScreen.root.appendChild(mainMenu.background1);
			mainMenuScreen.root.appendChild(mainMenu.background2);
			mainMenuScreen.root.appendChild(mainMenu.mainMenuLayer);
			
			mainMenu.mainMenuLayer.appendChild(mainMenu.title);
			mainMenu.mainMenuLayer.appendChild(mainMenu.copyright);
			mainMenu.mainMenuLayer.appendChild(mainMenu.round);
			mainMenu.mainMenuLayer.appendChild(mainMenu.button1);
			mainMenu.mainMenuLayer.appendChild(mainMenu.button2);
			mainMenu.mainMenuLayer.appendChild(mainMenu.button3);
			mainMenu.mainMenuLayer.appendChild(mainMenu.button4);
			mainMenu.mainMenuLayer.appendChild(mainMenu.underline1);
			mainMenu.mainMenuLayer.appendChild(mainMenu.underline2);
			mainMenu.mainMenuLayer.appendChild(mainMenu.underline3);
			mainMenu.mainMenuLayer.appendChild(mainMenu.underline4);
			
			mainMenuScreen.root.appendChild(mainMenu.configLayer);
			
			mainMenu.configLayer.appendChild(mainMenu.configSound);
			mainMenu.configSound.appendChild(mainMenu.configSoundText);
			mainMenu.configSound.appendChild(mainMenu.configSoundSelection);
			for(var i = 0; i < 10; i++) {
				var option = mainMenuScreen.createComponent({
					i: i,
					width:50,
					height:60 ,
					x: 20 + i * 50 ,
					y: 0 ,
					depth: 1,
					backgroundImage: 'data/images/slider_0' + i + (i <= ss.sysVar.soundVolume ? '_on.png' : '.png'),
					onMouseOut: function(e){
						this.backgroundY = 0;
					},
					onMouseIn: function(e){
						soundTrack.src = 'data/sounds/select.wav';
						soundTrack.play();
						this.backgroundY = -60;
					},
					onClick: function(e){
						for(var j = 0; j <= this.i; j++){
							this.parent.childComponents[j].backgroundImage = 'data/images/slider_0' + j + '_on.png';
						}
						for(var j = this.i + 1; j < 10; j++){
							this.parent.childComponents[j].backgroundImage = 'data/images/slider_0' + j + '.png';
						}
						ss.sysVar.soundVolume = this.i / 10;
						soundTrack.volume = this.i / 10;
					}
				});
				mainMenu.configSoundSelection.appendChild(option);
			}
			
			mainMenu.configLayer.appendChild(mainMenu.configMusic);
			mainMenu.configMusic.appendChild(mainMenu.configMusicText);
			mainMenu.configMusic.appendChild(mainMenu.configMusicSelection);
			for(var i = 0; i < 10; i++) {
				var option = mainMenuScreen.createComponent({
					i: i,
					width:50,
					height:60 ,
					x: 20 + i * 50 ,
					y: 0 ,
					depth: 1,
					backgroundImage: 'data/images/slider_0' + i + (i <= ss.sysVar.musicVolume ? '_on.png' : '.png'),
					onMouseOut: function(e){
						this.backgroundY = 0;
					},
					onMouseIn: function(e){
						soundTrack.src = 'data/sounds/select.wav';
						soundTrack.play();
						this.backgroundY = -60;
					},
					onClick: function(e){
						for(var j = 0; j <= this.i; j++){
							this.parent.childComponents[j].backgroundImage = 'data/images/slider_0' + j + '_on.png';
						}
						for(var j = this.i + 1; j < 10; j++){
							this.parent.childComponents[j].backgroundImage = 'data/images/slider_0' + j + '.png';
						}
						ss.sysVar.musicVolume = this.i / 10;
						musicTrack.volume = this.i / 10;
					}
				});
				mainMenu.configMusicSelection.appendChild(option);
			}
			
			mainMenu.configLayer.appendChild(mainMenu.configSpeed);
			mainMenu.configSpeed.appendChild(mainMenu.configSpeedText);
			mainMenu.configSpeed.appendChild(mainMenu.configSpeedSelection);
			for(var i = 0; i < 10; i++) {
				var option = mainMenuScreen.createComponent({
					i: i,
					width:50,
					height:60 ,
					x: 20 + i * 50 ,
					y: 0 ,
					depth: 1,
					backgroundImage: 'data/images/slider_0' + i + (i <= ss.sysVar.textSpeed ? '_on.png' : '.png'),
					onMouseOut: function(e){
						this.backgroundY = 0;
					},
					onMouseIn: function(e){
						soundTrack.src = 'data/sounds/select.wav';
						soundTrack.play();
						this.backgroundY = -60;
					},
					onClick: function(e){
						for(var j = 0; j <= this.i; j++){
							this.parent.childComponents[j].backgroundImage = 'data/images/slider_0' + j + '_on.png';
						}
						for(var j = this.i + 1; j < 10; j++){
							this.parent.childComponents[j].backgroundImage = 'data/images/slider_0' + j + '.png';
						}
						ss.sysVar.textSpeed = this.i * 10;
						if(global.storyObj){
							storyObj.dialogText.speed = ss.sysVar.textSpeed;
						}
					}
				});
				mainMenu.configSpeedSelection.appendChild(option);
			}
			
			mainMenu.configLayer.appendChild(mainMenu.configScreen);
			mainMenu.configScreen.appendChild(mainMenu.configScreenText);
			mainMenu.configScreen.appendChild(mainMenu.configScreenSelection);
			mainMenu.configScreenSelection.appendChild(mainMenu.configScreenWindowed);
			mainMenu.configScreenSelection.appendChild(mainMenu.configScreenFullscreen);
			
			mainMenu.configLayer.appendChild(mainMenu.configResolution);
			mainMenu.configResolution.appendChild(mainMenu.configResolutionText);
			mainMenu.configResolution.appendChild(mainMenu.configResolutionSelection);
			mainMenu.configResolutionSelection.appendChild(mainMenu.configResolution1);
			mainMenu.configResolutionSelection.appendChild(mainMenu.configResolution2);
			
			mainMenu.configLayer.appendChild(mainMenu.configSkip);
			mainMenu.configSkip.appendChild(mainMenu.configSkipText);
			mainMenu.configSkip.appendChild(mainMenu.configSkipSelection);
			mainMenu.configSkipSelection.appendChild(mainMenu.configSkip1);
			mainMenu.configSkipSelection.appendChild(mainMenu.configSkip2);
			
			mainMenu.configLayer.appendChild(mainMenu.configReturn);
		},

		/**
		 * 菜单出现动画
		 */
		show: function () {
			
			// BGM
			if(musicTrack.src != 'data/sounds/bgm01.ogg'){
				musicTrack.stop();
				musicTrack.src = 'data/sounds/bgm01.ogg';
				musicTrack.play();
			}
			
			mainMenu.mainMenuLayer.display = true;

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

			setTimeout(function () {
				mainMenu.button2.addAnimation({
					x: 80,
					opacity: 1,
					time: 1,
					replay: 'FastIn',
					canSkip: false
				});
			}, 200);

			setTimeout(function () {
				mainMenu.button3.addAnimation({
					x: 110,
					opacity: 1,
					time: 1,
					replay: 'FastIn',
					canSkip: false
				});
			}, 400);

			setTimeout(function () {
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
		hide: function () {

			// 拦截事件点击
			mainMenuScreen.root.catchClick = function () {
				return false;
			};

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
				time: 1,
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

			setTimeout(function () {
				mainMenu.button2.addAnimation({
					x: 110,
					opacity: 0,
					time: 1,
					replay: 'FastOut',
					canSkip: false
				});
			}, 200);

			setTimeout(function () {
				mainMenu.button3.addAnimation({
					x: 140,
					opacity: 0,
					time: 1,
					replay: 'FastOut',
					canSkip: false
				});
			}, 400);

			setTimeout(function () {
				mainMenu.button4.addAnimation({
					x: 110,
					opacity: 0,
					time: 1,
					replay: 'FastOut',
					canSkip: false
				});
			}, 600);
			
			setTimeout(function(){
				mainMenu.mainMenuLayer.display = false;
			}, 1600)
		},
		
		/**
		 * 显示配置菜单
		 */
		showConfig: function(){
			// 解除拦截事件点击
			mainMenu.configLayer.display = true;
			mainMenu.configSound.addAnimation({time: 0.8, opacity: 1, replay: 'FastIn', y: 100});
			mainMenu.configMusic.addAnimation({time: 0.7, opacity: 1, replay: 'FastIn', y: 180});
			mainMenu.configSpeed.addAnimation({time: 0.6, opacity: 1, replay: 'FastIn', y: 260});
			mainMenu.configScreen.addAnimation({time: 0.5, opacity: 1, replay: 'FastIn', y: 340});
			mainMenu.configResolution.addAnimation({time: 0.4, opacity: 1, replay: 'FastIn', y: 420});
			mainMenu.configSkip.addAnimation({time: 0.3, opacity: 1, replay: 'FastIn', y: 500});
			mainMenu.configReturn.addAnimation({time: 0.2, opacity: 1, replay: 'FastIn', y: 580});
			setTimeout(function(){
				mainMenuScreen.root.catchClick = undefined;
			}, 1000);
		},
		
		/**
		 * 隐藏配置菜单
		 */
		hideConfig: function(){
			// 拦截事件点击
			mainMenuScreen.root.catchClick = function () {
				return false;
			};
			setTimeout(function(){
				mainMenu.configReturn.addAnimation({time: 0.3, opacity: 0, replay:'FastOut', yDelta: 10});
			}, 0);
			setTimeout(function(){
				mainMenu.configSkip.addAnimation({time: 0.4, opacity: 0, replay:'FastOut', yDelta: 30});
			}, 100);
			setTimeout(function(){
				mainMenu.configResolution.addAnimation({time: 0.5, opacity: 0, replay:'FastOut', yDelta: 50});
			}, 200);
			setTimeout(function(){
				mainMenu.configScreen.addAnimation({time: 0.5, opacity: 0, replay:'FastOut', yDelta: 70});
			}, 300);
			setTimeout(function(){
				mainMenu.configSpeed.addAnimation({time: 0.6, opacity: 0, replay:'FastOut', yDelta: 90});
			}, 400);
			setTimeout(function(){
				mainMenu.configMusic.addAnimation({time: 0.6, opacity: 0, replay:'FastOut', yDelta: 110});
			}, 500);
			setTimeout(function(){
				mainMenu.configSound.addAnimation({time: 0.6, opacity: 0, replay:'FastOut', yDelta: 130});
			}, 600);
			setTimeout(function(){
				mainMenu.configLayer.display = false;
			}, 1200);
		}
	}
};

mainMenu.init();
mainMenuScreen.focus();

// 进入菜单
mainMenu.show();