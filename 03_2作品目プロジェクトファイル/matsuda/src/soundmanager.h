//==========================================
//
//�����N���X[soundmanager.h]
//Auther : Haruki Chiba
//
//==========================================


//==========================================
//�C���N���[�h�K�[�h
#pragma once


//==========================================
//�C���N���[�h
#include <string>

#pragma comment( lib, "winmm.lib" )


//==========================================
//�ȗ�
using namespace std;


//==========================================
// �T�E���h�Ǘ�
//==========================================
class CSoundManager
{
public:
	CSoundManager() {};
	virtual ~CSoundManager() {};

	//NOTE : �p�X��n�����͗�̂悤�ɋ�Ԃ��J���ď����Ă�������

	/**
	* @brief ������ʕ��@�ōĐ�
	*/
	static void AntherPlay(string name)
	{
		//��� �p�X�̎w��A��� �������\�[�X�̎w��i��{�͖��j�A��O �Đ����@�i�����p�X���w�� | �񓯊��Đ����w��<-��������Ȃ��Ƃ߂���߂���d���j
		PlaySound(TEXT(name.c_str()), NULL, SND_FILENAME | SND_ASYNC); //�����I�Ƀ����������
	}

	//=========================================
	//�}�N����`
	static constexpr int MAX_VOLUME = 400;                    //���ʂ̍ő吔
};