#include <iostream>
#include <vector>
#include <time.h>
#include <chrono>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <math.h>
#include <windows.h>
#include <string.h>
#include <queue>

#define ENDINDEX descList.size() - 1

using namespace std;

struct node {
        int value;
        struct node* leftChild;
        struct node* rightChild;
        int height;
};

vector<int> reverseVector(vector<int> &baseVector) {
    vector<int> newVector;
    for (int i = baseVector.size() - 1; i >= 0; i--) {
        newVector.push_back(baseVector[i]);
    }
    return newVector;
}

vector<int> randomDesc(int length) {
    vector<int> result;
    for (int i = 0; i < length; i++) {
        result.push_back(i);
    }
    sort(result.begin(), result.end());
    reverse(result.begin(), result.end());
    return result;
}

vector<int> randomList(int length) {
    vector<int> result;
    for (int i = 0; i < length; i++) {
        result.push_back(i);
    }
    random_shuffle(result.begin(), result.end());
    return result;
}

struct node* genAVL(vector<int> &testList, int startIndex, int endIndex) {
    struct node* newNode = new struct node;
    newNode->value = testList[(startIndex + endIndex) / 2];
    if (startIndex == endIndex) {
        newNode->leftChild = 0;
        newNode->rightChild = 0;
        return newNode;
    }
    if (endIndex - startIndex == 1) {
        newNode->leftChild = 0;
        newNode->rightChild = genAVL(testList, endIndex, endIndex);
        return newNode;
    }
    newNode->leftChild = genAVL(testList, startIndex, (startIndex + endIndex) / 2 - 1);
    newNode->rightChild = genAVL(testList, (startIndex + endIndex) / 2 + 1, endIndex);
    return newNode;
}

void insertBST(struct node* currNode, int newValue) {
    if (newValue < currNode->value) {
        if (currNode->leftChild != 0) {
           insertBST(currNode->leftChild, newValue);
        }
        else {
            struct node* newNode = new struct node;
            newNode->value = newValue;
            newNode->leftChild = 0;
            newNode->rightChild = 0;
            currNode->leftChild = newNode;
        }
    }
    else {
        if (currNode->rightChild != 0) {
            insertBST(currNode->rightChild, newValue);
        }
        else {
            struct node* newNode = new struct node;
            newNode->value = newValue;
            newNode->leftChild = 0;
            newNode->rightChild = 0;
            currNode->rightChild = newNode;
        }
    }
    return;
}

struct node* genBST(vector<int> &testList) {
    struct node* root = new struct node;
    root->value = testList[0];
    root->leftChild = 0;
    root->rightChild = 0;
    for (int i = 1; i < testList.size(); i++) {
            insertBST(root, testList[i]);
    }
    return root;
}

void deleteTree(struct node* root, bool consoleInput) {
    if (root->leftChild != 0) {
        deleteTree(root->leftChild, consoleInput);
    }
    if (root->rightChild != 0) {
        deleteTree(root->rightChild, consoleInput);
    }
    if (consoleInput) {
        cout << root->value << "\n";
    }
    delete root;
}

void printTree(vector<int> &targetTree, struct node* root, int place) {
    targetTree[place - 1] = root->value;
    if (root->leftChild != 0) {
        printTree(targetTree, root->leftChild, place * 2);
    }
    if (root->rightChild != 0) {
        printTree(targetTree, root->rightChild, place * 2 + 1);
    }
    return;
}

struct node* findLeast(struct node* root, bool consoleInput) {
    struct node* current = root;

    while (current->leftChild != 0) {
            if (consoleInput) {
                cout << current->value << "\n";
            }
            current = current->leftChild;
    }
    if (consoleInput) {
        cout << current->value << "\n";
    }
    return current;
}

struct node* findMost(struct node* root, bool consoleInput) {
    struct node* current = root;

    while (current->rightChild != 0) {
            if (consoleInput) {
                cout << current->value << "\n";
            }
            current = current->rightChild;
    }
    if (consoleInput) {
        cout << current->value << "\n";
    }
    return current;
}

