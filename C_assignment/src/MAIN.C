/*
 *	A program to demonstrate simple graphical operations
 */

/*  This line allows the compiler to understand the
 *	graphics functions
 */
 #include <graphics_lib.h>
 #include <math.h>
 #define pi 3.14159265
 /* If the file uses the graphics library, it should be included into the src folder */

/* Function prototypes */
void changecolour(int user_input1);
double Mean(double values[],int num_values);
double draw_projectile_path(double initial_pos_x, double initial_pos_y, int *proj_x, int restriction_height, int x_target, int *proj_y);
void draw_target(int x_target);
int score_board(int x, int distance, int y);
void draw_stick_man(double x_position,double y_position);
void draw_restriction(int restriction_height);
double maximum(double array1[],int size);
double minimum(double array2[],int length);
void illustration(int x_position, int user_input1, int y_position,  int initial_pos_x, int initial_pos_y, int mark, int key, int proj_x, int proj_y, char string_mark[11]);
void over_interface(int mark, double mean_distance, int max, int min, char string_mark[11]);
double draw_power_bar(double *velocity);

/* Main function starts here */
int main(void)
{
    /* Declare variables for the x and y positions */
    double x_position;
    double y_position;

    /* Declare variable for choosing colour */
    int user_input1;

    /* Declare variables for initial position of stick man */
    double initial_pos_x;
    double initial_pos_y;

    /* Declare variable for pointer of keyboard */
    int key;

    /* Declare variable for left x-coordinate of blue target */
    int x_target;

    /* Declare variables to save maximum and minimum distance */
    int max;
    int min;

    /* Declare pointers to represent pos_x and pos_y from projectile function */
    int proj_x;
    int proj_y;

    /* Declare variable to save the score into and set its initial value */
    int mark = 0;

    /* Declare the variable to represent highest point of restriction */
    int restriction_height;

    /* Declare arraies to store letters */
    char string_mark[11];
    char string_count[25];

    /* Flag to symbol when we want to end */
    int count = 0;

    /* Flage to symbol how many shootings are tying */
    int num_distance = 0;

    /* Declare an array storing distance of 3 shooting */
    double data_values[3];

    /* Store the value from function of draw_projectile */
    double mean_distance;

    /* Declare variables of welcome window */
    /* Mouse postion where to click */
    int x_start;
    int y_start;

    /* Flage to symbol when to exit the welome window */
    int done = 0;

    /* Declare a variable to represent left mouse button */
    int button;

    /* Set initial position of the stick man */
    x_position = 80;
    y_position = 480;

    /* Set initial position of the hand */
    initial_pos_x = 110;
    initial_pos_y = 520;

	/* Open a 800 pixels wide by 640 pixels high graphics window */
    GFX_InitWindow(800, 640);

    /* Set up event queue,keyboard and mouse */
    GFX_CreateEventQueue();
    GFX_InitFont();
    GFX_InitMouse();
    GFX_RegisterMouseEvents();

    /* Initialise Bitmap Images, which goes after GFX_InitWindow but before any other BITMAP functions */
    GFX_InitBitmap();

    /* Set the background colour */
    GFX_SetBackgroundColour(BLACK);

    /* Draw the start interface */
    /* Draw welcome bitmap */
    BITMAP image5 = GFX_LoadBitmap("welcome.png");
    GFX_DrawBitmap(image5,390,120);

    /* Set characters' colour */
    GFX_SetColour(WHITE);

    /* Draw welcome text*/
    GFX_DrawText(150,240,"CLICK START TO PLAY THE GAME OR ILLUSTRATION TO START TUTORIAL");
    GFX_DrawText(330,270,"START");
    GFX_DrawText(420,270,"CANCEL");
    GFX_DrawText(350,340,"ILLUSTRATION");

        /* Make figures written before draw */
    GFX_UpdateDisplay();

    /* Set a while loop for starting the game */
    while(!done)
    {
        /* Wait for an event */
        GFX_WaitForEvent();

        /* Process mouse events */
        if (GFX_IsEventMouseButton())
        {
            /* Check if left mouse button click */
            GFX_GetMouseButton(&button);
            if (button == MOUSE_BUTTON_LEFT)
            {
                /* Get click coordinates and save the value of x and y */
                GFX_GetMouseCoordinates(&x_start,&y_start);

                /* When user clicks start */
                if (x_start > 320 && x_start < 380 && y_start > 270 && y_start < 290)
                {

                    done = 1;

                }

                /* When user clicks illustration */
                else if (x_start > 340 && x_start < 460 && y_start > 340 && y_start < 360)
                {
                    illustration(x_position, user_input1, y_position, initial_pos_x, initial_pos_y, mark, key, proj_x, proj_y, string_mark);

                    GFX_ClearWindow();

                    done = 1;
                }

                /* When user clicks cancel */
                else if (x_start > 410 && x_start < 470 && y_start > 270 && y_start < 290)
                {
                    GFX_CloseWindow();
                }
            }
        }
    }

    /* Release memory of bitmap and clear window to exit starting window */
    GFX_FreeBitmap(image5);
    GFX_ClearWindow();

    /* Random x coordinate for the target */
    x_target = GFX_RandNumber(560,611);

    /* Random height for restriction */
    restriction_height = GFX_RandNumber(250,520);

    /* Fill grey to the ground and the lightcyan to the background */
    GFX_DrawFilledRectangle(0,560,800,640,LIGHTGRAY);
    GFX_DrawFilledRectangle(0,0,800,560,LIGHTCYAN);

    /* Draw a quarter of the circle as power bar */
    GFX_DrawFilledCircle(0,640,80,LIGHTMAGENTA);

    /* Set a display queue */
    GFX_RegisterDisplayEvents();

    /* Writing the reminder on the window */
    GFX_InitFont();
    GFX_SetColour(BLACK);
    GFX_DrawText(50,40,"BACK TO THE TERMINAL TO SET THE COLOUR OF YOUR STICK MAN.");
    GFX_DrawText(670,60,"vel:");
    GFX_DrawText(670,100,"ang:");
    GFX_DrawText(650,10,"Score: 0");

    /* Make figures written before draw */
    GFX_UpdateDisplay();

    /* make the colour selection above case insensitive. */
    printf("Please input the number from 0-10 to represent colour of stick man: ");
    scanf("%d",&user_input1);

    /* Draw a rectangle to hide th text before */
    GFX_DrawFilledRectangle(50,40,600,60,LIGHTCYAN);

    /* Draw the reminder on the top of the main interface */
    GFX_DrawText(50,40,"YOU HAVE THREE TIMES TO THROW THE BALL UNITL YOU HIT THE TARGET.");
    GFX_DrawText(50,80,"USE POWER BAR AT LEFT CORNER TO ADJUST POWER AND ANGLE. ");
    GFX_DrawText(50,100,"PRESS RIGHT AND LEFT KEYBOARD TO MOVE LEFT AND RIGHT. ");
    GFX_DrawText(50,120,"PRESS T KEYBOARD TO THROW THE PROJECTILE. ");

    /* Set the colour and draw the stick man using the function */
    changeColour(user_input1);
    printf("\n");

    /* Display targets, restriction and stick man */
    draw_target(x_target);
    draw_restriction(restriction_height);
    draw_stick_man(x_position,y_position);

    /* Make figures written before draw */
    GFX_UpdateDisplay();

    /* Initialise keyboard */
    GFX_InitKeyboard();
    GFX_RegisterKeyboardEvents();

    /* Define 3 movements using do-while loop */
    do
    {
        /* Tell user how many shoots they did */
        sprintf(string_count, "THIS IS YOUR %d SHOOT.", count+1);
        GFX_SetColour(BLACK);
        GFX_DrawText(300, 200, string_count);

        /* Wait for an event */
        GFX_WaitForEvent();

        /* Move left */
        if (GFX_IsEventKeyDown())
        {

            GFX_GetKeyPress(&key);
            if (key == ALLEGRO_KEY_LEFT)
            {
                if (x_position > 50)
                {
                    /* Draw a rectangle to hide the previous stick man */
                    GFX_DrawFilledRectangle(x_position-40,y_position-30,x_position+30,y_position+80,LIGHTCYAN);

                    /* Do the move of going left */
                    x_position -= 20;

                    /* Set the colour and draw the stick man again */
                    changeColour(user_input1);
                    draw_stick_man(x_position,y_position);

                    /* Refresh the coordinates of initial pos_x and pos_y */
                    initial_pos_x = x_position + 30;
                    initial_pos_y = y_position + 40;

                    /* Change the variable into string */
                    GFX_DrawFilledRectangle(700,10,800,30,LIGHTCYAN);

                    /* Change the variable into string */
                    GFX_SetColour(BLACK);
                    sprintf(string_mark, "Score: %d", mark);
                    GFX_DrawText(650,10,string_mark);

                    /* Make figures written before draw */
                    GFX_UpdateDisplay();
                }
            }

        /* Move right */
           else if (key == ALLEGRO_KEY_RIGHT)
            {
                if (x_position < 360)
                {
                    /* Draw a rectangle to hide the previous stick man */
                    GFX_DrawFilledRectangle(x_position-40,y_position-30,x_position+30,y_position+80,LIGHTCYAN);

                    /* Do the move of going right */
                    x_position +=  20;

                    /* Set the colour and draw the stick man again */
                    changeColour(user_input1);
                    draw_stick_man(x_position,y_position);

                    /* Refresh the coordinates of initial pos_x and pos_y */
                    initial_pos_x = x_position + 30;
                    initial_pos_y = y_position + 40;

                    /* Change the variable into string */
                    GFX_DrawFilledRectangle(700,10,800,30,LIGHTCYAN);

                    GFX_SetColour(BLACK);
                    sprintf(string_mark, "Score: %d", mark);
                    GFX_DrawText(650,10,string_mark);

                    /* Make figures written before draw */
                    GFX_UpdateDisplay();
                }
            }

        /* Throw coin */

           else if (key == ALLEGRO_KEY_T)
            {
                /* Draw the projectile from the hands */
                changeColour(user_input1);
                data_values[num_distance] = draw_projectile_path(initial_pos_x, initial_pos_y, &proj_x, restriction_height, x_target, &proj_y);

                /* Get the data into the array storing it into the position of num_distance */
                printf("The distance you throw is %.0lf and number of tries is %d\n",data_values[num_distance], num_distance + 1);

                /* Calculate the score user gets */
                mark += score_board(x_target,proj_x,proj_y);

                /* Draw the filled rectangle to hide the previous mark and time of shoot */
                GFX_DrawFilledRectangle(700,10,800,30, LIGHTCYAN);
                GFX_DrawFilledRectangle(300,200,500,220,LIGHTCYAN);

                GFX_SetColour(BLACK);

                /* Change the variable into string */
                sprintf(string_mark, "Score: %d", mark);
                GFX_DrawText(650,10, string_mark);

                /* Redraw the part hidded by the projectile */
                GFX_DrawFilledRectangle(400,restriction_height,440,558,LIGHTGRAY);

                /* Redraw all elements which can be erased */
                GFX_DrawText(50,40,"YOU HAVE THREE TIMES TO THROW THE BALL UNITL YOU HIT THE TARGET.");
                GFX_DrawText(50,80,"USE POWER BAR AT LEFT CORNER TO ADJUST POWER AND ANGLE. ");
                GFX_DrawText(50,100,"PRESS RIGHT AND LEFT KEYBOARD TO MOVE LEFT AND RIGHT. ");
                GFX_DrawText(50,120,"PRESS T KEYBOARD TO THROW THE PROJECTILE. ");
                GFX_DrawFilledRectangle(0,560,800,640,LIGHTGRAY);
                GFX_DrawFilledCircle(0,640,80,LIGHTMAGENTA);

                /* Make figures written before draw */
                GFX_UpdateDisplay();

                /* Update the value in the array */
                num_distance += 1;

                /* Calculate the mean distance that the user throws */
                mean_distance = Mean(data_values,num_distance);

                /* Calculate the minimum and the maximum */
                min = minimum(data_values,num_distance);
                max = maximum(data_values,num_distance);

                /* Count how many times users tried */
                count += 1;

            }

        }

    /* Leave the loop in 3 trying */
    } while (count < 3);

    /* Wait for 3 second to print out the records */
    GFX_PauseFor(3000);

    /* Draw the over_interface and restart it */
    over_interface(mark, mean_distance, max, min, string_mark);

    return 0;
}

