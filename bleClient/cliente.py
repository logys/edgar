import asyncio
import sys
from bleak import BleakClient
import struct

address = "78:E3:6D:11:7F:82"
commands_charac = "b03a659e-897e-45e1-b016-007107c910f7"

async def main():
    client = BleakClient(address)
    try:
        await client.connect()
    except Exception as e:
        print(e)
    finally:
        commands = {
                "start" : 0,
                "stop" : 1,
                "dynKp" : 50,
                "dynKi" : 51,
                "dynKd" : 52,
                "speeds" : 100,
                "point" : 101
                }
        running = True
        while(running):
            print("Welcome to the jungle")
            line = ""
            while line != "quit":
                line = input("edgar> ")
                command = commands[line.split()[0]]
                bytes_value = []
                if command < 50:
                    bytes_value = []
                elif command >= 50 and command < 100:
                    value = float(line.split()[1])
                    bytes_value = struct.pack("f", value)
                elif command >= 100 and command < 127:
                    value1 = float(line.split()[1])
                    value2 = float(line.split()[2])
                    bytes_value = struct.pack("2f", *[value1, value2])

                buffer = bytearray([command])
                print(bytes_value)
                for byte in bytes_value:
                    buffer.append(byte)
                await client.write_gatt_char(commands_charac, buffer)

        await client.disconnect()

if __name__ == '__main__':
    asyncio.run(main())

