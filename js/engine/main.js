/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.script to execute other scripts */

window = new Window();
window.windowTitle = "Hello";

window.onWindowInit = function() {
	app.log("running init");
};

window.onMouseMotion = function(event) {
    app.log(event.x + ", " + event.y);
};

/*window.onKeyDown = function(event) {
	app.log("Key " + event.getVkName() + " pressed");
};*/

window.onKeyUp = function(event) {
	app.log("Key " + event.getVkName() + " released");
};

window.displayMode = window.getDesktopDisplayMode();

window.open();
window.run();