/* Set a change colour function */
void changeColour(int user_input1)
{
    switch(user_input1)
    {
    // Case is used to select the colour
    case 0:
        GFX_SetColour(RED);
        break;
    case 1:
        GFX_SetColour(LIGHTBLUE);
        break;
    case 2:
        GFX_SetColour(LIGHTGREEN);
        break;
    case 3:
        GFX_SetColour(BLUE);
        break;
    case 4:
        GFX_SetColour(GREEN);
        break;
    case 5:
        GFX_SetColour(BROWN);
        break;
    case 6:
        GFX_SetColour(LIGHTMAGENTA);
        break;
    case 7:
        GFX_SetColour(DARKGRAY);
        break;
    case 8:
        GFX_SetColour(WHITE);
        break;
    case 9:
        GFX_SetColour(CYAN);
        break;
    case 10:
        GFX_SetColour(MAGENTA);
        break;
    default:
        GFX_SetColour(BLACK);
    }

}


/* Function of drawing the projectile */
double draw_projectile_path(double initial_pos_x, double initial_pos_y, int *proj_x, int restriction_height, int x_target, int *proj_y)
{
    /* Declare variables for velocities of x,y and initial velocity, angle and final position and gravity */
    double vel_x,vel_y,initial_angle,initial_velocity,pos_x,pos_y,final_x,pre_pos_x;
    float n = 9.81;
    float time;
    int gravity;
    double velocity;

    /* Insert a bitmap following the trace of projectile */
    BITMAP image4 = GFX_LoadBitmap("coin.png");

    /* Move the line on the power bar to decide the power and the angle */
    initial_angle = draw_power_bar(&velocity);
    initial_velocity = velocity;

    /* Set the initial position for the projectile and gravity */
    pos_x = initial_pos_x + 2;
    pos_y = initial_pos_y;

    /* Set the value for previous pos_x */
    pre_pos_x = pos_x;

    /* Give initial value of pos_y */
    pos_y = 0;

    /* Change type of gravity into integer */
    gravity = (int) n;

    /* Using math to separate velocity to x and y direction */
    vel_x = initial_velocity * cos(initial_angle/180 * 3.1415926);
    vel_y = initial_velocity * sin(initial_angle/180 * 3.1415926);

    /* Move to initial point of the projectile */
    GFX_MoveTo(initial_pos_x, initial_pos_y);

    /* Set a while-loop to draw invisible projectile */
    while (pos_x <= 800 && pos_y <= 560)
    {
        /* Function to draw the projectile */
        /* Draw a filled rectangle to hide previous coin */
        GFX_DrawFilledRectangle(pre_pos_x-13,pos_y-9,pre_pos_x+13,pos_y+12,LIGHTCYAN);
        GFX_SetColour(LIGHTCYAN);

        /* Calculate the coordinates of projectile and bitmap */
        time = (pos_x - initial_pos_x) / vel_x;
        pos_y = initial_pos_y - (vel_y * time) + (gravity * time * time)/2;
        GFX_DrawLineTo(pos_x,pos_y,1);
        GFX_DrawBitmap(image4,pos_x,pos_y);

        /* Make figures written before draw */
        GFX_UpdateDisplay();

        /* Give value to previous pos_x */
        pre_pos_x = pos_x;
        pos_x += 2;

        /* If the coordinates of projectile are in the range of restriction, stop throwing */
        if (pos_x+10 >= 400 && pos_x-10 <= 440 && pos_y+6 >= restriction_height && pos_y <= 560)
        {
            break;
        }

        /* If the projectile hits the frame, stop throwing */
        else if (pos_y == 0 || pos_x == 800)
        {
            break;
        }

        /* If the projectile hits the blue target, stop throwing */
        else if (pos_x+10 >= x_target && pos_x+10 <= x_target+70 && pos_y+9 >= 490 && pos_y+9 <= 560)
        {
            break;
        }

        /* If the projectile hits the red target, stop throwing */
        else if (pos_x+10 >= x_target-120 && pos_x+10 <= x_target-40 && pos_y+9 >= 490 && pos_y+9 <= 560)
        {
            break;
        }

        /* If the projectile hits the green target, stop throwing */
        else if (pos_x+10 >= x_target+110 && pos_x+10 <= x_target+189 && pos_y+9 >= 490 && pos_y+9 <= 560)
        {
            break;
        }



    }

    /* Calculate the final x position of the projectile */
    final_x = vel_x * time;

    /* use the final_x and pos_x, pos_y into the main function */
    *proj_x = pos_x;
    *proj_y = pos_y;

    /* Clear the final coin */
    GFX_DrawFilledRectangle(pre_pos_x-13,pos_y-9,pre_pos_x+13,pos_y+12,LIGHTCYAN);

    /* Return final x-coordinate of coin used in main function */
    return final_x;

    /* Manually free the memory used by the image once done with it */
    getchar();
    GFX_FreeBitmap(image4);

    /* Make figures written before draw */
    GFX_UpdateDisplay();
}

