/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.script to execute other scripts */

window = new Window();
window.windowTitle = "Hello";

window.onWindowInit = function() {
	app.log("running init");
};

window.onMouseMotion = function(event) {
    app.log(event.xRel + ", " + event.yRel);
};

window.displayMode = window.getDesktopDisplayMode();
window.fullScreen = false;
window.open();

logWindow = new Window();
logWindow.windowTitle = "Log window";

logWindow.resizable = false;
logWindow.open();

window.run();

logWindow.open();
logWindow.run();
