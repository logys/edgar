#include "CppUTest/TestHarness.h" 
#include "CppUTestExt/MockSupport.h" 
#include "../src/serial.h" 
#include "../src/communication_driver.h" 
#include "avr/io.h"

class Mock_ble : public CommunicationDriver{
	void sendUserInput(short data) override
	{
		mock().actualCall("dataNew").withParameter("data", data);
	}
};

static CommunicationDriver * ble;
TEST_GROUP(SERIAL) 
{ 
	 void setup(void) 
	 {
		 ble = new Mock_ble();
		 UCSR0B = 0;
		 UCSR0C = 0;
		 UBRR0L = 0;
	 	 serial_init(ble);
	 } 
 	 void teardown(void) 
	 { 
		 delete ble;
		 mock().clear();
	 } 
}; 
 
TEST(SERIAL, enableTx)
{
	BITS_EQUAL(1<<TXEN0, UCSR0B, 1<<TXEN0); 
}

TEST(SERIAL, enableRx)
{
	BITS_EQUAL(1<<RXEN0, UCSR0B, 1<<RXEN0); 
}

TEST(SERIAL, baudRate)
{
	CHECK_EQUAL(103, UBRR0L); 
}

TEST(SERIAL, dataFrame)
{
	BITS_EQUAL(1<<UCSZ01, UCSR0C, 1<<UCSZ01);
	BITS_EQUAL(1<<UCSZ00, UCSR0C, 1<<UCSZ00); 
}

TEST(SERIAL, asyncMode)
{
	BITS_EQUAL(0<<UMSEL00, UCSR0C, 1<<UMSEL00);
	BITS_EQUAL(0<<UMSEL01, UCSR0C, 1<<UMSEL01);
}

TEST(SERIAL, ReadData)
{
	UDR0 = 10;

	short data = serial_read();

	CHECK_EQUAL(10, data);
}

TEST(SERIAL, there_is_new_data)
{
	UCSR0A |= 1<<RXC0;

	bool dataNew = serial_dataNew();

	CHECK(dataNew);
}

TEST(SERIAL, sendDataToBle)
{
	short data = 10;
	mock().expectOneCall("dataNew").withParameter("data", data);

	serial_asyncCall(data);

	mock().checkExpectations();
}
