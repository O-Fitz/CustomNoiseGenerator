# CustomNoiseGenerator

HOW TO USE

PREREQUESITES:
  python installed
    matplotlib installed
  c++ compiler if you want to recompile the scripts

WINDOWS:
  Files needed (same directory):
    Displayer.py
    field.txt
    NoiseGenerator.exe

  Run the Displayer.py python file.
  It will ask you to enter an order, this is the nxn grid it will export to field.txt
  A matplotlib window will

LINUX/MAC:
  Need all files
 
  You will need to compile the c++ scripts.
  The scripts are: NoiseGenerator.cpp and RANDOM.cpp
 
  Using g++, it would look like:
  g++ -o NoiseGenerator NoiseGenerator.cpp RANDOM.cpp
 
  In the Displayer.py python file, remove the .exe ending to the running of the executable on line 31
  Run the Displayer.py python file.
  It will ask you to enter an order, this is the nxn grid it will export to field.txt
 
 
 
ACCESSING THE DATA
  The python file is acutally padding.
  All it does is ask for the order, run the cpp file, and finally display it using matplotlib
  The acutal data is stored in the field.txt file
  The format is:
    -The first line is the order
    -The rest of the lines are the actual data 
  
