js_main.log_separator = '--------------------------------------------------------------------------';
js_main.lib_result = js_main.executeFile('engine/lib.js');
if (js_main.lib_result !== true) { js_main.textLog(js_main.lib_result); js_main.textLog(js_main.log_separator); }

js.log("hello world!");
js.log(5);
js.log({
	a:15,
	b: "Hello"
});