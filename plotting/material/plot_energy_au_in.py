#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Jul 31 12:34:10 2020

@author: dchen
"""

import numpy as np
import math
import matplotlib.pyplot as plt
import seaborn as sns
from scipy.optimize import curve_fit
from scipy import interpolate
    
# energy = np.logspace(math.log10(1.12*(10**(-9))),math.log10(15.9),num=52)

energy = [1.12E-09, 1.59E-09, 2.51E-09, 0.000000004, 6.31E-09, 
          0.00000001, 1.59E-08, 2.51E-08, 3.98E-08, 6.31E-08, 
          0.0000001, 0.000000159, 0.000000251, 0.000000398, 0.000000631, 
          0.000001, 0.00000159, 0.00000251, 0.00000398, 0.00000631, 
          0.00001, 0.0000159, 0.0000251, 0.0000398, 0.0000631, 
          0.0001, 0.000159, 0.000251, 0.000398, 0.000631, 
          0.001, 0.00159, 0.00251, 0.00398, 0.00631, 
          0.01, 0.0159, 0.0251, 0.0398, 0.0631, 
          0.1, 0.159, 0.251, 0.398, 0.631, 
          1, 1.59, 2.51, 3.98, 6.31, 10, 15.9]

cflux_au = np.mean(np.loadtxt('aug08_10000n_au_in/CellFlux with 0 shells_au.txt',delimiter='\n'))
cflux_in = np.mean(np.loadtxt('aug08_10000n_au_in/CellFlux with 0 shells_in.txt',delimiter='\n'))

ncap_au = np.loadtxt('aug08_10000n_au_in/Captures with 0 shells_au.txt',delimiter=',')[:,1]/cflux_au
ncap_in = np.loadtxt('aug08_10000n_au_in/Captures with 0 shells_in.txt',delimiter=',')[:,1]/cflux_in

avg_resp_au = np.mean(ncap_au.reshape(5, 52), axis=0)
avg_resp_in = np.mean(ncap_in.reshape(5, 52), axis=0)

xx = np.linspace(min(energy), max(energy), 10000)
spln_au = interpolate.splrep(energy, avg_resp_au)
spln_in = interpolate.splrep(energy, avg_resp_in)
yy_au = interpolate.splev(energy, spln_au)
yy_in = interpolate.splev(energy, spln_in)

err_resp_au = np.std(ncap_au.reshape(5, 52), axis=0)/5
err_resp_in = np.std(ncap_in.reshape(5, 52), axis=0)/5

f1 = plt.figure(figsize=(8, 8/1.6))
plt.plot(energy, avg_resp_au, 'C0s', alpha=0.6,label="Gold foil")
plt.plot(energy, avg_resp_in, 'C1o',alpha=0.6,label="Hypothetical indium foil")
plt.plot(energy,yy_au,'C0-', alpha=0.6)
plt.plot(energy,yy_in,'C1-', alpha=0.6)
sns.set(style="white", font_scale=1.5)
plt.rcParams['font.family'], plt.rcParams['axes.linewidth'] = 'DejaVu Sans', 2
plt.rcParams['xtick.bottom'], plt.rcParams['ytick.left'] = True, True
plt.xlabel("Neutron energy [MeV]")
plt.ylabel("Sensitivity [cm$^{2}$/g]")
plt.xscale('log')
plt.legend(frameon=False)
plt.tight_layout()
plt.show()