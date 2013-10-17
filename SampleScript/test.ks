// This is a test script file
// Here will test all kscript statements

// Chinese variable testing...
变量 = "我是变量";

if(b == 0)
{
	b = 10;
}

for a = 1 to 10{
	b /= a;
}

a = 100 * 2;

theNumber = a;

//@include("test_include.ks", true, true);

@显示{
	值: 变量
	头: "变量值：\n"
};