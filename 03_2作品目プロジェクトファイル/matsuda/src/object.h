//=============================================
//
//オブジェクト[object.h]
//Author Matsuda Towa
//
//=============================================
#ifndef _OBJECT_H_ //これが定義されてないとき

#define _OBJECT_H_
#include "main.h"

/** @brief My 名前空間 */
namespace My
{
	/** @brief オブジェクトクラス */
	class CObject
	{
	public:
		static const int MAX_OBJECT = 8192; //オブジェクトの最大数

		static const int PRI_MAX = 30; //プライオリティの最大値

		enum OBJECT_TYPE
		{
			OBJECT_TYPE_NONE = 0,
			OBJECT_TYPE_TITLE,
			OBJECT_MOUSE,
			OBJECT_MOUSE_DEBUG,
			OBJECT_TYPE_TUTORIAL,
			OBJECT_TYPE_MOVE_POINT,
			OBJECT_TYPE_ATTACK_POINT,
			OBJECT_TYPE_START_POINT,
			OBJECT_TYPE_NUMBER,
			OBJECT_TYPE_RESULT,
			OBJECT_TYPE_FADE,
			OBJECT_TYPE_PLAYER,
			OBJECT_TYPE_BOARD_HORDER,
			OBJECT_TYPE_MUZZLE_FLUSH,
			OBJECT_TYPE_FIELD,
			OBJECT_TYPE_BOARD,
			OBJECT_TYPE_EFFECT,
			OBJECT_TYPE_BG,
			OBJECT_TYPE_SHADOW,
			OBJECT_TYPE_MAX,
		};

		explicit CObject(int nPriority = PRI_MAX);

		virtual ~CObject();
		virtual HRESULT Init() = 0;
		virtual void Uninit() = 0;
		virtual void Update() = 0;
		virtual void Draw() = 0;

		static void ReleaseAll(); //全オブジェクト解放

		static void UpdateAll(); //全オブジェクト更新

		static void DrawAll(); //全オブジェクト描画

		static CObject* Getobject(int nPri, int nIdx);

		inline OBJECT_TYPE GetType()
		{
			return m_type;
		}

		inline bool GetIsDelete()
		{
			return m_isDelete;
		}

		inline void SetisDraw(bool isDraw)
		{
			m_isDraw = isDraw;
		}

		inline void SetisDelete(bool isDelete)
		{
			m_isDelete = isDelete;
		}

		//オブジェクトの処理を止めるかを設定
		inline void SetStop(bool isStop) 
		{ 
			m_isStop = isStop; 
		}

		//オブジェクトの処理を止めるかを取得
		inline bool GetStop() 
		{ 
			return m_isStop; 
		}

	protected:
		void Release(); //自分自身の解放

		inline bool& GetisDraw()
		{
			return m_isDraw;
		}

		inline void SetType(OBJECT_TYPE type)
		{
			m_type = type;
		}

	private:
		static CObject* m_apObject[CObject::PRI_MAX][MAX_OBJECT];

		int m_nPriority; //描画優先度

		static int m_nNumAll; //総数

		bool m_isStop;	//処理を止める

		bool m_isDelete;	//消すかどうか

		bool m_isDraw;		//描画するか

		int m_nID; //オブジェクトのID
		OBJECT_TYPE m_type;

	};
}
#endif