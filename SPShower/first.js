var callback = function () {
    newCom.x += 10;
    textBox.addText('哈');
    scroll.scrollBy(10);
    if (newCom.x < 1000) {
        clearTimeout(callbackHandle);
        callbackHandle = setTimeout(callback, 16);
    } else {
        ss.window.resize(1280, 720);
        ss.window.title = JSON.stringify(track);
        track.stop();
        particleSystem.pause();
    }
};

var callback2 = function () {
    ss.screen.backgroundColor = ss.screen.backgroundColor - 1;
    clearTimeout(callbackHandle2);
    callbackHandle2 = setTimeout(callback2, 10);
};

var callbackHandle = setTimeout(callback, 16);
var callbackHandle2 = setTimeout(callback2, 10);