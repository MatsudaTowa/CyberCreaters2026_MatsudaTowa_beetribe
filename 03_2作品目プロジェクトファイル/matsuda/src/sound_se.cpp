//==========================================
//
//SEの処理[sound_se.cpp]
//Auther Haruki Chiba
//
//==========================================


//==========================================
//インクルード
#include "sound_se.h"


//==========================================
//static変数の初期化
int CSoundSE_000::m_nvolume = MAX_VOLUME;   //音量設定
bool CSoundSE_000::m_boneflag = false;      //フラグ設定
std::string CSoundSE_000::m_svolume = "0";  //音量変換用の初期化
