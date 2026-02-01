# Import all of vpython
from vpython import *

##########################################
###### Section ONE                 ########
############################################
# Math functions/constants ##################
# Math functions/constants ###################
# Math functions/constants ##################
############################################
###### Section ONE                  #######
##########################################

# Global Variables
######################
# scale of the scene
scale = 2
# Strength of the wind (m/s)
vw = 5.5
# Power output of cyclist (Watts)
P = 300
# Angle of the slope
theta = 7.3
# Coefficient of Friction
beta = 0.18
# mass of rider (kg)
m = 70
# distance to travel upwards (m)
L = 800

# Main Function
#####################
# MAIN # MAIN # MAIN # MAIN # MAIN # MAIN # MAIN # MAIN # >>>>
# # MAIN # MAIN # MAIN # MAIN # MAIN # MAIN # MAIN # MAIN <<<<
# MAIN # MA
# IN # MAIN # MAIN # MAIN # MAIN # MAIN # MAIN # >>>>
def main():
    print ("Sin:", sin(rad(theta)))
    print ("SinDown:", sin_down(theta))
    print ("SinUp:", sin_up(theta))

    print ("V_Up: ", vel_up())
    print ("V_Term", v_term())
    print ("T_up", L/vel_up())
    print ("T_down", t_down())

    while True:
        rate(120)
        if (not t.tick()):
            continue

        v = vel_up()
        vd = L/(t_down()*2)
        if (going_up):
            vel_curve.plot(t.t, v)
            pm.update(t.dt()*v*0.5)
            c.cycle(t.dt()*v*0.5)
        else:
            vel_curve.plot(t.t, vd)
            c.cycle(t.dt()*vd*0.5, 1)
            pm.update(t.dt()*vd*0.5)

######################################
######### Section Breaker ############
######################################

# Object Definitions
######################
##### Creates a Complex number object to handle calculations
class Complex:
    # Constructor
    def __init__(self, real, img=0):
        self.real = real  
        self.img = img

    # Allows adding of Complex numbers
    def add(self, other):
        return Complex(self.real + other.real, self.img + other.img)
    
    # Allows subtraction of Complex numbers
    def sub(self, other):
        return Complex(self.real - other.real, self.img - other.img)
    
    # Allows multiplication of Complex numbers
    def mul(self, other):
        real = self.real * other.real - (self.img * other.img)
        img = self.real * other.img + self.img * other.real
        return Complex(real, img)
    
    def div(self, other):
        bot = other.real**2 + other.img**2
        return Complex((self.real*other.real + self.img*other.img)/bot,(self.img*other.real  - self.real*other.img)/bot)
    
    # Allows us to negate our Complex number
    def neg(self):
        return Complex(-self.real, -self.img)
    
    # Allows us to check if two Complex numbers are real
    def eq(self, other):
        return (self.real == other.real and self.img == other.img)
    
    # Allows us to grab our Complex conjugate
    def conjugate(self):
        return Complex(self.real, -self.img)
    
    # Grabs the absolute value of our Complex number
    def abs(self):
        return (self.real**2 + self.img**2)**0.5
    
    # Allows us to print a Complex number
    def str(self):
        return "(" + str(self.real) + ", " + str(self.img) + "i)"
#################################################################

# Function Definitions
#######################
# Grabs the sign of a value
def sgn(val):
    if (val > 0):
        return 1
    elif (val == 0):
        return 0
    else:
        return -1

# Convers angle theta to radians
def rad(theta):
    return (theta * pi / 180)

# Gets the Sin Up w/rolling friction
def sin_up(theta):
    # turn our angle into radians
    ang = rad(theta)
    return sin(ang) + (mu * cos(ang))

# Gets the Sin Down w/rolling friction
def sin_down(theta):
    # turn our angle into radians
    ang = rad(theta)
    return sin(ang) - (mu * cos(ang))

#### Grabs only the real roots and returns them
def real_roots(vals):
    newList = []
    for i in vals:
        if (abs(i.img) < 1e-6):
            newList.append(i.real)
    return newList

#### SQUARE POWER FUNCTION
def csqrt(x):
    if (x < 0):
        return Complex(0, abs(x)**0.5)
    return Complex(x**0.5, 0)

