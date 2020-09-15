import os
for file in os.listdir():
    if file[len(file)-4:] == '.gch':
        os.remove(file)
    elif file[len(file)-2:] == '.o':
        os.remove(file)