/* Function of drawing stick man */
void draw_stick_man(double x_position, double y_position)
{
    /* Draw a circle at x_position, y_position with radius 20 and line thickness 2 */
    GFX_DrawCircle(x_position, y_position, 20, 4);

    /* Draw the ground */
    GFX_DrawLine(0,560,800,560,4);

    /* Draw body of the stick man which are four lines */
    /* Draw lines according to the coordinate of the circle*/
    GFX_DrawLine(x_position-30,y_position+40,x_position+30,y_position+40,4);
    GFX_DrawLine(x_position,y_position+20,x_position,y_position+60,4);
    GFX_DrawLine(x_position,y_position+60,x_position-20,y_position+80,4);
    GFX_DrawLine(x_position,y_position+60,x_position+20,y_position+80,4);

    /* Draw face of the stick man */
    GFX_DrawArc(x_position-2,y_position-5,5,500,240,2);
    GFX_DrawArc(x_position+10,y_position-5,20,70,80,2);

    /* move the contents of the screen buffer to the display */
    GFX_UpdateDisplay();

}

/* Function of drawing target */
void draw_target(int x_target)
{
    /* Draw three targets randomly on the ground representing different score */
    GFX_DrawFilledRectangle(x_target,550,x_target+70,560,BLUE);
    GFX_DrawFilledRectangle(x_target-120,550,x_target-40,560,RED);
    GFX_DrawFilledRectangle(x_target+110,550,x_target+189,560,GREEN);

    /* Load the image into a variable of type BITMAP to represent blue target */
    BITMAP image1 = GFX_LoadBitmap("blue_target.png");
    BITMAP image2 = GFX_LoadBitmap("green_target.png");
    BITMAP image3 = GFX_LoadBitmap("red_target.png");

    /* Draw the image to the window, the x,y position is the centre of the image. */
    /* blue_target */
    GFX_DrawBitmap(image1,x_target+35,525);

    /* green_target */
    GFX_DrawBitmap(image2,x_target+149,525);

    /* red target */
    GFX_DrawBitmap(image3,x_target-80,525);

    /* Make figures written before draw */
    GFX_UpdateDisplay();

    /* Manually free the memory used by the image once done with it */
    getchar();
    GFX_FreeBitmap(image1);
    GFX_FreeBitmap(image2);
    GFX_FreeBitmap(image3);

    /* Make figures written before draw */
    GFX_UpdateDisplay();


}

