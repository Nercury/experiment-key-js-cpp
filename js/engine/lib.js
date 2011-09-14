function Js() 
{
	this.config = JSON.parse(js_main_config_contents);
	this.app = {
		nativePath : js_main_app_path,
		pathSeparator : js_main_app_path_separator
	};
}
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
		js_main.textLog(js_main_log_separator);
		return false;
	}
}
js = new Js();