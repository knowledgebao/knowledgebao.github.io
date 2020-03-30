# coding=utf-8
import asyncio
from bleak import discover
from bleak import BleakClient

MAC_ADDRESS = "A4:C1:38:45:68:F1"

SERVICE_UUID = "ebe0ccb0-7a0a-4b0c-8a1a-6ff2997da3a6"
MODEL_NBR_UUID = "ebe0ccc1-7a0a-4b0c-8a1a-6ff2997da3a6" # 53
BATTERY_UUID = "00002a19-0000-1000-8000-00805f9b34fb"

async def scan_devices():
    devices = await discover()
    for d in devices:
        print(d.address, d.name, d.rssi)

async def measure_battery(address, loop):
    """
    获取电池电量
    """
    async with BleakClient(address, loop=loop) as client:
        battery_level  = await client.read_gatt_char(BATTERY_UUID)
        print("Battery Level: {0}%".format(int(battery_level[0])))
        return int(battery_level[0])

async def connect_device(address, loop):
    for i in range(10):
        try:
            async with BleakClient(address, loop=loop) as client:
                await client.get_services()
                await client.start_notify(MODEL_NBR_UUID, callback)
                print("订阅成功")
                while True:
                    pass
                    # battery_level  = await client.read_gatt_char(BATTERY_UUID)
                    # print("Battery Level: {0}%".format(int(battery_level[0])))
                    await asyncio.sleep(6)
        except Exception as e:
            print(e) 

            
def callback(sender, data):
    data_list = [format(i, 'x')   for i in data]
    temp = int(f'0X{data_list[1]}{data_list[0]}',16)/100.0
    sd = int(f'0x{data_list[2]}',16)
    print(f"{sender}: 温度:{temp}℃, 湿度:{sd}%")

loop = asyncio.get_event_loop()
# loop.run_until_complete(scan_devices())
loop.run_until_complete(connect_device(MAC_ADDRESS , loop))
