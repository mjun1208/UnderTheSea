#pragma once
class cEffect;
class cEffectAdmin
{
private:
	vector<cEffect *> m_effect;
public:
	cEffectAdmin();
	~cEffectAdmin();

	void Update();
	void Render();
	void Release();

	vector<cEffect *>& GetEffect() {return m_effect; }
};

