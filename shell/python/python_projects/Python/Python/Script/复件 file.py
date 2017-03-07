def readfile1() :
    filename = raw_input('Enter file name:')
    file = open(filename, 'r')
    allline = file.readlines()
    file.close()
    for eachline in allline:
        print eachline

def readfile2() :
    """
    文件对象 可以访问普通的磁盘文件，还可以访问符合“文件”抽象概念的其他类型的设备
    访问文件时使用open()内建函数打开文件，并返回一个文件对象，这个文件对象提供了操作文件读写的方法
    open()函数中filename是文件的文件名称，‘a+’是文件对象的访问方式（表示以读和写方式打开）
    文件输入 read()函数把字节直接读到一个字符串里，根据参数决定读取长度
    文件输出 write()函数
    关闭文件句柄 close() 如果一个文件对象的引用线索减少为零，Python的废弃回收例程也会自动关闭这个文件
    文件对象的访问方式
    r 以读的方式打开
    w 以写的方式打开
    a 以写的方式打开，从EOF开始，文件不存在时，先创建文件
    r+ 以读和写的方式打开
    w+ 以读和写的方式打开
    a+ 以读和写的方式打开
    rb 以二进制读方式打开
    wb 以二进制写方式打开
    ab 以二进制追加方式打开
    rb+ 以二进制读和写方式打开
    wb+ 以二进制读和写方式打开
    ab+ 以二进制读和写方式打开
    """
    filename = raw_input('enter file name:')
    readsize = 100
    done = 0
    file = open(filename, 'a+')
    while not done :
        readdata = file.read(readsize)
        if readdata != "":
            #print readdata
            print file.tell()
        else :
            done = 1
    file.close()

if __name__ == "__main__":
    readfile2()
