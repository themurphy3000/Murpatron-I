#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

typedef int(*OPEN_DEVICE)(int);
typedef void(*OUTPUT_ANALOG)(int, int);
typedef void(*CLOSE)(void);

class K8055
{
public:
	K8055();
	~K8055();

	void OpenDevice(int address);
	void CloseDevice();
	void OutputAnalog(int channel, int value);
	void ClearAllAnalog();
private:
	DynamicLibrary K8055Dll;
	OUTPUT_ANALOG outputAnalog;
	OPEN_DEVICE openDevice;
	CLOSE clear;
	CLOSE close;
};
