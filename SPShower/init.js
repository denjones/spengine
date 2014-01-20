
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

var textBox = screen.createComponent({
    type: 'textBox',
    id: 'textBox',
    backgroundColor: 0xffaaaaaa,
    width: 400,
    height: 200,
    x: 100,
    y: 50,
    paddingTop: 10,
    paddingRight: 10,
    paddingLeft: 10,
    paddingBottom: 10,
    color: 0xaaff2233,
    letterSpace: 1,
    autoHeight: true
});

screen.root.appendChild(screen.getComponentById('testCom'));
screen.root.appendChild(textBox);

textBox.text = '哈哈哈哈哈哈，测试下';

include('first.js');