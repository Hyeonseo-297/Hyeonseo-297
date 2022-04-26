#include <stdio.h>  
int main()
{
   
    char op_type;
    // Variable to store 2 operand values
    int num1, num2;

    printf("Enter 1st integer : ");
    scanf_s("%d", &num1);
   //Remove Enter Key entered with Operator
    rewind(stdin);

    printf("Enter operator (+, -, *, /): ");
    scanf_s("%c", &op_type, 1);
    rewind(stdin);

    printf("Enter 2nd integer : ");
    scanf_s("%d", &num2);

    switch (op_type)
    {
    case '+':  // case of plus
        printf("%d + %d = %d\n", num1, num2, num1 + num2);
        break;
    case '-': // case of minus
        printf("%d - %d = %d\n", num1, num2, num1 - num2);
        break;
    case '*': // case of multiply
        printf("%d * %d = %d\n", num1, num2, num1 * num2);
        break;
    case '/': // case of division
        if (num2 == 0) printf("Error. Cannot divide by 0 \n");
        else printf("%d / %d = %.3f\n", num1, num2, num1 / (double)num2);
        break;
    }
    return 0;
}