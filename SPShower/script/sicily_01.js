/**
 * 剧本01
 */

$tag('序1');

$(function(e){
	storyObj.switchBGM('data/sounds/bgm12.ogg');
	storyObj.changeBackground({target: 'data/images/bg_black.png', type: 'Mask', texture: 'mask/mask_040.png', time: 0, quality: 3, control: 'play'});
	storyObj.say(e, {role: '', content: '最初的相遇——\n金色。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.changeBackground({target: 'data/images/bg_white.png', type: 'Mask', texture: 'mask/mask_003.png', time: 1, quality: 3, control: 'play'});
});
$(function(e){
	waitTimeOrClick(1000, e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '我和一个人手牵手走在一条平时没有走过的路。\n顺着牵着的手，我的视线逐渐抬高。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '那个人包裹在一片金色之中。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '那时的她美丽吗，还是可爱呢？'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '或者跟之后我的记忆里那个人一模一样吗……'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '我想不起来了，这份记忆并非是被抹除了。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '只是当时的我太小了，单纯的遗忘了她的容貌。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '唯一清晰的记忆，只有那还是小小的我拥有的——'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '那小小的幸福而已。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '因为看到了从未看过的景象而欣喜。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '因为能够与她相遇而雀跃不已。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '也因为随之而来的分别而遗憾不已。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '但那时的我却未意识到……'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '站在试验台前，看着那个人逐渐睁开的双眼。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '早已消失的记忆也随之涌现出来。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '不仅是很久之前消失的记忆，就连跟她最初的记忆也依依浮现。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '此刻的我才意识到——'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '她比我更加的难过，她的悲伤远远超出了我的想象。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '', content: '第一次的相遇，最后一次的离别。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '?', content: '能够再次遇见你……'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '?', content: '感谢你……'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '?', content: '但正因为如此……'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: ' ', content: '脑海里渐渐的感觉有些僵硬，不断闪回的记忆，只剩下几个模糊的碎片，以及几句断断续续的话语。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.say(e, {role: '?', content: '请忘掉我吧……'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.changeBackground({target: 'data/images/bg_black.png', type: 'Mask', texture: 'mask/mask_040.png', time: 3, quality: 3, control: 'play'});
	storyObj.say(e, {role: ' ', content: '黑色将我的视线带走。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});


$(function(e){
	storyObj.maskBegin({time: 3});
});
$(function(e){
	waitTime(3000, e);
});


$(function(e){
	musicTrack.stop();
	ss.goto({file: 'script/sicily_02.js'});
});
