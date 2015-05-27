#include "TrackingManager.h"
#include "ButtonTrigger.h"

TrackingManager::TrackingManager()
{

}

TrackingManager::~TrackingManager()
{

}

void TrackingManager::setup()
{
    IM.setup();

    setupGui();

    //--- set up tracking
    tracker.setup(IM.width, IM.height);
    minBlob		= 10*10;
    maxBlob		= 100*100;
    threshold	= 21;

    bFoundEye = false;
    eyePoint.set(0,0,0);
}

void TrackingManager::update()
{
    //--- update video/camera input
    IM.update();

    //--- eye tracking (on new frames)
    if (IM.bIsFrameNew)
    {
        trackEyes();
    }

    //--- gui
    panel.update();
    updateGui();
}



ofPoint	TrackingManager::getEyePoint()
{
    return eyePoint;
}

bool TrackingManager::bGotAnEyeThisFrame()
{
    return bFoundEye;
}

//--------------------------------------------------------------
void TrackingManager::trackEyes()
{
    tracker.update(IM.grayImage, threshold, minBlob, maxBlob, 0.5f);
    bFoundEye	= tracker.bFoundOne;
    eyePoint	= tracker.getEyePoint();
}


void TrackingManager::setupGui()
{

    panel.setup("cv panel", 700, 20, 300, 450);
    panel.addPanel("image adjustment", 1, false);
    panel.addPanel("edge fixer", 1, false);
    panel.addPanel("blob detection", 1, false);
    panel.addPanel("button settings", 1, false);

    if (IM.mode == INPUT_VIDEO)
    {
        panel.addPanel("video file settings", 1, false);
    }
    else
    {
        panel.addPanel("live video settings", 1, false);
    }

    //---- img adjust
    panel.setWhichPanel("image adjustment");
    panel.setWhichColumn(0);
    panel.addToggle("flip horizontal ", "B_RIGHT_FLIP_X", false);
    panel.addToggle("flip vertical ", "B_RIGHT_FLIP_Y", false);
    panel.addToggle("use contrast / bri", "B_USE_CONTRAST", true);
    panel.addSlider("contrast ", "CONTRAST", 0.28f, 0.0, 1.0f, false);
    panel.addSlider("brightness ", "BRIGHTNESS", -0.02f, -1.0, 3.0f, false);
    panel.addToggle("use gamma ", "B_USE_GAMMA", true);
    panel.addSlider("gamma ", "GAMMA", 0.57f, 0.01, 3.0f, false);
    panel.addSlider("threshold ", "THRESHOLD_GAZE", threshold, 0, 255, true);

    //---- blog detect
    panel.setWhichPanel("blob detection");
    panel.addToggle("use dilate", "B_USE_DILATE", true);
    panel.addSlider("dilate num ", "N_DILATIONS", 0, 0, 10, true);
    panel.addSlider("min blob","MIN_BLOB",10*10,0,5000,true);
    panel.addSlider("max blob","MAX_BLOB",100*100,0,50500,true);

    //---- tracker edges
    panel.setWhichPanel("edge fixer");
    panel.setWhichColumn(0);
    panel.addSlider("x position ", "EDGE_MASK_X", 320, 0, 640, true);
    panel.addSlider("y position ", "EDGE_MASK_Y", 240, 0, 640, true);
    panel.addSlider("inner radius ", "EDGE_MASK_INNER_RADIUS", 250, 0, 500, true);
    panel.addSlider("outer radius ", "EDGE_MASK_OUTER_RADIUS", 350, 0, 600, true);


    if (IM.mode == INPUT_VIDEO)
    {
        panel.setWhichPanel("video file settings");
        // TODO: add theo's video playing things.... [zach]
    }
    else
    {
        panel.setWhichPanel("live video settings");
        panel.addToggle("load video settings", "VIDEO_SETTINGS", false);
    }

    //---- button settings
    panel.setWhichPanel("button settings");
    panel.addSlider("button press time", "BUTTONPRESS_TIME", 5.0f, 0.5f, 30.0f, true);


    //---- load xml settings
    panel.loadSettings("settings/trackingSettings.xml");
}