/* Function of calculating mean distance */
double Mean(double values[],int num_values)
{
    /* Declare variables */
    double average;
    int current_value;

    /* Initialise the average to zero*/
    average = 0;

    /* Calculate the sum of all of the values */
    for (current_value = 0; current_value < num_values; current_value ++)
    {
        average += values[current_value];
    }

    /* Divide by the number of values, if there are any */
    if (num_values > 0)
    {
        average /= current_value;
    }

    /* Return average and used in main funciton */
    return average;
    }

/* Function to symbolize score users get hitting different targets */
int score_board(int x, int distance, int y)
{

    /* When the projectile is hitting the blue target */
    if (distance+10 >= x && distance <= x+50 && y+9 >= 490 && y+9 <= 530)
    {
        return 50;
    }

    /* When the projectile is hitting the red target */
    else if (distance+10 >= x-60 && distance <= x-20 && y+9 >= 490 && y+9 <= 530)
    {
        return 30;
    }

    /* When the projectile is hitting the green target */
    else if (distance+10 >= x+110 && distance <= x+150 && y+9 >= 490 && y+9 <= 530)
    {
        return 60;
    }

    /* When the user didn't hit the target */
    else
    {
        return 0;
    }


}

/* Function for drawing restriction */
void draw_restriction(int restriction_height)
{
    /* Draw the restriction to restrict stick_man position before this */
    GFX_DrawFilledRectangle(400,restriction_height,440,558,LIGHTGRAY);

    /* Make restriction draw */
    GFX_UpdateDisplay();

}

