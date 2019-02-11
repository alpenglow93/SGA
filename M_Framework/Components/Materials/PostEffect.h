#pragma once
#include "./Material.h"
class PostEffect : public Material
{
private:
	ID3D11ShaderResourceView* SRV;
public:
	PostEffect(wstring file);
	~PostEffect();

	void Update() override;
	void Render() override;

	void Texture(ID3D11ShaderResourceView* SRV);

	virtual void SetInsfector() override;

};

