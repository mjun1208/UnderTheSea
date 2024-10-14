#pragma once

#include "cScene.h"
class cLoadScene : public cScene
{
private:

	cTexture * m_image = nullptr;
	cTexture * m_Gauge = nullptr;
	cTexture * m_GaugeEdge = nullptr;
	cFrame * m_frame = nullptr;
	struct strBun
	{
		string key;
		string path;
		int count;

		strBun(const string& key, const string& path, int count = 0)
			:key(key), path(path), count(count) {}
	};

	int m_iCurLoad = 0;
	int m_iMaxLoad = 0;

	vector<strBun> m_sLoading;

public:
	cLoadScene();
	virtual ~cLoadScene();

	virtual void Init() override;
	virtual void Update() override;
	virtual void Render() override;
	virtual void Release() override;

	void Load(const string& key, const string& path, int count = 0){ m_sLoading.push_back(strBun(key, path, count)); }
};

