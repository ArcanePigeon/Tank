#include "ofApp.h"
#include <vector>

//--------------------------------------------------------------
void ofApp::setup(){

    sun1.setPointLight();
    sun.setRadius(90);

    sun2.setPointLight();
    sun3.setRadius(90);

    bound.set(50,50,20);

    sky.setRadius(5000);

    skyimg.loadImage("bluecloud_up.jpg");
    wallimg.loadImage("wall.jpg");
    floorimg.loadImage("floor.jpg");

    Tank1.setup();
    TankGroup.add(Tank1.tankParam);
    Tank1.red = 255;
    Tank1.upk = 101;
    Tank1.downk = 100;
    Tank1.leftk = 115;
    Tank1.rightk = 102;

    Tank2.setup();
    TankGroup.add(Tank2.tankParam);
    Tank2.green = 255;
    Tank2.upk = 357;
    Tank2.downk = 359;
    Tank2.leftk = 356;
    Tank2.rightk = 358;

    Tank3.setup();
    TankGroup.add(Tank3.tankParam);
    Tank3.blue = 255;
    Tank3.upk = 105;
    Tank3.downk = 107;
    Tank3.leftk = 106;
    Tank3.rightk = 108;

    Bullet1.setup();
    BulletGroup.add(Bullet1.bulletParam);
    Bullet1.shootk = 113;

    Bullet2.setup();
    BulletGroup.add(Bullet2.bulletParam);
    Bullet2.shootk = 109;

    Bullet3.setup();
    BulletGroup.add(Bullet3.bulletParam);
    Bullet3.shootk = 121;

    reset();



}

void ofApp::reset(){
    red = false;
    green = false;
    blue = false;
    Tank1.xPos = -ms/2 + wallw;
    Tank1.yPos = -ms/2 + wallw;
    Tank1.rotation = 0;
    Tank1.explode = false;

    Tank2.xPos = +ms/2 - wallw;
    Tank2.yPos = -ms/2 + wallw;
    Tank2.rotation = 0;
    Tank2.explode = false;

    Tank3.xPos = +ms/2 - wallw;
    Tank3.yPos = +ms/2 - wallw;
    Tank3.rotation = 0;
    Tank3.explode = false;



    Bullet1.bxPos = 9999;
    Bullet1.byPos = 9999;
    Bullet1.bTimer = 0;
    Bullet1.bullet.setPosition(999,999,999);


    Bullet2.bxPos = 9999;
    Bullet2.byPos = 9999;
    Bullet2.bTimer = 0;
    Bullet2.bullet.setPosition(999,999,999);


    Bullet3.bxPos = 9999;
    Bullet3.byPos = 9999;
    Bullet3.bTimer = 0;
    Bullet3.bullet.setPosition(999,999,999);
    std::cout << "Red: " << redScore << " Green: " << greenScore << " blue: " << blueScore << std::endl;

    ofSeedRandom();

    for (int i=0; i<wallz; i++) {
        for (int j=0; j<wallz; j++) {
           distribution = ofRandom(1,3);
           if (distribution == 1) {
               MyWall var1;
               var1.x = i;
               var1.y = j;
               var1.vertical = false;
               var1.wall.set(ms/wallz,wallw,wallh);
               vec.push_back(var1);
           }
        }
    }

    for (int i=0; i<wallz; i++) {
        for (int j=0; j<wallz; j++) {
           distribution = ofRandom(1,3);
           if (distribution == 1) {
               MyWall var1;
               var1.x = i;
               var1.y = j;
               var1.vertical = true;
               var1.wall.set(wallw,ms/wallz,wallh);
               vec.push_back(var1);
           }
        }
    }


    floor.set(ms,ms,100,100,OF_PRIMITIVE_TRIANGLES);

    for (std::vector<MyWall>::iterator it = vec.begin() ; it != vec.end(); ++it) {
        if((*it).vertical == true){
            (*it).x = (*it).x * (ms/wallz + wallh*2) + ms/wallz/2 - (wallw*2.777);
            (*it).y = (*it).y * ms/wallz + ms/wallz/2;
        }else{
            (*it).x = (*it).x * ms/wallz + ms/wallz/2;
            (*it).y = (*it).y * ms/wallz + ms/wallz/2;
        }
    }



}

