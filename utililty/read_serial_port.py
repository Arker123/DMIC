# code to read serial port and save data to file
from serial import Serial

# open serial port
ser = Serial("COM9",115200)

# open file to save data
#f = open('data.txt', 'w')

with open('data.txt', 'wb') as f:
    k = 0
    while (True):
        line = ser.readline()        
        #print(line, end=' ')        
        if line == b'-- start\r\n':
            print('start')            

        if line == b'-- mid\r\n':
            k+=1
            if (k%100 == 0):
                print('mid', k)
            continue
        
        if line == b'-- end\r\n':
            print('empty')          
            break

        f.write(line)