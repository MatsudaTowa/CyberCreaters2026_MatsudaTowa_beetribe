//==========================================
//
//音源クラス[soundmanager.h]
//Auther : Haruki Chiba
//
//==========================================


//==========================================
//インクルードガード
#pragma once


//==========================================
//インクルード
#include <string>

#pragma comment( lib, "winmm.lib" )


//==========================================
//省略
using namespace std;


//==========================================
// サウンド管理
//==========================================
class CSoundManager
{
public:
	CSoundManager() {};
	virtual ~CSoundManager() {};

	//NOTE : パスを渡す時は例のように空間を開けて書いてください

	/**
	* @brief 音源を別方法で再生
	*/
	static void AntherPlay(string name)
	{
		//第一 パスの指定、第二 音声リソースの指定（基本は無）、第三 再生方法（音声パスを指定 | 非同期再生を指定<-これをしないとめちゃめちゃ重い）
		PlaySound(TEXT(name.c_str()), NULL, SND_FILENAME | SND_ASYNC); //自動的にメモリを解放
	}

	//=========================================
	//マクロ定義
	static constexpr int MAX_VOLUME = 400;                    //音量の最大数
};