# coding: utf-8

import wave
import struct
import numpy as np

SCRIPTNAME = "create_wave"  # スクリプト名
FILEDIRPATH = "../data"  # データ保存先

I16 = 32767.0  # 正の整数値16ビット
SFREQ = 8000.0  # サンプリング周波数
QBIT = 16  # 量子化ビット

def create_simple_wave(A, freq, fs, length):
    """
        A: 振幅
        freq: 目的の周波数
        fs: サンプリング周波数
        length: 信号長
    """

    data = []
    for n in range(int(fs * length)):
        s = A * np.sin(2.0 * np.pi * freq * n / fs)
        # Aが大きい場合はクリッピング
        if s > 1.0:
            s = 1.0
        if s < -1.0:
            s = -1.0
        data.append(s)

    # 整数値変換
    data = [int(x * I16) for x in data]
    # バイナリ変換
    data = struct.pack("h" * len(data), *data)

    return data


def create_combined_wave(A, freq_list, fs, length):
    """
        A: 振幅
        freq_list: 合成する周波数のリスト
        fs: サンプリング周波数
        length: 信号長
    """

    data = []
    amp = float(A) / len(freq_list)  # 合成して目的のAになるように調整

    for n in range(int(length * fs)):  # サンプリング点数分

        s = 0.0  # 各サンプリング点におけるAの累積和を管理
        for f in freq_list:
            s += amp * np.sin(2.0 * np.pi * f * n / fs)

        # Aが大きくなるときはクリッピング
        if s > 1.0:
            s = 1.0
        if s < -1.0:
            s = -1.0

        data.append(s)

    # 整数値変換
    data = [int(x * 32767.0) for x in data]

    # バイナリ変換
    data = struct.pack("h" * len(data), *data)

    return data

def save_wav(data, fs, bit, filepath):
    """
        data: 信号データ
        fs: サンプリング周波数
        bit: 標本化ビット
        filepath: 出力パス
    """

    wf = wave.open(filepath, "wb")
    wf.setnchannels(1)
    wf.setsampwidth(bit // 8)
    wf.setframerate(fs)
    wf.writeframes(data)
    wf.close()

if __name__ == "__main__":

    freq_list = [(200, 300, 400)]

    for i, fl in enumerate(freq_list):
        data = create_combined_wave(1.0, fl, SFREQ, 5.0)
        filepath = "%s/%s_%s.wav" % (FILEDIRPATH, SCRIPTNAME, i)
        save_wav(data, SFREQ, QBIT, filepath)
