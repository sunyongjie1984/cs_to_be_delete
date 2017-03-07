import threading
from time import sleep, time, ctime

loops = [4, 2]

def loop(nloop, nsec) :
    print 'start loop', nloop, 'at :', ctime(time())
    sleep(nsec)
    print 'loop', nloop, 'done at:', ctime(time())

def main() :
    print 'starting threads.....'
    threads = []
    nloops = range(len(loops))

    for i in nloops :
        t = threading.Thread(target=loop, args=(i, loops[i]))
        threads.append(t)

    for i in nloops :
        threads[i].start()

    for i in nloops :
        threads[i].join()

    print 'all DONE at :', ctime(time())

if __name__ == '__main__' :
    main()