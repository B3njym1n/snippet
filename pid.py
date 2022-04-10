%matplotlib inline
from tclab import clock, setup, Historian, Plotter

def texter_gen():
    a = yield "Started"
    b = yield a
    yield b

def our_numbers():
    n = 0
    while True:
        n = yield n * n

def proportional(Kp, SP):
    """Creates propostional controller"""
    MV = 0
    while True:
        PV = yield MV
        MV = Kp * (SP - PV)

def PID(Kp, Ki, Kd, MV_bar=0):
    # initialization
    e_prev = 0
    t_prev = 0
    I = 0

    MV = MV_bar

    while True:
        t, PV, SP = yield MV
        e = SP - PV
        P = Ke * e
        I = I + Ki * e * (t - t_prev)
        D = Kd * (e - e_prev)/(t - t_prev)

        MV = MV_bar + P + I + D

        e_prev = e
        t_prev = t


if __name__ == '__main__':
    # texter = texter_gen()
    # print(texter.send(None))
    # print(texter.send("alpha"))
    # print(texter.send("beta"))
    # numbers = our_numbers()
    # numbers.send(None)
    # print(numbers.send(4))
    # print(numbers.send(14))
    # print(numbers.send(44))
    # print(numbers.send(64))
    # numbers.close()
    TCLab = setup(connected=False, speedup=10)
    controller = PID(2, 0.1, 2)
    controller.send(None)

    with TCLab() as lab:
        h = Historian([('SP', lambda: SP),('T1', lambda: lab.T1), ('MV', lambda: MV), ('Q1', lab.Q1)])
        p = Plotter(h, tfinal)
        T1 = lab.T1
        for t in clock(tfinal, 2):
            SP = T1 if t < 50 else 50
            PV = lab.T1
            MV = controller.send([t, PV, SP])
            lab.U1 = MV
            p.update(t)
