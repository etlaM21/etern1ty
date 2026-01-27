#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char * argv[]) {

#ifdef OF_TARGET_OPENGLES
	ofGLESWindowSettings settings;
	settings.glesVersion=2;
#else
	ofGLWindowSettings settings;
	settings.setGLVersion(3,2);
#endif

	auto window = ofCreateWindow(settings);
	auto app = make_shared<ofApp>();

	ofSetFullscreen(false);
	// ofSetupOpenGL(1024, 768, OF_FULLSCREEN);
	// Pass the arguments to a custom function in your ofApp
	app->arguments.assign(argv, argv + argc);

	ofRunApp(window, app);
	// ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
