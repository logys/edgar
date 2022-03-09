import dbus
from gi.repository import GLib
from dbus.mainloop.glib import DBusGMainLoop

BUS = 'org.bluez'
DEVICE_PATH = '/org/bluez/hci0/dev_78_E3_6D_11_7F_82'
CHAR_PATH = DEVICE_PATH+'/service000f/char0010'
INTERFACE = '/org/bluez/Device1'

def main():
    DBusGMainLoop(set_as_default=True)
    global bus
    bus = dbus.SystemBus()
    global mainloop
    mainloop = GLib.MainLoop()

    device = bus.get_object(BUS, DEVICE_PATH)
    device_iface = dbus.Interface(device, 'org.bluez.Device1')
    device_iface.Connect()
    char = bus.get_object(BUS, CHAR_PATH)
    char_iface = dbus.Interface(char, 'org.bluez.GattCharacteristic1')
    char_iface.WriteValue([45],{})

    mainloop.run()
    device_iface.Disconnect()

if __name__ == '__main__':
    main()
