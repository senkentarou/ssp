# coding: utf-8

#
# fft/dft アルゴリズム確認用
#

import numpy as np

if __name__ == "__main__":

    data = []
    num_sample = 8
    fft_sample = 16
    for s in range(num_sample):
        #data.append(np.sin(2.0 * np.pi * s / num_sample))
        data.append(1.0)

    print ("data: ", data)

    fft_data = data
    for i in range(num_sample, fft_sample):
        fft_data.append(0.0)

    print ("fft_data: ", fft_data)

    dft = np.fft.fft(fft_data, fft_sample)

    print ("fft: ", dft)

    pdft = np.abs(dft) ** 2

    print ("power: ", pdft)