//--------------------------------------------------------------
void ofApp::update(){
    Tank1.update();
    Tank2.update();
    Tank3.update();

    Bullet1.update();
    Bullet2.update();
    Bullet3.update();

    if(Bullet1.shoot == true && Tank1.explode == false){
        if(Bullet1.bTimer <= 0){
            Bullet1.bTimer = 10000;
            Bullet1.bTimerStart = ofGetElapsedTimef();
            Bullet1.bxPos = Tank1.xPos+Tank1.xSpeed*15;
            Bullet1.byPos = Tank1.yPos+Tank1.ySpeed*15;
            Bullet1.brotation = Tank1.rotation;
        }
    }
    if(Bullet2.shoot == true && Tank2.explode == false){
        if(Bullet2.bTimer <= 0){
            Bullet2.bTimer = 10000;
            Bullet2.bTimerStart = ofGetElapsedTimef();
            Bullet2.bxPos = Tank2.xPos+Tank2.xSpeed*15;
            Bullet2.byPos = Tank2.yPos+Tank2.ySpeed*15;
            Bullet2.brotation = Tank2.rotation;
        }
    }
    if(Bullet3.shoot == true && Tank3.explode == false){
        if(Bullet3.bTimer <= 0){
            Bullet3.bTimer = 10000;
            Bullet3.bTimerStart = ofGetElapsedTimef();
            Bullet3.bxPos = Tank3.xPos+Tank3.xSpeed*15;
            Bullet3.byPos = Tank3.yPos+Tank3.ySpeed*15;
            Bullet3.brotation = Tank3.rotation;
        }
    }
    collide();
    tankhit();
    bulletCollide();

    if(Tank1.explode == true && Tank2.explode == true){
        reset();
        blueScore += 1;
    }else if(Tank1.explode == true && Tank3.explode == true){
        reset();
        greenScore += 1;
    }else if(Tank2.explode == true && Tank3.explode == true){
        reset();
        redScore += 1;
    }


        bound.setPosition(Tank1.xPos,Tank1.yPos,Tank1.zPos);

}

void ofApp::tankhit(){


        if(((Bullet1.bxPos+(ms/2) < Tank1.xPos +(ms/2) +25 && Bullet1.bxPos+(ms/2) > Tank1.xPos +(ms/2) -25) &&
           (Bullet1.byPos+(ms/2) < Tank1.yPos +(ms/2) +25 && Bullet1.byPos+(ms/2) > Tank1.yPos +(ms/2) -25))
           ||
           ((Bullet2.bxPos+(ms/2) < Tank1.xPos +(ms/2) +25 && Bullet2.bxPos+(ms/2) > Tank1.xPos +(ms/2) -25) &&
           (Bullet2.byPos+(ms/2) < Tank1.yPos +(ms/2) +25 && Bullet2.byPos+(ms/2) > Tank1.yPos +(ms/2) -25))
           ||
           ((Bullet3.bxPos+(ms/2) < Tank1.xPos +(ms/2) +25 && Bullet3.bxPos+(ms/2) > Tank1.xPos +(ms/2) -25) &&
           (Bullet3.byPos+(ms/2) < Tank1.yPos +(ms/2) +25 && Bullet3.byPos+(ms/2) > Tank1.yPos +(ms/2) -25))){
                Tank1.explode = true;
                std::cout << "iv been hit" << std::endl;
        }
        if(((Bullet1.bxPos+(ms/2) < Tank2.xPos +(ms/2) +25 && Bullet1.bxPos+(ms/2) > Tank2.xPos +(ms/2) -25) &&
           (Bullet1.byPos+(ms/2) < Tank2.yPos +(ms/2) +25 && Bullet1.byPos+(ms/2) > Tank2.yPos +(ms/2) -25))
           ||
           ((Bullet2.bxPos+(ms/2) < Tank2.xPos +(ms/2) +25 && Bullet2.bxPos+(ms/2) > Tank2.xPos +(ms/2) -25) &&
           (Bullet2.byPos+(ms/2) < Tank2.yPos +(ms/2) +25 && Bullet2.byPos+(ms/2) > Tank2.yPos +(ms/2) -25))
           ||
           ((Bullet3.bxPos+(ms/2) < Tank2.xPos +(ms/2) +25 && Bullet3.bxPos+(ms/2) > Tank2.xPos +(ms/2) -25) &&
           (Bullet3.byPos+(ms/2) < Tank2.yPos +(ms/2) +25 && Bullet3.byPos+(ms/2) > Tank2.yPos +(ms/2) -25))){
                Tank2.explode = true;
                std::cout << "iv been hit" << std::endl;
        }
        if(((Bullet1.bxPos+(ms/2) < Tank3.xPos +(ms/2) +25 && Bullet1.bxPos+(ms/2) > Tank3.xPos +(ms/2) -25) &&
           (Bullet1.byPos+(ms/2) < Tank3.yPos +(ms/2) +25 && Bullet1.byPos+(ms/2) > Tank3.yPos +(ms/2) -25))
           ||
           ((Bullet2.bxPos+(ms/2) < Tank3.xPos +(ms/2) +25 && Bullet2.bxPos+(ms/2) > Tank3.xPos +(ms/2) -25) &&
           (Bullet2.byPos+(ms/2) < Tank3.yPos +(ms/2) +25 && Bullet2.byPos+(ms/2) > Tank3.yPos +(ms/2) -25))
           ||
           ((Bullet3.bxPos+(ms/2) < Tank3.xPos +(ms/2) +25 && Bullet3.bxPos+(ms/2) > Tank3.xPos +(ms/2) -25) &&
           (Bullet3.byPos+(ms/2) < Tank3.yPos +(ms/2) +25 && Bullet3.byPos+(ms/2) > Tank3.yPos +(ms/2) -25))){
                Tank3.explode = true;
                std::cout << "iv been hit" << std::endl;
        }

}


