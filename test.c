#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>                     //12181539 ����ȣ

int hanoi_tower(int scale, char from, char temp, char target);

int main(void) {
    unsigned scale;

    printf("Input n : ");
    scanf("%d", &scale);
    printf("\nTime to move disk : %d", hanoi_tower(scale, 'A', 'B', 'C'));           //���
}

int hanoi_tower(int scale, char from, char temp, char target) {
    static int times = 0;

    if (scale == 1) {                   //������ 1�� ������ ��
        times++;
        printf("%d: Move disk %d from tower %c to tower %c\n", times, scale, from, target);
    }
    else {
        hanoi_tower(scale - 1, from, target, temp);           //A���� C�� ���� B�� �ű�� ���
        times++;
        printf("%d: Move disk %d from tower %c to tower %c\n", times, scale, from, target);
        hanoi_tower(scale - 1, temp, from, target);       //B���� A�� ����, C�� �ű�� ���
    }
    return times;   // �� ������ Ƚ�� ����
}
