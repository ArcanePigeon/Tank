#ifndef BULLETCLASS_H
#define BULLETCLASS_H

#include "ofMain.h"

class BulletClass
{
    public:
        void setup();
        void update();
        void draw();



        ofParameterGroup bulletParam;
        ofParameter<float> bxPos;
        ofParameter<float> byPos;
        ofParameter<float> bzPos;
        ofParameter<float> bxSpeed;
        ofParameter<float> bySpeed;
        ofParameter<float> bzSpeed;
        ofParameter<float> brSpeed;
        ofParameter<float> brotation;
        ofParameter<float> bTimer;
        ofParameter<float> bTimerStart;
        ofParameter<bool> shoot;
        ofParameter<int> shootk;

        ofSpherePrimitive bullet;

	int oldx;
	int oldy;
	int oldz;


};

#endif // BULLETCLASS_H
