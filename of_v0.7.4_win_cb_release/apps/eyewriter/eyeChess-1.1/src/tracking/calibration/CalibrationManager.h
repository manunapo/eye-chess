#ifndef _CALIBMANGER
#define _CALIBMANGER

#include "ofMain.h"
#include "ofxXmlSettings.h"
#include "ofxControlPanel.h"
#include "ofxLeastSquares.h"
#include "CalibrationFileSaver.h"
#include "PointFitter.h"

class CalibrationManager
{

public:

    void setup();
    void setupControlPanel();
    void update();
    void updateControlPanel();
    void draw();

    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void keyPressed(int key);

    ofRectangle calibrationRectangle;

    void clear();
    void advancePosition();

    int			nDivisionsWidth;
    int			nDivisionsHeight;
    int			nPosition;

    float		xp, yp;
    int			pos;
    float		inputEnergy;

    void		start();
    void		stop();

    bool		bPreAutomatic;
    bool		bAutomatic;
    bool		bAmInAutodrive;
    float		startTime;
    float		preTimePerDot;
    float		recordTimePerDot;
    float		totalTimePerDot;
    bool		bInAutoRecording;
    bool		bRemovePointsFarFromAverage;

    float		autoPct;
    int			pt;

    ofImage		calibrationInfo;
    ofTrueTypeFont font;

    float	smoothing;
    float	menuEnergy;

    bool	bDrawCalibrationGrid;
    bool	bDrawEyeInput;
    bool	bDrawRawInput;
    bool	bDrawMapOutput;

    ofxControlPanel			panel;
    CalibrationFileSaver calibFileSaver;
    PointFitter		fitter;


};

#endif


