#ifndef _FILE_COMMON_H_
#define _FILE_COMMON_H_
#include <string>
#include "cocos2d.h"

namespace common
{
	static const std::string dataChars = 
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz"
		"0123456789+/";

	static inline bool baseData(unsigned char c) {
		return (isalnum(c) || (c == '+') || (c == '/'));
	}

	std::string himiSaveData(unsigned char const* bytes_to_encode, unsigned int in_len) 
	{
		std::string ret;
		int i = 0;
		int j = 0;
		unsigned char char_array_3[3];
		unsigned char char_array_4[4];

		while (in_len--) {
			char_array_3[i++] = *(bytes_to_encode++);
			if (i == 3) {
				char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
				char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
				char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
				char_array_4[3] = char_array_3[2] & 0x3f;

				for(i = 0; (i <4) ; i++)
					ret += dataChars[char_array_4[i]];
				i = 0;
			}
		}

		if (i)
		{
			for(j = i; j < 3; j++)
				char_array_3[j] = '\0';

			char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
			char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
			char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
			char_array_4[3] = char_array_3[2] & 0x3f;

			for (j = 0; (j < i + 1); j++)
				ret += dataChars[char_array_4[j]];

			while((i++ < 3))
				ret += '=';

		}

		return ret;
	}

	std::string himiParseData(std::string const& encoded_string)
	{
		int in_len = encoded_string.size();
		int i = 0;
		int j = 0;
		int in_ = 0;
		unsigned char char_array_4[4], char_array_3[3];
		std::string ret;

		while (in_len-- && ( encoded_string[in_] != '=') && baseData(encoded_string[in_])) {
			char_array_4[i++] = encoded_string[in_]; in_++;
			if (i ==4) {
				for (i = 0; i <4; i++)
					char_array_4[i] = dataChars.find(char_array_4[i]);

				char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
				char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
				char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

				for (i = 0; (i < 3); i++)
					ret += char_array_3[i];
				i = 0;
			}
		}

		if (i) {
			for (j = i; j <4; j++)
				char_array_4[j] = 0;

			for (j = 0; j <4; j++)
				char_array_4[j] = dataChars.find(char_array_4[j]);

			char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
			char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
			char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

			for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
		}

		return ret;
	}
	//本地保存
	void SaveData(const char* key, int status){
		char tempString[50] = {0};
		sprintf(tempString, "%d", status);
		std::string sValue = tempString;
		cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey(key, sValue);
		cocos2d::CCUserDefault::sharedUserDefault()->flush();
	}

	void SaveData(const char* key, const char* status){
		std::string sValue = status;
		cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey(key, sValue);
		cocos2d::CCUserDefault::sharedUserDefault()->flush();
	}

	void SaveData(const char* key, int* status, int num){
		std::string str = key;
		char buffer[20];
		sprintf(buffer, "%d", num);
		str += buffer;

		char tempString[50] = {0};
		sprintf(tempString, "%d", status[num]);
		std::string sValue = tempString;
		cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey(str.c_str(), sValue);
		cocos2d::CCUserDefault::sharedUserDefault()->flush();
	}

	void SaveData(const char* key, int status, int num){
		std::string str = key;
		char buffer[20];
		sprintf(buffer, "%d", num);
		str += buffer;

		char tempString[50] = {0};
		sprintf(tempString, "%d", status);
		std::string sValue = tempString;
		cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey(str.c_str(), sValue);
		cocos2d::CCUserDefault::sharedUserDefault()->flush();
	}

	void SaveData(const char* key, const char* status, int num){
		std::string str = key;
		char buffer[20];
		sprintf(buffer, "%d", num);
		str += buffer;

		std::string sValue = status;
		cocos2d::CCUserDefault::sharedUserDefault()->setStringForKey(str.c_str(), sValue);
		cocos2d::CCUserDefault::sharedUserDefault()->flush();
	}

	void SaveUpdate(){
		cocos2d::CCUserDefault::sharedUserDefault()->flush();
	}
	//数据读取
	void LoadData(const char* key, int& status){
		std::string s = cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey(key);
		if ( s != "" ){
			status = atoi(s.c_str());
		}
		else
			status = 0;
	}

	void LoadData(const char* key, int& status, int num){
		std::string str = key;
		char buffer[20];
		sprintf(buffer, "%d", num);
		str += buffer;

		std::string s = cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey(key);
		if ( s != "" ){
			status = atoi(s.c_str());
		}
		else
			status = 0;
	}

	void LoadData(const char* key, std::string& status){
		status = cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey(key);
	}

	void LoadData(const char* key, std::string& status, int num){
		std::string str = key;
		char buffer[20];
		sprintf(buffer, "%d", num);
		str += buffer;
		status = cocos2d::CCUserDefault::sharedUserDefault()->getStringForKey(key);
	}

	bool IsFirstTime()
	{
		int _FIRST_TIME_;
		LoadData("f", _FIRST_TIME_);
		return !_FIRST_TIME_;
	}
}

#define SaveArray(key, array, num) \
	for ( int i = 0; i < num; i++ ) \
{ \
	std::string str = key; \
	char buffer[20]; \
	sprintf(buffer, "%d", i); \
	str += buffer; \
	common::SaveData(str.c_str(), array[i]); \
}

#define LoadArray(key, array, num) \
	for ( int i = 0; i < num; i++ ) \
{ \
	std::string str = key; \
	char buffer[20]; \
	sprintf(buffer, "%d", i); \
	str += buffer; \
	common::LoadData(str.c_str(), array[i]); \
}

#endif
