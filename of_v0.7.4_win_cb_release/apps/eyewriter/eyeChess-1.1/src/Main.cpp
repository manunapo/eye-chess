#include "ofMain.h"
#include "TestApp.h"
#include "ofAppGlutWindow.h"

//========================================================================
int main( )
{

    ofAppGlutWindow window;
    ofSetupOpenGL(&window, 1100,800, OF_WINDOW);			// <-------- setup the GL context

    // this kicks off the running of my app
    // can be OF_WINDOW or OF_FULLSCREEN
    // pass in width and height too:
    ofRunApp( new TestApp());

}
