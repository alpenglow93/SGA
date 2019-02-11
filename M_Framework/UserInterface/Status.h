#pragma once
#include "IUserInterface.h"
class Status : public IUserInterface
{
public:
	static Status* Get();
	static void Delete();

	void Update();
	void Render();

	void ShowItem(struct ItemInfo * item,class QuadObject * obj);

	void Active() override { bShow = !bShow; }

	bool IsOverlapBackground();
	ItemInfo* EquipItem(ItemInfo* item);

	ItemInfo* GetHeadItem() { return head; }
	ItemInfo* GetBodyItem() { return body; }
	ItemInfo* GetWeaponItem() { return weapon; }

	// IUserInterface을(를) 통해 상속됨
	virtual Shader * GetMaterial(wstring name) override;
	virtual void SetCamera(class Camera * camera) override;
private:
	Status();
	~Status();
private:
	static Status* instance;
	class Camera* camera;


	ID3D11ShaderResourceView* backgroundImage;

	bool bShow = false;

	class Inventory* inven;

	class TextureShader* shader;

	class QuadObject* background; //배경
	class Transform* backTrans; //배경 트랜스 폼

	class QuadObject* headObj; //충돌 위치 
	class QuadObject* bodyObj;
	class QuadObject* weaponObj;

	struct ItemInfo* head;
	struct ItemInfo* body;
	struct ItemInfo* weapon;

	class BoxCollider* backgroundCollder;
	class BoxCollider* headCollider;
	class BoxCollider* bodyCollider;
	class BoxCollider* weaponCollider;


};