void ofApp::bulletCollide(){

    for (std::vector<MyWall>::iterator it = vec.begin() ; it != vec.end(); ++it) {

        if((*it).vertical == false){
            if(
               ((((*it).x-((ms/wallz)/2)
                  < (Bullet1.bxPos+(ms/2) + 6))
               && ((Bullet1.bxPos+(ms/2) + 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet1.byPos+(ms/2) + 6))
               && ((Bullet1.byPos+(ms/2) + 6)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Bullet1.bxPos+(ms/2) - 6))
               && ((Bullet1.bxPos+(ms/2) - 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet1.byPos+(ms/2) + 6))
               && ((Bullet1.byPos+(ms/2) + 6)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                   < (Bullet1.bxPos+(ms/2) + 6))
               && ((Bullet1.bxPos+(ms/2) + 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet1.byPos+(ms/2) - 6))
               && ((Bullet1.byPos+(ms/2) - 6)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Bullet1.bxPos+(ms/2) - 6))
               && ((Bullet1.bxPos+(ms/2) - 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet1.byPos+(ms/2) - 6))
               && ((Bullet1.byPos+(ms/2) - 6)
                   < (*it).y+(wallw/2))))
               ){
                   Bullet1.brotation += 90;
                   }
            }else{
               if(
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet1.byPos+(ms/2) + 6))
               && ((Bullet1.byPos+(ms/2) + 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet1.bxPos+(ms/2) + 6))
               && ((Bullet1.bxPos+(ms/2) + 6)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet1.byPos+(ms/2) + 6))
               && ((Bullet1.byPos+(ms/2) + 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet1.bxPos+(ms/2) - 6))
               && ((Bullet1.bxPos+(ms/2) - 6)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet1.byPos+(ms/2) - 6))
               && ((Bullet1.byPos+(ms/2) - 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet1.bxPos+(ms/2) + 6))
               && ((Bullet1.bxPos+(ms/2) + 6)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet1.byPos+(ms/2) - 6))
               && ((Bullet1.byPos+(ms/2) - 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet1.bxPos+(ms/2) - 6))
               && ((Bullet1.bxPos+(ms/2) - 6)
                   < (*it).x+(wallw/2))))
               ){
                   Bullet1.brotation += 90;
            }
        }

        if((*it).vertical == false){
            if(
               ((((*it).x-((ms/wallz)/2)
                  < (Bullet2.bxPos+(ms/2) + 6))
               && ((Bullet2.bxPos+(ms/2) + 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet2.byPos+(ms/2) + 6))
               && ((Bullet2.byPos+(ms/2) + 6)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Bullet2.bxPos+(ms/2) - 6))
               && ((Bullet2.bxPos+(ms/2) - 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet2.byPos+(ms/2) + 6))
               && ((Bullet2.byPos+(ms/2) + 6)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                   < (Bullet2.bxPos+(ms/2) + 6))
               && ((Bullet2.bxPos+(ms/2) + 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet2.byPos+(ms/2) - 6))
               && ((Bullet2.byPos+(ms/2) - 6)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Bullet2.bxPos+(ms/2) - 6))
               && ((Bullet2.bxPos+(ms/2) - 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet2.byPos+(ms/2) - 6))
               && ((Bullet2.byPos+(ms/2) - 6)
                   < (*it).y+(wallw/2))))
               ){
                   Bullet2.brotation += 90;
                   }
            }else{
               if(
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet2.byPos+(ms/2) + 6))
               && ((Bullet2.byPos+(ms/2) + 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet2.bxPos+(ms/2) + 6))
               && ((Bullet2.bxPos+(ms/2) + 6)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet2.byPos+(ms/2) + 6))
               && ((Bullet2.byPos+(ms/2) + 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet2.bxPos+(ms/2) - 6))
               && ((Bullet2.bxPos+(ms/2) - 6)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet2.byPos+(ms/2) - 6))
               && ((Bullet2.byPos+(ms/2) - 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet2.bxPos+(ms/2) + 6))
               && ((Bullet2.bxPos+(ms/2) + 6)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet2.byPos+(ms/2) - 6))
               && ((Bullet2.byPos+(ms/2) - 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet2.bxPos+(ms/2) - 6))
               && ((Bullet2.bxPos+(ms/2) - 6)
                   < (*it).x+(wallw/2))))
               ){
                   Bullet2.brotation += 90;
            }
        }

        if((*it).vertical == false){
            if(
               ((((*it).x-((ms/wallz)/2)
                  < (Bullet3.bxPos+(ms/2) + 6))
               && ((Bullet3.bxPos+(ms/2) + 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet3.byPos+(ms/2) + 6))
               && ((Bullet3.byPos+(ms/2) + 6)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Bullet3.bxPos+(ms/2) - 6))
               && ((Bullet3.bxPos+(ms/2) - 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet3.byPos+(ms/2) + 6))
               && ((Bullet3.byPos+(ms/2) + 6)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                   < (Bullet3.bxPos+(ms/2) + 6))
               && ((Bullet3.bxPos+(ms/2) + 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet3.byPos+(ms/2) - 6))
               && ((Bullet3.byPos+(ms/2) - 6)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Bullet3.bxPos+(ms/2) - 6))
               && ((Bullet3.bxPos+(ms/2) - 6)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Bullet3.byPos+(ms/2) - 6))
               && ((Bullet3.byPos+(ms/2) - 6)
                   < (*it).y+(wallw/2))))
               ){
                   Bullet3.brotation += 90;
                   }
            }else{
               if(
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet3.byPos+(ms/2) + 6))
               && ((Bullet3.byPos+(ms/2) + 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet3.bxPos+(ms/2) + 6))
               && ((Bullet3.bxPos+(ms/2) + 6)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet3.byPos+(ms/2) + 6))
               && ((Bullet3.byPos+(ms/2) + 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet3.bxPos+(ms/2) - 6))
               && ((Bullet3.bxPos+(ms/2) - 6)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet3.byPos+(ms/2) - 6))
               && ((Bullet3.byPos+(ms/2) - 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet3.bxPos+(ms/2) + 6))
               && ((Bullet3.bxPos+(ms/2) + 6)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Bullet3.byPos+(ms/2) - 6))
               && ((Bullet3.byPos+(ms/2) - 6)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Bullet3.bxPos+(ms/2) - 6))
               && ((Bullet3.bxPos+(ms/2) - 6)
                   < (*it).x+(wallw/2))))
               ){
                   Bullet3.brotation += 90;
            }
        }

    }

    Bullet1.oldx = Bullet1.bxPos;
    Bullet1.oldy = Bullet1.byPos;
    Bullet1.oldz = Bullet1.bzPos;

    Bullet2.oldx = Bullet2.bxPos;
    Bullet2.oldy = Bullet2.byPos;
    Bullet2.oldz = Bullet2.bzPos;

    Bullet3.oldx = Bullet3.bxPos;
    Bullet3.oldy = Bullet3.byPos;
    Bullet3.oldz = Bullet3.bzPos;


}