/* Function for defining how power bar is working */
double draw_power_bar(double *velocity)
{
    /* Declare the coordinates of mouse position */
    int x_mouse;
    int y_mouse;
    double y_distance;
    double x_distance;

    /* Declare line length and angle between line and x-axial */
    float length;
    float angle;
    float initial_velocity;

    /* val is used to change radius into degree */
    int val = 180.0 / pi;

    /* Declare arrays to store letters of velocity and angle */
    char string_vel[15];
    char string_ang[10];

    /* Initialise the mouse and turn on mouse events. */
    GFX_InitMouse();
    GFX_RegisterMouseEvents();

    /* Initialise the font so you can draw text */
    GFX_InitFont();

    /* While loop will recognize coordinates of mouse and draw a line */
    while(1)
       {
        /* Pause the program until an event occurs */
        GFX_WaitForEvent();

        /* Once an event has occurred, check whether to move the mouse */
        if (GFX_IsEventMouseMoved())
        {
            /* Get the position of the mouse, store the values in x_mouse1 and y_mouse1 */
            GFX_GetMouseCoordinates(&x_mouse, &y_mouse);

            /* If the line is in the power bar, draw the indicator */
            if (x_mouse >= 1 && x_mouse <= 81 && y_mouse >= 561 && y_mouse <= 640)
            {
                /* Clear previous line */
                GFX_DrawFilledRectangle(0,563,80,640,LIGHTGRAY);
                GFX_DrawFilledCircle(0,640,80,LIGHTMAGENTA);

                /* CLear previous velocity and angle */
                GFX_DrawFilledRectangle(670,60,750,140,LIGHTCYAN);

                /* Make figures written before draw */
                GFX_UpdateDisplay();

                /* Display the mouse position in terminal*/
                printf("x_mouse: %d \n y_mouse: %d \n", x_mouse, y_mouse);

                /* Calculate angle between the line and the frame */
                y_distance = 640 - y_mouse;
                x_distance = x_mouse;
                angle = val * atan2(y_distance,x_distance);

                /* Calculate length between original point and mouse location */
                length = sqrt((x_mouse)*(x_mouse) + (640 - y_mouse)*(640 - y_mouse));

                /* Change the length into the initial velocity the velocity is in range of 0 - 135.8 */
                initial_velocity = 1.2 * length;

                /* Display the velocity and angle on the main interface */
                GFX_SetColour(BLACK);

                /* Change variables into string */
                sprintf(string_vel,"vel: %.1f",initial_velocity);
                sprintf(string_ang,"ang: %.1f",angle);

                /* Display velocity and angle */
                GFX_DrawText(670,60,string_vel);
                GFX_DrawText(670,100, string_ang);

                /* Draw line corresponding to coordinates of mouse */
                GFX_SetColour(BLUE);
                GFX_DrawLine(0,640,x_mouse, y_mouse,1);

                /* Display velocity and angle decided by users on screen */
                GFX_UpdateDisplay();

            }
        }

        /* If event is not moved, check if event is mouse clicked. If so, break */
        else if (GFX_IsEventMouseButton())
        {
            break;
        }
    }

    /* Use these two values to define the projectile in draw_projectile function */
    *velocity = initial_velocity;
    return angle;
}

