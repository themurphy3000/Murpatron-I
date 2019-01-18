#include "K8055.h"

K8055::K8055()
{
	K8055Dll.open("c:\\program files\\vstplugins\\K8055D.dll");
	outputAnalog = (OUTPUT_ANALOG)K8055Dll.getFunction("OutputAnalogChannel");
	openDevice = (OPEN_DEVICE)K8055Dll.getFunction("OpenDevice");
	clear = (CLOSE)K8055Dll.getFunction("ClearAllAnalog");
	close = (CLOSE)K8055Dll.getFunction("CloseDevice");
	OpenDevice(0);
}

K8055::~K8055()
{
	ClearAllAnalog();
	CloseDevice();
}

void K8055::OutputAnalog(int channel, int value)
{
	if (outputAnalog)
		outputAnalog(channel, value);
}

void K8055::OpenDevice(int address)
{
	if (openDevice)
		openDevice(address);
}

void K8055::ClearAllAnalog()
{
	if (clear)
		clear();
}

void K8055::CloseDevice()
{
	if (close)
		close();
}
