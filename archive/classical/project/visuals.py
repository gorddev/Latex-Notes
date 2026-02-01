from vpython import *

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
    def rotate(self, ang):
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

    def cycle(self, mod):
        mod = mod *-1
        self.ang += mod
        #rotate the bike
        self.bf.rotate(mod)

        ## move legs with pedals
        self.rleg.set_pos(self.bf.frontped.pedal.pos)
        self.lleg.set_pos(self.bf.backped.pedal.pos)
        ## rotate legs when pedaling
        rlegmod = 5*pi/16 - (pi/8)*sin(self.ang*8)
        rlegvec = vec(cos(rlegmod), sin(rlegmod), 0)
        self.rleg.set_axis(rlegvec)
        self.lleg.set_axis(rlegvec)

        ## move body up and down
        self.body.set_pos(self.bf.seat.pos + vec(self.scale*0.5,self.bf.seat.height,0) + vec(0, sin(self.ang*8)*self.scale*0.1, 0))
        self.head.pos = (self.body.pivot + self.body.axis*0.65*scale) + + vec(0, sin(self.ang*8 + pi/4)*self.scale*0.1, 0)

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


scale = 2
alpha = 11.3

# tilts the camera in a certain direction.
def tilt_camera(angle_deg):
    # first get our angle in degrees
    ang = radians(angle_deg)
    # find the amount we have to move
    move = (scene.camera.ang -ang)
    #update with a new angle
    scene.camera.ang = ang
    scene.camera.rotate(angle = move, axis=vec(0,0,1), origin= vec(0,0,0))

def uphill(evt):
    tilt_camera(alpha)
    scene.camera.pos = vec(0, 5, 20)
    

def downhill(evt):
    tilt_camera(-alpha)
    scene.camera.pos = vec(0, 5, 20)
    


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
    uphill(alpha)

###############
###############
###############


button(text = "Uphill", bind=uphill)
button(text = "Downhill", bind=downhill)


#bike frame object
c = Cyclist(scale)

# Create our timer running at 120 frames per second.
t = Timer(120)

# creates a particle maker
pm = ParticleMaker(scale)

# bottom box to ride on
bbox = box(pos = vec(0,-2.3*scale,0), length = 100, width = 10, height = 1 )

# function that initializes our scene
initialize_scene()

# Main loop to spin the wheel
while True:
    rate(10000)
    if (not t.tick()):
        continue

    c.cycle(t.dt())
    pm.update(t.dt()*2)
    
