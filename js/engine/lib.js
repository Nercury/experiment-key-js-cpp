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
		js_main.textLog(js_main_log_separator);
		return false;
	}
}
Js.prototype.man = function(obj) {
	var fields = obj.__fields;
	if (!fields)
		return "Object has no documentation";
	var str = '';
	for (var i = 0; i < fields.length; i++) {
		var info = obj[fields[i]];
		if (info.field == 'property') {
			str += "\n" + info.type + ' ' + fields[i] + ' (' + (info.read_only == '1' ? 'get' : 'get, set') + ')';
		} else if (info.field == 'method') {
			str += "\n" + info.return_type + ' ' + fields[i] + info.parameters;
		}
		str += "\n" + info.doc + "\n";
	}
	return str;
}
Js.prototype.help = function(obj) {
	return Js.prototype.log(Js.prototype.man(obj));
}
js = new Js();

function App() 
{
	this.config = JSON.parse(js_main_config_contents);
	this.nativePath = js_main_app_path;
	this.pathSeparator = js_main_app_path_separator;
}
App.prototype.criticalMessage = function(title, text) {
	return js_main.criticalMessage(title, text);
}
App.prototype.kill = function() {
	return js_main.terminateApp();
}

app = new App();