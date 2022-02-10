/**
This is a simple wrapper for communication with the manager.
DO NOT CHANGE THIS FILE!!!!!
**/

#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <set>
#include <string>
#include <vector>
using namespace std;

// Functions to be implemented in the solution.
void initialize(int);
void make_available(int);
void make_unavailable(int);
vector<set<int>> calculate_optimal_bundle_set(vector<long long>);

// Functions provided to the solution.
void set_bundle(int, int, long long);

////////////////////////////////////////////////
namespace {  // Used in this file only.
void run();
FILE *fifo_in, *fifo_out;
void _send_msg(const string& msg);
void _send_msg(const std::vector<long long>& result);
int _recv_int();
long long _recv_longlong();
}  // namespace
////////////////////////////////////////////////

int main(int argc, char **argv) {
    
    // IF YOU WANT TO TEST LOCALLY ON YOUR COMPUTER,
    // 如果你想要在本地端測試你的程式，
    // COMMENT THESE TWO LINES AND UNCOMMENT THE TWO LINES BELOW.
    // 把下面這兩行註解起來，然後把更下面兩行打開，這樣就可以從命令列互動了。
    fifo_in = fopen(argv[1], "r");
    fifo_out = fopen(argv[2], "w");
    // fifo_in = stdin;
    // fifo_out = stdout;

    run();

    fclose(fifo_in);
    fclose(fifo_out);
    return 0;
}

////////////////////////////////////////////////
namespace {
void _send_msg(const string& msg) {
    fprintf(fifo_out, "%s\n", msg.c_str());
    fflush(fifo_out);
}
void _send_msg(const std::vector<long long>& result) {
    for (int i = 0; i < result.size(); ++i) {
        fprintf(fifo_out, "%lld%c", result[i], " \n"[i==result.size()-1]);
    }
    fflush(fifo_out);
}

long long _recv_longlong() {
    long long val;
    int ret = fscanf(fifo_in, "%lld", &val);
    // Receives error.
    if (val == -1 || ret != 1) {
        fclose(fifo_in);
        fclose(fifo_out);
        exit(0);
    }
    return val;
}

int _recv_int() {
    int val;
    int ret = fscanf(fifo_in, "%d", &val);
    // Receives error.
    if (val == -1 || ret != 1) {
        fclose(fifo_in);
        fclose(fifo_out);
        exit(0);
    }
    return val;
}

class LocalGrader {
    private:
        static const int av_set_quota = 60;
        static const int maxM = 1024;
        static const int max_button = 65536;

        struct Button {int v; long long q;};
        static Button button[max_button+1];
        static int cur_quota;
        static int max_id;
        static int M;
        static bitset<maxM> allow_button;
        static int button_count[maxM];
        static bool run_initiated;

