#pragma once
#include "qthread.h"
class WorkerThread : public QThread
{
	Q_OBJECT

public:
	WorkerThread();
	void run() = 0;
};

template <typename T>
class MRI_Module
{
public:
	virtual void start() = 0;
	virtual T getResult() = 0;
};

