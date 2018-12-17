#pragma once
#include "cocos2d.h"
USING_NS_CC;
#include "json\rapidjson.h"
#include "json\document.h"
class DataParse//不需继承任何父类
{
public:
	//把资源路径下的源文件复制到缓存区AppDate中，拷贝出一个可读写的文件，用于闯关的时候修改数据
	static  void copyFile( );
	//把方法定义成static，目的是任何地方可以不用对象，而直接引用，若则不用对象引用非静态方法的话则出现"非静态成员引用必须与特定对象对应"
	static __Dictionary * getChapter(int chaperIndex);
	static int getNum(int chapterIndex,int levelIndex);//获取刚体数量
	static void setStar(int chapterIndex,int levelIndex,int starNum);//设置星星的数量
	static int getStar(int chapterIndex,int levelIndex);//得到星星数量
	static void writefile(rapidjson::Document &document, std::string path);//数据写入 
	
};

