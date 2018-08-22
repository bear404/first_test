import turtle as t
t.setup(1500,1000)
side=80
width=8
t.pensize(0.5*width)
t.pencolor("red")
def drawline (draw):
    t.penup()
    t.fd(width)
    t.pendown() if draw else t.penup()
    t.fd(side)
    t.penup()
    t.fd(width)
    t.right(90)

def drawnext(long=30):
    t.penup()
    t.seth(0)
    t.fd(long)

def drawnum(num):
    drawline(True) if num in [2,3,4,5,6,8,9] else drawline(False)
    drawline(True) if num in [0,1,3,4,5,6,7,8,9] else drawline(False)
    drawline(True) if num in [0,2,3,5,6,8,9] else drawline(False)
    drawline(True) if num in [0,2,6,8] else drawline(False)
    t.left(90)
    drawline(True) if num in [0,4,5,6,8,9] else drawline(False)
    drawline(True) if num in [0,2,3,5,6,7,8,9] else drawline(False)
    drawline(True) if num in [0,1,2,3,4,7,8,9] else drawline(False)

t.penup()
t.fd(-700)
for i in range(10):
    drawnum(i)
    drawnext(40)
