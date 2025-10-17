//==========================================
//
//SE�N���X[sound_se.h]
//Auther Haruki Chiba
//
//==========================================


//==========================================
//�C���N���[�h�K�[�h
#pragma once


//==========================================
//�C���N���[�h
#include "soundmanager.h"


//==========================================
//�����O�Ԗځi�����������̉����j
//==========================================
class CSoundSE_000 : public CSoundManager
{
public:
	CSoundSE_000() {};
	~CSoundSE_000() {};
	/**
    * @brief �t�@�C�����J��
    * @param [in]�J���t�@�C���̏ꏊ�Ɣԍ� ��open data/SOUND/sample.mp3 alias BGM type mpegvideo
    */
	static void Open()
	{
		mciSendString("open data/SOUND/hit_finger.mp3 alias SE0 type mpegvideo", NULL, 0, NULL);
	}

	/**
	* @brief �t�@�C�������
	* @param [in]����t�@�C���̔ԍ� ��close BGM
	*/
	static void Close()
	{
		//cout << "�T�E���h�N���[�Y�I" << endl;
		mciSendString("close SE0", NULL, 0, NULL);
	}

	/**
	* @brief �t�@�C�����Đ�������
	* @param [in]�Đ�������t�@�C���̔ԍ� ��play BGM
	*/
	static void Play()
	{
		//cout << "�T�E���h�Đ���" << endl;
		mciSendString("play SE0", NULL, 0, NULL);
	}

	/**
	* @brief �t�@�C�����~�߂�
	* param [in]�~�߂����t�@�C���̔ԍ�,�Đ��ʒu ��stop BGM�Aseek BGM to start
	*/
	static void Stop()
	{
		//cout << "�T�E���h��~�B" << endl;
		mciSendString("stop SE0", NULL, 0, NULL);
		mciSendString("seek SE0 to start", NULL, 0, NULL);
	}

	/**
	* @brief �����̉��ʂ�ݒ肷�鏈��(�O�`�P�O�O�O�܂�)
	*/
	static void volume(int volume)
	{
		string m_sset_bgm_volume = "setaudio SE0 volume to "; //���ʂ̒����R�}���h
		m_svolume = to_string(volume);                        //int�^�̐��l��string�^�ɕϊ�
		string ssetvolume = m_sset_bgm_volume + m_svolume;    //���ʒl���擾
		mciSendString(ssetvolume.c_str(), NULL, 0, NULL);     //���ʂ�ݒ�(string�^��LPCSTR�ɕϊ�)
	}

	/**
	* @brief �������O����Đ�
	*/
	static void Zero()
	{
		mciSendString("play SE0 from 0", NULL, 0, NULL);
	}

	static int m_nvolume;                                     //����
	static bool m_boneflag;                                   //��x����
private:
	static string m_svolume;                                  //int�^�̉��ʂ�string�^�ɕύX�p�̕ϐ�
};