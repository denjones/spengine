/**
 * 剧情屏幕
 * @file sicily_init.js
 * @author Ken.J
 * @date 2014-07-05
 */

var storyScreen;
if (!storyScreen) {

	// 创建屏幕
	storyScreen = ss.createScreen({
		id: 'Sicily剧情'
	});

	// 初始化组件
	var storyObj = {
		// 跳过模式
		isSkipping: true,
		// 自动模式
		isAuto: false,

		/****************************** 组件 Begin ******************************/

		/********************* 背景层 Begin *********************/
		backgroundLayer: storyScreen.createComponent({
			id: '背景',
			width: 1280,
			height: 720,
			depth: 10,
			onClick: function (e) {
				if (e.key == 0) {
					// 停止等待点击
					storyObj.skipBackground();
					if (!storyObj.dialogText.isAllDisplayed()) {
						storyObj.dialogText.next();
					} else {
						stopWaitingClick();
					}
					return false;
				} else if (e.key == 1) {
					// 显示隐藏对话框
					if(storyObj.dialogLayer.display){
						storyObj.hideDialog();
					} else {
						storyObj.showDialog();
					}
				}
			},
			onMouseScroll: function (e) {
				if (e.movementY > 0 && !storyObj.backlogLayer.display) {
					storyObj.hideDialog();
					storyObj.showBackLog();
				}
			}
		}),

		backgroundBack: storyScreen.createComponent({
			id: '背景后',
			width: 1280,
			height: 720,
			depth: 1,
			backgroundImage: 'data/images/bg_black.png'
		}),

		backgroundFront: storyScreen.createComponent({
			id: '背景前',
			width: 1280,
			height: 720,
			depth: 2,
			backgroundImage: 'data/images/bg_black.png'
		}),
		/********************* 背景层 End *********************/

		/********************* 角色层 Begin *********************/
		roleLayer: storyScreen.createComponent({
			id: '立绘',
			width: 1280,
			height: 720,
			depth: 20
		}),

		roleFront1: storyScreen.createComponent({
			id: '立绘前1',
			width: 1280,
			height: 720,
			depth: 2
		}),

		roleBack1: storyScreen.createComponent({
			id: '立绘后1',
			width: 1280,
			height: 720,
			depth: 1
		}),

		roleFront2: storyScreen.createComponent({
			id: '立绘前2',
			width: 1280,
			height: 720,
			depth: 2
		}),

		roleBack2: storyScreen.createComponent({
			id: '立绘后2',
			width: 1280,
			height: 720,
			depth: 1
		}),

		roleFront3: storyScreen.createComponent({
			id: '立绘前3',
			width: 1280,
			height: 720,
			depth: 2
		}),

		roleBack3: storyScreen.createComponent({
			id: '立绘后3',
			width: 1280,
			height: 720,
			depth: 1
		}),
		/********************* 角色层 End *********************/

		/********************* 对话框层 Begin *********************/
		dialogLayer: storyScreen.createComponent({
			id: '对话框',
			width: 1280,
			height: 180,
			y: 540,
			depth: 30,
			catchScroll: function (e) {
				if (e.y < 0) {
					// 显示履历
					// @TODO
				}
			}
		}),

		dialogBackground: storyScreen.createComponent({
			id: '对话框背景',
			width: 1220,
			height: 166,
			x: 30,
			y: 0,
			depth: 0,
			backgroundImage: 'data/images/dialog_bg.png'
		}),

		dialogText: storyScreen.createComponent({
			type: 'dialogBox',
			id: '对话框文字',
			width: 1120,
			height: 126,
			x: 80,
			y: 40,
			depth: 10,
			backgroundColor: 0x00FFFFFF,
			font: {
				size: 30,
				weight: 600,
				font: '微软雅黑'
			},
			nextLineImage: {
				src: 'data/images/dialog_next_line.png',
				row: 2,
				col: 4,
				fps: 14
			},
			nextPageImage: {
				src: 'data/images/dialog_next_page.png',
				row: 2,
				col: 4,
				fps: 14
			},
			textEffectFront: {
				type: 'TextShadow',
				texture: 'data/images/dialog_text.png',
				level: 0,
				quality: 0,
				opacity: 1,
				control: 'play'
			},
			textEffectBack: {
				type: 'TextShadow',
				texture: 'data/images/dialog_shadow.png',
				level: 2,
				quality: 10,
				opacity: 2,
				control: 'play'
			}
		}),

		dialogRoleBackground: storyScreen.createComponent({
			id: '对话框角色背景',
			width: 200,
			height: 40,
			depth: 2
			//backgroundColor: 0xDD334455 
		}),

		dialogRoleText: storyScreen.createComponent({
			type: 'textBox',
			id: '对话框角色',
			width: 200,
			height: 40,
			x: 80,
			padding: 5,
			depth: 3,
			font: {
				size: 30,
				weight: 600,
				font: '微软雅黑'
			},
			textEffectFront: {
				type: 'TextStroke',
				texture: 'data/images/dialog_shadow.png',
				level: 2,
				quality: 4,
				opacity: 1,
				control: 'play'
			},
			textEffectBack: {
				type: 'TextShadow',
				texture: 'data/images/dialog_shadow.png',
				level: 5,
				quality: 4,
				opacity: 0.9,
				control: 'play'
			}
		}),
		/********************* 对话框层 End *********************/

		/********************* 选项层 Begin *********************/
		seclectionLayer: storyScreen.createComponent({
			id: '选项框',
			width: 500,
			height: 200,
			x: 390,
			y: 200,
			display: false,
			depth: 40
		}),

		seclection1: storyScreen.createComponent({
			type: 'textBox',
			id: '选项1',
			width: 500,
			height: 40,
			y: 0,
			padding: 5,
			depth: 1,
			backgroundColor: 0xDD002244,
			font: {
				size: 30,
				weight: 600,
				font: '微软雅黑'
			}
		}),

		seclection2: storyScreen.createComponent({
			type: 'textBox',
			id: '选项2',
			width: 500,
			height: 40,
			y: 50,
			padding: 5,
			depth: 1,
			backgroundColor: 0xDD002244,
			font: {
				size: 30,
				weight: 600,
				font: '微软雅黑'
			}
		}),

		seclection3: storyScreen.createComponent({
			type: 'textBox',
			id: '选项3',
			width: 500,
			height: 40,
			y: 100,
			padding: 5,
			depth: 1,
			backgroundColor: 0xDD002244,
			font: {
				size: 30,
				weight: 600,
				font: '微软雅黑'
			}
		}),
		/********************* 选项层 End *********************/

		/********************* 功能按钮层 Begin *********************/
		buttonLayer: storyScreen.createComponent({
			id: '功能按钮',
			width: 450,
			height: 30,
			x: 871,
			y: 545,
			depth: 50,
			backgroundColor: 0x00FFFFFF
		}),

		buttonPlaySound: storyScreen.createComponent({
			id: '播放声音按钮',
			width: 26,
			height: 26,
			x: 0,
			y: 2,
			depth: 4,
			backgroundY: -26,
			backgroundImage: 'data/images/dialog_button_sound.png',
			backgroundColor: 0x00FFFFFF,
			onMouseIn: function (e) {
				this.backgroundY = 0;
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
			},
			onMouseOut: function (e) {
				this.backgroundY = -26;
			},
			onClick: function (e) {
				// @TODO 播放声音
				return false;
			}
		}),

		buttonSkip: storyScreen.createComponent({
			id: '快进按钮',
			width: 26,
			height: 26,
			x: 26,
			y: 2,
			depth: 4,
			backgroundY: -26,
			backgroundImage: 'data/images/dialog_button_skip.png',
			backgroundColor: 0x00FFFFFF,
			onMouseIn: function (e) {
				this.backgroundY = 0;
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
			},
			onMouseOut: function (e) {
				this.backgroundY = -26;
			},
			onClick: function (e) {
				// @TODO 快进
				return false;
			}
		}),

		buttonAuto: storyScreen.createComponent({
			id: '自动按钮',
			width: 26,
			height: 26,
			x: 52,
			y: 2,
			depth: 4,
			backgroundY: -26,
			backgroundImage: 'data/images/dialog_button_auto.png',
			backgroundColor: 0x00FFFFFF,
			onMouseIn: function (e) {
				this.backgroundY = 0;
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
			},
			onMouseOut: function (e) {
				this.backgroundY = -26;
			},
			onClick: function (e) {
				// @TODO 播放声音
				return false;
			}
		}),

		buttonSave: storyScreen.createComponent({
			id: '保存按钮',
			width: 40,
			height: 26,
			x: 87,
			y: 2,
			depth: 4,
			backgroundY: -26,
			backgroundImage: 'data/images/dialog_button_save.png',
			backgroundColor: 0x00FFFFFF,
			onMouseIn: function (e) {
				this.backgroundY = 0;
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
			},
			onMouseOut: function (e) {
				this.backgroundY = -26;
			},
			onClick: function (e) {
				// @TODO 播放声音
				return false;
			}
		}),

		buttonLoad: storyScreen.createComponent({
			id: '读取按钮',
			width: 40,
			height: 26,
			x: 131,
			y: 2,
			depth: 4,
			backgroundY: -26,
			backgroundImage: 'data/images/dialog_button_load.png',
			backgroundColor: 0x00FFFFFF,
			onMouseIn: function (e) {
				this.backgroundY = 0;
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
			},
			onMouseOut: function (e) {
				this.backgroundY = -26;
			},
			onClick: function (e) {
				// @TODO 播放声音
				return false;
			}
		}),

		buttonQuickSave: storyScreen.createComponent({
			id: '快速保存按钮',
			width: 58,
			height: 26,
			x: 177,
			y: 2,
			depth: 4,
			backgroundY: -26,
			backgroundImage: 'data/images/dialog_button_qsave.png',
			backgroundColor: 0x00FFFFFF,
			onMouseIn: function (e) {
				this.backgroundY = 0;
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
			},
			onMouseOut: function (e) {
				this.backgroundY = -26;
			},
			onClick: function (e) {
				// @TODO 播放声音
				return false;
			}
		}),

		buttonQuickLoad: storyScreen.createComponent({
			id: '快速读取按钮',
			width: 58,
			height: 26,
			x: 238,
			y: 2,
			depth: 4,
			backgroundY: -26,
			backgroundImage: 'data/images/dialog_button_qload.png',
			backgroundColor: 0x00FFFFFF,
			onMouseIn: function (e) {
				this.backgroundY = 0;
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
			},
			onMouseOut: function (e) {
				this.backgroundY = -26;
			},
			onClick: function (e) {
				// @TODO 播放声音
				return false;
			}
		}),

		buttonBackLog: storyScreen.createComponent({
			id: '履历按钮',
			width: 26,
			height: 26,
			x: 308,
			y: 2,
			depth: 4,
			backgroundY: -26,
			backgroundImage: 'data/images/dialog_button_blog.png',
			backgroundColor: 0x00FFFFFF,
			onMouseIn: function (e) {
				this.backgroundY = 0;
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
			},
			onMouseOut: function (e) {
				this.backgroundY = -26;
			},
			onClick: function (e) {
				// @TODO 播放声音
				return false;
			}
		}),

		buttonExit: storyScreen.createComponent({
			id: '退出按钮',
			width: 26,
			height: 26,
			x: 346,
			y: 2,
			depth: 4,
			backgroundY: -26,
			backgroundImage: 'data/images/dialog_button_close.png',
			backgroundColor: 0x00FFFFFF,
			onMouseIn: function (e) {
				this.backgroundY = 0;
				soundTrack.src = 'data/sounds/select.wav';
				soundTrack.play();
			},
			onMouseOut: function (e) {
				this.backgroundY = -26;
			},
			onClick: function (e) {
				// @TODO 播放声音
				return false;
			}
		}),
		/********************* 功能按钮层 End *********************/

		/********************* 履历层 Begin *********************/
		backlogLayer: storyScreen.createComponent({
			id: '履历',
			width: 1240,
			height: 680,
			x: 20,
			y: 20,
			depth: 60,
			display: false,
			catchClick: function (e) {
				// @TODO
				if (e.key == 1) {
					storyObj.hideBackLog();
					storyObj.showDialog();
				}
				return false;
			}
		}),

		backlogTitle: storyScreen.createComponent({
			type: 'textBox',
			id: '履历标题',
			width: 200,
			height: 40,
			paddingTop: 5,
			paddingLeft: 10,
			depth: 2,
			backgroundColor: 0xDD334455,
			text: '   履 历',
			font: {
				font: '微软雅黑',
				size: 25,
				weight: 'SemiBold'
			}
		}),

		backlogList: storyScreen.createComponent({
			type: 'scroll',
			id: '履历列表',
			width: 1240,
			height: 660,
			x: 20,
			y: 50,
			depth: 1,
			maxCount: 20,
			onMouseScroll: function (e) {
				// @TODO
				if ((this.scrollPosition == 1 || this.childComponents.length == 0) && e.movementY < 0) {
					storyObj.hideBackLog();
					storyObj.showDialog();
				} else {
					this.scrollBy(-e.movementY / 120 * 20);
				}
				return false;
			}
		}),

		backlogBackground: storyScreen.createComponent({
			id: '履历背景',
			width: 1240,
			height: 660,
			y: 20,
			depth: 0,
			backgroundColor: 0xDD002244
		}),
		/********************* 履历层 End *********************/

		/********************* 其他层 Begin *********************/
		videoLayer: storyScreen.createComponent({
			type: 'pictureBox',
			id: '视频',
			width: 1280,
			height: 720,
			depth: 70,
			display: false
		}),

		maskLayer: storyScreen.createComponent({
			id: '全屏遮挡',
			width: 1280,
			height: 720,
			depth: 254,
			display: false,
			catchMouseIn: function (e) {
				return false;
			},
			catchMouseOut: function (e) {
				return false;
			},
			catchMouseOver: function (e) {
				return false;
			},
			catchClick: function (e) {
				return false;
			},
			catchMouseScroll: function (e) {
				return false;
			}
		}),
		/********************* 其他层 End *********************/

		/****************************** 组件 End ******************************/
		
		/****************************** 方法 Begin ******************************/
		// 初始化父子关系
		init: function () {
			storyScreen.root.appendChild(storyObj.backgroundLayer);
			storyScreen.root.appendChild(storyObj.roleLayer);
			storyScreen.root.appendChild(storyObj.dialogLayer);
			storyScreen.root.appendChild(storyObj.seclectionLayer);
			storyScreen.root.appendChild(storyObj.buttonLayer);
			storyScreen.root.appendChild(storyObj.backlogLayer);
			storyScreen.root.appendChild(storyObj.videoLayer);
			storyScreen.root.appendChild(storyObj.maskLayer);

			storyObj.backgroundLayer.appendChild(storyObj.backgroundFront);
			storyObj.backgroundLayer.appendChild(storyObj.backgroundBack);

			storyObj.roleLayer.appendChild(storyObj.roleFront1);
			storyObj.roleLayer.appendChild(storyObj.roleBack1);
			storyObj.roleLayer.appendChild(storyObj.roleFront2);
			storyObj.roleLayer.appendChild(storyObj.roleBack2);
			storyObj.roleLayer.appendChild(storyObj.roleFront3);
			storyObj.roleLayer.appendChild(storyObj.roleBack3);

			storyObj.dialogLayer.appendChild(storyObj.dialogBackground);
			storyObj.dialogLayer.appendChild(storyObj.dialogText);
			storyObj.dialogLayer.appendChild(storyObj.dialogRoleBackground);
			storyObj.dialogLayer.appendChild(storyObj.dialogRoleText);

			storyObj.seclectionLayer.appendChild(storyObj.seclection1);
			storyObj.seclectionLayer.appendChild(storyObj.seclection2);
			storyObj.seclectionLayer.appendChild(storyObj.seclection3);

			storyObj.buttonLayer.appendChild(storyObj.buttonPlaySound);
			storyObj.buttonLayer.appendChild(storyObj.buttonSkip);
			storyObj.buttonLayer.appendChild(storyObj.buttonAuto);
			storyObj.buttonLayer.appendChild(storyObj.buttonSave);
			storyObj.buttonLayer.appendChild(storyObj.buttonLoad);
			storyObj.buttonLayer.appendChild(storyObj.buttonQuickSave);
			storyObj.buttonLayer.appendChild(storyObj.buttonQuickLoad);
			storyObj.buttonLayer.appendChild(storyObj.buttonBackLog);
			storyObj.buttonLayer.appendChild(storyObj.buttonExit);

			storyObj.backlogLayer.appendChild(storyObj.backlogTitle);
			storyObj.backlogLayer.appendChild(storyObj.backlogList);
			storyObj.backlogLayer.appendChild(storyObj.backlogBackground);
		},

		// 某人说某话
		say: function (e, obj) {
			if (obj instanceof String) {
				obj = {
					content: obj
				};
			}
			if (obj.role) {
				storyObj.dialogRoleText.text = obj.role;
			}
			if (obj.content) {
				if (e.read) {
					storyObj.dialogText.text = '';
					storyObj.dialogText.addText({
						text: obj.content,
						color: 0xffff5555,
						frontEffect: {}
					})
				} else {
					storyObj.dialogText.text = obj.content;
				}
			}
			storyObj.dialogText.markNextPage();

			// 添加到履历            
			var newLog = storyScreen.createComponent({
				width: 1200,
				height: 100,
				backgroundColor: 0x00FFFFFF
			});
			var logTitle = storyScreen.createComponent({
				type: 'textBox',
				width: 140,
				height: 90,
				x: 10,
				y: 5,
				backgroundColor: 0x00FFFFFF,
				text: obj.role || ''
			});
			var logContent = storyScreen.createComponent({
				type: 'textBox',
				width: 1000,
				height: 90,
				x: 160,
				y: 5,
				text: obj.content || '',
				autoHeight: true
			});
			
			newLog.appendChild(logTitle);
			newLog.appendChild(logContent);
			newLog.height = Math.max(logContent.height + 20, 40);
			storyObj.backlogList.appendChild(newLog);
		},

		// 全屏遮挡开始
		maskBegin: function (obj) {
			var time = obj && obj.time ? obj.time : 0;
			storyObj.maskLayer.opacity = 0;
			storyObj.maskLayer.display = true;
			storyObj.maskLayer.backgroundImage = obj && obj.image ? obj.image : 'data/images/bg_black.png';
			storyObj.maskLayer.addAnimation({
				time: time,
				opacity: 1
			});
		},

		// 全屏遮挡结束
		maskEnd: function (obj) {
			var time = obj && obj.time ? obj.time : 0;
			storyObj.maskLayer.addAnimation({
				time: time,
				opacity: 0
			});
			setTimeout(function () {
				storyObj.maskLayer.display = false;
			}, time);
		},

		// 显示履历
		showBackLog: function () {
			storyObj.backlogLayer.opacity = 0;
			storyObj.backlogLayer.display = true;
			storyObj.backlogLayer.addAnimation({
				time: 0.2,
				opacity: 1,
				addMode: 'merge'
			});
		},

		// 隐藏履历
		hideBackLog: function () {
			storyObj.backlogLayer.addAnimation({
				time: 0.2,
				opacity: 0,
				addMode: 'merge'
			});
			setTimeout(function () {
				storyObj.backlogLayer.display = false;
			}, 200);
		},
		
		// 显示对话框
		showDialog: function(){
			storyObj.dialogLayer.opacity = 0;
			storyObj.dialogLayer.display = true;
			storyObj.dialogLayer.addAnimation({
				time: 0.2,
				opacity: 1,
				addMode: 'merge'
			});
		},
		
		// 隐藏对话框
		hideDialog: function(){
			storyObj.dialogLayer.addAnimation({
				time: 0.2,
				opacity: 0,
				addMode: 'merge'
			});
			setTimeout(function () {
				storyObj.dialogLayer.display = false;
			}, 200);
		},

		// 换背景延时函数句柄
		backgroundHandle: null,

		// 换背景
		changeBackground: function (obj) {
			if (!obj.target) {
				return;
			}
			storyObj.skipBackground();
			obj.time = obj.time || 0;
			storyObj.backgroundBack.backgroundImage = obj.target;
			storyObj.backgroundFront.addEffect(obj);
			storyObj.backgroundHandle = setTimeout(function () {
				storyObj.backgroundFront.backgroundImage = obj.target;
				storyObj.backgroundFront.clearEffect();
			}, obj.time * 1000);
		},

		// 马上换背景
		skipBackground: function () {
			if (storyObj.backgroundHandle) {
				clearTimeout(storyObj.backgroundHandle);
				storyObj.backgroundHandle = null;
				storyObj.backgroundFront.backgroundImage = storyObj.backgroundBack.backgroundImage;
				storyObj.backgroundFront.clearEffect();
			}
		},

		// 抖
		shake: function () {

		},

		// 等待对话框（队列函数）
		waitDialog: function (e) {
			if (!storyObj.dialogText.isAllDisplayed()) {
				e.repeat = true;
				return;
			}
		},

		// 开启跳过
		skipOn: function () {
			storyObj.isSkipping = true;
			storyObj.isAuto = false;
		},

		// 关闭跳过
		skipOff: function () {
			storyObj.isSkipping = false;
		},

		// 开启自动模式
		autoOn: function () {
			storyObj.isAuto = true;
			storyObj.isSkipping = false;
		},

		// 关闭自动模式
		autoOff: function () {
			storyObj.isAuto = false;
		},

		// 等待对话框和之后的点击（队列函数）
		waitDialogAndClick: function (e) {
			// 跳过全部及跳过已读
			if (storyObj.skipOn) {
				if (ss.sysVar.skipMode == 'all' || (ss.sysVar.skipMode == 'read' && e.read)) {
					storyObj.dialogText.skip();
					return;
				}
			}
			if (!storyObj.dialogText.isAllDisplayed()) {
				e.repeat = true;
				return;
			}
			waitClick(e);
		}
		/****************************** 方法 End ******************************/
	}

	storyObj.init();
}