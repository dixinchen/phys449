#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Jul 29 01:57:40 2020

@author: dchen
"""

import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
from scipy import stats

au = [99.99, 99.95]
for i in range(400):
    au.append(au[i+1]-0.05)

ncap = np.loadtxt('Captures with 0 shells.txt',delimiter=',')[:,1]
cflux = np.loadtxt('CellFlux with 0 shells.txt',delimiter='\n')

resp = ncap/cflux

avg_resp = np.mean(resp.reshape(-1, 5), axis=1)
err = np.std(resp.reshape(-1, 5), axis=1)

z = np.polyfit(au, avg_resp, 1)
fx = np.linspace(min(au), max(au), 1000)
fit_popt = np.poly1d(z)
fy = fit_popt(fx)

#%%
p, V = np.polyfit(au, avg_resp, 1, cov=True)

print("x_1: {} +/- {}".format(p[0], np.sqrt(V[0][0])))
print("x_2: {} +/- {}".format(p[1], np.sqrt(V[1][1])))

#%%
stats.pearsonr(au, avg_resp)


#%%



# f1 = plt.figure(figsize=(8, 8/1.6))
# plt.errorbar(au[::4], avg_resp[::4], yerr=err[::4], fmt = 'C0.',
#               markersize = '4', capsize = 2, ecolor='C0',
#               elinewidth = 1, markeredgewidth = 1,label='Data')
# sns.set(style="white", font_scale=1.5)
# plt.rcParams['font.family'], plt.rcParams['axes.linewidth'] = 'DejaVu Sans', 2
# plt.rcParams['xtick.bottom'], plt.rcParams['ytick.left'] = True, True
# plt.xlabel("Gold foil thickness [cm]")
# plt.ylabel("Sensitivity [cm$^{2}$/g]")
# plt.grid()
# plt.tight_layout()
# plt.show()

# f, (a0, a1) = plt.subplots(2, 1, sharex = True, gridspec_kw = {'height_ratios':[3, 1]},figsize=(12, 12/1.6))
# a0.errorbar(au[::4], avg_resp[::4], yerr=err[::4], fmt = 'k.',
#               markersize = '4', capsize = 2, ecolor='k',
#               elinewidth = 1, markeredgewidth = 1,label='Simulation')
# # a0.errorbar(au, avg_resp, yerr=err, fmt = 'C0.',
# #               markersize = '4', capsize = 2, ecolor='C0',
# #               elinewidth = 1, markeredgewidth = 1,label='Data')
# a0.plot(fx,fy,'k--',label='Linear fit')
# a1.errorbar(au[::4], avg_resp[::4]-fit_popt(au)[::4], yerr=err[::4], fmt = 'k.',
#               markersize = '4', capsize = 2, ecolor='k',
#               elinewidth = 1, markeredgewidth = 1, label='Linear fit')
# # a1.errorbar(au, avg_resp-fit_popt(au), yerr=err, fmt = 'C0.',
# #               markersize = '4', capsize = 2, ecolor='C0',
# #               elinewidth = 1, markeredgewidth = 1, label='Linear fit')
# a1.plot(au, [0 for i in range(len(au))], 'k')
# sns.set(style="white", font_scale=1.5)
# plt.rcParams['font.family'], plt.rcParams['axes.linewidth'] = 'DejaVu Sans', 2
# plt.rcParams['xtick.bottom'], plt.rcParams['ytick.left'] = True, True
# # a0.grid()
# # a1.grid()
# a0.set_ylabel("Sensitivity [cm$^{2}$/g]")
# a1.set_ylabel("Residual [cm$^{2}$/g]")
# a1.set_xlabel("Gold foil purity [%]")
# a0.legend(frameon=False) #loc='upper left'
# f.tight_layout()
# f.show()



#%%
import numpy as np
from scipy import stats
from matplotlib import pyplot as plt


t = au[::4]
L_obs = avg_resp[::4]
N = len(t)

f, (a0, a1) = plt.subplots(2, 1, sharex = True, gridspec_kw = {'height_ratios':[3, 1]},figsize=(12, 12/1.6))

y_vals = fit_popt(au)[::4]
y_errs = err[::4]

# compute the mean and the chi^2/dof
mu = np.mean(y_vals)
z = (y_vals - mu) / y_errs
chi2 = np.sum(z ** 2)
chi2dof = chi2 / (N - 1)

# compute the standard deviations of chi^2/dof
sigma = np.sqrt(2. / (N - 1))
nsig = (chi2dof - 1) / sigma

# plot the points with errorbars
a0.vlines(99.99, 0.0884,0.116231,'k', linestyles='dotted', alpha=0.6, label="Present purity in use")
a0.errorbar(au[::4], avg_resp[::4], yerr=err[::4], fmt = 'k.',
              markersize = '4', capsize = 2, ecolor='k',
              elinewidth = 1, markeredgewidth = 1,label='GEANT4 simulation')
a0.plot(fx,fy,'k--',label='Linear fit')
handles, labels = a0.get_legend_handles_labels()
order = [1,2,0]
a0.legend([handles[idx] for idx in order],[labels[idx] for idx in order],frameon=False)
# a0.text(0.02, 0.02, r'$\hat{\mu} = %.2f$' % mu, ha='left', va='bottom',
        # transform=a0.transAxes)
a0.text(0.395, 0.02, "sensitivity = 7.63*$10^{-4}$purity+3.01*$ 10^{-2}$", ha='left', va='bottom',
        transform=a0.transAxes)
a0.text(0.98, 0.13,
        r'$\chi^2_{\rm dof} = %.2f\, (%.2g\,\sigma)$' % (chi2dof, nsig),
        ha='right', va='bottom', transform=a0.transAxes)
a1.errorbar(au[::4], avg_resp[::4]-fit_popt(au)[::4], yerr=err[::4], fmt = 'k.',
              markersize = '4', capsize = 2, ecolor='k',
              elinewidth = 1, markeredgewidth = 1, label='Linear fit')
a1.plot(au, [0 for i in range(len(au))], 'k')
sns.set(style="white", font_scale=1.7)
plt.rcParams['font.family'], plt.rcParams['axes.linewidth'] = 'DejaVu Sans', 2
plt.rcParams['xtick.bottom'], plt.rcParams['ytick.left'] = True, True
a0.set_ylabel("Sensitivity [cm$^{2}$/g]")
a1.set_ylabel("Residual [cm$^{2}$/g]")
a1.set_xlabel("Gold foil purity [%]")
f.tight_layout()
plt.show()