////////////////////////////////////////////////////////////////////////////
// Demo script of SPShower Alpha 0.8
//
// Author: Ken.J
// Date: 2012-08-19
////////////////////////////////////////////////////////////////////////////

// Setting a screen
@screen{
	name:"sicily"
};

@component{
	name:"black"
	background_color: 0xFF000000
	width:800
	height:600
	layer:1
};

// Set picture box
@picture{ name:"sicily" src:"data/images/sicily.jpg" };
@pictureBox{
	name:			"哈"
	picture:		"sicily"
	fill_mode:		"Positioning"
	position_mode:	"CenterAll"
	width:800
	height:600
	layer:2
};

// Set a component
@component{
	name : "com"
	layer : 3
	width : 728
	height : 728
	background_color : 0x00000000
	background_image : "data/images/st_01.png"
};

////////////////////////////////////////////////////////////////////////////

// Set another screen
@screen{
	name: "display"
};

// Set a text box 
@textBox{ 
	name:"text"
	layer:2
	padding:20
	background_color: 0x66FFFFFF
	width: 400
	height:300
	x:100
	y:100
	layer:5
	rotation_center_x: 100
	rotation_center_y: 100
	word_space: 0
};

// Define a font
@font{name:"yh" size:40 font:"微软雅黑"};

/////////////////////////////////////////////////////////////////////////////

// Add text to text box
@addText{
	box:"text"
	content:"大家好，欢迎使用SPShower图文演示系统Alpha0.8。"
	font:"yh"
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Add text to text box
@clearText{
	box:"text"
	content:"这里是可以显示文字的文字框。"
	font:"yh"
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Add text to text box
@clearText{
	box:"text"
	content:"这样演示可能比较单调，"
	font:"yh"
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Add text to text box
@addText{
	box:"text"
	content:"我们先添加一个背景组件吧。"
	font:"yh"
};

// Set a component
@component{
	name : "background"
	layer : 0
	width : 800
	height : 600
	background_color : 0x00000000
	background_image : "data/images/bg_01.jpg"
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Add text to text box
@addText{
	box:"text"
	content:"然后添加一个人物。"
	font:"yh"
};

// Set a component
@component{
	name : "com"
	layer : 1
	width : 728
	height : 728
	background_color : 0x00000000
	background_image : "data/images/st_01.png"
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Set a component
@component{
	name : "com"
	background_image : "data/images/st_01_01.png"
};

@animation{
	component: "text"
	x: 400
	y: 200
	width: 250
	height: 150
	background_color: 0xAAAAAAFF
	time: 2
	can_skip:true
};

@clearText{
	box:"text"
	content:"大家好，我是罗罗娜。"
	font:"yh"
};

/////////////////////////////////////////////////////////////////////////////

@waitClick;

@component{
	name : "com"
	background_image : "data/images/st_01.png"
};

@clearText{
	box:"text"
	content:"下面为大家演示图层叠加以及图像变换。"
	font:"yh"
};

@animation{
	component: "text"
	x: 20
	y: 20
	width: 400
	height: 200
	background_color: 0xAAAAAAFF
	time: 2
	can_skip:true
};

/////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"首先是图层叠加。"
	font:"yh"
};

/////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"右边这幅立绘是不包括Alpha通道的JPG。"
	font:"yh"
};

// Set a mixed picture
@picture{ name:"st_02" src:"data/images/st_02.jpg" };

// Set picture box
@pictureBox{
	name : "st"
	picture : "st_02"
	fill_mode :	"ResizeBox"
	position_mode : "Normal"
	x : 100
	y : -100
	layer : 2
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"然后叠加一幅黑白图上去。"
	font:"yh"
};

// Wait for clicking
@waitClick;

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" };

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"如果我们设置的叠加模式，就可以把两张图以某种方式混合。"
	font:"yh"
};

@waitClick;

@clearText{
	box:"text"
	content:"比如这样。"
	font:"yh"
};

// Wait for clicking
@waitClick;

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" mix_mode:"Mask"};

////////////////////////////////////////////////////////////////////////////

// Set another picture
@picture{ name:"st_03" src:"data/images/st_03.png" };

// Set picture box
@pictureBox{
	name : "st"
	picture : "st_03"
	fill_mode :	"ResizeBox"
	position_mode : "Normal"
	x : 100
	y : -100
	layer : 2
};

/////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@component{
	name : "com"
	background_image : "data/images/st_01_01.png"
};

@clearText{
	box:"text"
	content:"不好意思- -|||"
	font:"yh"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"应该是这样"
	font:"yh"
};

// Set picture box
@pictureBox{
	name : "st"
	picture : "st_02"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"除此之外，还有很多PS中的叠加样式。"
	font:"yh"
};

@component{
	name : "com"
	background_image : "data/images/st_01.png"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"比如下面这些。"
	font:"yh"
};

@picture{ name:"st_02" src:"data/images/st_02.jpg" };

////////////////////////////////////////////////////////////////////////////

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" mix_mode:"ColorBurn"};

@waitTime{time:1};

////////////////////////////////////////////////////////////////////////////

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" mix_mode:"Darken"};

@waitTime{time:1};

////////////////////////////////////////////////////////////////////////////

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" mix_mode:"Difference"};

@waitTime{time:1};

////////////////////////////////////////////////////////////////////////////

@mixPicture{ layer:1 src:"data/images/mask_st_02.jpg" mix_mode:"Mask"};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"下面演示图像变换。"
	font:"yh"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"可以从一个人变成另一个人哦。"
	font:"yh"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Switch picture with transformation
@switchPicture{
	box:"st" 
	target:"st_03"
	trans:"Fade" 
	time:5
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"不过场景只能有一个吗？"
	font:"yh"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"当然不是，我们现在换到另一个屏幕吧。"
	font:"yh"
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

@clearText{
	box:"text"
	content:"点击鼠标换屏。。。"
	font:"yh"
};

PI = 3.1415926;

// Set an animation to the component
@animation{
	component: "text"
	x: 0
	y: 0
	width: 800
	height: 200
	rotation: 2 * PI
	rotation_center_x: 0
	rotation_center_y: 0
	background_color: 0x66FFFF00
	time:4
};

@animation{
	component: "text"
	x: 30
	y: 430
	width: 740
	height: 150
	background_color: 0xAAAAAAFF
	time:4
};

////////////////////////////////////////////////////////////////////////////

// Wait for clicking
@waitClick;

// Switch the screen with transformation
@switchScreen{ target:"sicily" trans:"Fade" time:5 };

// Wait for switching
@waitTime{time:5};

////////////////////////////////////////////////////////////////////////////

// Set a text box 
@textBox{ 
	name:"text"
	layer:4
	padding:20
	x: 30
	y: 430
	width: 740
	height: 150
	background_color: 0xAAAAAAFF
	word_space:0
};

@clearText{
	box:"text"
	content:"现在已经转换到另外一个屏幕了！"
	font:"yh"
};

@component{
	name : "com"
	background_image : "data/images/st_01_01.png"
};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"现在我们来做更加有趣的事情！"
	font:"yh"
};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"为这幅风景画添加特效！"
	font:"yh"
};

