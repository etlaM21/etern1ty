#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main(int argc, char * argv[]) {

	// Check if we are on a Raspberry Pi (Linux + ARM architecture)
	#if defined(TARGET_RASPBERRY_PI) || defined(TARGET_LINUX_ARM)
		ofGLESWindowSettings settings;
		settings.glesVersion = 2;
		settings.setSize(1280, 720);
		settings.windowMode = OF_FULLSCREEN;
	#else
		ofGLWindowSettings settings;
		settings.setGLVersion(3, 2);
		settings.setSize(1280, 720);
		settings.windowMode = OF_WINDOW; // Don't force fullscreen on your laptop
	#endif

	auto window = ofCreateWindow(settings);
	auto app = make_shared<ofApp>();

	ofSetFullscreen(false);
	// ofSetupOpenGL(1024, 768, OF_FULLSCREEN);
	// Pass the arguments to a custom function in ofApp -> CMD LINE ARGUMENTS
	app->arguments.assign(argv, argv + argc);

	ofRunApp(window, app);
	// ofRunApp(window, make_shared<ofApp>());
	ofRunMainLoop();

}
