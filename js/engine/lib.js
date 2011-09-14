function Js() {}
Js.prototype.log = function(o) {
	if (typeof o == 'undefined')
		js_main.textLog('[undefined]');
	else if (o === null)
		js_main.textLog('[null]');
	else if (typeof o === 'string' || typeof o === 'integer')
		js_main.textLog(o);
	else
		js_main.textLog(JSON.stringify(o));
}
Js.prototype.script = function(filename) {
	var execute_result = js_main.executeFile(filename);
	if (execute_result === true) {
		return true;
	} else {
		js_main.textLog(execute_result);
		js_main.textLog(js_main.log_separator);
		return false;
	}
}
js = new Js();