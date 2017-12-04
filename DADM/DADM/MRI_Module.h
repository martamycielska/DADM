#pragma once
#include "qthread.h"

template <typename T>
class MRI_Module
{
public:
	virtual void start() = 0;
	virtual T getResult() = 0;
};

