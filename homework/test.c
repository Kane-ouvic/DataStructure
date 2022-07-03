#include <stdio.h>
#include <string.h>

int main(void)
{
	char str1[20];
	char str2[20];
    int a[10];

    scanf("%s %s" ,str1 ,str2);
    for(int i = 0; i < 10; i++){
        scanf("%d",&a[i]);
    }


	if (strcmp(str1, str2) == 0) {
	    printf("Yessss!\n");
	}
	else {
	    printf("nooooo\n");
	}

    for(int i = 0; i < 10; i++){
        printf("%d",a[i]);
    }

	return 0;
}