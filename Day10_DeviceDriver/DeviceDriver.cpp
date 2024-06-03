#include "DeviceDriver.h"
#include <stdexcept>

using std::exception;

DeviceDriver::DeviceDriver(FlashMemoryDevice* hardware) : m_hardware(hardware)
{}

int DeviceDriver::read(long address)
{
    // TODO: implement this method 
    int ret = (int)(m_hardware->read(address));
    printf("1st [%ld] = %d\n", address, ret);
    for (int i = 2; i < 6; i++) {
        int val = (int)(m_hardware->read(address));
        printf("[%ld] = %d\n", address, val);
        if (ret != val) {
            AssertReadFailException(i);
        }
    }
    return ret;
}

void DeviceDriver::write(long address, int data)
{
    // TODO: implement this method
    int val = (int)(m_hardware->read(address));
    if (val == 0xFF) {
        m_hardware->write(address, (unsigned char)data);
    }
    else {
        AssertWriteFailException(address, val);
    }
    
}

void DeviceDriver::AssertReadFailException(int cnt) {
    printf("[%d]th value is not same, READ FAIL\n", cnt);
    //throw invalid_argument("read value : not same");
    throw std::exception("read value : not same");
}

void DeviceDriver::AssertWriteFailException(long address, int val) {
    printf("[%ld] was already writed as [%d]!!\n", address, val);
    //throw invalid_argument("read value : not same");
    throw std::exception("already writed");
}