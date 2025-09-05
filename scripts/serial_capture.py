import serial
import csv
from datetime import datetime

PORT = "/dev/ttyUSB0"
BAUDRATE = 115200

try:
    ser = serial.Serial(PORT, BAUDRATE, timeout=1)
except serial.SerialException:
    print(f"Erro: não foi possível abrir a porta {PORT}")
    exit(1)

with open("data.csv", "w", newline="") as csvfile:
    writer = csv.writer(csvfile)
    writer.writerow(["Umidade", "Temperatura", "Timestamp"])

    print("Capturando dados... Pressione Ctrl+C para parar.\n")

    try:
        while True:
            line = ser.readline().decode("utf-8").strip()
            if "," in line:
                humidity, temperature = line.split(",")
                writer.writerow([humidity, temperature, datetime.now().isoformat()])
                print(f"Saved: {humidity}, {temperature}\n")

    except KeyboardInterrupt:
        print("Captura finalizada!\n")