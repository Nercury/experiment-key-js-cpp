/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.script to execute other scripts */

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
	
	return self;
};

w1 = MyWindow();
//w2 = MyWindow();
//w3 = MyWindow();

w1.open();
//w2.open();
//w3.open();

w1.run();
