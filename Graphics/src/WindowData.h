#pragma once
#include "EntityCircle.h"
#include "Test.h"

struct WindowData
{
	TestControl* testControlPtr;
	EntityCircle* clickedCirclePtr;
	bool clickedCircleFixed;
};