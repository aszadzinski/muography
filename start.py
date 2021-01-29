#!/usr/bin/env python3

import random
from itertools import count
import matplotlib.pyplot as plt
import os
import subprocess
import time
from sys import argv
import numpy as np

#plt.style.use('ggplot')

x_values = []
y_values = []

nlines = 0




if __name__ == "__main__":
    with open(argv[1],'r') as file:
        lines = file.readlines()
        data = [ i[:-1].split() for i in lines ]
        data = np.array(data,dtype='float64').T
    plt.hist2d(data[1],data[2],bins=int(argv[2]))
    plt.xlabel("X ")
    plt.ylabel("Y ")
    plt.legend()
    plt.show()
