//=============================================
//
//���U���g[result_rank.cpp]
//Author Kasai Keisuke
//
//=============================================

#include "result_rank.h"

using namespace std;	//std�ȗ�

//�e�N�X�`���ꗗ(��قǃe�N�X�`�����ύX)
const string My::CResult_Rank::BandTextures[] =
{
	"data\\TEXTURE\\aaa000.png",
	"data\\TEXTURE\\test_band.png",
	"data\\TEXTURE\\ccc000.png",
	"data\\TEXTURE\\ddd000.png",
	"data\\TEXTURE\\eee000.png",
};

//=============================================
//�����N�ݒ菈��
//=============================================
std::string My::CResult_Rank::SetRank(const char* FileName, int nScore)
{
	int nRank = 0;	//�����N�i�[�p

	if (nScore < 0)
	{// �X�R�A���擾�ł��Ȃ������ꍇ
		cout << "�����N�ɔ��f�ł��܂���...\n";
	}
	else
	{// �X�R�A���擾�ł����ꍇ(�ׂ������l�͗v����)
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

	//�o�C�i���t�@�C���ǂݍ���
	std::ifstream ifs(FileName, ios::in | ios::binary);

	if (!ifs)
	{// �t�@�C���p�X���Ԉ���Ă����ꍇ
		cout << "�t�@�C�����J���܂���ł���\n";

		return "";
	}

	const char Key = 0x5A;	//�Í������邽�߂̃L�[

	// �����N�𐔒l������ƍŏ���1�ɂȂ邽��-1���ď�����
	int nTargetIndex = nRank - 1;

	int nTexNum = sizeof(My::CResult_Rank::BandTextures) / sizeof(My::CResult_Rank::BandTextures[0]);	//�z��̗v�f�����擾

	for (int i = 0; i < nTexNum; ++i)
	{
		int nLength = 0;	//������̒���

		ifs.read(reinterpret_cast<char*>(&nLength), sizeof(int));	//�t�@�C������ǂݍ���

		if (!ifs)
		{//�ǂݍ��ݎ��s������I��
			break;
		}

		string encrypted(nLength, '\0');	//�����񕪂̃o�C�g�����m��

		ifs.read(&encrypted[0], nLength);

		if (!ifs)
		{//�ǂݍ��ݎ��s������I��
			break;
		}

		if (i == nTargetIndex)
		{// �����N�l�ƈ�v�����e�N�X�`���f�[�^����������
			//XOR����
			for (int j = 0; j < nLength; ++j)
			{
				encrypted[j] ^= Key;
			}

			//�t�@�C�������
			ifs.close();

			return encrypted;
		}
	}
	return "";
}

//=============================================
//�o�C�i���t�@�C���������ݏ���
//=============================================
void My::CResult_Rank::WriteBin(const char* FileName)
{
	ofstream ofs(FileName, ios::out | ios::binary);	//�㏑

	if (!ofs)
	{//�t�@�C�����J���Ȃ��Ƃ�
		cout << "�t�@�C�����J���܂���ł���\n";

		quick_exit(0);	//�I��
	}
	else
	{//�t�@�C�����J�����Ƃ�
		const char Key = 0x5A;	// ��

		int nNumTex = sizeof(My::CResult_Rank::BandTextures) / sizeof(My::CResult_Rank::BandTextures[0]);

		for (int i = 0; i < nNumTex; ++i)
		{
			const string& str = BandTextures[i];
			int nLength = static_cast<int>(str.size());

			//��������������
			ofs.write(reinterpret_cast<const char*>(&nLength), sizeof(int));

			// ���e��XOR�Í������ď�������
			for (int j = 0; j < nLength; ++j)
			{
				char encryptedChar = str[j] ^ Key;

				ofs.write(&encryptedChar, sizeof(char));
			}
		}

		// �t�@�C�������
		ofs.close();
	}
}
