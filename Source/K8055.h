#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

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
};
