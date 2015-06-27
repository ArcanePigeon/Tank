#include "BulletClass.h"

void BulletClass::setup(){


    bulletParam.add(bxPos.set("bxPos",9999.0,-1000000.0,1000000.0));
    bulletParam.add(byPos.set("byPos",9999.0,-1000000.0,1000000.0));
    bulletParam.add(bzPos.set("bzPos",0.0,-1000000.0,1000000.0));
    bulletParam.add(bxSpeed.set("bxSpeed",0.0,-1000000.0,1000000.0));
    bulletParam.add(bySpeed.set("bySpeed",0.0,-1000000.0,1000000.0));
    bulletParam.add(bzSpeed.set("bzSpeed",0.0,-1000000.0,1000000.0));
    bulletParam.add(brSpeed.set("brSpeed",3.5,-1000000.0,1000000.0));
    bulletParam.add(brotation.set("brotation",0.0,-1000000.0,1000000.0));
    bulletParam.add(bTimer.set("bTimer",3.5,-1000000.0,1000000.0));
    bulletParam.add(bTimerStart.set("bTimerStart",0.0,-1000000.0,1000000.0));
    bulletParam.add(shoot.set("shoot",false));
    bulletParam.add(shootk.set("shootk",0,0,1000));

    bullet.setRadius(5.9);

bullet.setPosition(99999,99999,9999);
}

void BulletClass::update(){

    if(bTimer >=0){
        bTimer -= ofGetElapsedTimef() - bTimerStart;
    }
    if(bTimer <=500 && bTimer >0){
        bullet.setPosition(10000,10000,10);
    }


    bySpeed = sin((brotation)*PI/180)*6.5;
    bxSpeed = cos((brotation)*PI/180)*6.5;

    if(bTimer > 500){
        bzPos = 13;
        byPos += bySpeed;
        bxPos += bxSpeed;
        bullet.setPosition(bxPos,byPos,bzPos);
    }

}
void BulletClass::draw(){
            bullet.draw();
}
