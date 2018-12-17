#include "DataParse.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include  "json/stringbuffer.h"
#include "json\writer.h"

//为了在可写路径下生成一个文件（用于闯关的时候修改数据）
void DataParse::copyFile()
{
	//获取可读写的缓存路径
	std::string  writePath =FileUtils::getInstance()->getWritablePath();
	//根据可读写路径，拼接出可写的文件Data.json路径
	writePath = writePath +"Data.json";
	//资源里的文件Data.json路径，
	std::string  filefullPath=FileUtils::getInstance()->fullPathForFilename("Data.json");
	log("fullPath=%s",filefullPath.c_str());//测试获取的全路径
	//可写路径下的文件是否存在
	if(!FileUtils::getInstance()->isFileExist(writePath))
	{
		std::string data=FileUtils::getInstance()->getStringFromFile(filefullPath);
		FILE *file=fopen(writePath.c_str(),"w");
		if(file)
		{
			fputs(data.c_str(),file);
			fclose(file);
		}

	}
}
//解析出锁的状态值lock和所获得的星星数star，把它们存到字典dic中，最终返回这个字典dic
__Dictionary * DataParse::getChapter(int chaperIndex)
{
	//先拷贝到可写路径下
	copyFile();
	std::string  writePath=FileUtils::getInstance( )->getWritablePath( );
	writePath=writePath  +  "Data.json";
	log("WritablePath=%s",writePath.c_str());
	std::string data=FileUtils::getInstance( )->getStringFromFile(writePath);
	log("WritablePathNR=%s",data.c_str());
	//解析对象
	rapidjson::Document  doc;
	//开始解析
	doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	//判断解析是否出问题
	if(doc.HasParseError())
	{
		return 0;
	}
	__Dictionary *dic=__Dictionary::create();
	char chapterName[20];	
	//通过点击的章节（key）数拼接成json文件里的章节(即游戏难度的)标签名字
	sprintf(chapterName,"chapter_%d",chaperIndex);	
	for (int i = 1; i <= 6; i++)
	{
		//关卡
		char level[20];		
		sprintf(level,"level_%d",i);
		
		//自定义键，通过循环变量，拼接成json文件里的关卡标签的名字
		char lock[20];		
		sprintf(lock,"level_%d_lock",i);
		
		//通过循环变量，拼接成json文件里的星星标签的名字
		char star[20];
		sprintf(star,"level_%d_star",i);
	    Integer *lockValue=Integer::create(doc[chapterName][level]["lock"].GetInt());
		Integer *starValue=Integer::create(doc[chapterName][level]["star"].GetInt());
		dic->setObject(lockValue,lock);
		dic->setObject(starValue,star);
	}
	return dic;
}
//获取关卡中的刚体数
 int DataParse::getNum(int chapterIndex,int levelIndex)
 {
	 std::string  writePath=FileUtils::getInstance()->getWritablePath();
	 writePath = writePath + "Data.json";
	 std::string  data=FileUtils::getInstance()->getStringFromFile(writePath);
	 rapidjson::Document  doc;
	 doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	 if( doc.HasParseError())
	 {
		 return 0;
	 }
	 char chapterName[20];
     sprintf(chapterName,"chapter_%d",chapterIndex);
	 char levelName[20];
	 sprintf(levelName,"level_%d",levelIndex);
	 int  num=doc[chapterName][levelName]["num"].GetInt();
	 return num;
 }
 //或设置星星数，即当前游戏所获得的星星数，存入json文件
 void DataParse::setStar(int chapterIndex,int levelIndex,int starNum)
 {
	 std::string writePath=FileUtils::getInstance()->getWritablePath();
	 writePath= writePath + "Data.json";
	 std::string data=FileUtils::getInstance()->getStringFromFile(writePath);
	 rapidjson::Document doc;
	 doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	 if(doc.HasParseError())
	 {
		 return  ;
	 }
	 char chapterName[20];
	 sprintf(chapterName,"chapter_%d",chapterIndex);
	 char levelName[20];
	 sprintf(levelName,"level_%d",levelIndex);
	 //从json文件中解析出之前存储的星星数，即starNum，把它给整型变量num。
	 int num=doc[chapterName][levelName]["star"].GetInt();

	 /*把当前游戏进行中获得的星星数starNum与从json中解析出来的之前的星星数num进行比较，即比较starNum与num，
	 若当前所得的星星数starNum大，则把starNum存到json文件中，作为所得到的星星数。
		 */
	 if(num< starNum)
	 {
		 doc[chapterName][levelName]["star"].SetInt(starNum);//把starNum存入rapidjson的doc中
		 if(starNum==3 && levelIndex!=6)
		 {
			 char nextLevelName[20];
			 sprintf(nextLevelName,"level_%d",levelIndex+1);
			 //通过调用setInt（）方法，把0保存到json文件的lock状态中，意思是把下一关解锁
			 doc[chapterName][nextLevelName]["lock"].SetInt(0);
		 }

		 //写入数据
		 writefile(doc,writePath);
	 }
 }
 //数据写入（覆盖）：先把上面setStar方法中json文档doc中数据通过rapidjson写入器写入到缓存buffer中，再通过调用fputs方法把缓冲区buffer中的数据转变成。。。格式存入json文件
void  DataParse::writefile(rapidjson::Document &document, std::string path)
{
	rapidjson::StringBuffer buffer;//初始化缓冲区
	rapidjson::Writer<rapidjson::StringBuffer>write(buffer);//初始化写入器
    document.Accept(write);//写入buffer
	FILE *file=fopen(path.c_str(),"w");
	//将原来的文件内容覆盖
	if(file)
	{
		fputs(buffer.GetString(),file);
		fclose(file);
	}
}

//把json文件解析到rapidjson格式的doc，从doc中获取章节关卡中对应的星星数
 int DataParse::getStar(int chapterIndex,int levelIndex)
 {
	 std::string writePath=FileUtils::getInstance()->getWritablePath();
	 writePath= writePath + "Data.json";
	 std::string data=FileUtils::getInstance()->getStringFromFile(writePath);
	 rapidjson::Document doc;
	 doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	 if(doc.HasParseError())
	 {
		 return 0 ;
	 }
	 char chapterName[20];
	 sprintf(chapterName,"chapter_%d",chapterIndex);
	 char levelName[20];
	 sprintf(levelName,"level_%d",levelIndex);
	 int num=doc[chapterName][levelName]["star"].GetInt();
	 return num;
 }