#### CUBE POWER FUNCTION
# gets the cubic root
def cbrt(x):
    if x.real >= 0:
        return Complex(x.real**(0.333333333))
    else:
        return Complex(-((-x.real)**(0.333333333)))

#### CUBE ROOT FUNCTION
# gets the cubic root of a polynomial ax^3 +bx^2 + cx + d
def cubic_roots(a, b, c, d):
    # Convert to depressed cubic t^3 + pt + q (very sad)
    p = (3*a*c - b*b) / (3*a*a)
    q = (27*a*a*d - 9*a*b*c + 2*b*b*b) / (27*a*a*a)

    #Then we calculate the discriminate
    dis = (q*q)/4 + (p*p*p)/27

    # First we calculate the root with the big annoying formula.
    dd = csqrt(dis)              # csqrt turns it into a Complex
    A = cbrt(Complex(-q/2).add(dd))
    B = cbrt(Complex(-q/2).add(dd.neg()))

    # Then we find A + B which gives us our first root
    t1 = A.add(B)
    ba = Complex(b/(3*a), 0)       # We will use this value later
    r1 = t1.sub(ba)

    #Now we can start solving for the other roots.
    # We first find the Complex root thing
    omega = Complex(-0.5, (3**0.5)/2)
    # calc t1 & t2
    t2 = A.mul(omega).add(B.mul(omega.conjugate()))
    t3 = A.mul(omega.conjugate()).add(B.mul(omega))

    # then we get our other roots
    r2 = t2.sub(ba)
    r3 = t3.sub(ba)

    # finally we return
    return real_roots([r1, r2, r3])

# Calculates the upward velocity of the cyclist.
def vel_up():
    a = beta
    b = -2 * beta * vw
    c = beta * vw**2 + m*g*(sin(rad(theta)) + mu*cos(rad(theta)))
    d = -P

    roots = cubic_roots(a, b, c, d)
    # physically valid root: positive real
    roots = [r for r in roots if r > 0]
    return min(roots)

# Calculates the terminal velocity of the cyclist.
def v_term():
    return (abs(m*g*sin_down(theta)/beta))**(0.5)

#####################################
# Solving the Transcendental Equation
#####################################

# First, we just define a generic exponent function
def exp(x):
    x = float(x) 
    if x > 700.0:
        return -1
    if x < -700.0:
        return 0.0
    if abs(x) < 1e-5:
        return 1 + x + x*x/2
    return e ** x

# Natual logging time. We just use a taylor series approximation
def ln(x):
    if x <= 0:
        print("Natural log domain error, must be greater than or eq to 0. returning -1")
        return -1

    # extract exponent k such that x = m * 2^k
    k = 0
    m = x
    while m > 2.0:
        m *= 0.5
        k += 1
    while m < 1.0:
        m *= 2.0
        k -= 1
    y = m - 1.0

    # 4th-order taylor approximation
    y2 = y*y
    y3 = y2*y
    y4 = y3*y

    ln_m = y - y2/2 + y3/3 - y4/4
    return ln_m + k * ln2 #natural log of 2

# Next we just get the generic cosh formula for the trasncendental equation
def cosh(x):
    x = float(x)
    ax = abs(x)
    ex = exp(ax)
    return 0.5 * (ex + 1/ex)
    
def ln_cosh(x):
    x = float(x)
    ax = abs(x)
    term = ln(1 + exp(-2*ax))
    return ax + term - ln2

# This inverse tanh method will give us tau
def itanh(x):
    return 0.5*ln((1+x)/(1-x))
def tau_func():
    vt = v_term()
    return (el/vt)*itanh(vw/vt)

# We want to find the root of this transcendental function, so we perform a binary search.
# This is the function we perform the search on! (The yucky one from the write-up)
def transcendental_func(t, tau):
    vt = v_term()
    X1 = vt*(t + tau)/el
    X2 = vt*(tau)/el
    c1 = ln_cosh(X1)
    c2 = ln_cosh(X2)
    return el*(c1 - c2) - vw*t - L/2

