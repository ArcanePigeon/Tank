#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofx3DModelLoader.h"
#include "TankClass.h"
#include "BulletClass.h"
#include <vector>

class MyWall {
    public:
        int x;
        int y;
        bool vertical;
        ofBoxPrimitive wall;
};

class ofApp : public ofBaseApp{
	public:

	void setup();
	void update();
	void draw();
	void collide();
	void bulletCollide();
	void tankhit();
	void reset();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);


    ofEasyCam camera;
    ofLight sun1;
    ofLight sun2;

    float sunx = 0;
    float suny = 0;
    float sunz = 0;
    float xSpeed = 0;
    float ySpeed = 0;
    float zSpeed = 0;
    float rotation = 0;
    int distribution;

    ofParameterGroup TankGroup;
    TankClass Tank1;
    TankClass Tank2;
    TankClass Tank3;

    ofBoxPrimitive bound;

    ofParameterGroup BulletGroup;
    BulletClass Bullet1;
    BulletClass Bullet2;
    BulletClass Bullet3;

    ofPlanePrimitive floor;
    ofSpherePrimitive sun;
    ofSpherePrimitive sun3;
    ofBoxPrimitive wall1;
    ofBoxPrimitive wall2;
    ofBoxPrimitive wall3;
    ofBoxPrimitive wall4;

    ofSpherePrimitive sky;
    ofTexture skytex;
    ofTexture walltex;
    ofTexture floortex;

    ofImage skyimg;
    ofImage wallimg;
    ofImage floorimg;

    unsigned char pixels1[512*512*4];
    unsigned char pixels2[512*512*4];
    unsigned char pixels3[512*512*4];

    int ms = 4000;
    int wallz = 10;
    int wallh = 26;
    int wallw = 60;

    int redScore = 0;
    int blueScore = 0;
    int greenScore = 0;

    bool red = false;
    bool green = false;
    bool blue = false;

    std::vector<MyWall> vec;


};

