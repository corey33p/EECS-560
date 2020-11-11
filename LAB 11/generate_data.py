import random

def generate(how_many,max_dist = 100):
    file = open("data.txt", "w+")
    for i in range(how_many):
        how_many_neighbors = random.gauss(how_many/8,how_many/14)
        how_many_neighbors = max(how_many_neighbors,2)
        how_many_neighbors = min(how_many_neighbors,how_many/3)
        how_many_neighbors = min(how_many_neighbors,15)
        how_many_neighbors = int(how_many_neighbors)
        is_neighbors = set()
        is_neighbors.add(i)
        for j in range(how_many_neighbors):
            neighbor = random.randint(0,how_many-1)
            while neighbor in is_neighbors:
                neighbor = random.randint(0,how_many-1)
            is_neighbors.add(neighbor)
            weight = random.randint(1,100)
            file.write(str(i)+","+str(neighbor)+","+str(weight)+",")
    file.close()

import filecmp
import time
import os
from shutil import copyfile
import difflib

def isSame(a,b):
    file1 = open(a, 'r')
    file2 = open(b, 'r')
    a = difflib.SequenceMatcher(None, file1.read(), file2.read())
    file1.close()
    file2.close()
    return a.ratio() == 1

def resetFiles():
    file = open("outputy.txt", "w+")
    file.write("A")
    file.close()
    file = open("outputz.txt", "w+")
    file.write("A")
    file.close()
    file = open("outputx.txt", "w+")
    file.write("A")
    file.close()

def saveFiles():
    copyfile("outputy.txt", "outputyout.txt")
    copyfile("outputz.txt", "outputzout.txt")
    copyfile("data.txt", "dataout.txt")

import draw_network

n = 13
generate(n)
resetFiles()
while True:
    counter = 1
    while True:
        generate(n)
        os.system("./a.out data.txt > outputy.txt 0 0")
        os.system("./a.out data.txt > outputx.txt 0 1")
        os.system("./a.out data.txt > outputz.txt 1 0")
        print("attempt "+str(counter),end="\r")
        counter += 1
        # draw_network.make_graph('data.txt')
        # time.sleep(2)
        if not isSame("outputy.txt","outputz.txt") and not isSame("outputx.txt","outputz.txt"):
            break
    saveFiles()
    draw_network.make_graph('data.txt')
    # break
    resetFiles()
    print(str(n)+" success. pausing...")
    # time.sleep(2)
    n-=1
