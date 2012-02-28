
var GuiWindow = function () {
    var self = new key.input.Window();

    self.windowTitle = "Hello";
    self.resizable = true;
    self.fullScreen = false;

    self.onWindowInit = function () {
        app.log("running init");
    };

    self.onMouseMotion = function (event) {
        app.log(event.x + ", " + event.y);
    };

    self.onKeyDown = function (event) {
        app.log("Key " + event.getVkName() + " pressed");
    };

    self.onKeyUp = function (event) {
        app.log("keyup");
        if (event.scanCode == key.input.ScanCode.ESCAPE)
            this.close();
        else if (event.scanCode == key.input.ScanCode.N) {
            var w = GuiWindow();
            w.open();
        }
    };

    self.displayMode = self.getDesktopDisplayMode();



    /*var viewer = new key.scene.DrawTree()
    .at([new Rotate(1, 2, 3)], new CameraPosition(), new Model())
    .at([new key.Translate(0, 5, 0)], new Model("great"))
	.add(new Model("hat"))
    ;

    var display = new key.DrawTree()
    .add(new Viewport(0, 0, 500, 400))
    .add(new Perspective(60, 1, 0.1, 500))
    .add(new CameraTransform())
    .at([new ModelIdentity()], viewer)
    ;*/

    return self;
};