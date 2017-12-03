#pragma once
#include "MRI_Module.h"
class Skull_stripping:
	public MRI_Module<float***>
{
public:
	Skull_stripping();
	void test();
	~Skull_stripping();
};

