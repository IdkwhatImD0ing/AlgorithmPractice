import Expr
from Expr import V
import matplotlib
import matplotlib.pyplot as plt
import numpy as np


#Checking code
def check_true(x, msg=None):
    if not x:
        if msg is None:
            print("Error: assertion is false")
        else:
            print("Error in", msg, ": false")
    assert x
    print("Success")

def fit(loss, points, params, delta=0.0001, num_iterations=5000):
    """
    @param loss: expression giving the loss as a function of variables and parameters.
    @param points: list of (x, y) values to which we have to fit the expression.
    @param params: list of parameters whose value we can tune.
    @param delta: learning step size.
    @param num_iterations: number of learning iterations.
    """
    for iteration_idx in range(num_iterations):
        loss.zero_gradient()
        total_loss = 0.
        for x, y in points:
            # Here, you have to assign values to vx and vy, forward propagate,
            # then backpropagate the gradient.  4 lines are enough; it is not 
            # a trick question.
            vx.assign(x)
            vy.assign(y)
            loss.eval()
            loss.compute_gradient()
            total_loss += loss.eval()
        if (iteration_idx + 1) % 100 == 0:
            print("Loss:", total_loss)
        for vv in params:
            vv.assign(vv.eval() - delta * vv.gradient)
    return total_loss

def plot_points(points):
    """Plots points"""
    fig, ax = plt.subplots()
    xs, ys = zip(*points)
    ax.plot(xs, ys, 'r+')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.show()

def plot_points_and_y(points, vx, oy):
    """Plots points and a line"""
    fig, ax = plt.subplots()
    xs, ys = zip(*points)
    ax.plot(xs, ys, 'r+')
    x_min, x_max = np.min(xs), np.max(xs)
    step = (x_max - x_min) / 100
    x_list = list(np.arange(x_min, x_max + step, step))
    y_list = []
    for x in x_list:
        vx.assign(x)
        y_list.append(oy.eval())
    ax.plot(x_list, y_list)
    plt.xlabel('x')
    plt.ylabel('y')
    plt.show()


points = [
    (-2, 2.7),
    (-1, 3),
    (0, 1.3),
    (1, 2.4),
    (3, 5.5),
    (4, 6.2),
    (5, 9.1),
]


matplotlib.rcParams['figure.figsize'] = (8.0, 3.)
params = {'legend.fontsize': 'large',
          'axes.labelsize': 'large',
          'axes.titlesize':'large',
          'xtick.labelsize':'large',
          'ytick.labelsize':'large'}
matplotlib.rcParams.update(params)



plot_points(points)

#Linear Regression
#y = ax + b

# Parameters
va = V(1.)
vb = V(1.)

# x and y
vx = V(0.)
vy = V(0.)

# Predicted y
oy = va * vx + vb

# Loss
loss = (vy - oy) * (vy - oy)

#Start
fit(loss, points, [va, vb])

#Plot linear regression line
plot_points_and_y(points, vx, oy)

#Quadratic Regression
# y = ax^2 + bx + c

#Initial Values
va = V(0.)
vb = V(0.)
vc = V(0.)
vx = V(0.)
vy = V(0.)

#Predicted Values
oy = va * vx * vx + vb * vx + vc
loss = (vy - oy) * (vy - oy)

#Start
final_loss = fit(loss, points, [va, vb, vc])
check_true(final_loss < 2.5)

#Let's display the parameter values after the training:
print("a:", va.eval(), "b:", vb.eval(), "c:", vc.eval())

#The line fitted to points
plot_points_and_y(points, vx, oy)

#Cubic Regression
# y=ax^3+bx^2+cx+d

# Some random initializations.
vx = V(0.)
vy = V(0.)
va = V(-0.1)
vb = V(0.2)
vc = V(-0.3)
vd = V(0.4)
# Define below what is the prediction oy and loss.
oy = va * vx * vx * vx + vb * vx * vx + vc * vx + vd
loss = (vy - oy) * (vy - oy)
final_loss = fit(loss, points, [va, vb, vc, vd], delta=2e-5, num_iterations=10000)

#Plot line
plot_points_and_y(points, vx, oy)