# Finally solving for the actual value. We perform a binary search because there's no analytical solution to this, and I know how to implement a binary search algorithm.
# Note here that:
# Left = lower boundary time guess
# Right = higher boundary time guess
# Tolerance = how satisfied we are with our answer
def t_down(left = 0.0, right = 10.0, tolerance = 1e-6):
    # expand right bound until sign differs
    vt = v_term()
    tau = tau_func()
    # perform a while loop to move the right boundary up. 
    while transcendental_func(left, tau) * transcendental_func(right, tau) > 0:
        # multiply by powers of two because i dont want this to take forever
        right *= 2.0
        # If our right ges super super high, we are not finding the solution
        if right > 1e9:
            print("Cannot find the end boundary for the binary search. Returning -1!!!")
            return -1

    # now we find a point where the right boundary is ABOVE the correct answer
    # and the left boundary is BELOW the correct answer. 
    # then we average the two and just say "yea it's good".
    while right - left > tolerance:
        mid = (left + right) / 2.0
        # calculate our transcendental functions
        if transcendental_func(left, tau) * transcendental_func(mid, tau) <= 0:
            # if our right is too high, make it the midpoint
            right = mid
        else:
            # if our left is too low, we move it to the midpoint
            left = mid
    # Here we return the average of the the two
    ret =  (left + right) / 2.0
    # but we also got to get the terminal downwards velocity too:
    ret2 = (L/2)/v_term()
    return ret + ret2


######################################
######### Section Breaker ############
############ Constants ###############
######################################

# Define our constants
######################
# Gravity (m/s^2)
g = 9.81
# Air density (1.225 kg/m^3)
p = 1.225
# Coefficient of rolling resistance
mu = 0.006
# Pi
pi = 3.14159
# e
e = 2.71828182845
# natural log of 2
ln2 = 0.6931471805599453
# special distance constant
el = m/beta
# which direction we are goind
going_up = True
















##########################################
###### Section TWO                 ########
############################################
# Visuals ###################################
# Visuals ####################################
# Visuals ###################################
############################################
###### Section TWO                  #######
##########################################


############################
## Timer keeps track of many aspects of the scene. Keeps main clean.
class Timer:
    #initializes the timer
    def __init__(self, frame_rate):
        # keeps track of the previous frame's time
        self.prev = clock()
        # keeps track of current time
        self.t = 0
        # keeps track of the change in time
        self.ct = 0
        # keeps track of our target frame_rate
        self.target_dt = 1/frame_rate
        # keeps track of the number of times we need to update per frame
        self.updates = 0

    # returns true if we run the simulation, false otherwise  
    def tick(self):
        # update current time
        self.t = clock()
        # find change in time
        self.ct += (self.t - self.prev)
        # get the previous time
        self.prev = clock()
        # get the number of frames we missed
        self.updates = 0
        # if our dt is over our target, count the number of times we need to update. 
        while (self.ct >= self.target_dt):
            # Keep subtracting from our target and add the numnber of updates
            self.ct -= self.target_dt
            self.updates += 1
        # if the number of updates is none, we don't advance
        if (self.updates == 0):
            return False
        # otherwise, we advance
        return True
    
    # this returns the amount we need to update each element by. 
    def dt(self):
        return self.target_dt * self.updates

