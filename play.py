import serial
import subprocess
import sys
import os

SERIAL_PORT = '/dev/cu.usbserial-58EB0141801'
BAUD_RATE = 115200
SOUNDS_DIR = './sounds'

instruments = ["flute", "horn", "tambourine", "clarinet", "lyre"]

looping_processes = {}

def play_once(inst):
    path = f"{SOUNDS_DIR}/{inst}.mp3"
    if os.path.exists(path):
        subprocess.Popen(["afplay", path])
    else:
        print(f"Missing sound file: {path}")

def start_loop(inst):
    path = f"{SOUNDS_DIR}/{inst}.mp3"
    if os.path.exists(path) and inst not in looping_processes:
        p = subprocess.Popen(
            f'while true; do afplay "{path}"; done',
            shell=True
        )
        looping_processes[inst] = p
        print(f"  Started loop: {inst}")

def stop_loop(inst):
    if inst in looping_processes:
        looping_processes[inst].kill()
        looping_processes.pop(inst)
        print(f"Stopped loop: {inst}")

def stop_all_loops():
    for inst in list(looping_processes.keys()):
        stop_loop(inst)

try:
    ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    print(f"Connected to {SERIAL_PORT}")
except Exception as e:
    print(f"Could not connect: {e}")
    sys.exit(1)

current_mode = 0
print("Listening for touch events...")
print("Mode 0 = single hit | Mode 1 = loop and composition")

while True:
    try:
        line = ser.readline().decode('utf-8').strip()
        if not line:
            continue

        print(f"Received: {line}")

        if line.startswith("MODE:"):
            current_mode = int(line.split(":")[1])
            print(f"Switched to Mode {current_mode}")
            stop_all_loops()
            continue

        parts = line.split(",")
        if len(parts) == 2:
            mode = int(parts[0])
            inst = parts[1]

            if mode == 0:
                play_once(inst)
            elif mode == 1:
                if inst in looping_processes:
                    stop_loop(inst)
                else:
                    start_loop(inst)

    except KeyboardInterrupt:
        print("\nQuitting...")
        stop_all_loops()
        ser.close()
        break
    except Exception as e:
        print(f"Error: {e}")