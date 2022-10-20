from xtb import *

class TestScript(xtb.ScriptBase):
    def __init__(self):
        print("TestScript.__init__")
    
    def start(self):
        print("TestScript.start")
        
    def update(self):
        if Input.key_press(KEY_D):
            self.actor.transform.position.x += 10 time.delta_time
        
        print("TestScript.update")