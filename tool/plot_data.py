# coding: utf-8

import wave
import numpy as np
import matplotlib.pyplot as plt


def plot_wav(filepath, plot_sample_num):
    """
        filepath: ファイルパス
        plot_sample_num: 表示するフレーム数
    """
    
    wf = wave.open(filepath, "rb")

    buffer = wf.readframes(wf.getnframes())

    # data = 16bit(2 byte) * frame(num)
    print("sampling rate: ", wf.getframerate())
    print("sample width: ", wf.getsampwidth())
    print("frame num: ", wf.getnframes())
    print("read data: ", len(buffer))  # byte_num = 2 (byte per 1 frame) * frames

    # beffer is binary data. compose to integer per 2 byte
    data = np.frombuffer(buffer, dtype="int16")

    # make figure: x-axis=time, y-axis=amplitude
    print("--- show wav plot ---")
    plt.title("wave plot: %s" % filepath)
    plt.ylabel("amplitude")
    plt.xlabel("time")
    plt.legend(("data",), loc="upper left")
    plt.plot(data[:plot_sample_num])
    plt.show()


if __name__ == "__main__":

    plot_wav("../data/create_wave_0.wav", 400)
