/*
 *	A program to demonstrate simple graphical operations
 */

/*  This line allows the compiler to understand the
 *	graphics functions
 */
 #include <graphics_lib.h>
 /* If the file uses the graphics library, it should be included into the src folder */



int user_input;
int random_number;

random_number = GFX_RandNumber(0,100);

do
{
    /* Ask the user to guess the number */
    printf("I have chosen a number between 0 to 100, guess a number: ");
    scanf("%d",&user_input);

} while(user_input == random_number);

return 0;


