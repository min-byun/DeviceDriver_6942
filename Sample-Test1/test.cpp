#pragma once
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Day10_DeviceDriver/DeviceDriver.cpp"
#include "../Day10_DeviceDriver/Application.cpp"
#include <stdexcept>

using namespace testing;
using std::exception;
using std::iostream;

class MockFlash :public FlashMemoryDevice {
public:
	MOCK_METHOD(unsigned char, read, (long address), (override));
	MOCK_METHOD(void, write, (long address, unsigned char data), (override));
};

class DeviceDriverTestFixture : public Test {
public:
	MockFlash fMock;
	DeviceDriver mokDevice = DeviceDriver(&fMock);
	long addr = 0xaaaa;
};

TEST_F(DeviceDriverTestFixture, ReadTest) {
	//5번 read
		//behavior verification - 몇 번 호출되어야 해 , 행동검증
	EXPECT_CALL(fMock, read(_)).Times(5);
	mokDevice.read(addr);
}

TEST_F(DeviceDriverTestFixture, ReadExceptionTest) {
	EXPECT_CALL(fMock,read)
	.WillOnce(Return((unsigned char)0xA))
	.WillOnce(Return((unsigned char)0xA))
	.WillOnce(Return((unsigned char)0xA))
	.WillOnce(Return((unsigned char)0xA))
	.WillOnce(Return((unsigned char)0xF));

	EXPECT_THROW(mokDevice.read(addr), exception);
}

TEST_F(DeviceDriverTestFixture, WriteTest1) {
	EXPECT_CALL(fMock, read)
		.Times(1)
		.WillOnce(Return((unsigned char)0xFF));
	EXPECT_CALL(fMock, write)
		.Times(1);
	mokDevice.write(addr,0x10);
}


TEST_F(DeviceDriverTestFixture, WriteExceptionTest) {
	EXPECT_CALL(fMock, read)
		.Times(1)
		.WillOnce(Return((unsigned char)0xA));
	
	EXPECT_THROW(mokDevice.write(addr, 0x10), exception);
}

TEST_F(DeviceDriverTestFixture, ReadWriteTest) {
	EXPECT_CALL(fMock, read)
		.WillOnce(Return((unsigned char)0xFF));
	EXPECT_CALL(fMock, write)
		.Times(1);
	mokDevice.write(addr, 0x10);

	EXPECT_CALL(fMock, read)
		.WillOnce(Return((unsigned char)0x10))
		.WillOnce(Return((unsigned char)0x10))
		.WillOnce(Return((unsigned char)0x10))
		.WillOnce(Return((unsigned char)0x10))
		.WillOnce(Return((unsigned char)0x10));

	EXPECT_EQ(mokDevice.read(addr), 0x10);
}

class AppFixture : public Test {
public:
	MockFlash fMock;
	DeviceDriver mokDevice = DeviceDriver(&fMock);
	Application app{ &mokDevice };

};


TEST_F(AppFixture, App1) {
	EXPECT_CALL(fMock, read)
		.Times(25);
	app.readAndPrint(0x00, 0x04);
};

TEST_F(AppFixture, App2) {
	EXPECT_CALL(fMock, read)
		.Times(5)
		.WillRepeatedly(Return(0xFF));

	EXPECT_CALL(fMock, write(_, 0xFA))
		.Times(5);
	app.WriteAll(0xFA);
};