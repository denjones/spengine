/**
 * 剧本01
 */

$tag('序1');

$(function(e){
	storyObj.switchBGM('data/sounds/bgm12.ogg');
	storyObj.changeBackground({target: 'data/images/bg_black.png', type: 'Mask', texture: 'mask/mask_040.png', time: 0, quality: 3, control: 'play'});
	storyObj.say(e, {role: '', content: '最初的相遇——\n纯白。'});
});
$(function(e){	storyObj.waitDialogAndClick(e); });

$(function(e){	storyObj.changeBackground({target: 'data/images/bg_white.png', type: 'Mask', texture: 'mask/mask_003.png', time: 1, quality: 3, control: 'play'}); });
$(function(e){	waitTimeOrClick(1000, e); });

$(function(e){	storyObj.say(e, {role: '', content: '我和她手牵手走在陌生的路上，\n顺着牵着的手，我的视线逐渐抬高。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '那个人包裹在一片纯白的光辉之中。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '那时的她美丽吗，还是可爱呢？'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '我想不起来了。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '这份记忆并非是被抹除了，只是单纯的遗忘了她的容貌。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '唯一清晰的记忆，只有那小小的温暖而幸福的感觉而已。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '因为看到了从未看过的景象而欣喜。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '因为她慈祥的笑容而温馨。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '也因为随之而来的分别而失落。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '但那时的我却未意识到，这次相遇，决定了我的一生……'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });

$(function(e){	storyObj.say(e, {role: '', content: '如今，伏在透明的试验台前，看着她逐渐睁开的双眼。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '早应忘记的记忆却随之涌现出来。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '此刻的我才意识到——'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '她比我更加的难过，她的悲伤远远超出了我的想象。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '既是第一次相遇，也是最后一次离别。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '?', content: '能够再次遇见你……'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '?', content: '感谢你……'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '?', content: '但正因为如此……'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '', content: '脑海里渐渐的感觉有些僵硬，不断闪回的记忆，只剩下几个模糊的碎片，以及几句断断续续的话语。'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.say(e, {role: '?', content: '请忘掉我吧……'}); });
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){
	storyObj.changeBackground({target: 'data/images/bg_black.png', type: 'Mask', texture: 'mask/mask_040.png', time: 3, quality: 3, control: 'play'});
	storyObj.say(e, {role: ' ', content: '悲伤与喜悦交加，黑暗将我的视线带走。'});
});
$(function(e){	storyObj.waitDialogAndClick(e); });
$(function(e){	storyObj.maskBegin({time: 3}); });
$(function(e){	waitTime(3000, e); });

$(function(e){
	musicTrack.stop();
	ss.goto({file: 'script/sicily_02.js'});
});
