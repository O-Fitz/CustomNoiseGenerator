# CustomNoiseGenerator

## HOW TO USE

### PREREQUESITES:
  python installed
    matplotlib installed
  c++ compiler if you want to recompile the scripts

### WINDOWS:
  Files needed (same directory):
    Displayer.py
    field.txt
    NoiseGenerator.exe

  - Run the Displayer.py python file.
  - You can either pass in the order from the command line (eg. python Displayer.py 100) or not.
  - If not, it will ask you to enter an order as an input() statement.
  - The order is the nxn grid it will export to field.txt.
  - A matplotlib window will open visuallising the data after it has been computed.

### LINUX/MAC:
  - Need all files
 
  - You will need to compile the c++ scripts NoiseGenerator.cpp and RANDOM.cpp
 
  - Using g++, it would look like:
      g++ -o NoiseGenerator NoiseGenerator.cpp RANDOM.cpp
 
  - In the Displayer.py python file, remove the .exe ending to the running of the executable on line 31.
  - Run the Displayer.py python file.
  - You can either pass in the order from the command line (eg. python3 Displayer.py 100) or not.
  - If not, it will ask you to enter an order as an input() statement.
  - The order is the nxn grid it will export to field.txt.
  - A matplotlib window will open visuallising the data after it has been computed.
 
 
 
## ACCESSING THE DATA
  - The python file is acutally padding.
  - All it does is ask for the order, run the cpp file, and finally display it using matplotlib.
  - The acutal data is stored in the field.txt file.
  - The format the data is stored in is:
    - The first line is the order.
    - The rest of the lines are the actual data (first n terms is the row in the array, second n terms the second etc).
  - When running the NoiseGenerator execuable, you must pass in the order as an argument (eg. ./NoiseGenerator 100)



