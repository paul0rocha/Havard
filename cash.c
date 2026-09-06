#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int cents;

    do
    {
        cents = get_int("Change owed: ");
    }
    while (cents < 0);

    int c25 = cents / 25;
    cents = cents % 25;

    int c10 = cents / 10;
    cents = cents % 10;

    int c5 = cents / 5;
    cents = cents % 5;

    int c1 = cents;

    printf("%i\n", c25 + c10 + c5 + c1);
}
