#include <vector>
#include <array>
#include <stdio.h>
#include <map>
#include <string>
#include <algorithm>
#include <DxLib.h>
#include "ImageMng.h"
#include "CronoMng.h"

ImageMng* ImageMng::sInstance = nullptr;

void ImageMng::DrawNaw(void)
{
	if (dScreenH_ == -1)
	{
		dScreenH_ = MakeScreen(screenSize_.x, screenSize_.y, true);
	}
	stable_sort(drawList_.begin(), drawList_.end(), [](auto& x, auto& y) {
		return x.first.second < y.first.second;
		});

	stable_sort(drawList_.begin(), drawList_.end(), [](auto& x, auto& y) {
		if (x.first.second == y.first.second)
		{
			return x.second.first.y < y.second.first.y;
		}
		return false;
		});

	SetDrawScreen(dScreenH_);
	ClsDrawScreen();

	for (auto itr = drawList_.begin(); itr != drawList_.end(); itr++)
	{
		int sname;
		if (!useShade_)
		{
			sname = SetShadImg(ShadName::none);
		}
		else
		{
			sname = SetShadImg(itr->second.second);
		}
		if ((30 <= itr->first.second && itr->first.second <= 39) || (70 <= itr->first.second && itr->first.second <= 79))
		{
			SetDrawBright(255, 255, 255);
			//MyDrawScreen(itr->second.first.x, itr->second.first.y, itr->first.first, itr->second.second);
			DrawGraph(itr->second.first.x, itr->second.first.y, itr->first.first, true);

			//MyDrawScreen(itr->second.first.x, itr->second.first.y, itr->first.first, sname, -1);
			//SetDrawMyImg(itr->first.first, sname, itr->second.first.x, itr->second.first.y);
		}
		else
		{
			SetDrawBright(bright_, bright_, bright_);
			//MyDrawScreen(itr->second.first.x, itr->second.first.y, itr->first.first, itr->second.second);
			DrawGraph(itr->second.first.x, itr->second.first.y, itr->first.first, true);

			//MyDrawScreen(itr->second.first.x, itr->second.first.y, itr->first.first, sname, -1);
			//SetDrawMyImg(itr->first.first, sname, itr->second.first.x, itr->second.first.y);
		}
	}

	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();
	MyDrawScreen(0, 0, dScreenH_, SetShadImg(ShadName::gray),-1);
	if (useGray_)
	{
		//SetDrawMyImg(dScreenH_, SetShadImg(ShadName::gray), 0, 0);
		MyDrawScreen(0, 0, dScreenH_, SetShadImg(ShadName::gray), -1);
	}
	else
	{
		//SetDrawMyImg(dScreenH_, SetShadImg(ShadName::none), 0, 0);
		MyDrawScreen(0, 0, dScreenH_, SetShadImg(ShadName::none), -1);
	}
}

void ImageMng::ReSetD(void)
{
	BuildBufferDate();

	drawList_.clear();
}

void ImageMng::GraphAddDrawQue(std::string id, Vector2 pos, ShadName name, int z)
{
	drawList_.emplace_back(std::pair<std::pair<int, int>, std::pair<Vector2, ShadName>>(std::pair<int, int>(GetGraphHandle(id), z), std::pair<Vector2, ShadName>(pos,name)));
}

void ImageMng::GraphAddDrawQue(std::string id, Vector2 pos, int z)
{
	drawList_.emplace_back(std::pair<std::pair<int, int>, std::pair<Vector2, ShadName>>(std::pair<int, int>(GetGraphHandle(id), z), std::pair<Vector2, ShadName>(pos, ShadName::none)));
}

void ImageMng::ScreenAddDrawQue(int id, ShadName name, int z)
{
	drawList_.emplace_back(std::pair<std::pair<int, int>, std::pair<Vector2, ShadName>>(std::pair<int, int>(id, z), std::pair<Vector2, ShadName>(Vector2(0, 0), name)));
}

