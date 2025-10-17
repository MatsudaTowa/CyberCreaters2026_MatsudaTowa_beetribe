//=============================================
//
//リザルト[result_rank.cpp]
//Author Kasai Keisuke
//
//=============================================

#include "result_rank.h"

using namespace std;	//std省略

//テクスチャ一覧(後ほどテクスチャ名変更)
const string My::CResult_Rank::BandTextures[] =
{
	"data\\TEXTURE\\aaa000.png",
	"data\\TEXTURE\\test_band.png",
	"data\\TEXTURE\\ccc000.png",
	"data\\TEXTURE\\ddd000.png",
	"data\\TEXTURE\\eee000.png",
};

//=============================================
//ランク設定処理
//=============================================
std::string My::CResult_Rank::SetRank(const char* FileName, int nScore)
{
	int nRank = 0;	//ランク格納用

	if (nScore < 0)
	{// スコアが取得できなかった場合
		cout << "ランクに反映できません...\n";
	}
	else
	{// スコアが取得できた場合(細かい数値は要調整)
		if (nScore < 30000)
		{
			nRank = 1;
		}
		else if (nScore < 60000)
		{
			nRank = 2;
		}
		else if (nScore < 90000)
		{
			nRank = 3;
		}
		else if (nScore < 120000)
		{
			nRank = 4;
		}
		else if (nScore < 150000)
		{
			nRank = 5;
		}
	}

	//バイナリファイル読み込み
	std::ifstream ifs(FileName, ios::in | ios::binary);

	if (!ifs)
	{// ファイルパスが間違っていた場合
		cout << "ファイルが開けませんでした\n";

		return "";
	}

	const char Key = 0x5A;	//暗号化するためのキー

	// ランクを数値化すると最小が1になるため-1して初期化
	int nTargetIndex = nRank - 1;

	int nTexNum = sizeof(My::CResult_Rank::BandTextures) / sizeof(My::CResult_Rank::BandTextures[0]);	//配列の要素数を取得

	for (int i = 0; i < nTexNum; ++i)
	{
		int nLength = 0;	//文字列の長さ

		ifs.read(reinterpret_cast<char*>(&nLength), sizeof(int));	//ファイルから読み込み

		if (!ifs)
		{//読み込み失敗したら終了
			break;
		}

		string encrypted(nLength, '\0');	//文字列分のバイト数を確保

		ifs.read(&encrypted[0], nLength);

		if (!ifs)
		{//読み込み失敗したら終了
			break;
		}

		if (i == nTargetIndex)
		{// ランク値と一致したテクスチャデータがあったら
			//XOR複合
			for (int j = 0; j < nLength; ++j)
			{
				encrypted[j] ^= Key;
			}

			//ファイルを閉じる
			ifs.close();

			return encrypted;
		}
	}
	return "";
}

//=============================================
//バイナリファイル書き込み処理
//=============================================
void My::CResult_Rank::WriteBin(const char* FileName)
{
	ofstream ofs(FileName, ios::out | ios::binary);	//上書

	if (!ofs)
	{//ファイルが開けないとき
		cout << "ファイルが開けませんでした\n";

		quick_exit(0);	//終了
	}
	else
	{//ファイルが開けたとき
		const char Key = 0x5A;	// 鍵

		int nNumTex = sizeof(My::CResult_Rank::BandTextures) / sizeof(My::CResult_Rank::BandTextures[0]);

		for (int i = 0; i < nNumTex; ++i)
		{
			const string& str = BandTextures[i];
			int nLength = static_cast<int>(str.size());

			//長さを書き込み
			ofs.write(reinterpret_cast<const char*>(&nLength), sizeof(int));

			// 内容をXOR暗号化して書き込み
			for (int j = 0; j < nLength; ++j)
			{
				char encryptedChar = str[j] ^ Key;

				ofs.write(&encryptedChar, sizeof(char));
			}
		}

		// ファイルを閉じる
		ofs.close();
	}
}
