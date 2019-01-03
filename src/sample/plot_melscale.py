# coding: utf-8

import pandas as pd
import matplotlib.pyplot as plt

if __name__ == "__main__":

    dataframe = pd.read_csv("../../data/mel_scale.csv", header=None)
    print("Mel Scale: \n", dataframe.ix[:,1])

    plt.figure(figsize=(16, 9), dpi=80)
    plt.plot(dataframe.ix[:, 1])

    plt.title("Plot Mel Scale")
    plt.legend("Mel Scale")
    plt.xlabel("frequency [Hz]")
    plt.ylabel("mel frequency")
    plt.savefig("../../data/plot_mel_scale.png")
    plt.show()
