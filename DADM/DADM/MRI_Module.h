#pragma once
#include "qthread.h"
class WorkerThread : public QThread
{
	Q_OBJECT

public:
	WorkerThread();
	void run() = 0;
};

class MRI_Module
{
public:
	MRI_Module();
	virtual void process();
	virtual float*** getResult();
	virtual ~MRI_Module();
};

