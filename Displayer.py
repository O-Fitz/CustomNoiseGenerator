import numpy as np
import matplotlib.pylab as plt
import subprocess as sub
import sys

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

if __name__ == "__main__":

    try:
        order = int(sys.argv[1])
    except IndexError:
        order = int(input("Order: "))
    o = sub.run(["NoiseGenerator.exe", str(order)])
    noise = getNoiseMap("field.txt")
    plt.imshow(noise, cmap=plt.cm.gray)
    #plt.size()
    plt.xlim([-1, order-1])
    plt.ylim([-1, order])
    plt.colorbar()
    plt.show()
