//=============================================
//
//���U���g[result_rank.h]
//Author Kasai Keisuke
//
//=============================================
#ifndef _RESULT_RANK_H_	//���ꂪ��`����Ă��Ȃ��Ƃ�
#define _RESULT_RANK_H_

// include
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

/** @brief My ���O��� */
namespace My
{
	/** @brief �����N���߃N���X */
	class CResult_Rank
	{
	public:
		/**
		 * @brief �����N���ߏ���
		 * @param [in] �o�C�i���t�@�C���p�X
		 * @param [in] �l�������X�R�A
		 * @return �e�N�X�`���t�@�C���p�X
		 */
		static std::string SetRank(const char* FileName, int nScore);

		/**
		 * @brief �t�@�C���������ݏ���
		 * @param [in] �o�C�i���t�@�C���p�X
		 */
		static void WriteBin(const char* FileName);

	private:
		static const std::string BandTextures[];	//!<�e�N�X�`���f�[�^
	};
}
#endif