############################
## BikeElement is a generic, easy to use soft shape
class BikeElement:
    def __init__(self, pos, length, rad, new_axis=vec(0,0,1), col=vec(1,1,1)):
        # store the variables inserted
        self.pivot = pos
        self.length = length
        self.rad = rad  
        self.axis = new_axis
        # Normalize the axis so we can scale it properly
        axis_unit = norm(new_axis)

        # first sphere at the start of the element
        self.c1 = sphere(pos=self.pivot + axis_unit*rad, radius=rad, color = col)
        # tube (cylinder) connecting the spheres
        # cylinder.axis already includes magnitude, so length parameter is included in axis
        self.tube = cylinder(pos=self.pivot + axis_unit*rad, axis=axis_unit*(self.length - 2*rad), radius=rad, color = col)
        # end cap sphere at the end of the element
        self.c2 = sphere(pos=self.pivot + axis_unit*(self.length - rad), radius=rad, color = col)

    # rotates around the original pivot point provided
    def rotate(self, ang):
        # rotate each component around the pivot along the given axis
        self.c1.rotate(angle=ang, axis=vec(0,0,1), origin=self.pivot)
        self.tube.rotate(angle=ang, axis=vec(0,0,1), origin=self.pivot)
        self.c2.rotate(angle=ang, axis=vec(0,0,1), origin=self.pivot)

    # lets us specify a specific axis
    def set_axis(self, axis):
        # c1 does not nede to change but the others do
        self.axis = norm(axis)
        self.tube.axis = self.axis*self.length
        self.c2.pos = (self.tube.pos + (self.axis)*self.length)

    # moves the object by a provided vector
    def move(self, pos):
        self.pivot += pos
        self.c1.pos += pos
        self.tube.pos += pos
        self.c2.pos += pos

    # sets the position of the object to a new pivot
    def set_pos(self, pos):
        self.move(pos - self.pivot)

    # changes the length of the element
    def set_length(self, ls):
        self.length = ls
        axis_unit = norm(self.tube.axis)          # Keep the current direction
        self.tube.axis = axis_unit * (ls - 2*self.rad)  # Update cylinder axis length
        self.c2.pos = self.pivot + axis_unit*(ls - self.rad)  # Update end sphere position

    def set_rad(self, rad):
        self.c1.radius = rad
        self.tube.radius = rad
        self.c2.radius = rad


############################
## Gets the wheel for the cyclist
class Wheel:
    # initializes our wheel object
    def __init__(self, pos, rad, numSpokes):
        # stores some locals
        self.pivot = pos
        self.rad = rad
        # first we get the center connector
        self.center = sphere(radius = 0.0625*rad, pos = pos, emissive = True)

        # thickness of the tire
        thick = 0.0525*rad
        # next we define each spoke
        self.spokes = []
        # flipper lets us offset the spokes on the wheel
        flipper = -1
        for i in range(numSpokes):
            # gets the angle of our spoke
            ang = 2 * pi * i / numSpokes
            # appends our spoke to the spoke list
            self.spokes.append(cylinder(pos = self.pivot, radius = 0.0225*rad, axis = vec(rad * cos(ang), rad * sin(ang), thick/1.5 * flipper), emissive = True))
            flipper = flipper * -1
        
        # Then we get our outer ring
        self.tire = ring(pos = self.pivot, radius = rad, axis = vec(0, 0, 1), thickness = thick, emissive = True)

    # this lets us spin our wheel

    def rotate(self, ang):
        # Rotate the center
        self.center.rotate(angle = ang, axis = vec(0, 0, 1), origin = self.pivot)

        # Rotate each spoke
        for i in self.spokes:
            i.rotate(angle = ang, axis = vec(0, 0, 1), origin = self.pivot)

        # Rotate the tire
        self.tire.rotate(angle = ang, axis = vec(0, 0, 1), origin = self.pivot)

    # moves the object by a certain distance
    def move(self, pos):
        self.pivot += pos
        self.center.pos += pos
        for i in self.spokes:
            i.pos += pos
        self.tire.pos += pos

    # sets the position of the object
    def set_pos(self, pos):
        self.move(pos - self.pivot)

############################
## Class for bike pedal
class Pedal:
    def __init__(self, pos, radius, axis, pedalAxis = vec(0,1,0)):
        # initialize some simpler variables
        self.pivot = pos
        self.rad = radius
        self.axis = norm(axis)
        self.pedalAxis = pedalAxis
        self.outward_length = radius
        self.ang = pi/2 * pedalAxis.y

        # the pretend gear for the pedal with 6 spokes
        self.gear = Wheel(pos, radius, 6)
        # the outward jut of the pedal
        self.jut = cylinder(pos = self.pivot + pedalAxis*radius, radius = self.rad*0.0625, axis = self.axis*radius*0.5)
        # the thing that actually connects the pedal to the jut
        # the pedal itself
        self.pedal = box(pos = self.pivot + pedalAxis*self.outward_length + axis * radius + vec(0,0.1,0)*self.rad, length = self.gear.rad, width = 0.5*radius, height = 0.1*radius, color = vec(1,0.6,1))

    # rotates the lements of the pedal
    def rotate(self, ang):
        self.ang += ang
        self.gear.rotate(ang)
        self.jut.rotate(ang,self.axis,self.pivot)

        mod = 0
        amod = 0
        if (self.pivot.z < 0):
            mod = -1
            amod = pi
        else:
            mod = 1
        self.pedal.pos = vec(self.pivot.x + self.rad*cos(mod*self.ang + amod), self.pivot.y +self.rad*sin(mod*self.ang + amod) + 0.1*self.rad, self.axis.z*self.rad)

