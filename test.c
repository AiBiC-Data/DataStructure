#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>                     //12181539 조권호

int hanoi_tower(int scale, char from, char temp, char target);

int main(void) {
    unsigned scale;

    printf("Input n : ");
    scanf("%d", &scale);
    printf("\nTime to move disk : %d", hanoi_tower(scale, 'A', 'B', 'C'));           //재귀
}

int hanoi_tower(int scale, char from, char temp, char target) {
    static int times = 0;

    if (scale == 1) {                   //원반이 1개 남았을 때
        times++;
        printf("%d: Move disk %d from tower %c to tower %c\n", times, scale, from, target);
    }
    else {
        hanoi_tower(scale - 1, from, target, temp);           //A에서 C를 통해 B로 옮기는 재귀
        times++;
        printf("%d: Move disk %d from tower %c to tower %c\n", times, scale, from, target);
        hanoi_tower(scale - 1, temp, from, target);       //B에서 A를 통해, C로 옮기는 재귀
    }
    return times;   // 총 움직인 횟수 리턴
}
