/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.script to execute other scripts */

function key() {}
key.DrawList = function () {
}
key.DrawList.prototype.at = function () {
    return this;
};
key.DrawList.prototype.add = function () {
    return this;
};
key.Translate = function () {
}
key.Rotate = function () {
}
key.Camera = function () {
}
key.Model = function () {
}
key.Viewport = function () {
}
key.Perspective = function () {
}
key.ModelIdentity = function () {
}

var MyWindow = function() {
	var self = new Window();

	self.windowTitle = "Hello";
	
	self.onWindowInit = function() {
		app.log("running init");
	};
	
	self.onMouseMotion = function(event) {
		//app.log(event.x + ", " + event.y);
	};
	
	self.onWindowClose = function() {
		return true;
	};

	self.onKeyDown = function(event) {
		app.log("Key " + event.getVkName() + " pressed");
	};

	self.onKeyUp = function(event) {
		if (event.scanCode == ScanCode.ESCAPE)
			this.close();
		else if (event.scanCode == ScanCode.N)
		{
			var w = MyWindow();
			w.open();
		}
	};	

	self.displayMode = self.getDesktopDisplayMode();

	var viewer = new key.DrawList()
        .at([new key.Translate(5, 20, 0), new key.Rotate(1, 2, 3)], new key.Camera())
        .at([new key.Translate(0, 5, 0)], new key.Model("great"))
	    .add(new key.Model("hat"));

	self.displayList = new key.DrawList()
        .add(new key.Viewport(0, 0, 500, 400))
        .add(new key.Perspective(60, 1, 0.1, 500))
        .at([new key.ModelIdentity()], viewer);

	return self;
};

w1 = MyWindow();
//w2 = MyWindow();
//w3 = MyWindow();

w1.open();
//w2.open();
//w3.open();

w1.run();
