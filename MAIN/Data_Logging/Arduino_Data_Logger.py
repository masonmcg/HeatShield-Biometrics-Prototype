import serial
import matplotlib.pyplot as plt
from drawnow import drawnow
import csv
from tkinter import *
import os

# Initialize serial connection
arduino_port = 'COM7'  # Change this to your Arduino's serial port
baud_rate = 9600
ser = serial.Serial(arduino_port, baud_rate)

# Initialize variables for plotting
data = []
plot_data_flag = False
csv_file = None
csv_writer = None

# Function to generate a unique file name
def get_unique_filename(base_filename):
    filename, extension = os.path.splitext(base_filename)
    counter = 1
    while os.path.exists(f"{filename}_{counter}{extension}"):
        counter += 1
    return f"{filename}_{counter}{extension}"

# Initialize GUI
root = Tk()
root.title("Arduino Data Logger")

start_stop_frame = Frame(root)
start_stop_frame.pack()

recording_indicator = Label(start_stop_frame, text="Not Recording", fg="red")
recording_indicator.grid(row=0, column=0, padx=20, pady=20)

def start_logging():
    global plot_data_flag, csv_file, csv_writer
    plot_data_flag = True
    csv_filename = get_unique_filename('arduino_data.csv')
    csv_file = open(csv_filename, 'w', newline='')
    csv_writer = csv.writer(csv_file)
    csv_writer.writerow(['Data'])
    recording_indicator.config(text="Recording", fg="green")

def stop_logging():
    global plot_data_flag, csv_file
    plot_data_flag = False
    if csv_file:
        csv_file.close()
    recording_indicator.config(text="Not Recording", fg="red")
    root.quit()  # Close the whole program

start_button = Button(start_stop_frame, text="Start Logging", command=start_logging)
start_button.grid(row=1, column=0, padx=20, pady=20)

stop_button = Button(start_stop_frame, text="Stop Logging", command=stop_logging)
stop_button.grid(row=2, column=0, padx=20, pady=20)

# Plotting function
def plot_data():
    plt.title('Live Arduino Data')
    plt.grid(True)
    plt.ylabel('Data')
    plt.plot(data, 'ro-')
    
    if data:
        plt.text(0.5, -0.1, f"Most recent value: {data[-1]}", horizontalalignment='center', verticalalignment='center', transform=plt.gca().transAxes)

# Main loop
while True:
    # Read data from serial port
    line = ser.readline().decode('utf-8').strip()
    try:
        val = float(line)
        data.append(val)
        if plot_data_flag:
            csv_writer.writerow([val])
    except ValueError:
        pass

    # Plot live data
    drawnow(plot_data)
    plt.pause(0.000001)  # Pause to update the plot

    # Limit the length of data to plot for better performance
    if len(data) > 50:
        data.pop(0)

    # Check for GUI events
    root.update()

# Close serial connection when the program exits
ser.close()