void TrackingManager::updateGui()
{

    tracker.flip(  panel.getValueB("B_RIGHT_FLIP_X"),  panel.getValueB("B_RIGHT_FLIP_Y") );

    minBlob = panel.getValueI("MIN_BLOB");
    maxBlob = panel.getValueI("MAX_BLOB");

    threshold				= panel.getValueI("THRESHOLD_GAZE");

    tracker.gamma			= panel.getValueF("GAMMA");
    tracker.bUseGamma		= panel.getValueB("B_USE_GAMMA");

    tracker.contrast		= panel.getValueF("CONTRAST");
    tracker.brightness		= panel.getValueF("BRIGHTNESS");
    tracker.bUseContrast	= panel.getValueB("B_USE_CONTRAST");

    tracker.nDilations		= panel.getValueI("N_DILATIONS");
    tracker.bUseDilate		= panel.getValueB("B_USE_DILATE");

    int oldx				= tracker.edgeMaskStartPos.x;
    int oldy				= tracker.edgeMaskStartPos.y;
    int oldir				= tracker.edgeMaskInnerRadius;
    int oldor				= tracker.edgeMaskOuterRadius;

    tracker.edgeMaskStartPos.x		= panel.getValueI("EDGE_MASK_X");
    tracker.edgeMaskStartPos.y		= panel.getValueI("EDGE_MASK_Y");
    tracker.edgeMaskInnerRadius	= panel.getValueI("EDGE_MASK_INNER_RADIUS");
    tracker.edgeMaskOuterRadius	= panel.getValueI("EDGE_MASK_OUTER_RADIUS");

    if (	oldx	!= tracker.edgeMaskStartPos.x  ||
            oldy	!= tracker.edgeMaskStartPos.y  ||
            oldir	!= tracker.edgeMaskInnerRadius ||
            oldor	!= tracker.edgeMaskOuterRadius	)
    {

        tracker.calculateEdgePixels();

    }

    if (IM.mode != INPUT_VIDEO)
    {
        panel.setWhichPanel("live video settings");
        if (panel.getValueB("VIDEO_SETTINGS") == true)
        {

#ifdef TARGET_OSX
            // since macs fuck up bad fullscreen with video settings
            ofSetFullscreen(false);
#endif
            IM.vidGrabber.videoSettings();
            panel.setValueB("VIDEO_SETTINGS", false);
        }
    }
}

void TrackingManager::videoSettings()
{


    // TODO: fix this!! [zach]
    //if( !bUseVideoFiles ) ((ofVideoGrabber *)videoSource)->videoSettings();

}

void TrackingManager::draw()
{



    ofSetColor(255,255,255);


    //---------------------------------------------------------------- edge
    if (panel.getSelectedPanelName() == "image adjustment" || panel.getSelectedPanelName() == "live video settings")
    {
        ofSetColor(255,255,255);

        tracker.grayImgPreModification.draw(10,10,320,240);
        tracker.grayImg.draw(320+20, 10, 320,240);


        tracker.threshImg.draw(10,20+240,320,240);

        ofSetColor(255,255,255);
        ofFill();
        ofRect( 320+20,240+20,320, 240);

        ofEnableAlphaBlending();
        ofSetColor(255,255,255, 80);
        tracker.grayImgPreModification.draw( 320+20,240+20,320, 240);
        tracker.eyeTrackedEllipse.draw( 320+20,240+20,320, 240);

    }

    if (panel.getSelectedPanelName() == "edge fixer")
    {
        ofSetColor(255,255,255);
        tracker.edgeMaskInverted.draw(10,10, 320, 240);
        tracker.grayImg.draw(320+20, 10, 320,240);
    }


    if (panel.getSelectedPanelName() == "blob detection")
    {
        ofSetColor(255,255,255);

        tracker.grayImg.draw(10, 10, 320,240);

        tracker.threshImg.draw(10 + 10 + 320,10,320,240);
        tracker.contourFinder.draw(10 + 10 + 320,10,320,240);
    }

    ofSetColor(0, 0, 0);
    ofRect(700,530, 300,135);
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("key commands: ", 720,550);

    ofDrawBitmapString("          (f) - toggle fullscreen",			700,550+30);
    ofDrawBitmapString("     (return) - change mode",	700,550+50);
    ofDrawBitmapString("        (esc) - exit",			700,550+70);

    if (panel.getSelectedPanelName() == "button settings ")
    {
        buttonPressTime = panel.getValueF("BUTTONPRESS_TIME");
    }

    panel.draw();
}

//--------------------------------------------------------------
float TrackingManager::getButtonPressTime()
{

    return buttonPressTime;

}

//--------------------------------------------------------------
void TrackingManager::mouseDragged(int x, int y, int button)
{

    panel.mouseDragged(x, y, button);

}

//--------------------------------------------------------------
void TrackingManager::mousePressed(int x, int y, int button)
{

    panel.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void TrackingManager::mouseReleased()
{

    panel.mouseReleased();

}