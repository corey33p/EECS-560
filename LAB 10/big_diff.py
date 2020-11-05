import sys

fName1,fName2 = sys.argv[1],sys.argv[2]

if fName1 is None or fName2 is None: assert(1/0=="face")

lineIndex = 0
file1 = open(fName1,'r')
file2 = open(fName2,'r')
file1Lines = file1.readlines()
file2Lines = file2.readlines()

def cleanLine(line):
    if line=="": return line
    line=line.strip("\n")
    if line=="": return line
    while line[len(line)-1]==" ":
        line = line[:len(line)-1]
        if line=="": return line
    return line

file1Lines = [cleanLine(a) for a in file1Lines]
file2Lines = [cleanLine(a) for a in file2Lines]

# print("len(file1Lines): "+str(len(file1Lines)))
# print("len(file2Lines): "+str(len(file2Lines)))

file1Spacing = ""
file2Spacing = ""
if not (file1Lines==file2Lines):
    if len(fName1)<len(fName2):
        for _ in range(len(fName2)-len(fName1)):
            file1Spacing += " "
    elif len(fName1)>len(fName2):
        for _ in range(len(fName1)-len(fName2)):
            file2Spacing += " "
    for i in range(len(file1Lines)):
        if file1Lines[i]!=file2Lines[i]:
            print("\nline "+str(i)+":")
            print(str(fName1)+file1Spacing+": '"+file1Lines[i]+"'")
            print(str(fName2)+file2Spacing+": '"+file2Lines[i]+"'")
else:
    print("Files " + fName1 + " and " + fName2 + " are identical")
