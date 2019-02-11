#pragma once
#include "IUserInterface.h"
class Inventory : public IUserInterface
{
public:
	static Inventory* Get();
	static void Delete();

	void Update();
	void Render();

	void SetCamera(class Camera* camera);
	virtual void Active() override { bShow = !bShow; };
private:
	Inventory();
	~Inventory();

	void SetItem();

	void SaveItems();
	void LoadItems();

	void Exchange();

private:
	static Inventory* instance;
	class Status* status;
	class Camera* camera;

	bool bShow;
	class QuadObject* backGround;
	class BoxCollider* backCollider;
	class Transform* bgTrans;

	vector<class BoxCollider*> slotsCollider;
	vector<class QuadObject*> slots;
	vector<struct ItemInfo*> items;

	class TextureShader* slotShader;

	class QuadObject* selectObject; //
	class Transform* selectTrans;

	struct ItemInfo* selectItem;
	int selectIndex;

	ID3D11ShaderResourceView* backTexture;

	// IUserInterface을(를) 통해 상속됨
	virtual Shader * GetMaterial(wstring name) override;
};

