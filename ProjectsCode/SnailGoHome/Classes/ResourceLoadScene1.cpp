#include "ResourceLoadScene1.h"

 Scene *ResourceLoadScene1::createScene()
 {
	 auto scene1=Scene::create();
	 auto layer1=ResourceLoadScene1::create();

	 scene1->addChild(layer1);
	 return scene1;


 }

 bool ResourceLoadScene1::init()
 {

	 if (!Layer::init())
	 {
        return false;
	 }



	 return true;
 }
