#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jul 28 14:33:16 2020

@author: dchen
"""
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns

#%%

## jul 28
# thickness = []
# for i in range(11):
#     thickness.append(0.005+0.001*int(i))

## jul 29
# thickness = []
# for i in range(20):
#     thickness.append(0.05+0.005*int(i))

## aug 07
# thickness = [0.005, 0.01, 0.015,0.02,0.0025, 0.0075, 0.0125, 0.0175]
thickness = [0.001, 0.005, 0.01, 0.05, 0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7]


ncap = np.loadtxt('shell0_1_12e-09_10000n/Captures with 0 shells.txt',delimiter=',')[:,1]
cflux = np.loadtxt('shell0_1_12e-09_10000n/CellFlux with 0 shells.txt',delimiter='\n')

resp = ncap/cflux

avg_resp = np.mean(resp.reshape(-1,5), axis=1)
err = np.std(resp.reshape(-1,5), axis=1)


#%%
f1 = plt.figure(figsize=(8, 8/1.6))
plt.vlines(0.01, 0.0068, 0.01238,'k', linestyles='dashdot', alpha=0.6, label="Present foil thickness in use")
plt.vlines(0.0025, 0.0068, 0.01238, 'k', linestyles='dotted', alpha=0.9, label="Min. foil thickness achievable")
plt.vlines(0.5, 0.0068, 0.009,'k', linestyles='dashed', alpha=0.6, label="Max. foil thickness achievable")
plt.errorbar(thickness, avg_resp, yerr=err, fmt = 'k.',
              markersize = '4', capsize = 2, ecolor='k',
              elinewidth = 1, markeredgewidth = 1)
# plt.plot(thickness, resp, 'C0.')
sns.set(style="white", font_scale=1.5)
plt.rcParams['font.family'], plt.rcParams['axes.linewidth'] = 'DejaVu Sans', 2
plt.rcParams['xtick.bottom'], plt.rcParams['ytick.left'] = True, True
plt.xlabel("Gold foil thickness [cm]")
plt.ylabel("Sensitivity [cm$^{2}$/g]")
# plt.grid()
plt.legend(frameon=False)
plt.tight_layout()
plt.show()

#%%
# thickness = [0.01, 0.3, 0.4]
# position = [1.275]
# small_insert_len = [2.54]
# imp = np.array(thickness)/2.0
# source = imp+0.00001

# for i in range(len(thickness)-1):
#     delta = thickness[i+1]-thickness[i]
#     position.append(position[i]+delta/4)
#     small_insert_len.append(small_insert_len[i]-delta/2)

    
# for i in range(len(thickness)-1):
#     print("sed -i -e \"s/gold_thick="+str(thickness[i])+"/gold_thick="+str(thickness[i+1])
#           +"/g\" ~/Documents/passive_nns/src/DetectorConstruction.cc")
#     print("sed -i -e \"s/"+str(position[i])+"/"+str(position[i+1])+"/g\" ~/Documents/passive_nns/src/DetectorConstruction.cc")
#     print("sed -i -e \"s/small_insert_len="+str(small_insert_len[i])+"/small_insert_len="+str(small_insert_len[i+1])
#           +"/g\" ~/Documents/passive_nns/src/DetectorConstruction.cc")
#     print("sed -i -e \"s/,"+str(imp[i])+"/,"+str(imp[i+1])
#           +"/g\" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc")
#     print("sed -i -e \"s/"+str(source[i])+"/"+str(source[i+1])
#           +"/g\" ~/Documents/passive_nns/build/shell0.mac")
#     print("\n")
    
# sed -i -e "s/gold_thick=0.01/gold_thick=0.0075/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/275/27375/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/small_insert_len=2.54/small_insert_len=2.54/g" ~/Documents/passive_nns/src/DetectorConstruction.cc
# sed -i -e "s/,0.005/,0.0025/g" ~/Documents/passive_nns/src/ImportanceDetectorConstruction.cc
# sed -i -e "s/0.00501/0.00251/g" ~/Documents/passive_nns/build/shell0.mac


#%%
## calculate the mass
# a1 = np.loadtxt('shell0_1_12e-09_10000n/Captures with 0 shells.txt',delimiter=',')[:,0]
# a2 = np.loadtxt('shell0_1_12e-09_10000n/Captures with 0 shells2.txt',delimiter=',')[:,0]
# a3 = np.concatenate((a1, a2))
# b1 = np.loadtxt('shell0_1_12e-09_10000n/Captures with 0 shells.txt',delimiter=',')[:,1]
# b2 = np.loadtxt('shell0_1_12e-09_10000n/Captures with 0 shells2.txt',delimiter=',')[:,1]
# b3 = np.concatenate((b1, b2))
# mass = a3/b3
# mass = np.mean(mass.reshape(-1, 5), axis=1)
# f2 = plt.figure()
# plt.plot(thickness, mass)