void ImageMng::ScreenAddDrawQue(int id, int z)
{
	drawList_.emplace_back(std::pair<std::pair<int, int>, std::pair<Vector2, ShadName>>(std::pair<int, int>(id, z), std::pair<Vector2, ShadName>(Vector2(0, 0), ShadName::none)));
}

void ImageMng::ScreenAddDrawQue(int id, Vector2 pos, ShadName name, int z)
{
	drawList_.emplace_back(std::pair<std::pair<int, int>, std::pair<Vector2, ShadName>>(std::pair<int, int>(id, z), std::pair<Vector2, ShadName>(pos, name)));
}

void ImageMng::ScreenAddDrawQue(int id, Vector2 pos, int z)
{
	drawList_.emplace_back(std::pair<std::pair<int, int>, std::pair<Vector2, ShadName>>(std::pair<int, int>(id, z), std::pair<Vector2, ShadName>(pos, ShadName::none)));
}

std::string ImageMng::LoadGraph(std::string fileName)
{
	if (GetGraphHandle(fileName) == -1)
	{
		std::string tstr = "resource\\img/";
		tstr += fileName;
		imgList_.try_emplace(fileName, DxLib::LoadGraph(tstr.c_str()));
	}
	return fileName;
}

void ImageMng::DeleteGraph(std::string id)
{
	imgList_.erase(id);
}

void ImageMng::ReSetDate(void)
{
	imgList_.clear();
}

int ImageMng::GetGraphHandle(std::string id)
{
	if (imgList_.find(id) == imgList_.end())
	{
		std::string tstr = "resource\\img/";
		tstr += id;
		imgList_.try_emplace(id, DxLib::LoadGraph(tstr.c_str()));
	}
	return imgList_.at(id);
}

void ImageMng::SetBright(int num)
{
	bright_ = min(max(0, num), 255);
	SetDrawBright(bright_, bright_, bright_);
}

void ImageMng::DrawImg(std::string name, Vector2 pos, ShadName shad)
{
	//SetShadImg(shad);
	int sname;
	if (!useShade_)
	{
		sname = SetShadImg(ShadName::none);
	}
	else
	{
		sname = SetShadImg(shad);
	}
	MyDrawScreen(pos.x, pos.y, lpImglMng.GetGraphHandle(name), sname, -1);
	//SetDrawMyImg(lpImglMng.GetGraphHandle(name), SetShadImg(ShadName::none), pos.x, pos.y);
}

void ImageMng::MyDrawScreen(int x, int y, int graphH, int shaderH, int non)
{
	SetUsePixelShader(shaderH);
	SetUseTextureToShader(0, graphH);
	SetUsePixelShader(shaderH);
	int w, h;
	GetGraphSize(graphH, &w, &h);
	FLOAT* bufferDate = static_cast<FLOAT*>(GetBufferShaderConstantBuffer(cbuffer_));

	bufferDate[0] = w;
	bufferDate[1] = h;
	bufferDate[2] = 0;
	bufferDate[3] = 0;

	UpdateShaderConstantBuffer(cbuffer_);
	SetShaderConstantBuffer(cbuffer_, DX_SHADERTYPE_PIXEL, 0);
	MyDrawScreen(graphH, non, shaderH, x, y, w, h);
}

void ImageMng::DrawMyImg(int texH, int x, int y, ShadName name)
{
	int sname;
	if (!useShade_)
	{
		sname = SetShadImg(ShadName::none);
	}
	else
	{
		sname = SetShadImg(name);
	}

	MyDrawScreen(x, y, texH, sname, -1);
	//SetDrawMyImg(texH, SetShadImg(ShadName::none), x, y);
}

void ImageMng::MyDrawScreen(int texH, int normH, int shaderH, int x, int y, int width, int height)
{
	SetUseTextureToShader(0, texH);
	SetUseTextureToShader(1, normH);
	SetUsePixelShader(shaderH);
	MyDrawScreen(x, y, width, height);
}

