#pragma once
#include "Vector2.h"
#include <string>
#include <memory>
#include <map>
#include <vector>

#define lpImglMng ImageMng::GetInstance()

/* Zバッファー
背景画像　0～9
マップ描画　10～19
キャラクター　20～29
FastUI　30～39
マウスの下にほしいもの　40～49
マウスの下にほしいもの2　50～49
マウス　60～69
UI　70～79
*/

enum class ShadName
{
	none,
	gray,
	dot,
	cross,
	slash,
};

class ImageMng
{
public:
	static ImageMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new ImageMng();
		}
	}

	static void Destroy()
	{
		if (sInstance != nullptr)
		{
			delete sInstance;
		}
		sInstance = nullptr;
	}

	/// <summary>
	/// 描画予約された画像を描画させる。
	/// シーンの描画処理で必ず呼び出すこと。
	/// </summary>
	/// <param name=""></param>
	void DrawNaw(void);

	/// <summary>
	/// 描画予約リストを削除する
	/// メインループの先頭で必ず呼び出すこと。
	/// </summary>
	/// <param name=""></param>
	void ReSetD(void);

	/// <summary>
	/// 画像を描画するように頼む
	/// </summary>
	/// <param name="id">画像ハンドル</param>
	/// <param name="pos">座標</param>
	void GraphAddDrawQue(std::string id, Vector2 pos, ShadName name = ShadName::none, int z = 10);
	void GraphAddDrawQue(std::string id, Vector2 pos, int z = 10);

	/// <summary>
	/// 別スクリーンを描画するように頼む
	/// </summary>
	/// <param name="id">スクリーンハンドル</param>
	void ScreenAddDrawQue(int id, ShadName name = ShadName::none, int z = 1);
	void ScreenAddDrawQue(int id, int z = 1);

	/// <summary>
	/// 別スクリーンを描画するように頼む
	/// </summary>
	/// <param name="id">スクリーンハンドル</param>
	/// <param name="pos">座標</param>
	void ScreenAddDrawQue(int id, Vector2 pos,ShadName name = ShadName::none, int z = 10);
	void ScreenAddDrawQue(int id, Vector2 pos, int z = 10);

	/// <summary>
	/// 画像を読み込む。
	/// 返り値はID。描画させたいときに必要。
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns>ID</returns>
	std::string LoadGraph(std::string fileName);

	/// <summary>
	/// IDに対応する保存されている画像を削除する
	/// </summary>
	/// <param name="id">ID</param>
	void DeleteGraph(std::string id);

	/// <summary>
	/// 格納されている画像データをすべて削除する。
	/// </summary>
	/// <param name=""></param>
	void ReSetDate(void);

	/// <summary>
	/// IDから画像ハンドルを取得する。
	/// </summary>
	/// <param name="id">ID</param>
	/// <returns>画像ハンドル</returns>
	int GetGraphHandle(std::string id);

	/// <summary>
	/// 破壊されたエフェクト
	/// </summary>
	/// <param name="pos">座標</param>
	void SetkillBanPos(Vector2 pos);

	/// <summary>
	/// 明るさを設定
	/// </summary>
	/// <param name="num">整数0~255</param>
	void SetBright(int num);

	/// <summary>
	/// 明るさを取得
	/// </summary>
	/// <returns>明るさ</returns>
	int GetBright()const noexcept
	{
		return bright_;
	}

	void DrawImg(std::string name,Vector2 pos, ShadName shad = ShadName::none);
	void DrawMyImg(int texH, int x, int y, ShadName name);
private:
	void MyDrawScreen(int x, int y, int graphH, int shaderH, int non);
	void MyDrawScreen(int texH, int normH, int shaderH, int x, int y, int width, int height);

	static ImageMng* sInstance;

	int SetShadImg(ShadName shad);

	void MyDrawScreen(int x, int y, int width, int height);
	void SetDrawMyImg(int texH, int shaderH, int x, int y);

	std::map<std::string, int> imgList_;	//読み込んだ画像リスト

	std::vector< std::pair<std::pair<int, int>, std::pair<Vector2,ShadName>>> drawList_;						//描画予約キュー//ハンドル&Z、座標&shadName

	int dScreenH_;

	int bright_;

	std::map<ShadName,int> pshandle_;

	int cbuffer_;

	bool useGray_;
	bool useShade_;

	std::vector<std::pair<int, Vector2>> banpos_;
	int banImg_[35];

	Vector2 screenSize_;
	ImageMng();
	void BuildBufferDate();
	~ImageMng();
};
