#Name: Nicholas Glover
#Date: 2/15/2022

import re
import string
import os

def printsomething():
    print("Hello from python!")

def PrintMe(v):
    print("You sent me: " + v)
    return 100;

def SquareValue(v):
    return v * v

# Reads the item list file into a dictionary
def ReadFile():
    filepath = '..\\Release\\Project-3-Input-File.txt'
    item_list = {}
    with open(filepath, 'r') as file:
        for line in file:
            line = line.strip()
            if line in item_list:
                item_list[line] = item_list[line] + 1
            else:
                item_list[line] = 1

    return item_list

# Prints out the dictionary of items purchased
def PrintItemDict():
    item_list = ReadFile()

    item_width = 0
    quant_width = 0
    
    for item, quant in item_list.items():
        if item_width < len(item):
            item_width = len(item)
        if quant_width < len(str(quant)):
            quant_width = len(str(quant))
    item_width += 3
    quant_width += 1
    for item, quant in item_list.items():
        print('{item:>{item_width}}:{quant:_>{quant_width}}'.format(item=item, quant=quant, item_width=item_width, quant_width=quant_width))
    print('\n')

# Prints out a specific item if it's in the dictionary read from the file and returns the frequency. If it isn't in the dictionary,
# it prints such and returns a 0.
def PrintSpecItem(item):
    item_list = ReadFile()

    item = item.strip().capitalize()

    if item in item_list:
        return item_list[item]
    else:
        return 0

# Reads data from the input file into a dictionary then writes to the passed file the items and their frequencies.
def WriteFrequencies(filename):
    item_list = ReadFile()

    path = '..\\Release\\'
    filepath = os.path.join(path, filename)

    file = open(filepath, 'w')

    for item, quant in item_list.items():
        file.write('{} {}\n'.format(item, quant))

    file.flush()
    file.close()

    return 0