import asyncio
import bluetooth
from enum import Enum
from typing import Dict, Tuple, Any
import json
import time
import random
import paho.mqtt.client as mqtt

# Events
EventType = Enum('EventType', ['device_found', 'device_connected', 'device_connection_failed', 'data_received'])
Event = Tuple[EventType, Dict[str, Any]]

def event(event_type: EventType, data: Dict[str, str]) -> Event:
    return (event_type, data)

device_name = 'HC-05'

Status = Enum('Status', ['connected', 'not_connected'])

# MQTT Configuration
MQTT_BROKER = "localhost"  # Replace with your MQTT broker address
MQTT_PORT = 1883
MQTT_TOPIC = "data"

# Define event loop and event handlers
class EventLoop:
    def __init__(self, mqtt_client):
        self.event_queue = asyncio.Queue()
        self.status = Status.not_connected
        self.mqtt_client = mqtt_client

    async def run(self):
        while True:
            if not self.event_queue.empty():
                event = await self.event_queue.get()
                if event:
                    await self.handle_event(event)
            await asyncio.sleep(1)

    async def handle_event(self, event):
        match self.status:
            case Status.not_connected:
                await self.not_connected_handler(event)
            case Status.connected:
                await self.connected_handler(event)

    async def connected_handler(self, event):
        match event:
            case (EventType.data_received, json_data):
                print(f"Received: {json_data}")
                await publish_mqtt(self.mqtt_client, json_data)

    async def not_connected_handler(self, event):
        match event:
            case (EventType.device_found, data):
                await self.handle_device_found_event(data)
            case (EventType.device_connected, data):
                await self.handle_device_connected_event(data)
            case (EventType.device_connection_failed, data):
                await self.handle_device_connection_failed_event(data)

    async def handle_device_found_event(self, data):
        match data:
            case {"address": address, "name": name}:
                print(f"Device {name} found with address {address}")
                if name == device_name:
                    await connect_bluetooth(self, address)

    async def handle_device_connected_event(self, sock):
        self.status = Status.connected
        asyncio.run_coroutine_threadsafe(receive_data(self, sock), asyncio.get_running_loop())

    async def handle_device_connection_failed_event(self, data):
        match data:
            case (err, address):
                print(f"Device with address {address} failed to connect")
                print(err)

async def receive_data(event_loop: EventLoop, sock):
    try:
        buffer = ""
        while True:
            data = sock.recv(1024).decode('utf-8')
            buffer += data

            # Cerca il carattere di nuova linea
            while '\n' in buffer:
                line, buffer = buffer.split('\n', 1)
                if line:
                    try:
                        json_data = json.loads(line.strip())
                        await publish_mqtt(event_loop.mqtt_client, json_data)

                    except json.JSONDecodeError:
                        print(f"Errore nel decodificare JSON: {line}")
    except:
        sock.close()
    finally:
        sock.close()


async def connect_bluetooth(event_loop: EventLoop, address: str):
    port = 1
    sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
    try:
        sock.connect((address, port))
        await event_loop.event_queue.put(event(EventType.device_connected, sock))
    except bluetooth.btcommon.BluetoothError as err:
        await event_loop.event_queue.put(event(EventType.device_connection_failed, (err, address)))
    return None


# Bluetooth scanner
async def bluetooth_scanner(event_loop: EventLoop):
    while True:
        devices = bluetooth.discover_devices(duration=8, lookup_names=True, flush_cache=True, lookup_class=False)
        for addr, name in devices:
            await event_loop.event_queue.put(event(EventType.device_found, {'address': addr, 'name': name}))
        await asyncio.sleep(10)


# Funzioni MQTT
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print(f"Connection failed with code {rc}")

def on_disconnect(client, userdata, rc):
    print("Disconnected from MQTT Broker!")

async def publish_mqtt(client, data: Dict[str, Any]):
    payload_str = json.dumps(data)
    client.publish(MQTT_TOPIC, payload_str)
    print(f"Data published: {payload_str}")

async def main():
    mqtt_client = mqtt.Client()
    mqtt_client.on_connect = on_connect
    mqtt_client.on_disconnect = on_disconnect
    mqtt_client.connect(MQTT_BROKER, MQTT_PORT, 60)
    mqtt_client.loop_start()

    event_loop = EventLoop(mqtt_client)

    await asyncio.gather(
        event_loop.run(),
        bluetooth_scanner(event_loop)
    )

if __name__ == "__main__":
    asyncio.run(main())
