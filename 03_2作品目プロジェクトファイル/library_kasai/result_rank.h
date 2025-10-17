//=============================================
//
//リザルト[result_rank.h]
//Author Kasai Keisuke
//
//=============================================
#ifndef _RESULT_RANK_H_	//これが定義されていないとき
#define _RESULT_RANK_H_

// include
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>

/** @brief My 名前空間 */
namespace My
{
	/** @brief ランク決めクラス */
	class CResult_Rank
	{
	public:
		/**
		 * @brief ランク決め処理
		 * @param [in] バイナリファイルパス
		 * @param [in] 獲得したスコア
		 * @return テクスチャファイルパス
		 */
		static std::string SetRank(const char* FileName, int nScore);

		/**
		 * @brief ファイル書き込み処理
		 * @param [in] バイナリファイルパス
		 */
		static void WriteBin(const char* FileName);

	private:
		static const std::string BandTextures[];	//!<テクスチャデータ
	};
}
#endif