        static void _assert_WA(bool cond, string msg) {
            if(cond) return;
            fprintf(stderr, "Wrong Answer\nMSG: %s\n", msg.c_str());
            replace(msg.begin(), msg.end(), ' ', '+');
            _send_msg(msg);
            exit(0);
        }
        static void _ack() {
            _send_msg("OK");
        }
        static void _set_button(int id, int v, long long q) {
            if(button[id].v) button_count[button[id].v]--;
            button[id] = {v, q};
            if(button[id].v) button_count[button[id].v]++;
        }
        static void _handle_available() {
            int x = _recv_int();
            assert(1<=x && x<M && !allow_button[x]);

            cur_quota = av_set_quota;
            allow_button[x] = 1;
            make_available(x);
            _ack();
        }
        static void _handle_unavailable() {
            int x = _recv_int();
            assert(1<=x && x<M && allow_button[x]);

            cur_quota = av_set_quota;
            make_unavailable(x);
            _assert_WA(button_count[x] == 0, "exists unavailable face value on ATM");
            allow_button[x] = 0;
            _ack();
        }
        static void _handle_calc() {
            cur_quota = 0;
            int k = _recv_int();
            vector<long long> values(k);
            for(auto &v:values) {
                v = _recv_longlong();
                assert(0<=v && v<=((long long)1e9)*((long long)1e9));
            }
            auto ans = calculate_optimal_bundle_set(values);
            _assert_WA(k == (int)ans.size(), "invalid length of returned vector");
            vector<long long> n_bills(k);
            for(int i=0; i<k; i++) {
                const auto &s = ans[i];
                _assert_WA(s.count(0) == 0, "button id out of range");
                _assert_WA(s.empty() || max(abs(*s.begin()), abs(*prev(s.end()))) <= max_button, 
                        "button id out of range");
                for(const auto pnid: s) {
                    _assert_WA(s.count(-pnid) == 0, "id and -id cannot coexist");
                }
                long long sum_vq = 0, sum_q = 0;
                for(const auto pnid: s) {
                    auto &b = button[abs(pnid)];
                    _assert_WA(allow_button[b.v] && b.v!=0, "answer contains invalid button");
                    sum_vq += b.v * b.q * (pnid > 0 ? 1 : -1);
                    sum_q += b.q;
                }
                _assert_WA(sum_vq == values[i], "returned set does not result in correct value");
                n_bills[i] = sum_q;
            }
            _ack();
            _send_msg(n_bills);
        }
        static double _score() {
            int x = max_id;
            if(x > 60 * M) return 0.0;
            else if(x <= 60 + (4*M+2)/3 - __lg(M)) return 1.0;
            else {
                double s = 1-0.18*(-1+sqrt(log((x-(60.0-__lg(M)))/M) / log(4.0/3)));
                return max(0.0, min(s, 1.0));
            }
        }
    public:
        static void precheck_set_bundle(int id, int v, long long q) {
            _assert_WA(cur_quota > 0, "no quota to edit");
            cur_quota--;
            _assert_WA(1<=id && id<=max_button, "button id out of range");
            _assert_WA(v>=0, "invalid v");
            _assert_WA(0<=q && q<(1LL<<60), "invalid q");
            _assert_WA((v==0) == (q==0), "(v, q) must be both zero or both non-zero");
            if(v>0) {
                _assert_WA(1<=v && v<=M, "invalid v");
                _assert_WA(1<=q && q<(1LL<<60), "invalid q");
            }
            _assert_WA(allow_button[v], "face value is unavailable");
            _set_button(id, v, q);
            max_id = max(max_id, id);
        }

        static void run() {
            assert(!run_initiated);
            run_initiated = true;
            max_id = 0;
            static const int max_flip = 1e5, max_calc = 30;

            M = _recv_int();
            int q = _recv_int();
            assert(1<=M && M<=1000);
            assert(0<=q && q<=max_flip + max_calc);

            allow_button[M] = allow_button[0] = 1;
            for(int i=1; i<=60; i++) _set_button(i, M, 1LL<<(i-1));
            initialize(M);
            int type[4] = {0,0,0,0};
            while(q--) {
                int op = _recv_int();
                assert(1<=op && op<=3);
                type[op]++;
                if(op == 1) {
                    _handle_available();
                } else if(op == 2) {
                    _handle_unavailable();
                } else {
                    _handle_calc();
                }
            }
            assert(type[1]+type[2]<=max_flip);
            assert(type[3]<=max_calc);
            fprintf(stderr, "Accepted (if the solutions indeed all use the least number of bills)\n");
            fprintf(stderr, "M = %d, max_id = %d, score weight is S = %.6f\n", M, max_id, _score());
            _send_msg(vector<long long>{max_id});
        }
};

LocalGrader::Button LocalGrader::button[LocalGrader::max_button + 1];
int LocalGrader::cur_quota = 0;
int LocalGrader::max_id = 0;
int LocalGrader::M = 0;
bitset<LocalGrader::maxM> LocalGrader::allow_button;
int LocalGrader::button_count[LocalGrader::maxM];
bool LocalGrader::run_initiated = false;

void run() {
    LocalGrader::run();
}
}  // namespace

void set_bundle(int id, int v, long long q) {
    LocalGrader::precheck_set_bundle(id, v, q);
}
