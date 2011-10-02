/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.script to execute other scripts */

window = new Window();

js.help(Window);

window.windowTitle = "Hello";
app.log("screen saver enabled: " + (window.screenSaverEnabled ? 'true' : 'false'));
app.log("number of displays: " + window.numDisplays);

window.onKeyUp = function(code) {
	
};
window.onKeyDown = function(code) {
	
};
window.onMouseMove = function(code) {
	
};
window.onMouseUp = function(code) {
	
};
window.onMouseDown = function(code) {
	
};

window.onWindowInit = function() {
	app.log("running init");
};

window.run();