void ofApp::collide(){

    for (std::vector<MyWall>::iterator it = vec.begin() ; it != vec.end(); ++it) {

        if((*it).vertical == false){
            if(
               ((((*it).x-((ms/wallz)/2)
                  < (Tank1.xPos+(ms/2) + 25))
               && ((Tank1.xPos+(ms/2) + 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank1.yPos+(ms/2) + 25))
               && ((Tank1.yPos+(ms/2) + 25)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Tank1.xPos+(ms/2) - 25))
               && ((Tank1.xPos+(ms/2) - 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank1.yPos+(ms/2) + 25))
               && ((Tank1.yPos+(ms/2) + 25)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                   < (Tank1.xPos+(ms/2) + 25))
               && ((Tank1.xPos+(ms/2) + 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank1.yPos+(ms/2) - 25))
               && ((Tank1.yPos+(ms/2) - 25)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Tank1.xPos+(ms/2) - 25))
               && ((Tank1.xPos+(ms/2) - 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank1.yPos+(ms/2) - 25))
               && ((Tank1.yPos+(ms/2) - 25)
                   < (*it).y+(wallw/2))))
               ){
                   Tank1.xPos = Tank1.oldx;
                   Tank1.yPos = Tank1.oldy;
                   Tank1.zPos = Tank1.oldz;
                   }
            }else{
               if(
               ((((*it).y-((ms/wallz)/2)
                  < (Tank1.yPos+(ms/2) + 25))
               && ((Tank1.yPos+(ms/2) + 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank1.xPos+(ms/2) + 25))
               && ((Tank1.xPos+(ms/2) + 25)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Tank1.yPos+(ms/2) + 25))
               && ((Tank1.yPos+(ms/2) + 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank1.xPos+(ms/2) - 25))
               && ((Tank1.xPos+(ms/2) - 25)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Tank1.yPos+(ms/2) - 25))
               && ((Tank1.yPos+(ms/2) - 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank1.xPos+(ms/2) + 25))
               && ((Tank1.xPos+(ms/2) + 25)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Tank1.yPos+(ms/2) - 25))
               && ((Tank1.yPos+(ms/2) - 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank1.xPos+(ms/2) - 25))
               && ((Tank1.xPos+(ms/2) - 25)
                   < (*it).x+(wallw/2))))
               ){
                   Tank1.xPos = Tank1.oldx;
                   Tank1.yPos = Tank1.oldy;
                   Tank1.zPos = Tank1.oldz;
            }
        }

        if((*it).vertical == false){
            if(
               ((((*it).x-((ms/wallz)/2)
                  < (Tank2.xPos+(ms/2) + 25))
               && ((Tank2.xPos+(ms/2) + 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank2.yPos+(ms/2) + 25))
               && ((Tank2.yPos+(ms/2) + 25)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Tank2.xPos+(ms/2) - 25))
               && ((Tank2.xPos+(ms/2) - 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank2.yPos+(ms/2) + 25))
               && ((Tank2.yPos+(ms/2) + 25)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                   < (Tank2.xPos+(ms/2) + 25))
               && ((Tank2.xPos+(ms/2) + 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank2.yPos+(ms/2) - 25))
               && ((Tank2.yPos+(ms/2) - 25)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Tank2.xPos+(ms/2) - 25))
               && ((Tank2.xPos+(ms/2) - 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank2.yPos+(ms/2) - 25))
               && ((Tank2.yPos+(ms/2) - 25)
                   < (*it).y+(wallw/2))))
               ){
                   Tank2.xPos = Tank2.oldx;
                   Tank2.yPos = Tank2.oldy;
                   Tank2.zPos = Tank2.oldz;
                   }
            }else{
               if(
               ((((*it).y-((ms/wallz)/2)
                  < (Tank2.yPos+(ms/2) + 25))
               && ((Tank2.yPos+(ms/2) + 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank2.xPos+(ms/2) + 25))
               && ((Tank2.xPos+(ms/2) + 25)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Tank2.yPos+(ms/2) + 25))
               && ((Tank2.yPos+(ms/2) + 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank2.xPos+(ms/2) - 25))
               && ((Tank2.xPos+(ms/2) - 25)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Tank2.yPos+(ms/2) - 25))
               && ((Tank2.yPos+(ms/2) - 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank2.xPos+(ms/2) + 25))
               && ((Tank2.xPos+(ms/2) + 25)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Tank2.yPos+(ms/2) - 25))
               && ((Tank2.yPos+(ms/2) - 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank2.xPos+(ms/2) - 25))
               && ((Tank2.xPos+(ms/2) - 25)
                   < (*it).x+(wallw/2))))
               ){
                   Tank2.xPos = Tank2.oldx;
                   Tank2.yPos = Tank2.oldy;
                   Tank2.zPos = Tank2.oldz;
            }
        }

        if((*it).vertical == false){
            if(
               ((((*it).x-((ms/wallz)/2)
                  < (Tank3.xPos+(ms/2) + 25))
               && ((Tank3.xPos+(ms/2) + 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank3.yPos+(ms/2) + 25))
               && ((Tank3.yPos+(ms/2) + 25)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Tank3.xPos+(ms/2) - 25))
               && ((Tank3.xPos+(ms/2) - 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank3.yPos+(ms/2) + 25))
               && ((Tank3.yPos+(ms/2) + 25)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                   < (Tank3.xPos+(ms/2) + 25))
               && ((Tank3.xPos+(ms/2) + 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank3.yPos+(ms/2) - 25))
               && ((Tank3.yPos+(ms/2) - 25)
                   < (*it).y+(wallw/2))))
               ||
               ((((*it).x-((ms/wallz)/2)
                  < (Tank3.xPos+(ms/2) - 25))
               && ((Tank3.xPos+(ms/2) - 25)
                   < (*it).x+((ms/wallz)/2)))
               && (((*it).y-(wallw/2)
                    < (Tank3.yPos+(ms/2) - 25))
               && ((Tank3.yPos+(ms/2) - 25)
                   < (*it).y+(wallw/2))))
               ){
                   Tank3.xPos = Tank3.oldx;
                   Tank3.yPos = Tank3.oldy;
                   Tank3.zPos = Tank3.oldz;
                   }
            }else{
               if(
               ((((*it).y-((ms/wallz)/2)
                  < (Tank3.yPos+(ms/2) + 25))
               && ((Tank3.yPos+(ms/2) + 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank3.xPos+(ms/2) + 25))
               && ((Tank3.xPos+(ms/2) + 25)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Tank3.yPos+(ms/2) + 25))
               && ((Tank3.yPos+(ms/2) + 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank3.xPos+(ms/2) - 25))
               && ((Tank3.xPos+(ms/2) - 25)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Tank3.yPos+(ms/2) - 25))
               && ((Tank3.yPos+(ms/2) - 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank3.xPos+(ms/2) + 25))
               && ((Tank3.xPos+(ms/2) + 25)
                   < (*it).x+(wallw/2))))
               ||
               ((((*it).y-((ms/wallz)/2)
                  < (Tank3.yPos+(ms/2) - 25))
               && ((Tank3.yPos+(ms/2) - 25)
                   < (*it).y+((ms/wallz)/2)))
               && (((*it).x-(wallw/2)
                    < (Tank3.xPos+(ms/2) - 25))
               && ((Tank3.xPos+(ms/2) - 25)
                   < (*it).x+(wallw/2))))
               ){
                   Tank3.xPos = Tank3.oldx;
                   Tank3.yPos = Tank3.oldy;
                   Tank3.zPos = Tank3.oldz;
            }
        }

    }
    Tank1.oldx = Tank1.xPos;
    Tank1.oldy = Tank1.yPos;
    Tank1.oldz = Tank1.zPos;

    Tank2.oldx = Tank2.xPos;
    Tank2.oldy = Tank2.yPos;
    Tank2.oldz = Tank2.zPos;

    Tank3.oldx = Tank3.xPos;
    Tank3.oldy = Tank3.yPos;
    Tank3.oldz = Tank3.zPos;
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofEnableLighting();
    ofSetSmoothLighting(true);
    glEnable (GL_DEPTH_TEST);

    ofColor centerColor = ofColor(255, 255, 255);
    ofColor edgeColor(250, 250, 250);
    ofBackgroundGradient(centerColor, edgeColor, OF_GRADIENT_CIRCULAR);

    camera.begin();

    sun1.enable();
    sun1.setPosition(300,0,5000);
    sun2.setPosition(300,0,5000);

    ofPushMatrix();
        float tx = ofGetWidth() / 2;
        float ty = ofGetHeight() / 2;
        ofTranslate(tx, ty);
    ofPopMatrix();

    ofPushStyle();
    skyimg.bind();
        ofSetColor(255,255,255);
        sky.draw();
    ofPopStyle();

    ofPushStyle();
    floorimg.bind();
        ofSetColor(255,255,255);
        floor.draw();
    ofPopStyle();

    sun1.disable();
    sun2.enable();

    Tank1.draw();
    //bound.draw();
    Tank2.draw();
    Tank3.draw();

    sun2.disable();
    sun1.enable();


    ofSetColor(0,0,0);
    Bullet1.draw();
    Bullet2.draw();
    Bullet3.draw();

    ofPushStyle();
    wallimg.bind();
    ofSetColor(255,255,255);

        ofTranslate(-ms/2,-ms/2);
        for (std::vector<MyWall>::iterator it = vec.begin() ; it != vec.end(); ++it) {
            ofSetColor(ofColor::white);
            (*it).wall.setPosition((*it).x,(*it).y,wallh/2);
            (*it).wall.draw();
        }

        ofTranslate(ms/2,ms/2);
    ofPopStyle();

    sun1.disable();
    camera.end();


    ofDisableLighting();
    ofSetSmoothLighting(false);
    glDisable (GL_DEPTH_TEST);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

    if(key == Tank1.upk){
        Tank1.up = true;
    }
    if(key == Tank1.downk){
        Tank1.down = true;
    }
    if(key == Tank1.leftk){
        Tank1.left = true;
    }
    if(key == Tank1.rightk){
        Tank1.right = true;
    }
    if(key == Bullet1.shootk){
        Bullet1.shoot = true;
    }






     if(key == Tank2.upk){
        Tank2.up = true;
    }
    if(key == Tank2.downk){
        Tank2.down = true;
    }
    if(key == Tank2.leftk){
        Tank2.left = true;
    }
    if(key == Tank2.rightk){
        Tank2.right = true;
    }
    if(key == Bullet2.shootk){
        Bullet2.shoot = true;
    }





     if(key == Tank3.upk){
        Tank3.up = true;
    }
    if(key == Tank3.downk){
        Tank3.down = true;
    }
    if(key == Tank3.leftk){
        Tank3.left = true;
    }
    if(key == Tank3.rightk){
        Tank3.right = true;
    }
    if(key == Bullet3.shootk){
        Bullet3.shoot = true;
    }



}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

    if(key == Tank1.upk){
        Tank1.up = false;
    }
    if(key == Tank1.downk){
        Tank1.down = false;
    }
    if(key == Tank1.leftk){
        Tank1.left = false;
    }
    if(key == Tank1.rightk){
        Tank1.right = false;
    }
    if(key == Bullet1.shootk){
        Bullet1.shoot = false;
    }






     if(key == Tank2.upk){
        Tank2.up = false;
    }
    if(key == Tank2.downk){
        Tank2.down = false;
    }
    if(key == Tank2.leftk){
        Tank2.left = false;
    }
    if(key == Tank2.rightk){
        Tank2.right = false;
    }
    if(key == Bullet2.shootk){
        Bullet2.shoot = false;
    }





     if(key == Tank3.upk){
        Tank3.up = false;
    }
    if(key == Tank3.downk){
        Tank3.down = false;
    }
    if(key == Tank3.leftk){
        Tank3.left = false;
    }
    if(key == Tank3.rightk){
        Tank3.right = false;
    }
    if(key == Bullet3.shootk){
        Bullet3.shoot = false;
    }



}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