void inOrder(struct node* root, vector<int> &targetVector) {
    if (root->leftChild != 0) {
        inOrder(root->leftChild, targetVector);
    }
    targetVector.push_back(root->value);
    if (root->rightChild != 0) {
        inOrder(root->rightChild, targetVector);
    }
    return;
}

void preOrder(struct node* root, vector<int> &targetVector) {
    targetVector.push_back(root->value);
    if (root->leftChild != 0) {
        preOrder(root->leftChild, targetVector);
    }
    if (root->rightChild != 0) {
        preOrder(root->rightChild, targetVector);
    }
    return;
}

int lengthRight(struct node* root, int result);

int lengthLeft(struct node* root, int result) {
    if (root == 0) {
        return 0;
    }
    int leftResult = 0, rightResult = 0;
    if (root->leftChild != 0) {
        leftResult = 1 + lengthLeft(root->leftChild, result);
    }
    if (root->rightChild != 0) {
        rightResult = 1 + lengthRight(root->rightChild, result);
    }
    if (root->leftChild == 0 && root->rightChild == 0) {
        return 1;
    }
    else {
        return max(leftResult, rightResult);
    }
}

int lengthRight(struct node* root, int result) {
    if (root == 0) {
        return 0;
    }
    int leftResult = 0, rightResult = 0;
    if (root->leftChild != 0) {
        leftResult = 1 + lengthLeft(root->leftChild, result);
    }
    if (root->rightChild != 0) {
        rightResult = 1 + lengthRight(root->rightChild, result);
    }
    if (root->rightChild == 0 && root->leftChild == 0) {
        return 1;
    }
    else {
        return max(leftResult, rightResult);
    }
}

struct node* rightRotate(struct node* root) {
    struct node* newRoot = root->leftChild;
    struct node* transportRoot = newRoot->rightChild;

    newRoot->rightChild = root;
    root->leftChild = transportRoot;

    return newRoot;

}

struct node* leftRotate(struct node* root) {
    struct node* newRoot = root->rightChild;
    struct node* transportRoot = newRoot->leftChild;

    newRoot->leftChild = root;
    root->rightChild = transportRoot;

    return newRoot;

}

struct node* deleteNode(struct node* root, int deleteValue) {
    if (deleteValue < root->value) {
        root->leftChild = deleteNode(root->leftChild, deleteValue);
    }
    else if (deleteValue > root->value) {
        root ->rightChild = deleteNode(root->rightChild, deleteValue);
    }
    else {
        if (root->leftChild == 0 || root->rightChild == 0) {
            struct node* child = root->leftChild ? root->leftChild : root->rightChild;
            if (child == 0) {
                child = root;
                root = 0;
            }
            else {
                *root = *child;
            }
        }
        else {
            struct node* temp = findLeast(root->rightChild, false);
            root->value = temp->value;
            root->rightChild = deleteNode(root->rightChild, temp->value);
        }
    }

    if (root == 0) {
        return 0;
    }

    int balance = lengthLeft(root, 0) - lengthRight(root, 0);

    if (balance > 1 && lengthLeft(root->leftChild, 0) - lengthRight(root->leftChild, 0) >= 0) {
        return rightRotate(root);
    }
    if (balance > 1 && lengthLeft(root->leftChild, 0) - lengthRight(root->leftChild, 0) < 0) {
        root->leftChild = leftRotate(root->leftChild);
        return rightRotate(root);
    }
    if (balance < -1 && lengthLeft(root->rightChild, 0) - lengthRight(root->rightChild, 0) >= 0) {
        root->rightChild = rightRotate(root->rightChild);
        return leftRotate(root);
    }
    if (balance < -1 && lengthLeft(root->rightChild, 0) - lengthRight(root->rightChild, 0) < 0) {
        return leftRotate(root);
    }

    return root;
}

