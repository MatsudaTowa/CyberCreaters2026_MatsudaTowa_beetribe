//==========================================
//
//SEクラス[sound_se.h]
//Auther Haruki Chiba
//
//==========================================


//==========================================
//インクルードガード
#pragma once


//==========================================
//インクルード
#include "soundmanager.h"


//==========================================
//音源０番目（当たった時の音源）
//==========================================
class CSoundSE_000 : public CSoundManager
{
public:
	CSoundSE_000() {};
	~CSoundSE_000() {};
	/**
    * @brief ファイルを開く
    * @param [in]開くファイルの場所と番号 例open data/SOUND/sample.mp3 alias BGM type mpegvideo
    */
	static void Open()
	{
		mciSendString("open data/SOUND/hit_finger.mp3 alias SE0 type mpegvideo", NULL, 0, NULL);
	}

	/**
	* @brief ファイルを閉じる
	* @param [in]閉じるファイルの番号 例close BGM
	*/
	static void Close()
	{
		//cout << "サウンドクローズ！" << endl;
		mciSendString("close SE0", NULL, 0, NULL);
	}

	/**
	* @brief ファイルを再生させる
	* @param [in]再生させるファイルの番号 例play BGM
	*/
	static void Play()
	{
		//cout << "サウンド再生♪" << endl;
		mciSendString("play SE0", NULL, 0, NULL);
	}

	/**
	* @brief ファイルを止める
	* param [in]止めたいファイルの番号,再生位置 例stop BGM、seek BGM to start
	*/
	static void Stop()
	{
		//cout << "サウンド停止。" << endl;
		mciSendString("stop SE0", NULL, 0, NULL);
		mciSendString("seek SE0 to start", NULL, 0, NULL);
	}

	/**
	* @brief 音源の音量を設定する処理(０～１０００まで)
	*/
	static void volume(int volume)
	{
		string m_sset_bgm_volume = "setaudio SE0 volume to "; //音量の調整コマンド
		m_svolume = to_string(volume);                        //int型の数値をstring型に変換
		string ssetvolume = m_sset_bgm_volume + m_svolume;    //音量値を取得
		mciSendString(ssetvolume.c_str(), NULL, 0, NULL);     //音量を設定(string型をLPCSTRに変換)
	}

	/**
	* @brief 音源を０から再生
	*/
	static void Zero()
	{
		mciSendString("play SE0 from 0", NULL, 0, NULL);
	}

	static int m_nvolume;                                     //音量
	static bool m_boneflag;                                   //一度きり
private:
	static string m_svolume;                                  //int型の音量をstring型に変更用の変数
};