############################
## Class for bike frame. Makes the bike and rotates it. 
class BikeFrame:
    # constructor for the bike frame
    def __init__(self, pos, scale):
        # position and scale
        self.pos = pos
        self.scl = scale

        # set our back and front wheels
        self.backWheel = Wheel(pos - vec(2,0,0)*scale, scale, 24)
        self.frontWheel = Wheel(pos + vec(2,0,0)*scale, scale, 24)

        # set up small connectors in their center
        bearlen = scale*0.75 #length
        bearrad = scale*0.0625 #radius
        # back wheel bearing
        self.bwbearing = cylinder(pos = self.backWheel.pivot - vec(0, 0,bearlen/2), axis = vec(0,0,bearlen), radius = bearrad)
        # front wheel bearing
        self.fwbearing = cylinder(pos = self.frontWheel.pivot - vec(0, 0,bearlen/2), axis = vec(0,0,bearlen), radius = bearrad)

        #radius of all the components
        srad = 0.0625*scale
        # upperconnectors
        conlen = scale*1
        contilt = 0.18
        conforward = 0.3
        # axis definitions
        conbackbwaxis = vec(conforward, 1, contilt) * conlen
        confrontbwaxis = vec(conforward,1, -contilt)* conlen
        conbackfwaxis = vec(-conforward, 1, contilt)* conlen
        confrontfwaxis = vec(-conforward,1, -contilt)* conlen
        # back upper connectors
        self.bwbackcon = cylinder(pos = self.bwbearing.pos, axis= conbackbwaxis*scale, radius = srad)
        self.bwfrontcon = cylinder(pos = self.bwbearing.pos + self.bwbearing.axis, axis = confrontbwaxis*scale, radius = srad)
        # front upperconnectors
        self.fwbackcon = cylinder(pos = self.fwbearing.pos, axis= conbackfwaxis*scale, radius = srad)
        self.bwfrontcon = cylinder(pos = self.fwbearing.pos + self.bwbearing.axis, axis = confrontfwaxis*scale, radius = srad)

        # primary arch
        archlen = 2.8*scale
        self.arch = cylinder(pos = self.bwbackcon.pos + self.bwbackcon.axis, radius = srad, axis = vec(archlen,0,0))

        #### PEDALS
        # pedal overhang
        overhangpos = self.arch.pos + vec(archlen/3,0, 0)
        overhanglen = 1.5*scale
        self.pedoverh = cylinder(pos = overhangpos, axis = vec(0,-overhanglen, 0), radius = srad)
        # pedal bearing
        pedbearlen = 0.7*scale
        self.pedbear = cylinder(pos = self.pedoverh.pos + self.pedoverh.axis - vec(0,0,pedbearlen/2), radius = srad, axis = vec(0,0, pedbearlen))
        # pedal connector
        pedconlen = 1.44*scale
        self.pedcon = cylinder(pos = self.pedoverh.pos + self.pedoverh.axis, radius = srad, axis=vec(pedconlen*1.3,pedconlen,0))
        #### Different pedals
        #back pedal
        self.backped = Pedal(self.pedbear.pos, scale*0.5, vec(0,0,-1), vec(0,-1,0))
        self.frontped = Pedal(self.pedbear.pos + self.pedbear.axis, scale*0.5, vec(0,0,1), vec(0,1,0))

        ### SEAT
        self.seatcon = cylinder(pos = self.bwbackcon.pos + self.bwbackcon.axis, axis = vec(0,0.5,0)*scale, radius = srad)
        self.seat = box(pos = self.seatcon.pos+self.seatcon.axis, height = 0.125*scale, width = 0.7*scale, length = 0.7*scale)

        #### HANDLES!!!! (almost done)
        handlen = scale
        self.handcon = cylinder (pos = self.arch.axis + self.arch.pos, axis = vec(0,0.7,0)*scale, radius = srad)
        self.handbar = cylinder (pos = self.handcon.pos + self.handcon.axis - vec(0,0,handlen/2), axis = vec(0,0,handlen), radius = srad)
        self.handback = cylinder(pos = self.handbar.pos, axis = vec(0,0,-handlen/2), radius = srad*1.5)
        self.handfront = cylinder(pos = self.handbar.pos + self.handbar.axis, axis = vec(0,0,handlen/2), radius = srad*1.5)

    ##### rotation method
    def rotate(self, ang, down = 0):
        if (down == 0):
            self.backped.rotate(-ang*8)
            self.frontped.rotate(ang*8)
        self.backWheel.rotate(ang)
        self.frontWheel.rotate(ang)
        
