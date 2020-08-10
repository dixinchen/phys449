#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jul 28 11:42:18 2020

@author: dchen
"""
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.optimize import curve_fit

radius = []
# for i in range(16):
    # radius.append(2*(0.2+0.05*i))
for i in range(11):
    radius.append(2*(0.5+i*0.05))

ncap = np.loadtxt('1_12e-09_10000n/Captures with 0 shells.txt',delimiter=',')[:,1]
cflux = np.loadtxt('1_12e-09_10000n/CellFlux with 0 shells.txt',delimiter='\n')

resp = ncap/cflux

avg_resp = np.mean(resp.reshape(-1, 5), axis=1)
err = np.std(resp.reshape(-1, 5), axis=1)


# def exp(x,x0,l):
#     return x0*np.exp(-l*x)

# popt, pcov = curve_fit(exp, radius[2:], avg_resp[2:])
# fx = np.linspace(min(radius[2:]), max(radius[2:]), 1000)
# fy = exp(fx, *popt)


f1 = plt.figure(figsize=(8, 8/1.6))
plt.vlines(1.6, 0.27, 0.07, linestyles='dashed', alpha=0.4, label="Present foil diameter in use,\nmax. foil diameter achievable")
plt.errorbar(radius[:-1], avg_resp[:-1], yerr=err[:-1], fmt = 'k.',
              markersize = '4', capsize = 2, ecolor='k',
              elinewidth = 1, markeredgewidth = 1)
# plt.yscale('log')
# plt.plot(fx,fy,'C1')
sns.set(style="white", font_scale=1.5)
plt.rcParams['font.family'], plt.rcParams['axes.linewidth'] = 'DejaVu Sans', 2
plt.rcParams['xtick.bottom'], plt.rcParams['ytick.left'] = True, True
plt.xlabel("Gold foil diameter [cm]")
plt.ylabel("Sensitivity [cm$^{2}$/g]")
# plt.grid()
plt.legend(loc="lower left",fontsize=16, frameon=False)
plt.tight_layout()
plt.show()


# a3 = np.loadtxt('1_00e-3_10000n/Captures with 0 shells.txt',delimiter=',')[:,0]
# b3 = np.loadtxt('1_00e-3_10000n/Captures with 0 shells.txt',delimiter=',')[:,1]
# mass = a3/b3
# mass = np.mean(mass.reshape(-1, 5), axis=1)
# f2 = plt.figure()
# plt.plot(radius, mass)