﻿/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.script to execute other scripts */

var Translate = function () { };
var Rotate = function () { };
var Camera = function () { };
var Model = function () { };
var Viewport = function () { };
var Perspective = function () { };
var ModelIdentity = function () { };

var MyWindow = function() {
	var self = new Window();

	self.windowTitle = "Hello";
	
	self.onWindowInit = function() {
		app.log("running init");
	};
	
	self.onMouseMotion = function(event) {
		//app.log(event.x + ", " + event.y);
	};
	
	self.onKeyDown = function(event) {
		app.log("Key " + event.getVkName() + " pressed");
	};

	self.onKeyUp = function(event) {
		if (event.scanCode == ScanCode.ESCAPE)
			this.close();
		else if (event.scanCode == ScanCode.N) {
			var w = MyWindow();
			w.open();
		}
	};

	self.displayMode = self.getDesktopDisplayMode();

	for (var i = 0; i < 50000; i++) {
	    var viewer = new DrawList()
        .at([new Translate(5, 20, 0), new Rotate(1, 2, 3)], new Camera(), new Model())
        .at([new Translate(0, 5, 0)], new Model("great"))
	    .add(new Model("hat"))
        ;

	    var display = new DrawList()
        .add(new Viewport(0, 0, 500, 400))
        .add(new Perspective(60, 1, 0.1, 500))
        .at([new ModelIdentity()], viewer)
        ;
	}

	return self;
};

w1 = MyWindow();
w1.open();
w1.run();
