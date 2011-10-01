/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.script to execute other scripts */

window = new Window();

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

