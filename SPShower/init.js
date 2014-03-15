
var ss = process.binding('speshow');

PI = 3.1415926;

ss.window.width = 800;
ss.window.height = 600;

ss.createScreen({
    id: 'testScreen',
    backgroundColor: 0xff000000
}).focus();

ss.screen.root.backgroundColor = 0xaaffffff;

var newCom = ss.screen.createComponent({
    id: 'testCom',
    backgroundColor: 0xff000000,
    width: 100,
    height: 200,
    x: 0,
    y: 0
});

ss.registerFont({
    file: 'data/fonts/DFPShaoNvW5-GB.ttf'
});

var textBox = ss.screen.createComponent({
    type: 'dialogBox',
    id: 'textBox',
    backgroundColor: 0x00ffffff,
    width: 400,
    height: 200,
    x: 100,
    y: 50,
    paddingTop: 10,
    paddingRight: 10,
    paddingLeft: 10,
    paddingBottom: 10,
    color: 0xffffffff,
    letterSpace: 1,
    autoHeight: true,
    font: {
        size: 20,
        weight: 500,
        font: '华康少女文字W5(P)'
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
        opacity: 1,
        control: 'play'
    }
});

var pictureBox = ss.screen.createComponent({
    type: 'pictureBox',
    id: 'pictureBox',
    backgroundColor: 0xdd000000,
    width: 1280,
    height: 720
});

var scroll = ss.screen.createComponent({
    type: 'scroll',
    id: 'scroll',
    backgroundColor: 0x22eeffdd,
    depth: 10,
    width: 1280,
    height: 720,
    onClick: function(e) {
        console.log(JSON.stringify(e));
        this.backgroundColor += 0x11; 
    }
});

scroll.addEffect({
    type:'Mask',
    texture: 'mask/mask_123.png',
    level:2,
    time:3,
    addMode:"Skip"
});

scroll.addAnimation({
    xDelta: 200,
    yDelta: 100,
    time: 5
});

var video = ss.createVideo({
    id: 'video',
    src: 'data/videos/openning.mp4'
});

var particleSystem = ss.createParticleSystem({
    id: 'ps',
    tex: { src: 'data/images/snow.png' },
    bornXMin: 0,
    bornXMax: 1280,
    bornYMin: 721,
    bornYMax: 722,
    liveXMin: -2,
    liveYMin: -2,
    liveXMax: 1282,
    liveYMax: 722,
    liveTime: 5,
    shootVelocityMin: 100,
    shootVelocityMax: 200,
    shootAngleMin: PI + PI / 6 * 2,
    shootAngleMax: PI + PI / 6 * 5,
    shootRate: 20,
    accelerationX: 0,
    accelerationY: 0,
    fadeTime: 1,
    scaleMax: 1,
    scaleMin: 0.5,
    scaleRateMin: -0.5,
    scaleRateMax: 0,
    countMax: 300,
    color: 0xf9ffffff,
    width: 1280,
    height: 720,
    specialRotation: true,
    rotateMax: 0,
    rotateMin: 0,
    rotateRateMin: 0,
    rotateRateMax: 0
});

pictureBox.setPicture({
    particleSystem: particleSystem
});

for (var i = 0; i < 100; i++) {
    scroll.appendChild(ss.screen.createComponent({
        type: 'textBox',
        backgroundColor: 0xffeeffdd,
        autoHeight: true,
        width: 300,
        color: 0xff000000,
        text: '测试' + i
    }));
}

ss.screen.root.appendChild(ss.screen.getComponentById('testCom'));
ss.screen.root.appendChild(pictureBox);
ss.screen.root.appendChild(textBox);
ss.screen.root.appendChild(scroll);

var track = ss.createTrack({
    id: 'track',
    src: 'data/sounds/bgm01.ogg'
});



textBox.text = '哈哈哈哈哈哈，测试下';

track.play();
video.play();
particleSystem.play();

ss.include('first.js');