void balanceTree(struct node** rootTracker) {
    struct node* currentNode = *rootTracker;
    int times = 0;
    while(currentNode->rightChild != 0) {
        if (currentNode == *rootTracker) {
            while (currentNode->leftChild != 0) {
                currentNode = rightRotate(currentNode);
                *rootTracker = currentNode;
            }
            times++;
        }
        while (currentNode->rightChild->leftChild != 0) {
            currentNode->rightChild = rightRotate(currentNode->rightChild);
        }
        currentNode = currentNode->rightChild;
        times++;
    }
    currentNode = *rootTracker;
    /*while (currentNode != 0) {
        cout << currentNode->value << "\n";
        currentNode = currentNode->rightChild;
    }*/
    bool check = max(lengthLeft(*rootTracker, 0), lengthRight(*rootTracker, 0)) == times;
    int check1 = lengthRight(*rootTracker, 0);
    int prepTurns = times - pow(2,floor(log2(times + 1))) + 1;

    currentNode = *rootTracker;
    for (int i = 0; i < prepTurns; i++) {
        if (i == 0) {
            *rootTracker = leftRotate(currentNode);
            currentNode = *rootTracker;
        }
        else {
            currentNode->rightChild = leftRotate(currentNode->rightChild);
            currentNode = currentNode->rightChild;
        }
    }



    times = pow(2, floor(log2(times + 1))) - 1;
    while (times > 1) {
        times /= 2;
        currentNode = *rootTracker;
        *rootTracker = leftRotate(currentNode);
        currentNode = *rootTracker;

        for(int i = 0; i < times - 1; i++) {
            currentNode->rightChild = leftRotate(currentNode->rightChild);
            currentNode = currentNode->rightChild;
        }
    }

}

