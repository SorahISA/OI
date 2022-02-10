/*

[題目敘述]
獅子王國六年一度的勇者大賽即將來臨！
今年有N位候選人，根據民調已知部分投票者心目中的候選人排名。
請根據民調結果，依候選人代號按照字典序輸出【每位候選人各贏過幾位競爭對手】，以及誰是【最有可能獲選的勇者】。
【註1】若A贏過B，則超過一半的投票者喜歡A勝過B(可能直接或間接贏過對手)
【註2】最有可能的勇者代表從未被其他對手打敗過。若A是最有可能的勇者，則在任何兩兩比較的結果中，喜歡A的人數皆不小於喜歡其他候選人的人數

[輸入]
1. 候選人數量(不超過26人)
2. 接下來的輸入行數
3. 投此順序的人數及偏好(從最喜歡到不喜歡)

[輸出]
1. 依照候選人代號按字典序列出對應的擊敗人數，各組擊敗人數以空格分隔
2. 有可能的當選人(從未被打敗過)，若多於一人請依字典序列出，中間以空格分隔


範例: 

[輸入1]
3       => 共有3名候選人ABC
2       => 以下有2行輸入
1 ABC   => 1位投票者的排名為ABC
1 ACB   => 1位投票者的排名為ACB

[輸出1]
2 0 0   => A擊敗2人 B擊敗0人 C擊敗0人
A       => A為最有可能的當選人

[輸入2]
5       => 共有5名候選人ABCDE
8       => 以下有8行輸入
5 ACBED => 5位投票者的排名為ACBED
5 ADECB => 5位投票者的排名為ADECB
8 BEDAC => 8位投票者的排名為BEDAC
3 CABED => 3位投票者的排名為CABED
7 CAEBD => 7位投票者的排名為CAEBD
2 CBADE => 2位投票者的排名為CBADE
7 DCEBA => 7位投票者的排名為DCEBA
8 EBADC => 8位投票者的排名為EBADC

[輸出2]
3 1 2 0 4 => A擊敗3人 B擊敗1人 C擊敗2人 D擊敗0人 E擊敗4人
E         => E為最有可能的當選人

*/


/* 解法 (Schulze Method; Widthest Path Problem; Floyd-Warshall Algorithm)
將每人贏過其他人(pairwise)的人次加總後，運用transitive relation性質更新總和(可能變大)。
經由pairwise comparison，印出答案。
*/

/*

<Easy>
[Input1]
3
2
1 ABC
1 ACB

[Output1]
2 0 0
A
------------------------------
[Input2]
3
2
1 ABC
1 CBA

[Output2]
0 0 0
A B C
------------------------------
<Normal>
 [Input1]
 5
 8
 5 ACBED
 5 ADECB
 8 BEDAC
 3 CABED
 7 CAEBD
 2 CBADE
 7 DCEBA
 8 EBADC

 [Output1]
 3 1 2 0 4
 E
 ------------------------------
 [Input2]
 4
 9
 5 ACBD
 2 ACDB
 3 ADCB
 4 BACD
 3 CBDA
 3 CDBA
 1 DACB
 5 DBAC
 4 DCBA
 
 [Output2]
 2 0 1 3
 D
 ------------------------------
 [Input3]
 5
 9
 3 ABDEC
 5 ADEBC
 1 ADECB
 2 BADEC
 2 BDECA
 4 CABDE
 6 CBADE
 2 DBECA
 5 DECAB
 
 [Output3]
 3 4 0 2 1
 B
 ------------------------------
<Special>
 [Input4]
 4
 4
 3 ABCD
 2 DABC
 2 DBCA
 2 CBDA
 
 [Output4]
 0 1 0 1
 B D
 ------------------------------
<Cool>
 [Input5]
 4
 5
 1 CADB
 1 DCAB
 1 CDAB
 1 BDAC
 2 ADCB
 
 [Output5]
 1 0 1 2
 A D

*/

#include <iostream>
#include <math.h>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

void find_distance();
void find_path();
void ranking();
void winner();
void print();

int n, m;
int d[10][10], p[10][10];


int main(void) {
    // initialize
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            d[i][j] = 0;
            p[i][j] = 0;
        }
    }
    // # of candidates
    cin >> n;
    // # of inputs
    cin >> m;
    int i=0;
    // order of preference and their # of voters
    int voter_num[10];
    string order[10];
    while (i < m) {
        cin >> voter_num[i];
        cin >> order[i];
        i++;
    }
    
    int j=0;
    // order to distance matrix
    while (j < i) {
        for (int x=0; x<n; x++) {
            for (int y=x; y<n; y++) {
                if (x != y) {
                    // prefer order[x] to order[y]
                    if (x < y) {
                        d[order[j][x]-'A'][order[j][y]-'A'] += voter_num[j];
                    }
                }
            }
        }
        j++;
    }
    
    find_distance();
    find_path();
    ranking();
    winner();
    
    return 0;
}

void find_distance()
{
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (i != j) {
                if (d[i][j] > d[j][i]) {
                    p[i][j] = d[i][j];
                }
                else {
                    p[i][j] = 0;
                }
            }
        }
    }

    //print();
}

void find_path()
{
    for (int k=0; k<n; k++) {
        for (int i=0; i<n; i++) {
            if (k != i) {
                for (int j=0; j<n; j++) {
                    if (k != j && i != j) {
                        p[i][j] = fmax(p[i][j], fmin(p[i][k],p[k][j]));
                    }
                }
            }
        }
    }

    //print();
}

void print()
{
    // for debug
    cout << endl;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cout << p[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void ranking()
{
    vector <int> count(n,0);

    // count for # of people one has defeated
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (p[i][j] > p[j][i]) {
                count[i]++;
            }
        }
    }
    // output_1
    for (int i=0; i<n; i++) {
        if (i == n-1) {
            cout << count[i];
        }
        else {
            cout << count[i] << " ";
        }
    }
    cout << endl;
}

void winner()
{
    vector <bool> win(n,true);

    // win[i] would only be true when he/she has never been defeated => potential winner
    for (int i=0; i<n; i++) {
        if (win[i] == true) {
            for (int j=0; j<n; j++) {
                if (i != j) {
                    if (p[i][j] >= p[j][i]) {
                        win[i] = true;
                    }
                    else {
                        win[i] = false;
                        break;
                    }
                }
            }
        }
    }

    // output potential winners
    for (int i=0; i<n; i++) {
        if (win[i] == true) {
            if (i == n-1) {
                cout << char(i+'A');
            }
            else {
                cout << char(i+'A') << " ";
            }
        }
    }
    cout << endl;
}