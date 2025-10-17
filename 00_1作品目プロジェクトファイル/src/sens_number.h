//=============================================
//
//感度の数字「sens_number.h」
// Author松田永久
//
//=============================================
#ifndef _SENS_NUMBER_H_ //これが定義されてないとき
#define _SENS_NUMBER_H_
#include "main.h"
#include "number.h"

//=============================================
//ナンバークラス2D
//=============================================
class CSensNumber :public CNumber_2D
{
public:
	static const int PRIORITY = 29;  //描画順
	/**
	 * @brief コンストラクタ
	 * @param [in]プライオリティ
	 */
	CSensNumber(int nPriority = PRIORITY) :CNumber_2D(nPriority) {};
};
#endif // DEBUG