@component{
	name : "com"
	background_image : "data/images/st_01.png"
};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@effect{
	component:"哈"
	effect:"Mask"
	time:5
	level:10
	effect_tex:"mask/mask_040.png"
};

@effect{
	component:"哈"
	effect:"Mask"
	time:5
	level:2
	effect_tex:"mask/mask_011.png"
};

@waitTime{time:10};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"是不是很有趣！"
	font:"yh"
};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"现在我们试下为他添加滤镜特效！"
	font:"yh"
};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"这个是所谓的圆形马赛克"
	font:"yh"
};

@effect{
	component:"哈"
	effect:"Mosaic"
	time:5
	level:2
};

@waitTime{time:5};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"我们来看看另外一种马赛克效果"
	font:"yh"
};

@effect{
	component:"哈"
	effect:"MosaicAll"
	time:5
	level:2
};

@waitTime{time:5};

////////////////////////////////////////////////////////////////////////////

@waitClick;

@clearText{
	box:"text"
	content:"除此之外还有很多风格化的滤镜效果"
	font:"yh"
};

@effect{
	component:"哈"
	effect:"Posure"
	time:3
	level:2
};

@waitTime{time:3};

////////////////////////////////////////////////////////////////////////////

@effect{
	component:"哈"
	effect:"Relievo"
	time:3
	level:2
};

@waitTime{time:3};

////////////////////////////////////////////////////////////////////////////

@effect{
	component:"哈"
	effect:"Pencil"
	time:3
	level:2
};

@waitTime{time:3};

////////////////////////////////////////////////////////////////////////////

@effect{
	component:"哈"
	effect:"Gray"
	time:3
	level:2
};

@waitTime{time:3};

////////////////////////////////////////////////////////////////////////////

@effect{
	component:"哈"
	effect:"Gauss"
	time:3
	level:2
};

@waitTime{time:3};

////////////////////////////////////////////////////////////////////////////

@clearText{
	box:"text"
	content:"演示到此结束，"
	font:"yh"
};

@addText{
	box:"text"
	content:"希望你能写出更有趣的脚本！"
	font:"yh"
};

@waitClick;

@goTo{ file:"script/main_menu.ks" }