/* Function to calculate maximum distance in 3 shooting */
double maximum(double array1[], int size)
{
    /* Declare variables */
    int current_values;
    double largest;

    /* Store the largest value of this array */
    for (current_values = 0; current_values < size; current_values ++)
    {
        if (largest < array1[current_values])
            largest = array1[current_values];
    }

    return largest;
}

/* Function to calculate minimum distance in 3 shooting */
double minimum(double array2[], int length)
{
    /* Declare variables */
    int current_values;
    double smallest;

    /* Store the smallest value of this array */
    for (current_values = 0; current_values < length; current_values ++)
    {
        if (smallest > array2[current_values])
            smallest = array2[current_values];
    }

    return smallest;
}

/* Function to define the starting interface */
void illustration(int x_position, int user_input1, int y_position,  int initial_pos_x, int initial_pos_y, int mark, int key, int proj_x, int proj_y, char string_mark[11])
{
    /* Declare variable in this function */
    char string_hit[40];
    double velocity;
    int x_target;
    int restriction_height;

    /* Check if the projectile to hit the target */
    int done = 0;

    /* Set the random position for x position of the target */
    x_target = GFX_RandNumber(560,611);


    /* Random height for restriction */
    restriction_height = GFX_RandNumber(250,520);

    /* Display the first step */
    /* Fill grey to the ground and the cyan to the background */
    GFX_DrawFilledRectangle(0,560,800,640,LIGHTGRAY);
    GFX_DrawFilledRectangle(0,0,800,560,LIGHTCYAN);

    /* Draw a quarter of the circle to decide the angle of projectile */
    GFX_DrawFilledCircle(0,640,80,LIGHTMAGENTA);

    /* Writing the reminder on the window */
    GFX_RegisterDisplayEvents();
    GFX_InitFont();
    GFX_SetColour(BLACK);
    GFX_DrawText(360,20,"TUTORIAL");
    GFX_DrawText(50,60,"FIRSTLY, BACK TO TERMINAL TO SET THE COLOUR OF STICK MAN.");
    GFX_DrawText(670,60,"vel:");
    GFX_DrawText(670,100,"ang:");
    GFX_DrawText(650,10,"Score: 0");

    /* Make figures written before draw */
    GFX_UpdateDisplay();

    /* make the colour selection above case insensitive. */
    printf("Please input the number from 0-10 to represent colour of stick man: ");
    scanf("%d",&user_input1);


    /* Display the second step */
    /* Draw a rectangle to hide the reminder for first step */
    GFX_DrawFilledRectangle(50,60,600,80,LIGHTCYAN);

    /* Draw the reminder on the top of the main interface */
    GFX_SetColour(BLACK);
    GFX_DrawText(50,60,"THE NEXT STEP: YOU CAN PRESS RIGHT AND LEFT ON THE KEYBOARD  ");
    GFX_DrawText(50,80,"TO MOVE YOUR STICK MAN.");
    GFX_DrawText(50,100,"BUT REMEMBER THE LEFT BOUNDARY AND RESTRICTION WILL STOP YOU.");
    GFX_DrawText(50,120,"WHEN YOU FINISH MOVING YOUR STICK MAN, TYPE 'T' ON KEYBOARD ");
    GFX_DrawText(50,140,"TO THROW THE MONEY.");
    GFX_DrawText(50,160,"THE TUTORIAL WILL EXIT UNTIL YOU GET THE SCORE.");

    /* Draw the stick man using the function */
    changeColour(user_input1);

    /* Draw the target using the function */
    draw_target(x_target);

    /* Draw components of the main interface */
    draw_restriction(restriction_height);
    draw_stick_man(x_position,y_position);

    /* Show how much score for different target */
    GFX_SetColour(MAGENTA);
    GFX_DrawText(x_target+20,580,"50");
    GFX_DrawText(x_target-70,580,"30");
    GFX_DrawText(x_target+100,580,"60");

    /* Make figures written before draw */
    GFX_UpdateDisplay();

    /* Set up event queue, keyboard */
    GFX_InitKeyboard();
    GFX_RegisterKeyboardEvents();

    /* Start a do-while loop to define 3 movements */
    do
    {
        /* Wait for an event */
        GFX_WaitForEvent();

        if (GFX_IsEventKeyDown())
        {

            GFX_GetKeyPress(&key);

            /* Move left */
            if (key == ALLEGRO_KEY_LEFT)
            {
                if (x_position > 50)
                {
                    /* Draw rectangle to hide the previous stick man */
                    GFX_DrawFilledRectangle(x_position-40,y_position-30,x_position+30,y_position+80,LIGHTCYAN);

                    /* Do the move of going left */
                    x_position -= 20;

                    /* Set the colour and draw the stick man again */
                    changeColour(user_input1);
                    draw_stick_man(x_position,y_position);
                    initial_pos_x = x_position + 30;
                    initial_pos_y = y_position + 40;

                    /* Draw the filled rectangle to hide the previous mark */
                    GFX_DrawFilledRectangle(700,10,800,30,LIGHTCYAN);

                    /* Change the variable into string */
                    GFX_SetColour(BLACK);
                    sprintf(string_mark, "Score: %d", mark);
                    GFX_DrawText(650,10,string_mark);

                    /* move the stick man to redisplay */
                    GFX_UpdateDisplay();
                }
            }
            /* Move right */

            else if (key == ALLEGRO_KEY_RIGHT)
            {
                if (x_position < 360)
                {
                    /* Draw a rectangle to hide the previous stick man */
                    GFX_DrawFilledRectangle(x_position-40,y_position-30,x_position+30,y_position+80,LIGHTCYAN);

                    /* Do the move of going right */
                    x_position +=  20;

                    /* Set the colour and draw the stick man again */
                    changeColour(user_input1);
                    draw_stick_man(x_position,y_position);
                    initial_pos_x = x_position + 30;
                    initial_pos_y = y_position + 40;

                    /* Draw the filled rectangle to hide the previous mark */
                    GFX_DrawFilledRectangle(700,10,800,30,LIGHTCYAN);

                    /* Change the variable into string */
                    GFX_SetColour(BLACK);
                    sprintf(string_mark, "Score: %d", mark);
                    GFX_DrawText(650,10,string_mark);

                    /* move the stick man to redisplay */
                    GFX_UpdateDisplay();
                }
            }

            /* Throw coin */

            else if (key == ALLEGRO_KEY_T)
            {
                /* Draw the projectile from the hands */
                changeColour(user_input1);
                draw_projectile_path(initial_pos_x, initial_pos_y, &proj_x, restriction_height, x_target, &proj_y);

                /* Calculate the score user gets */
                mark += score_board(x_target,proj_x,proj_y);

                /* Change the variable into string */
                GFX_DrawFilledRectangle(700,10,800,30,LIGHTCYAN);

                /* Change the variable into string */
                GFX_SetColour(BLACK);
                sprintf(string_mark, "Score: %d", mark);
                GFX_DrawText(650,10,string_mark);

                /* Redraw a quarter of the circle */
                GFX_DrawFilledCircle(0,640,80,LIGHTMAGENTA);

                /* move projectile path to the display */
                GFX_UpdateDisplay();

                /* Check if the projectile hits the target */
                /* If user didn't get mark, keep shooting */
                if (mark == 0)
                {
                    /* Redraw elements which have possibilities to be erased */
                    GFX_SetColour(BLACK);
                    GFX_DrawText(50,60,"THE NEXT STEP: YOU CAN PRESS RIGHT AND LEFT ON THE KEYBOARD  ");
                    GFX_DrawText(50,80,"TO MOVE YOUR STICK MAN.");
                    GFX_DrawText(50,100,"BUT REMEMBER THE LEFT BOUNDARY AND RESTRICTION WILL STOP YOU.");
                    GFX_DrawText(50,120,"WHEN YOU FINISH MOVING YOUR STICK MAN, TYPE 'T' ON KEYBOARD ");
                    GFX_DrawText(50,140,"TO THROW THE MONEY.");
                    GFX_DrawText(50,160,"THE TUTORIAL WILL EXIT UNTIL YOU GET THE SCORE.");
                    draw_restriction(restriction_height);
                    GFX_DrawFilledRectangle(0,560,800,640,LIGHTGRAY);
                    GFX_DrawFilledCircle(0,640,80,LIGHTMAGENTA);

                    GFX_UpdateDisplay();


                    done = 0;

                }

                /* If user gets mark, stop the turorial and tell the user mark  */
                else if (mark != 0)
                {
                    /* Change the variable into string */
                    GFX_SetColour(RED);

                    sprintf(string_hit, "CONGRATULATION, YOUR SCORE IS %d", mark);
                    GFX_DrawText(250,210,string_hit);
                    GFX_DrawText(250,240,"GAME WILL START AFTER 5 SECONDS.");

                    GFX_UpdateDisplay();

                    done = 1;

                }

            }
        }

    /* Leave the loop when the user hits the target */
    } while(done == 0);

    /*Wait for 5 seconds to exit tutorial */
    GFX_PauseFor(5000);
}