### Class for the cyclist
class Cyclist:
    # constructor w/bike frame and everything
    def __init__(self, scale):
        # first we make our bike frame
        self.bf = BikeFrame(vec(0,0,0), scale)

        # set a generic color
        col = vec(0.55,0.55,1)

        # establish a base angle
        self.ang = 0
        self.scale = scale

        ## then we make the biker's body
        self.body = BikeElement(self.bf.seat.pos + vec(scale*0.5,self.bf.seat.height,0), scale*1.5, scale*0.5, vec(1,3,0),col)

        ## then we make hands
        self.lhand = sphere(pos = self.bf.handback.pos + self.bf.handback.axis, radius = scale*0.25, color = col- vec(0.3,0.3,0.3))
        self.rhand = sphere(pos = self.bf.handfront.pos + self.bf.handfront.axis, radius = scale*0.25, color = col)

        ## make the head
        self.head = sphere(pos = self.body.pivot + self.body.axis*0.65*scale, radius = scale*0.4, color = col)

        ## then for the hard part, the legs
        self.lleg = BikeElement(self.bf.backped.pedal.pos, scale*1.2, scale*0.25, vec(0.5,1,0), col - vec(0.3,0.3,0.3))
        self.rleg = BikeElement(self.bf.frontped.pedal.pos, scale*1.2, scale*0.25, vec(1,1,0), col)

    def cycle(self, mod, down = 0):
        mod = mod *-1
        self.ang += mod
        #rotate the bike
        

        ## move legs with pedals
        self.rleg.set_pos(self.bf.frontped.pedal.pos)
        self.lleg.set_pos(self.bf.backped.pedal.pos)
        if (down == 0):
            #rotate bike
            self.bf.rotate(mod)
            ## rotate legs when pedaling
            rlegmod = 5*pi/16 - (pi/8)*sin(self.ang*8)
            rlegvec = vec(cos(rlegmod), sin(rlegmod), 0)
            self.rleg.set_axis(rlegvec)
            self.lleg.set_axis(rlegvec)
            
            ## move body up and down
            self.body.set_pos(self.bf.seat.pos + vec(self.scale*0.5,self.bf.seat.height,0) + vec(0, sin(self.ang*8)*self.scale*0.1, 0))
            self.head.pos = (self.body.pivot + self.body.axis*0.65*scale) + + vec(0, sin(self.ang*8 + pi/4)*self.scale*0.1, 0)
        ## otherwise
        else:
            self.bf.rotate(mod, 1)
            self.body.set_pos(self.bf.seat.pos + vec(self.scale*0.5,self.bf.seat.height,0) + vec(0, 0.2*sin(self.ang*8)*self.scale*0.1, 0))
            self.head.pos = (self.body.pivot + self.body.axis*0.65*scale) + + vec(0, 0.2*sin(self.ang*8 + pi/4)*self.scale*0.1, 0)
        

    # allows us to change size of the person
    def set_scale(self, scl):
        ratio = scl/self.scale
        self.body.set_rad(self.scale*ratio*0.5)
        self.head.set_rad(self.scale*ratio*0.4)
        self.lleg.set_rad(self.scale*ratio*0.25)
        self.rleg.set_rad(self.scale*ratio*0.25)


########################
#####################
#####################
# Particle Maker
#################
##################
#################


