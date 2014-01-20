var callback = function () {
    newCom.x += 10;
    textBox.addText('哈');
    if (newCom.x < 1000) {
        clearTimeout(callbackHandle);
        callbackHandle = setTimeout(callback, 16);
    } else {
        window.width = 1280;
        window.height = 720;
        window.title = JSON.stringify(global);
    }
};

var callback2 = function () {
    screen.backgroundColor = screen.backgroundColor - 1;
    clearTimeout(callbackHandle2);
    callbackHandle2 = setTimeout(callback2, 10);
};

var callbackHandle = setTimeout(callback, 16);
var callbackHandle2 = setTimeout(callback2, 10);