/* Function for drawing the over interface */
void over_interface(int mark, double mean_distance, int max, int min, char string_mark[11])
{
    /* Declare arrays used to display words in game window */
    char string_mean_distance[50];
    char string_max_min[40];

    /* Clear all the contents first */
    GFX_ClearWindow();

    /* Set characters' colour */
    GFX_SetColour(WHITE);

    /* Draw the over interface */
    /* If the user didn't get any mark */
    if (mark == 0)
    {
         /* Draw the mean distance */
        sprintf(string_mean_distance, "The mean distance that the user throws is %.0lf",mean_distance);
        GFX_DrawText(300,240,string_mean_distance);

        /* Draw the minimum and the maximum */
        sprintf(string_max_min,"The maximum is %d The minimum is %d.",max,min);
        GFX_DrawText(300,380,string_max_min);

        /* Draw reminder telling users that they didn't hit the target */
        GFX_DrawText(300,200,"Sorry you didn't hit the target.");

        /* Wait for 5s to restart the game again */
        GFX_DrawText(300,340,"The game will restart after 5 seconds.");
        GFX_UpdateDisplay();
        GFX_PauseFor(5000);
        GFX_CloseWindow();
        main();
    }

    /* If the user gets marks */
    else
    {
        /* Draw firework to congratulate users to get score */
        BITMAP image6 = GFX_LoadBitmap("congratulation.png");
        GFX_DrawBitmap(image6,400,80);

        /* Draw the score */
        /* Change the variable into string */
        sprintf(string_mark, "Score: %d", mark);
        GFX_DrawText(300,200, string_mark);


        /* Draw the mean distance */
        sprintf(string_mean_distance, "The mean distance that the user throws is %.0lf",mean_distance);
        GFX_DrawText(200,260,string_mean_distance);

        /* Draw the minimum and the maximum */
        sprintf(string_max_min,"The maximum is %d The minimum is %d.",max,min);
        GFX_DrawText(200,300,string_max_min);

        /* Wait for 5s to restart the game again */
        GFX_DrawText(200,340,"The game will start after 5 seconds.");
        GFX_UpdateDisplay();

        GFX_PauseFor(5000);
        GFX_CloseWindow();

        /* Release memory of bitmap */
        GFX_FreeBitmap(image6);

        /* Restart the game again from welcome window */
        main();

    }
}
