/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.script to execute other scripts */

js.log("hello world!");

window = new Window();
window.onWindowInit = function() {
	js.log("Window init");
};
window.run();

