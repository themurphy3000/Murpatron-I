#include "K8055.h"

typedef int(*OPEN_DEVICE)(int);
typedef void(*OUTPUT_ANALOG)(int, int);
typedef void(*CLOSE)(void);

K8055::K8055()
{
	K8055Dll.open("c:\\program files\\vstplugins\\K8055D.dll");
	OpenDevice(0);
}

K8055::~K8055()
{
	ClearAllAnalog();
	CloseDevice();
}

void K8055::OutputAnalog(int channel, int value)
{
	OUTPUT_ANALOG outputAnalog = (OUTPUT_ANALOG)K8055Dll.getFunction("OutputAnalogChannel");
	if (outputAnalog)
		outputAnalog(channel, value);
}

void K8055::OpenDevice(int address)
{
	OPEN_DEVICE openDevice = (OPEN_DEVICE)K8055Dll.getFunction("OpenDevice");
	if (openDevice)
		openDevice(address);
}

void K8055::ClearAllAnalog()
{
	CLOSE clear = (CLOSE)K8055Dll.getFunction("ClearAllAnalog");
	if (clear)
		clear();
}

void K8055::CloseDevice()
{
	CLOSE close = (CLOSE)K8055Dll.getFunction("CloseDevice");
	if (close)
		close();
}
