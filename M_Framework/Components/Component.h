#pragma once
class Component
{
protected:
	bool bActive = true; //
public:
	Component();
	virtual ~Component();

	virtual void Update() {};
	virtual void Render() {};

	bool Active() { return bActive; }

	virtual void SetInsfector() = 0;
};

