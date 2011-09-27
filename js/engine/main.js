/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.script to execute other scripts */

js.log("hello world!");

window = new Window();
window.windowTitle = "Hello World";

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

window.renderDevice = window.allRenderDevices[0];
window.run();

