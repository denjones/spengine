/**
 * 剧本01
 */

$tag('序2');
musicTrack.stop();


$(function(e){
	musicTrack.src = 'data/sounds/bgm12.ogg';
	musicTrack.play();
})
$(function(e){
	storyObj.changeBackground({target: 'data/images/bg_black.png', type: 'Mask', effectTex: 'mask/mask_040.png', time: 0, quality: 3});
});
$(function(e){
	waitClick(e);
});
$(function(e){
	storyObj.say({role: '', content: '最初的相遇——\n金色。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});
$(function(e){
	storyObj.changeBackground({target: 'data/images/bg_white.png', type: 'Mask', effectTex: 'mask/mask_003.png', time: 1, quality: 3});
});
$(function(e){
	waitTimeOrClick(1000, e);
});
$(function(e){
	storyObj.say({role: '', content: '我和一个人手牵手走在一条平时没有走过的路，顺着牵着的手，我的视线逐渐抬高。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});
$(function(e){
	storyObj.say({role: '', content: '那个人包裹在一片金色之中。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});
$(function(e){
	storyObj.say({role: '', content: '那时的她美丽吗，还是可爱呢？'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});
$(function(e){
	storyObj.say({role: '', content: '或者跟之后我的记忆里那个人一模一样吗……'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});
$(function(e){
	storyObj.say({role: '', content: '我想不起来了，这份记忆并非是被抹除了。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});
$(function(e){
	storyObj.say({role: '', content: '只是当时的我太小了，单纯的遗忘了她的容貌。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});
$(function(e){
	storyObj.say({role: '', content: '唯一清晰的记忆，只有那还是小小的我拥有的——'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});
$(function(e){
	storyObj.say({role: '', content: '那小小的幸福而已。'});
});
$(function(e){
	storyObj.waitDialogAndClick(e);
});
$(function(e){
	storyObj.say({role: '', content: '因为看到了从未看过的景象而欣喜。'});
});