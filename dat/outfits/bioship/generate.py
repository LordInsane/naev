#!/usr/bin/python

TEMPLATEPATH = "./templates/"

def lerpr( a, b ):
    return lambda x: a + x * (b-a)

def lerp( a, b ):
    return lambda x: round(a + x * (b-a))

class BioOutfit:
    def __init__( self, template, params ):
        self.template = template
        self.params = params
        with open(TEMPLATEPATH+template,"r") as f:
            self.txt = f.read()

    def run(self, names):
        for k,n in enumerate(names):
            x = 1 if len(names)==1 else k/(len(names)-1)
            p = {k: v(x) if callable(v) else v for k, v in self.params.items()}
            p["name"]  = n
            with open( f"{n.lower().replace(' ','_')}.xml", "w" ) as f:
                f.write( self.txt.format(**p) )

"""
pincer
stinger
barb
fang
talon
claw
"""


BioOutfit( "pincer.xml.template", {
    "name"  : "Pincer Organ Stage I",
    "price" : lerpr( 4500, 20000 ),
    "damage": lerp( 8, 17 ),
    "energy": 4,
    "range" : lerp( 750, 900 ),
    "falloff": lerp( 450, 750 ),
    "speed" : lerp( 550, 700 ),
    "heatup": lerp( 25, 40 ),
} ).run( ["Pincer Organ Stage I", "Pincer Organ Stage II", "Pincer Organ Stage III"] )
