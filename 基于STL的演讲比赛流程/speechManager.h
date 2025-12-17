#pragma once
#include<iostream>
#include<map>
#include<vector>
#include"speaker.h"
using namespace std;
class SpeechManager {
public:
	vector<int>v1;
	vector<int>v2;
	vector<int>vVictory;
	map<int, Speaker> m_Speaker;
	int m_Index;
	bool fileIsEmpty;
	map<int, vector<string>> m_Record;
	SpeechManager();
	void show_Menu();
	void initSpeech();
	void createSpeaker();
	void startSpeech();
	void speechDraw();
	void speechContest();
	void showScore(); //œ‘ æµ√∑÷
	void saveRecord();
	void loadRecord();
	void showRecord();
	void exitSystem();
	void clearRecord();
	~SpeechManager();
};
