#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jul 29 12:53:42 2020

@author: dchen
"""

import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

## full range plot
## change reshape to (-1,3) !!!!!!!!!!!
# density = [5.0,
#   7.0,
#   9.0,
#   11.0,
#   13.0,
#   15.0,
#   17.0,
#   19.0,
#   21.0,
#   23.0,
#   24.0,
#   26.0,
#   28.0,
#   30.0,
#   32.0]
# ncap = np.loadtxt('archive/Captures with 0 shells 1.37.07 PM.txt',delimiter=',')[:,1]
# cflux = np.loadtxt('archive/CellFlux with 0 shells 1.37.07 PM.txt',delimiter='\n')


# density = []
# for i in range(10):
#     density.append(14.0+i)
    
# for i in range(10):
#     density.append(14.5+i)
    
# ncap = np.loadtxt('archive/Captures with 0 shells.txt',delimiter=',')[:,1]
# cflux = np.loadtxt('archive/CellFlux with 0 shells.txt',delimiter='\n')

density = []
for i in range(10):
    density.append(14.3+i)
    

ncap = np.loadtxt('Captures with 0 shells.txt',delimiter=',')[:,1]
cflux = np.loadtxt('CellFlux with 0 shells.txt',delimiter=',')

resp = ncap/cflux

avg_resp = np.mean(resp.reshape(-1, 5), axis=1)
err = np.std(resp.reshape(-1, 5), axis=1)

f1 = plt.figure(figsize=(8, 8/1.6))
plt.vlines(19.3, 0.102, 0.1173, linestyles='dashed', alpha=0.4, label="Present foil density in use")
plt.errorbar(density, avg_resp, yerr=err, fmt = 'k.',
              markersize = '4', capsize = 2, ecolor='k',
              elinewidth = 1, markeredgewidth = 1)
sns.set(style="white", font_scale=1.5)
plt.rcParams['font.family'], plt.rcParams['axes.linewidth'] = 'DejaVu Sans', 2
plt.rcParams['xtick.bottom'], plt.rcParams['ytick.left'] = True, True
plt.xlabel("Gold foil density [g/cm$^3$]")
plt.ylabel("Sensitivity [cm$^{2}$/g]")
# plt.grid()
plt.legend(loc="lower left",frameon=False)
plt.tight_layout()
plt.show()