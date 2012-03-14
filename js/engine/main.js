/* load main lib */
{ var r = js_main.executeFile('engine/lib.js'); if (r !== true) js_main.textLog(r);}
/* end load main lib, use js.run to execute other scripts */

app.log("Hello World!");

js.use('gui/GuiWindow.js');

list = new key.render.RenderList();
js.help(key.render.RenderList);

list.append(new key.render.RenderList(), { a: 15 }, new key.scene.Translate());

w1 = GuiWindow();
w1.open();
w1.run();

