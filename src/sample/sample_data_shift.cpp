# include <iostream>
# include <vector>

using namespace std;

int main(void) {

    // original vectorの用意
    vector<int> original;
    original.resize(10);
    for (int i = 0; i < 10; i++) {
        original[i] = i;
    }

    // 部分要素を抽出して新たなvectorとする
    int window = 3;
    vector<int> sub1(original.begin(), original.begin()+window);

    // 部分要素を抽出したvectorを保持するvectorに格納 (固定長配列のほうが良い?)
    // (-> 生の配列はポインタしか持たないから格納不可)
    vector< vector<int> > all;
    for (int i = 0; i < 10 - window + 1; i++) {
        vector<int> tmp(original.begin()+i, original.begin()+i+window);
        all.push_back(tmp);
    }

    // 結果を表示
    cout << "original" << endl;
    for (unsigned int i = 0; i < original.size(); i++) {
        cout << original[i] << endl;
    }

    cout << "sub1" << endl;
    for (unsigned int i = 0; i < sub1.size(); i++) {
        cout << sub1[i] << endl;
    }

    cout << "all" << endl;
    for (unsigned int i = 0; i < all.size(); i++) {
        for (unsigned int j = 0; j < all[i].size(); j++) {
            cout << all[i][j] << ",";
        }
        cout << endl;
    }

    return 0;
}