//void ImageMng::MyDrawScreen(int x, int y, int graphH, ShadName shad)
//{
//	//SetShadImg(shad);
//	SetDrawMyImg(graphH, SetShadImg(ShadName::none), x, y);
//
//}

int ImageMng::SetShadImg(ShadName shad)
{
	//FLOAT* bufferDate = (FLOAT*)GetBufferShaderConstantBuffer(cbuffer_);
	//bufferDate[0] = 1280.0f;//chipsize
	//bufferDate[1] = 720.0f;//chipsize
	//bufferDate[2] = lpCronoMng.GetDeltaTime() / 10.0f;
	//bufferDate[3] = 0.0f;
	//UpdateShaderConstantBuffer(cbuffer_);
	//SetShaderConstantBuffer(cbuffer_, DX_SHADERTYPE_PIXEL, 0);

	if (pshandle_.find(shad) != pshandle_.end())
	{
		return pshandle_.at(shad);
	}
	return 0;
}

void ImageMng::MyDrawScreen(int x, int y, int width, int height)
{
	std::array<VERTEX2DSHADER, 4> verts;
	for (auto& v : verts) {
		v.rhw = 1.0f;
		v.dif = GetColorU8(0xff, 0xff, 0xff, 0xff);
		v.u = 0.0f;
		v.v = 0.0f;
		v.su = 0.0f;
		v.sv = 0.0f;
		v.pos.z = 0.0f;
		v.spc = GetColorU8(0, 0, 0, 0);
	}
	verts[0].pos.x = x;
	verts[0].pos.y = y;
	verts[1].pos.x = x + width;
	verts[1].pos.y = y;
	verts[1].u = 1.0f;
	verts[2].pos.x = x;
	verts[2].pos.y = y + height;
	verts[2].v = 1.0f;
	verts[3].pos.x = x + width;
	verts[3].pos.y = y + height;
	verts[3].u = 1.0f;
	verts[3].v = 1.0f;
	DrawPrimitive2DToShader(verts.data(), verts.size(), DX_PRIMTYPE_TRIANGLESTRIP);
}

void ImageMng::SetDrawMyImg(int texH, int shaderH, int x, int y)
{
	SetUseTextureToShader(0, texH);
	SetUsePixelShader(shaderH);
	int w, h;
	GetGraphSize(texH, &w, &h);
	MyDrawScreen(x, y, w, h);
}

ImageMng::ImageMng()
{
	dScreenH_ = -1;
	bright_ = 255;
	screenSize_.x = 0;
	screenSize_.y = 0;
	GetDrawScreenSize(&screenSize_.x, &screenSize_.y);
	cbuffer_ = -1;

	useGray_ = false;
	useShade_ = false;
}

void ImageMng::BuildBufferDate()
{
	if (cbuffer_ == -1)
	{
		pshandle_.try_emplace(ShadName::none, LoadPixelShader("non.pso"));
		pshandle_.try_emplace(ShadName::gray, LoadPixelShader("gray.pso"));
		pshandle_.try_emplace(ShadName::dot, LoadPixelShader("dot.pso"));
		pshandle_.try_emplace(ShadName::cross, LoadPixelShader("cross.pso"));
		pshandle_.try_emplace(ShadName::slash, LoadPixelShader("slash.pso"));

		cbuffer_ = CreateShaderConstantBuffer(sizeof(FLOAT) * 4);

		FLOAT* bufferDate = static_cast<FLOAT*>(GetBufferShaderConstantBuffer(cbuffer_));

		bufferDate[0] = 1280;
		bufferDate[1] = 720;
		bufferDate[2] = 0;
		bufferDate[3] = 0;

		UpdateShaderConstantBuffer(cbuffer_);
		SetShaderConstantBuffer(cbuffer_, DX_SHADERTYPE_PIXEL, 0);
	}
}

ImageMng::~ImageMng()
{
}
