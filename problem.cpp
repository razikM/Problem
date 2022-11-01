#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <cassert>

using namespace std;

// class representing a single number in a triangle
// accumulatedCost stores the sum of the most expensive path
// which has gone through this node
class Node{
    int value;
    int accumulatedCost;

public:
    Node (int value, int accumulatedCost = INT32_MIN){
        this->value = value;
        this->accumulatedCost = accumulatedCost;
    }

    void setValue(int value) {
        this->value = value;
    }

    void setAccumulatedCost(int accumulatedCost) {
        this->accumulatedCost = accumulatedCost;
    }

    int getValue() {
        return value;
    }

    int getAccumulatedCost(){
        return accumulatedCost;
    }

    bool pass (int accumulatedCost){
        if (this->accumulatedCost < accumulatedCost){
            this->accumulatedCost = accumulatedCost;
            return true;
        }

        return false;
    }
};

typedef  vector<vector<Node>> Triangle;

int maxSumPath(int row, int col, Triangle &triangle, int accumulatedCost){
    // return the accumulated cost if the end of the triangle is reached
    if (row >= triangle.size() || col >= triangle[row].size())
        return accumulatedCost;

    Node &n = triangle[row][col];

    // only those paths must be considered
    // which have accumulated a greater value
    // compared to the value already stored in the node
    if (n.pass(accumulatedCost)){
        int leftChild = maxSumPath(row + 1, col, triangle, accumulatedCost + n.getValue());
        int rightChild = maxSumPath(row + 1, col + 1, triangle, accumulatedCost + n.getValue());
        return max(leftChild, rightChild);
    }

    return accumulatedCost;
}

void TestPass(){
    // only the path with larger accumulated cost
    // must be pasted through by the node
    Node n(0,0);
    assert(n.pass(1));
    assert(n.getAccumulatedCost() == 1);
    assert(!n.pass(0));
    assert(n.getAccumulatedCost() == 1);
}

void TestMaxSumPath(){
    // one element triangle
    Node n(0);
    vector<Node> v;
    v.push_back(n);
    Triangle t;
    t.push_back(v);

    assert(maxSumPath(0,0,t,0) == 0);

    // one element triangle with initial accumulatedCost
    n.setValue(1);
    n.setAccumulatedCost(-1);
    v.clear();
    v.push_back(n);
    t.clear();
    t.push_back(v);
    assert(maxSumPath(0,0,t,10) == 11);

    // triangle
    //  1
    // 2 3
    Node n1(1);
    Node n2(2);
    Node n3(3);
    vector<Node> row1;
    vector<Node> row2;
    Triangle t2;

    row1.push_back(n1);
    row2.push_back(n2);
    row2.push_back(n3);
    t2.push_back(row1);
    t2.push_back(row2);

    assert(maxSumPath(0,0,t2,0) == 4);
}

void TestRunner(){
    TestPass();
    TestMaxSumPath();
}

int main() {

    TestRunner();

    // preparation to read the file
    ifstream file;
    file.open("..\\triangle.txt");
    string inputLine;
    Triangle triangle;

    if (file.is_open()) {
        while (!file.eof()){

            getline(file, inputLine);

            // mapping of string inputLine to char* for strtok function
            char inputChars[inputLine.size() + 1];

            for (int i = 0; i < inputLine.size(); i++)
                inputChars[i] = inputLine[i];

            inputChars[inputLine.size()] = '\0';

            // parsing ints from input line
            vector<Node> row;
            char* token = strtok(inputChars, " ");

            while (token != NULL){
                int num = strtol(token, NULL, 10);
                Node n(num);
                row.push_back(n);
                token = strtok(NULL, " ");
            }

            triangle.push_back(row);

        }
    } else {
        cerr << "File couldn't be opened:(" << endl;
        exit(1);
    }

    int result = maxSumPath(0, 0, triangle, 0);
    cout << "Result is: " << result << endl;

    return 0;
}
