// Exercicio Estrutura de dados
// Priscila Barbosa Floriano
// Curitiba, 27/04/2021

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    float value;
    struct node *next;
} node;

node *stackup(node *stack, float num)
{
    node *newValue = malloc(sizeof(node));
    if (newValue)
    {
        newValue->value = num;
        newValue->next = stack;
        return newValue;
    }
    else
        printf("\tOcorreu um erro\n");
    return NULL;
}

node *unstack(node **stack)
{
    node *remove = NULL;
    if (stack)
    {
        remove = *stack;
        *stack = remove->next;
    }
    else
        printf("\tPilha vazia\n");
    return remove;
}

// Funcao que calcula, define os operadores a e as variaveis a serem calculadas
float definition_operation(float op1, float op2, char x)
{
    switch (x)
    {
    case '+':
        return op1 + op2;
        break;
    case '-':
        return op1 - op2;
        break;
    case '/':
        printf("Op1: %f\tOp2: %f\n", op1, op2);
        return op1 / op2;
        break;
    case '*':
        return op1 * op2;
        break;
    default:
        return 0.0;
    }
}

// Funcao que determina a solucao da operacao
float solution(char x[])
{
    char *pointer;
    float num;
    node *n1, *n2, *stack = NULL;
    pointer = strtok(x, " ");
    while (pointer)
    {
        if (pointer[0] == '+' || pointer[0] == '/' || pointer[0] == '*')
        {
            n1 = unstack(&stack);
            n2 = unstack(&stack);
            num = definition_operation(n1->value, n2->value, pointer[0]);
            stack = stackup(stack, num);
            free(n1);
            free(n2);
        }
        else
        {
            num = strtol(pointer, NULL, 10);
            stack = stackup(stack, num);
        }
        pointer = strtok(NULL, " ");
    }
    n1 = unstack(&stack);
    num = n1->value;
    free(n1);
    return num;
}

// Saida dos resultados no console
int main()
{
    char expression[10] = ("2 3 * 4 +"); // Resultado: 10
    // char expression[10] = ("5 3 * 9 -"); // Resultado: 0
    // char expression[10] = ("6 8 - 7 *"); // Resultado: 0
    // char expression[10] = ("6 8 + 9 /"); // Resultado: 0.6

    printf("Resultado final de %s: %f\n", expression, solution(expression));
}
