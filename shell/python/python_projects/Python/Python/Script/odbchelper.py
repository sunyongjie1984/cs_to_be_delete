def buildConnectionString(params):
    """Build a connection string from a dictionary of parameters.

    Returns string."""
    return ";".join(["%s=%s" % (k, v) for k, v in params.items()])

def foo(debug = 1) :
    'derermine if in debug mode with default argument'
    if debug :
        print 'in debug mode'
    print 'done'

class fooclass :
    'my very first class : fooclass'
    version = 0.1

    def __init__(self, nm = 'Jchn Doe') :
        'constructor'
        self.name = nm
        print 'Created a class instance for', nm

    def showname(self) :
        'display instance attribute and class name'
        print 'Your name is', self.name
        print 'My name is', self.__class__

    def showver(self) :
        'display class(static) attribute'
        print self.version

    def addMe2Me(self, x) :
        'apply + operation to argument'
        return (x+x)

if __name__ == "__main__":
    fool = fooclass()

    fool.showname()
    fool.showver()
    print fool.addMe2Me(5)
    print fool.addMe2Me('xyz')

    myParams = {"server":"mpilgrim", \
                "database":"master", \
                "uid":"sa", \
                "pwd":"secret" \
                }
    print buildConnectionString(myParams)
    
    mystr = 'hello world!'    
    print 'hello world!'
    print mystr

    print -2*4, 3**2
    print '%s is number %d !' %('python', 2)

    #user = raw_input('Enter login name : ')
    #print 'your login is:', user

    #num = raw_input('Now enter a number : ')
    #print 'doubling your number : %d' %(int(num) *2)

    counter = 0
    miles = 1000.0
    counter += 4
    kilometers = 1.609 * miles
    print '%f miles is the same as %f km' %(miles, kilometers)

    if counter > 5 :
        print 'true stopping after %d iterations' %(counter)
    elif counter <> 5 :
        print 'elif stopping after %d iterations' %(counter)
    else :
        print 'false stopping after %d iterations' %(counter)

    while counter > 0 :
        print 'loop # %d' %(counter)
        counter -= 1

    for eachNum in [0,1,2,3,4,5] :
        print eachNum

    for item in ['e-mail', 'net-srufing', 'homework', 'chat'] :
        print item

    for eachNum in range(6) :
        print eachNum

    foo(0)

    