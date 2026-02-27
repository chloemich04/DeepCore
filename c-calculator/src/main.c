#include <stdio.h>

int main() {
    int num1, num2;
    int choice;

    do {        
        printf("-----------------------------------------");
        printf("\nChoose an operation:\n1. Addition\n2. Substraction (first - second)\n3. Multiplication\n4. Division (first / second)\n5. Exit\n");
        printf("-----------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        printf("Enter first number: ");
        scanf("%d", &num1);

        printf("Enter second number: ");
        scanf("%d", &num2);

        switch(choice) {
            case 1:
                printf("Result: %d\n", num1 + num2);
                printf("-----------------------------------------\n");
                break;
            case 2:
                printf("Result: %d\n", num1 - num2);
                printf("-----------------------------------------\n");
                break;
            case 3:
                printf("Result: %d\n", num1 * num2);
                printf("-----------------------------------------\n");
                break;
            case 4:
                if (num2 == 0) {
                    printf("Error: Division by zero is not allowed.\n");
                    printf("-----------------------------------------\n");
                }
                else {
                    printf("Result: %.2f\n", (float)num1 / num2);
                    printf("-----------------------------------------\n");
                }
                break;
            case 5:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice - please enter 1-5.\n");
        }

        printf("\n");
    } while (choice != 5);

    return 0;
}