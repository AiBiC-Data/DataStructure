#include <iostream>
#include <string>
#include <stdlib.h>
#define MAX_SIZE 200
using namespace std;

typedef int Compare(int a, int b);
int arr[200] = { 0, };

//heap struct
struct Heap {
    Compare* comp;
    int num;
    int heapArr[MAX_SIZE];
};

//initializing maxheap
void heapinit(Heap* h, Compare pc) {
    h->num = 0;
    h->comp = pc;
}

//checking heap is empty
int isEmpty(Heap* h) {
    if (h->num == 0) {
        return true;
    }
    else return false;
}

//parent heap
int Parentheap(int idx) {
    return idx / 2;
}

//leftchild heap
int Lchildheap(int idx) {
    return idx * 2;          //left
}

//rightchild heap
int Rchildheap(int idx) {
    return idx * 2 + 1;            //right
}

//bigger child heap
int highChildheap(Heap* h, int idx) {
    if (Lchildheap(idx) > h->num) {
        return 0;
    }
    else if (Lchildheap(idx) == h->num) {
        return Lchildheap(idx);
    }
    else {

        if (h->comp(h->heapArr[Lchildheap(idx)], h->heapArr[Rchildheap(idx)]) < 0) {
            return Rchildheap(idx);
        }
        else {
            return Lchildheap(idx);
        }
    }
}

//Inserting data in maxheap
void hInsert(Heap* h, int data) {
    int idx = h->num + 1;              //마지막 위치

    while (idx != 1) {             //루트 노드가 아니고 적절한 위치를 찾을 때 까지
        if (h->comp(data, h->heapArr[Parentheap(idx)]) > 0) {
            h->heapArr[idx] = h->heapArr[Parentheap(idx)];          
            idx = Parentheap(idx);
        }
        else break;
    }
    h->heapArr[idx] = data;
    h->num += 1;
}

//deleting data in maxheap
int hDelete(Heap* h) {
    int data = h->heapArr[1];           //반환할 노드 저장
    int lastData = h->heapArr[h->num];        //마지막 노드 저장
    int parentidx = 1;
    int childidx;

    while (childidx = highChildheap(h, parentidx)) {
        if (h->comp(lastData, h->heapArr[childidx]) >= 0) {            //만약 자식노드보다 크다면 종료
            break;
        }
        h->heapArr[parentidx] = h->heapArr[childidx];       //부모노드와 자식노드 교환
        parentidx = childidx;          //한레벨 아래로 이동
    }
    h->heapArr[parentidx] = lastData;         //마지막 노드를 재설정한 위치에 삽입
    h->num -= 1;                    //사이즈 1 감소
    return data;                //최댓값 노드 반환
}

//Max value in Maxheap
int hMax(Heap* h) {
    return h->heapArr[1];
}

//printing maxheap
void hPrint(Heap* h) {
    if (isEmpty(h)) {
        cout << "error" << endl;
    }
    for (int i = 1; i <= h->num; i++) {
        cout << h->heapArr[i] << " ";
    }
    cout << endl;
}

//sorting a heap
void hSort(int arr[], int n, Compare pc) {
    Heap heap;

    heapinit(&heap, pc);
    for (int i = 1; i <= n; i++) {
        hInsert(&heap, arr[i]);
    }
    for (int i = 1; i <= n; i++) {
        arr[i] = hDelete(&heap);
    }
}

//deleting heap userlocation
int hdeleteN(Heap* h, int loc1) {
    int loc = 0;

    for (int i = 1; i <= h->num; i++) {
        if (h->heapArr[i] == arr[loc1]) {
            loc = i; break;
        }
    }

    int data = h->heapArr[loc];
    int lastData = h->heapArr[h->num];
    int parentidx = loc;
    int childidx;

    while (childidx = highChildheap(h, parentidx)) {
        if (h->comp(lastData, h->heapArr[childidx]) >= 0) {
            break;
        }

        h->heapArr[parentidx] = h->heapArr[childidx];
        parentidx = childidx;
    }
    h->heapArr[parentidx] = lastData;
    h->num -= 1;
    return data;
}

//compare function
int compare(int a, int b) {
    return a - b;
}

//main
int main() {
    Heap heap;    //heap
    heapinit(&heap, compare);      //초기 힙 선언

    while (true) {
        string in;                 
        string in2 = "";             

        getline(cin, in);         //입력을 받는다

        char input1 = in[0];             //입력 받은 문자 확인
        int input2 = -1;              //공백 후 숫자나 문자 확인

        // type input exception
        if (in[0] < 65 || in[0] > 90) {     
            cout << "type input error\n";
            break;
        }

        bool err = false;            //err선언 
        //parsing char and int
        if (in[2] != '\0') {

            for (int i = 2; i < in.length(); i++) {
                in2 += in[i];
                if (in[i] < 48 || in[i] > 57) {
                    err = true;
                }
            }
            //num input exception
            if (err) {
                cout << "input number error\n";
                break;
            }

            input2 = stoi(in2);
        }

        //sorting heap array
        if (!isEmpty(&heap)) {                  //힙이 비지 않았을 경우
            for (int i = 1; i <= heap.num; i++) {
                arr[i] = heap.heapArr[i];
            }
            hSort(arr, heap.num, compare);       //정렬시킨다
        }

        //switching function
        switch (input1) {
        case 'I':              //insert
            hInsert(&heap, input2);
            cout << "done" << endl;
            break;
        
        case 'D':                  //delete
            if (isEmpty(&heap)) {
                cout << "error" << endl;
            }
            else if (input2 == -1) {
                hDelete(&heap);
                cout << "done" << endl;
            }
            else {
                hdeleteN(&heap, input2);
                cout << "done" << endl;

            }
            break;

        case 'T':            //print max value in heap
            if (isEmpty(&heap)) {
                cout << "error" << endl;
            }

            else if (input2 == -1) {
                cout << hMax(&heap) << endl;
            }

            else {
                cout << arr[input2] << endl;
            }

            break;

        case 'P':         //print max heap
            hPrint(&heap);
            break;
        }
    }
}