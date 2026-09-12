from pymodbus.server.sync import StartTcpServer
from pymodbus.datastore import ModbusSequentialDataBlock, ModbusSlaveContext, ModbusServerContext
import threading, time

hr = ModbusSequentialDataBlock(0, [0]*10)
co = ModbusSequentialDataBlock(0, [0]*10)
store = ModbusSlaveContext(hr=hr, co=co)
context = ModbusServerContext(slaves=store, single=True)

def physics():
    level = 0
    while True:
        pump_on = store.getValues(1, 0, count=1)[0]  # coil
        level = min(1000, level + 15) if pump_on else max(0, level - 8)
        store.setValues(3, 0, [level])  # holding register
        time.sleep(0.25)

threading.Thread(target=physics, daemon=True).start()
StartTcpServer(context=context, address=("127.0.0.1", 5020))
