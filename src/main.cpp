#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char * argv[]) {

	// ofGLESWindowSettings settings;
	// settings.glesVersion = 2;
	ofGLWindowSettings settings;
	settings.setGLVersion(2, 1);
	settings.setSize(1920, 1080);
	settings.windowMode = OF_FULLSCREEN;

	auto window = ofCreateWindow(settings);
	auto app = make_shared<ofApp>();

	// ofSetFullscreen(false);
	// ofSetupOpenGL(1024, 768, OF_FULLSCREEN);
	// Pass the arguments to a custom function in ofApp -> CMD LINE ARGUMENTS
	app->arguments.assign(argv, argv + argc);

	ofRunApp(window, app);
	// ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
