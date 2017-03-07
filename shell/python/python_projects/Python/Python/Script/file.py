def readfile1() :
    filename = raw_input('Enter file name:')
    file = open(filename, 'r')
    allline = file.readlines()
    file.close()
    for eachline in allline:
        print eachline

def readfile2() :
    filename = raw_input('enter file name:')
    readsize = 100
    done = 0
    file = open(filename, 'a+')
    while not done :
        readdata = file.read(readsize)
        if readdata != "":
            file.seek(20, 1)
            print readdata
            print '--------------------------------'
            #print file.tell()
            done = 1

        else :
            done = 1
    file.close()

if __name__ == "__main__":
    readfile2()
