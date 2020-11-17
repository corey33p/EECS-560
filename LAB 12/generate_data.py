import random

def generate(how_many,max_val = 100):
    file = open("data.txt", "w+")
    for i in range(how_many):
        val = random.randint(1,100)
        file.write(str(val)+",")
    file.close()

import filecmp
import time
import os
from shutil import copyfile
import difflib

# def isSame(a,b):
#     file1 = open(a, 'r')
#     file2 = open(b, 'r')
#     a = difflib.SequenceMatcher(None, file1.read(), file2.read())
#     file1.close()
#     file2.close()
#     return a.ratio() == 1

def resetFiles():
    file = open("outputy.txt", "w+")
    file.write("A")
    file.close()
    # file = open("outputz.txt", "w+")
    # file.write("A")
    # file.close()

def saveFiles():
    copyfile("outputy.txt", "outputyout.txt")
    # copyfile("outputz.txt", "outputzout.txt")
    copyfile("data.txt", "dataout.txt")


n = 33
generate(n)
resetFiles()
while True:
    counter = 1
    while True:
        generate(n)
        os.system("./b.out data.txt > outputy.txt")
        print("attempt "+str(counter),end="\r")
        counter += 1
        # draw_network.make_graph('data.txt')
        # time.sleep(2)
        with open("outputy.txt") as f:
            lines = f.readlines()

        the_list = lines[0].split()
        while the_list[len(the_list)-1] == '\n':
            the_list = lines[:len(the_list)-1]

        # print("the_list: "+str(the_list))
        # input("len(the_list): "+str(len(the_list)))
        isSorted = all(the_list[i] <= the_list[i+1] for i in range(len(the_list)-1))
        if not isSorted: break
    saveFiles()
    # break
    resetFiles()
    print(str(n)+" success. pausing...")
    # time.sleep(2)
    n-=1
