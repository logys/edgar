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
                "lineal" : 3,
                "angular" : 4,
                "kpl" : 5,
                "kpr" : 6,
                "kpi" : 7
                }
        running = True
        while(running):
            print("Welcome to the jungle")
            line = ""
            while line != "quit":
                line = input("edgar> ")
                command = commands[line.split()[0]]
                value = float(line.split()[1])
                bytes_value = struct.pack("f", value)
                print(bytes_value)
                buffer = bytearray([command])
                for byte in bytes_value:
                    buffer.append(byte)
                await client.write_gatt_char(commands_charac, buffer)

        await client.disconnect()

if __name__ == '__main__':
    asyncio.run(main())

