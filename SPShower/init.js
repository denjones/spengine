
window.width = 800;
window.height = 600;

createScreen({
    id: 'testScreen',
    backgroundColor: 0xffffffff
}).focus();

screen.root.backgroundColor = 0xaaffffff;

var newCom = screen.createComponent({
    id: 'testCom',
    backgroundColor: 0xaaff1122,
    width: 100,
    height: 200,
    x: 0,
    y: 0
});

registerFont({
    file: 'data/fonts/DFPShaoNvW5-GB.ttf'
});

var textBox = screen.createComponent({
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

screen.root.appendChild(screen.getComponentById('testCom'));
screen.root.appendChild(textBox);

textBox.text = '哈哈哈哈哈哈，测试下';

include('first.js');