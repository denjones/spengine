////////////////////////////////////////////////////////////////////////////
// Demo script of SpeShow Beta 0.8.6
// SpsShow 0.8.6 演示脚本
// Sicily 零与一的幻想 预览版
//
// Author: Ken.J
// Date: 2013-06-07
////////////////////////////////////////////////////////////////////////////

// 履历出现
@component{ name:"履历按钮" background_y:-26}
@component{	name:"履历" transparency:0 display:"unhidden"}
@list{ name:"履历列表" scroll_position:1 }
@animation{ component:"履历" transparency:1 time:0.3}
@waitTime{ time:0.3 }