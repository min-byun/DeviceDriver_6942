#include "DeviceDriver.h"

class Application {
public:
	Application(DeviceDriver* dd) : dd { dd } {

	}
	void readAndPrint(long start_add, long end_addr) {
		for (long addr = start_add; addr <= end_addr; addr++) {
			dd->read(addr);
		}
	}
	void WriteAll(int data) {
		for (long addr = 0x0; addr <= 0x04; addr++) {
			dd->write(addr,data);
		}
	}
private:
	DeviceDriver* dd;
};