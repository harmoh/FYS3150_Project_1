import sys, os
from  matplotlib import pyplot as plt
import numpy as np

filename = "out"
exponent = 3

# Start making figures looping over all exponents
for i in range(1, exponent+1):
    #   define files to open data and make plots to
    fout = filename + str(i) + ".txt"
    figfile = fout + ".pdf"
    data = np.loadtxt(fout)
    x = data[:,0]
    exact = data[:,1]
    numerical = data[:,2]
    plt.axis([0, 1, 0, 0.7])
    #numericalplot = plt.plot(x, solution, 'r:.', linewidth = 1.0, label = 'Numerical')
    #exactplot = plt.plot(x, exact, 'm:v', linewidth = 1.0, label = 'Exact')
    exactplot = plt.plot(x, exact, label = 'Exact, $u(x)$')
    numericalplot = plt.plot(x, numerical, label = 'Numerical, $v(x)$')
    plt.legend(loc='lower center', fancybox='True')
    plt.grid(True)
    plt.xlabel(r'$x$')
    plt.ylabel(r'Solutions')
    plt.savefig(figfile)
    #   Then clean up
    plt.clf()

# Plot relative error
fout = "out24_error_time.txt"
figfile = fout + ".pdf"
data = np.loadtxt(fout)
x = data[:,1]
solution = data[:,2]
plt.yscale('log', nonposy='clip')
plt.xscale('log', nonposy='clip')
plt.axis([0.00000001, 1, 0.000000001, 1])
plt.grid(True)
numericalplot = plt.plot(x, solution, 'r:.', linewidth = 2.0, label = 'Numerical')
plt.xlabel(r'$h$')
plt.ylabel(r'$\epsilon_i = |\frac{v_i - u_i}{u_i}|$')
plt.savefig(figfile)

#   Then clean up
plt.clf()