class ParticleMaker:
    def __init__(self, scale):
        self.particles = []

        for _ in range(70):
            basepos = vec(40*scale*(random()%10) + 10*scale, random()*scale*20, (random()%10) - (random()%10))
            vel = (random()%10)*5 + 5
            self.particles.append(sphere(basePos=basepos, pos = basepos, velocity = vel, radius = 0.1*scale))
    #updates the particles
    def update(self, speed):
        for i in self.particles:
            i.axis.x = -i.velocity*speed
            i.pos.x -= i.velocity*speed*5
            if (i.pos.x <= -i.basePos.x):
                i.pos.x = i.basePos.x


#########################
##########################
#########################
############ User Interface time!
#######################
#######################
#######################
#######################





    


###############
########## Scene initializer
######### uh oh
#########################
#initializes the conditions for our scene
def initialize_scene():
    scene.camera.ang = 0
    scene.lights = []
    scene.ambient = color.white

    scene.width = 600
    scene.height = 500

    # Lock all user camera interaction
    scene.userpan = False
    scene.userspin = False
    scene.userzoom = False
    scene.autoscale = False

    # Center the scene on the bike
    scene.center = vec(0, scale, 0)

    # Camera position (NOT aligned with any axis)
    scene.camera.pos = vec(-12*scale, 6*scale, 12*scale)

    # Camera direction (this is the critical part)
    scene.forward = norm(scene.center - scene.camera.pos)

    # Explicit zoom control
    scene.range = 8*scale
    uphill(theta)

###############
###############
###############










##########################################
###### Section THREE                 ######
############################################
# Finishy ###################################
# Finishy ####################################
# Finishy ###################################
############################################
###### Section THREE                  #####
##########################################

wtext(text="\n")
text_theta = wtext(text = f"  Angle of Ascent: {theta:.1f}˚\n")
# tilts the camera in a certain direction.
def tilt_camera(angle_deg):
    global text_theta
    ang = radians(angle_deg)
    # find the amount we have to move
    move = (scene.camera.ang -ang)
    #update with a new angle
    scene.camera.ang = ang
    scene.camera.rotate(angle = move, axis=vec(0,0,1), origin= vec(0,0,0))

def uphill(evt):
    tilt_camera(theta)
    global text_theta
    text_theta.text = f"  Angle of Ascent: {theta:.1f}˚\n"
    global going_up
    going_up = True
    scene.camera.pos = vec(0, 5, 20)
    

def downhill(evt):
    tilt_camera(-theta)
    global going_up
    global text_theta
    text_theta.text = f"  Angle of Descent: {theta:.1f}˚\n"
    going_up = False
    scene.camera.pos = vec(0, 5, 20)


### sliders and buttons
def change_theta(s):
    global theta
    global text_theta
    theta = s.value
    if (going_up):
        uphill(theta)
    else:
        downhill(theta)
    
    
########################################
########## Defining our objects ########
########################################

#bike frame object
c = Cyclist(scale)

# Create our timer running at 120 frames per second.
t = Timer(120)

# creates a particle maker
pm = ParticleMaker(scale)

# bottom box to ride on
bbox = box(pos = vec(0,-2.6*scale,0), length = 100, width = 15, height = 1 )

# function that initializes our scene
initialize_scene()


########################################
########## Buttons and other shit ######
########################################

# slider 

sld_theta = slider(
    min=3,
    max=18,
    value=theta,
    step=0.1,
    bind=change_theta,
    length = 200
)


wtext(text="   ")
# uphill button
button(text = "Uphill", bind=uphill) 
wtext(text="    ")
# downhill button
button(text = "Downhill", bind=downhill)
wtext(text="\n")
# slider for mass

vel_graph = graph(
    title='Velocity vs Time',
    xtitle='time (s)',
    ytitle='velocity (m/s)',
    width=600,
    height=400
)

vel_curve = gcurve(color=vec(0.7,0.5,0.5))


# Main loop to spin the wheel

times = []
values = []

def plot_rolling(t, v):
    times.append(t)
    values.append(v)

    if len(times) > MAX_POINTS:
        times.pop(0)
        values.pop(0)

    curve.delete()           # remove old curve
    curve = gcurve(color=color.cyan)

    for i in range(len(times)):
        curve.plot(times[i], values[i])



# call main at the end
main()