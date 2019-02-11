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

	// IUserInterface��(��) ���� ��ӵ�
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

	class QuadObject* background; //���
	class Transform* backTrans; //��� Ʈ���� ��

	class QuadObject* headObj; //�浹 ��ġ 
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

