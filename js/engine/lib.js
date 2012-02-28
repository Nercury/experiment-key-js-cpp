function Js() {
    this.class2type = {};
    this.usedScripts = {};
	var class2type_items = "Boolean Number String Function Array Date RegExp Object".split(" ");
	for (var i = 0; i < class2type_items.length; i++) {
		var name = class2type_items[i];
		this.class2type[ "[object " + name + "]" ] = name.toLowerCase();
	}
	// Check for digits
	this.rdigit = /\d/
}

/**
    Run another javascript file.
*/
Js.prototype.run = function(filename) {
	var execute_result = js_main.executeFile(filename);
	if (execute_result === true) {
		return true;
	} else {
		js_main.textLog(execute_result);
		js_main.textLog(js_main_log_separator);
		return false;
	}
}

/**
    Run another javascript file once.
*/
Js.prototype.use = function (filename) {
    if (this.usedScripts.hasOwnProperty(filename)) {
        return true;
    }
    this.usedScripts[filename] = true;
    return this.run(filename);
}

/**
    Get a type of javascript object.
*/
Js.prototype.typeOf = function(obj){
    return Object.prototype.toString.call(obj).match(/^\[object (.*)\]$/)[1];
}

/**
    Get a manual for key engine object.
*/
Js.prototype.man = function(obj, finalLookup) {
	var fields = obj.__fields;
	var str = '';
	if (!fields && finalLookup !== true) {
		var objType = js.typeOf(obj);
		str = objType + " object";
		str += "\n";
		eval("str += js.man(" + objType + ", true);");
	} else {
		for (var i = 0; i < fields.length; i++) {
			var info = obj["reflect__" + fields[i]];
			if (info.field == 'property') {
				str += "\n" + info.type + ' ' + fields[i] + ' (' + (info.read_only == '1' ? 'get' : 'get, set') + ')';
			} else if (info.field == 'method') {
				str += "\n" + info.return_type + ' ' + fields[i] + info.parameters;
			} else if (info.field == 'static enum') {
				str += "\nstatic " + info.return_type + ' ' + fields[i];
			}
			str += (info.doc == "" ? "" : "\n" + info.doc + "\n");
		}
	}
	return str;
}

/**
    Print help for key engine object: for example, js.help(key.input.Window)
*/
Js.prototype.help = function(obj) {
	return app.log(js.man(obj));
}

/**
    Iterate each element of something. Works the same as jQuery.each, because it is actually the same.
*/
Js.prototype.each = function( object, callback, args ) {
	var name, i = 0,
		length = object.length,
		isObj = length === undefined || js.isFunction( object );

	// A special, fast, case for the most common use of each
	if ( isObj ) {
		for ( name in object ) {
			if ( callback.call( object[ name ], name, object[ name ] ) === false ) {
				break;
			}
		}
	} else {
		for ( ; i < length; ) {
			if ( callback.call( object[ i ], i, object[ i++ ] ) === false ) {
				break;
			}
		}
	}

	return object;
};

/**
    Get object type.
*/
Js.prototype.type = function( obj ) {
	return obj == null ?
		String( obj ) :
		this.class2type[ Object.prototype.toString.call(obj) ] || "object";
};

/**
    Check if something is a function.
*/
Js.prototype.isFunction = function( obj ) {
	return js.type(obj) === "function";
};

/**
    Check if something is an array.
*/
Js.prototype.isArray = Array.isArray || function( obj ) {
	return js.type(obj) === "array";
};

/**
    Check if something is Not a Number
*/
Js.prototype.isNaN = function( obj ) {
	return obj == null || !this.rdigit.test( obj ) || isNaN( obj );
};
js = new Js();

function App() 
{
	this.nativePath = js_main_app_path;
	this.pathSeparator = js_main_app_path_separator;
}

/**
    Output critical message: usefull if you want to scare bejeezus out of your application user.
*/
App.prototype.criticalMessage = function(title, text) {
	return js_main.criticalMessage(title, text);
}

/**
    Kill the app right now, without cleaning anything up. Usefull if you want to get away quick after scaring your user.
*/
App.prototype.kill = function() {
	return js_main.terminateApp();
}

/**
    Print something to console.
*/
App.prototype.log = function(o) {
	if (typeof o == 'undefined')
		js_main.textLog('[undefined]');
	else if (o === null)
		js_main.textLog('[null]');
	else if (typeof o === 'string' || typeof o === 'integer')
		js_main.textLog(o);
	else
		js_main.textLog(JSON.stringify(o));
}

app = new App();