int main()
{
    srand(time(NULL));
    int menuPick;
    while (true) {
        cout << "-----------WYBOR OPCJI------------\n";
        cout << "(1) - Podany na wejsciu ciag liczb calkowitych o dlugosci n <= 10.\n";
        cout << "(2) - Ciagi losowych liczb calkowitych o dlugosciach n = 10000, 35000, 60000, 85000, ..., 210000.\n";
        cout << "(3) - Wyjscie z programu.\n";
        cin >> menuPick;
        if (menuPick == 1) {
            cout << "Prosze wpisac pojedynczo unikalne liczby. Gdy chcesz zakonczyc wprowadzanie, wpisz 0.\n";
            vector<int> bstList(10, 0);
            vector<int> inOrderList, preOrderList;
            int i = 0, nElements;
            for (i = 0; i < 10; i++) {
                int newNumber;
                cin >> newNumber;
                if (newNumber == 0) {
                    break;
                }
                bstList[i] = newNumber;
            }
            //vector<int> targetTree(1024, 0);
            LARGE_INTEGER freq, startBST, endBST, startAVL, endAVL;

            QueryPerformanceFrequency(&freq);
            double nsFreq = freq.QuadPart / 1000000.0, resultAVL, resultBST;

            QueryPerformanceCounter(&startBST);
            struct node *BSTroot = genBST(bstList);
            QueryPerformanceCounter(&endBST);
            resultBST = (endBST.QuadPart - startBST.QuadPart) / nsFreq;

            sort(bstList.begin(), bstList.end());

            QueryPerformanceCounter(&startAVL);
            struct node *AVLroot = genAVL(bstList, 0, i - 1);
            QueryPerformanceCounter(&endAVL);
            resultAVL = (endAVL.QuadPart - startAVL.QuadPart) / nsFreq;
            //printTree(targetTree, BSTroot, 1);

            cout << "CZAS GENEROWANIA DRZEWA AVL: " << resultAVL << "\n";
            cout << "CZAS GENEROWANIA DRZEWA BST: " << resultBST << "\n";

            QueryPerformanceCounter(&startBST);
            findLeast(BSTroot, true);
            QueryPerformanceCounter(&endBST);
            resultBST = (endBST.QuadPart - startBST.QuadPart) / nsFreq;

            QueryPerformanceCounter(&startAVL);
            findLeast(AVLroot, true);
            QueryPerformanceCounter(&endAVL);
            resultAVL = (endAVL.QuadPart - startAVL.QuadPart) / nsFreq;

            cout << "CZAS SZUKANIA NAJMNIEJSZEGO ELEMENTU DRZEWA BST: " << resultBST << "\n";
            cout << "CZAS SZUKANIA NAJMNIEJSZEGO ELEMENTU DRZEWA AVL: " << resultAVL << "\n";

            QueryPerformanceCounter(&startBST);
            findMost(BSTroot, true);
            QueryPerformanceCounter(&endBST);
            resultBST = (endBST.QuadPart - startBST.QuadPart) / nsFreq;

            QueryPerformanceCounter(&startAVL);
            findMost(AVLroot, true);
            QueryPerformanceCounter(&endAVL);
            resultAVL = (endAVL.QuadPart - startAVL.QuadPart) / nsFreq;

            cout << "CZAS SZUKANIA NAJWIĘKSZEGO ELEMENTU DRZEWA BST: " << resultBST << "\n";
            cout << "CZAS SZUKANIA NAJWIĘKSZEGO ELEMENTU DRZEWA AVL: " << resultAVL << "\n";

            QueryPerformanceCounter(&startBST);
            inOrder(BSTroot, inOrderList);
            QueryPerformanceCounter(&endBST);
            resultBST = (endBST.QuadPart - startBST.QuadPart) / nsFreq;

            for (int i = 0; i < inOrderList.size(); i++) {
                cout << inOrderList[i] << " ";
            }
            cout << "\n";
            inOrderList.clear();

            QueryPerformanceCounter(&startAVL);
            inOrder(AVLroot, inOrderList);
            QueryPerformanceCounter(&endAVL);
            resultAVL = (endAVL.QuadPart - startAVL.QuadPart) / nsFreq;

            for (int i = 0; i < inOrderList.size(); i++) {
                cout << inOrderList[i] << " ";
            }
            cout << "\n";

            cout << "CZAS PRZESZUKIWANIA IN-ORDER DRZEWA BST: " << resultBST << "\n";
            cout << "CZAS PRZESZUKIWANIA IN-ORDER DRZEWA AVL: " << resultAVL << "\n";

            QueryPerformanceCounter(&startBST);
            preOrder(BSTroot, preOrderList);
            QueryPerformanceCounter(&endBST);
            resultBST = (endBST.QuadPart - startBST.QuadPart) / nsFreq;

            for (int i = 0; i < preOrderList.size(); i++) {
                cout << preOrderList[i] << " ";
            }
            cout << "\n";
            preOrderList.clear();

            QueryPerformanceCounter(&startAVL);
            preOrder(AVLroot, preOrderList);
            QueryPerformanceCounter(&endAVL);
            resultAVL = (endAVL.QuadPart - startAVL.QuadPart) / nsFreq;

            for (int i = 0; i < preOrderList.size(); i++) {
                cout << preOrderList[i] << " ";
            }
            cout << "\n";
            preOrderList.clear();

            cout << "CZAS PRZESZUKIWANIA PRE-ORDER DRZEWA BST: " << resultBST << "\n";
            cout << "CZAS PRZESZUKIWANIA PRE-ORDER DRZEWA AVL: " << resultAVL << "\n";

            while (true) {
                cout << "Ile elementow chcesz usunac z drzewa?\n";
                cin >> nElements;
                if (nElements < 0 || nElements > 10) {
                    cout << "Podaj liczbe od 0 do 10\n";
                }
                else {
                    break;
                }
            }

           if (nElements > 0) {
                cout << "Podaj wartosci do usuniecia z drzewa.\n";
                int deleteValue;
                bool deleteStatus = false;
                for (nElements; nElements > 0; nElements--) {
                    cin >> deleteValue;
                    AVLroot = deleteNode(AVLroot, deleteValue);
                }
            }
            cout << "\n";

            preOrderList.clear();
            preOrder(AVLroot, preOrderList);

            cout << "STATUS DRZEWA AVL PO USUNIĘCIU ELEMENTÓW:\n";
            for (int i = 0; i < preOrderList.size(); i++) {
                cout << preOrderList[i] << " ";
            }
            cout << "\n";
            cout << "ROWNOWAZENIE DRZEWA:\n";

            preOrderList.clear();
            preOrder(BSTroot, preOrderList);

            for (int i = 0; i < preOrderList.size(); i++) {
                cout << preOrderList[i] << " ";
            }
            cout << "\n";
            preOrderList.clear();

            struct node** rootTracker = &BSTroot;
            balanceTree(rootTracker);

            preOrder(BSTroot, preOrderList);

            for (int i = 0; i < preOrderList.size(); i++) {
                cout << preOrderList[i] << " ";
            }
            cout << "\n";
            preOrderList.clear();

            cout << "USUWANIE DRZEWA BST.\n";
            deleteTree(BSTroot, true);
            cout << "USUWANIE DRZEWA AVL.\n";
            deleteTree(AVLroot, true);



        }
        else if (menuPick == 2) {
            vector<int> bstList, descList;
            fstream fileOutput;
            fileOutput.open("wyniki.txt", ios::out);
            LARGE_INTEGER freq;
            QueryPerformanceFrequency(&freq);
            double nsFreq = freq.QuadPart / 1000000.0, resultAVL, resultBST;
            for (int i = 15000; i <= 40000; i += 2500) {
                for (int j = 0; j < 10; j++) {
                    string newInput = to_string(i) + ", ";
                    descList = randomDesc(i);
                    bstList = randomList(i);
                    vector<int> reverseList = reverseVector(descList);
                    //vector<int> targetTree(pow(2, ceil(log(descList.size()) / log(2))) - 1, 0);

                    LARGE_INTEGER startBST, endBST, startAVL, endAVL;
                    QueryPerformanceCounter(&startBST);
                    struct node *BSTroot = genBST(bstList);
                    QueryPerformanceCounter(&endBST);
                    resultBST = (endBST.QuadPart - startBST.QuadPart) / nsFreq;
                    newInput += to_string(resultBST) + ", ";

                    QueryPerformanceCounter(&startAVL);
                    struct node *AVLroot = genAVL(reverseList, 0, ENDINDEX);
                    QueryPerformanceCounter(&endAVL);
                    resultAVL = (endAVL.QuadPart - startAVL.QuadPart) / nsFreq;
                    newInput += to_string(resultAVL) + ", ";

                    QueryPerformanceCounter(&startBST);
                    findLeast(BSTroot, false);
                    QueryPerformanceCounter(&endBST);
                    resultBST = (endBST.QuadPart - startBST.QuadPart) / nsFreq;

                    QueryPerformanceCounter(&startAVL);
                    findLeast(AVLroot, false);
                    QueryPerformanceCounter(&endAVL);
                    resultAVL = (endAVL.QuadPart - startAVL.QuadPart) / nsFreq;

                    newInput += to_string(resultBST) + ", ";
                    newInput += to_string(resultAVL) + ", ";

                    vector<int> inOrderList;

                    QueryPerformanceCounter(&startBST);
                    inOrder(BSTroot, inOrderList);
                    QueryPerformanceCounter(&endBST);
                    resultBST = (endBST.QuadPart - startBST.QuadPart) / nsFreq;

                    inOrderList.clear();

                    QueryPerformanceCounter(&startAVL);
                    inOrder(AVLroot, inOrderList);
                    QueryPerformanceCounter(&endAVL);
                    resultAVL = (endAVL.QuadPart - startAVL.QuadPart) / nsFreq;

                    newInput += to_string(resultBST) + ", ";
                    newInput += to_string(resultAVL) + ", ";

                    QueryPerformanceCounter(&startBST);
                    struct node** rootTracker = &BSTroot;
                    balanceTree(rootTracker);
                    QueryPerformanceCounter(&endBST);
                    resultBST = (endBST.QuadPart - startBST.QuadPart) / nsFreq;

                    newInput += to_string(resultBST) + ", ";

                    deleteTree(AVLroot, false);
                    deleteTree(BSTroot, false);

                    newInput += "\n";
                    fileOutput << newInput;

                }
            }
        }
        else if (menuPick == 3) {
            break;
        }
        else {
            cout << "Prosze wybrac poprawna opcje.\n";
        }
    }
    //struct node *AVLroot = genAVL(reverseList, 0, ENDINDEX);
    //struct node *BSTroot = genBST(bstList);
    //printTree(targetTree, AVLroot, 1);
    /*for (int i = 0; i < targetTree.size(); i++) {
        if (i < testList.size()) {
            cout << testList[i];
        }
        cout << "           " << targetTree[i] << "\n";
    }*/
    //deleteTree(AVLroot);
    //deleteTree(BSTroot);
    return 0;
}
