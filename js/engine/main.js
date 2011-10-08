/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.script to execute other scripts */

window = new Window();

js.help(Window);

window.windowTitle = "Hello";
//app.log("screen saver enabled: " + (window.screenSaverEnabled ? 'true' : 'false'));
//app.log("number of displays: " + window.numDisplays);
/*js.each(window.getDisplayModes(0), function(i, mode) {
	app.log("mode " + i + " = " + JSON.stringify(mode));
});*/

//app.log(window.getDisplayModes(0)[0]);

window.displayMode = window.getDisplayModes(0)[0];

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

window.windowSize = [300, 200];
window.inputGrabbed = false;
window.fullScreen = true;

window.run();
window.run();
