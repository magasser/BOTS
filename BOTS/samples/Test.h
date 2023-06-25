#pragma once
class Test
{
public:
	virtual ~Test() = 0;

	virtual void OnUpdate(float deltaTime) = 0;
	virtual void OnRender() = 0;
	virtual void OnUIRender() = 0;
};

