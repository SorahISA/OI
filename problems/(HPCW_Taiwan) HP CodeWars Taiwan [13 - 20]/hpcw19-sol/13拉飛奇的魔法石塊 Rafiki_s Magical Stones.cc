#include <iostream>
#include <string>
#include <cstring>

using namespace std;

template<typename T>
int artillery_sort(T arr[], const int len) {
    int j, left = 0, right = len - 1;
    int time = 0;

    // Steps of the crane moving to the right, this would be set to -1 to make sure the first step would be zero.
    int step_move_to_right = -1;

    // Steps of the crane moving to the left.
    int step_move_to_left = 0;

    // The position of the crane.
    int anchor = 0;

    // Bubble sort from left to the right, and then from the left to the right.
    // A traditional bubble sort would be sorted from the left to the right, this would not reflect the real situation of a crane.
    // The crane must be move from the left to the right and then move from the right to the left.
    while (left < right) {
        for (j = left; j < right; ++j)
        {
            ++step_move_to_right;
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                time += (step_move_to_right * 10 + 30);
                step_move_to_right = 0;
                anchor = j;
            }
        }
        right = anchor; // Marks the position of the crane
        step_move_to_right = 0;

        for (j = right; j > left; j--)
        {
            ++step_move_to_left;
            if (arr[j - 1] > arr[j])
            {
                swap(arr[j - 1], arr[j]);
                time += (step_move_to_left * 10 + 30);
                step_move_to_left = 0;
                anchor = j;
            }
        }
        left = anchor;
        step_move_to_left = -1;
    }
    return time;
}

int main()
{
    string str;
    getline(std::cin, str);

    char A[27];
    memset(A, '\0', 27);
    str.copy(A, (str.size() + 1));

    int time = artillery_sort(A, str.size());

    std::cout <<  time << std::endl;

    return 0;
}