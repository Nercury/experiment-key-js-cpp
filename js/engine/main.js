/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.script to execute other scripts */

js.log("hello world!");

for (var i = 0; i < 50000; i++) {
	window = new Window();
	window.onWindowInit = function() {
		js.log("callback to js!");
	};
	window.run();
}

