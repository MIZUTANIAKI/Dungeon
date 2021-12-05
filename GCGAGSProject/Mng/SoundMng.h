#pragma once
#include <string>
#include <map>
#include <vector>

#define lpSoundMng SoundMng::GetInstance()

class SoundMng
{
public:

	static SoundMng& GetInstance(void)
	{
		Create();
		return *sInstance;
	}

	static void Create()
	{
		if (sInstance == nullptr)
		{
			sInstance = new SoundMng();
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
	/// 音声を読み込む。
	/// 返り値はID。描画させたいときに必要。
	/// </summary>
	/// <param name="fileName">ファイル名</param>
	/// <returns>ID</returns>
	void LoadSound(std::string fileName);

	/// <summary>
	/// 音声を再生する
	/// </summary>
	/// <param name="id">音声ハンドル</param>
	/// <param name="PlayType">再生タイプ</param>
	void SoundPlay(std::string id, int PlayType = 0x0001);

	/// <summary>
	/// 音声が再生されているか調べる
	/// </summary>
	/// <param name="id">ID</param>
	/// <returns>再生中ならtrue</returns>
	bool CheckPlaySound(std::string id);

	/// <summary>
	/// 再生中の音声を止める
	/// </summary>
	/// <param name="id"></param>
	void StopSound(std::string id);

	/// <summary>
	/// IDに対応する保存されている音声を削除する
	/// </summary>
	/// <param name="id">ID</param>
	void DeleteSound(std::string id);

	/// <summary>
	/// 格納されている音声データをすべて削除する。
	/// </summary>
	/// <param name=""></param>
	void ReSetDate(void);

	/// <summary>
	/// IDから音声ハンドルを取得する。
	/// </summary>
	/// <param name="id">ID</param>
	/// <returns>音声ハンドル</returns>
	int GetSoundHandle(std::string id);

	/// <summary>
	/// 音量をセットする
	/// </summary>
	/// <param name="num">音量</param>
	void SetSoundVol(int num);

	/// <summary>
	/// 音量を取得する
	/// </summary>
	/// <param name=""></param>
	/// <returns>音量</returns>
	int GetSoundVol(void)const noexcept
	{
		return soundVol_;
	}

private:
private:
	static SoundMng* sInstance;

	std::map<std::string, int> soundList_;	//読み込んだ音声リスト

	int soundVol_;

	SoundMng();
	~SoundMng();
};
