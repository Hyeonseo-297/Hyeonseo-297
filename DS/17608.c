//막대기
#include<stdio.h>
#include<stdlib.h>

int cansee(int num, int arr[]);

int main() {
    int n, *h;
    scanf("%d", &n);

    h = (int*)malloc(sizeof(int) * n);

    for (int i = 0; i < n; i++) {
        scanf("%d", &h[i]);
    }
    cansee(n, h);
    free(h);
}

int cansee(int num, int arr[]) {
    int cnt = 0, duplicate = 0;
    //마지막에 있는 값보다 큰 값들 count
    for (int i = 0; i < num; i++) {
        if (arr[i] > arr[num - 1]) {
            cnt++;
        }
    }
    //중복 값 개수 count
    for (int i = 0; i < num; i++){
        for(int j = 0; j <i; j++) {
            if(arr[i] == arr[j]) {
                duplicate++;
            }
        }
    }

    //마지막 값도 포함해야 하니까 +1
    cnt = cnt + 1 - duplicate;
    printf("%d", cnt);
}
