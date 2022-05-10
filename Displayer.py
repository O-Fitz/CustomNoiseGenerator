import numpy as np
import matplotlib.pylab as plt
import subprocess as sub

def getNoiseMap(filename="field.txt"):
    data_from_file = []
    with open(filename, "r") as file:
        for line in file:
            data_from_file.append(line.rstrip())
    itemNo = -1
    lineNo = 0
    for line in data_from_file:
        if (itemNo == -1):
            #print(int(line))
            length = int(line)
            data = np.zeros((length, length))
        else:
            if itemNo == length-1:
                lineNo += 1
                itemNo = 0
            if lineNo == length:
                break
            #print(lineNo, itemNo)
            data[lineNo][itemNo] = float(line)
        itemNo += 1
    return data


#o = sub.call("Debug/NoiseGenerator.exe")
#o.wait()
#noise = getNoiseMap("Debug/field.txt")
noise = getNoiseMap("field.txt")
plt.imshow(noise, cmap=plt.cm.gray, interpolation='none')
plt.colorbar()
plt.show()
