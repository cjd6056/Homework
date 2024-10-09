//AERSP 424 HW 1, Problem 1
//Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo

/* Prompt:
Assuming you are about to fly a plane that carries that following items:
(1) its own empty weight,
(2) baggage,
(3) front seat passengers,
(4) rear seat passengers, and
(5) usable fuel.
Each item contributes to the gross weight and the Center of Gravity (CG) location of the airplane.
Write a program to receive information below from the user and store them in appropriate variables
(i.e., the user should “input” the values to the code via the terminal)
• Airplane empty weight (pounds)
• Airplane empty-weight moment (pounds-inches)
• The number of front seat occupants
• Weight of each front seat occupant (pounds)
• Front seat moment arm (inches)
• The number of rear seat occupants
• Weight of each rear seat occupant (pounds)
• Rear seat moment arm (inches)
• The number of gallons of usable fuel (gallons)
• Usable fuel weights per gallon (pounds)
• Fuel tank moment arm (inches)
• Baggage weight (pounds)
• Baggage moment arm (inches)
Then, check if the gross weight and the CG location are within the airplane design limits using the
moment equation.
Moment = distance ∗ force
If not, calculate the amount of fuel that need to be added or drained to meet the limits. Also, print
out the new value of the gross weight and the CG location.
The airplane design limits are as follow:
• Maximum allowable gross weight: 2950 lbs.
• Forward C.G. limit: 82.1 inches & Aft C.G. limit: 84.7 inches
• Use a decimal precision of 0.01 lbs. when adding or draining fuel.
NOTE: All calculations must be done by a computer, e.g., no hard-coded number other than the ones
provided. You may use the following numbers to check your result (but the code needs to be able to
receive user inputs).
• Airplane empty weight (pounds): 2050
• Airplane empty-weight moment (pounds-inches): 155400
• The number of front seat occupants: 2
• Weight of each front seat occupant (pounds): 180, 150
• Front seat moment arm (inches): 85
• The number of rear seat occupants: 2
• Weight of each rear seat occupant (pounds): 160, 170
• Rear seat moment arm (inches): 121
• The number of gallons of usable fuel (gallons): 44
• Usable fuel weights per gallon (pounds): 6
• Fuel tank moment arm (inches): 75
• Baggage weight (pounds): 10
• Baggage moment arm (inches): 140
*/


#include <stdio.h>
#include <math.h>
#define MAX_GROSS_WEIGHT 2950.0
#define FORWARD_CG_LIMIT 82.1
#define AFT_CG_LIMIT 84.7

int main() 
{
    double empty_weight, empty_weight_moment;
    int front_occupants, rear_occupants;
    double front_seat_weights[2], rear_seat_weights[2];
    double front_moment_arm, rear_moment_arm;
    int usable_fuel_gallons;
    double usable_fuel_weight_per_gallon, fuel_tank_moment_arm;
    double baggage_weight, baggage_moment_arm;

    // User inputs
    printf("Enter the aircraft empty weight (lbs): ");
    scanf("%lf", &empty_weight);

    printf("Enter the aircraft empty-weight moment (pounds-inches): ");
    scanf("%lf", &empty_weight_moment);

    printf("Enter the number of front seat occupants: ");
    scanf("%d", &front_occupants);

    for (int i = 0; i < front_occupants; i++) 
    {
        printf("Enter the weight of front seat occupant %d (lbs): ", i + 1);
        scanf("%lf", &front_seat_weights[i]);
    }

    printf("Enter the front seat moment arm (inches): ");
    scanf("%lf", &front_moment_arm);

    printf("Enter the number of rear seat occupants: ");
    scanf("%d", &rear_occupants);

    for (int i = 0; i < rear_occupants; i++) 
    {
        printf("Enter the weight of rear seat occupant %d (lbs): ", i + 1);
        scanf("%lf", &rear_seat_weights[i]);
    }

    printf("Enter the rear seat moment arm (inches): ");
    scanf("%lf", &rear_moment_arm);

    printf("Enter the number of gallons of usable fuel: ");
    scanf("%d", &usable_fuel_gallons);

    printf("Enter the weight of usable fuel per gallon (lbs): ");
    scanf("%lf", &usable_fuel_weight_per_gallon);

    printf("Enter the fuel tank moment arm (inches): ");
    scanf("%lf", &fuel_tank_moment_arm);

    printf("Enter the baggage weight (lbs): ");
    scanf("%lf", &baggage_weight);

    printf("Enter the baggage moment arm (inches): ");
    scanf("%lf", &baggage_moment_arm);

    // Calculations (Weights & Moments)
    double front_seat_total_weight = 0.0;
    double front_seat_moment = 0.0;
    for (int i = 0; i < front_occupants; i++) 
    {
        front_seat_total_weight += front_seat_weights[i];
        front_seat_moment += front_seat_weights[i] * front_moment_arm;
    }

    double rear_seat_total_weight = 0.0;
    double rear_seat_moment = 0.0;
    for (int i = 0; i < rear_occupants; i++) 
    {
        rear_seat_total_weight += rear_seat_weights[i];
        rear_seat_moment += rear_seat_weights[i] * rear_moment_arm;
    }

    double fuel_weight = usable_fuel_gallons * usable_fuel_weight_per_gallon;
    double fuel_moment = fuel_weight * fuel_tank_moment_arm;

    double baggage_moment = baggage_weight * baggage_moment_arm;

    // Include fuel weight in initial gross weight and CG calculations
    double gross_weight_without_fuel = empty_weight + front_seat_total_weight + rear_seat_total_weight + baggage_weight;
    double total_moment_without_fuel = empty_weight_moment + front_seat_moment + rear_seat_moment + baggage_moment;

    double gross_weight = gross_weight_without_fuel + fuel_weight;
    double total_moment = total_moment_without_fuel + fuel_moment;

    double cg_location = total_moment / gross_weight;

    // Output initial calculations
    printf("\nInitial Gross Weight (including entered fuel weight): %.2lf lbs\n", gross_weight);
    printf("Initial CG Location (including entered fuel weight): %.2lf inches\n", cg_location);

    // Check limits
    if (gross_weight > MAX_GROSS_WEIGHT) 
    {
        printf("WARNING: Gross weight exceeds maximum limit!\n");

        // Calculate how much fuel can be removed to satisfy Gross Weight requirement
        double adjustment_fuel_weight = fuel_weight;
        while (gross_weight > MAX_GROSS_WEIGHT && adjustment_fuel_weight > 0) 
        {
            adjustment_fuel_weight -= 1.00; // Decrease fuel weight by 1.00 lbs

            // Recalculate weights and moments
            fuel_weight = adjustment_fuel_weight;
            fuel_moment = fuel_weight * fuel_tank_moment_arm;

            gross_weight = gross_weight_without_fuel + fuel_weight;
            total_moment = total_moment_without_fuel + fuel_moment;
            cg_location = total_moment / gross_weight;
        }
      
      // Useful for debugging!
    
    if (cg_location >= FORWARD_CG_LIMIT && cg_location <= AFT_CG_LIMIT && gross_weight <= MAX_GROSS_WEIGHT)
    {
        printf("Adjusted Gross Weight: %.2lf lbs\n", gross_weight);
        printf("Adjusted CG Location: %.2lf inches\n", cg_location);
        printf("Adjusted fuel weight: %.2lf lbs (%.2lf gallons)\n", adjustment_fuel_weight, adjustment_fuel_weight / usable_fuel_weight_per_gallon);
        printf("Final Adjustments successful. CG and Gross weight should now be within limits... Ready for takeoff!\n");

    }
        
      
      
    } 

    // Check CG after gross weight adjustment
    if (cg_location < FORWARD_CG_LIMIT || cg_location > AFT_CG_LIMIT) 
    {
        //printf("WARNING: CG is out of limits after initial adjustments. We need to adjust fuel to move the CG.\n");

        // Adjust the fuel weight gradually to bring CG within limits
        double adjustment_fuel_weight = fuel_weight;
        while ((cg_location < FORWARD_CG_LIMIT || cg_location > AFT_CG_LIMIT)) 
        {
            // If CG is too far forward
            if (cg_location < FORWARD_CG_LIMIT) 
            {
                adjustment_fuel_weight -= 0.01; // Reduce fuel to shift CG aft
            } 
            // If CG is too far aft
            else if (cg_location > AFT_CG_LIMIT) 
            {
                adjustment_fuel_weight += 0.01; // Add fuel to shift CG forward
            }

            // Recalculate weights and moments after adjusting fuel
            fuel_weight = adjustment_fuel_weight;
            fuel_moment = fuel_weight * fuel_tank_moment_arm;

            gross_weight = gross_weight_without_fuel + fuel_weight;
            total_moment = total_moment_without_fuel + fuel_moment;
            cg_location = total_moment / gross_weight;

            // Check if gross weight exceeds the maximum allowed
            if (gross_weight > MAX_GROSS_WEIGHT) 
            {
                printf("WARNING: Unable to adjust CG without exceeding maximum gross weight.\n");
                break;
            }
        }

        // Final CG and weight after adjustment
        printf("\nFinal Adjusted Gross Weight: %.2lf lbs\n", gross_weight);
        printf("Final Adjusted CG Location: %.2lf inches\n", cg_location);

        if (cg_location < FORWARD_CG_LIMIT || cg_location > AFT_CG_LIMIT)
        {
            printf("WARNING: CG still out of limits after fuel adjustment. Further redistribution is needed.\n");
        }
        else
        {
            printf("Final Adjustments successful. CG and Gross weight should now be within limits... Ready for takeoff!\n");
        }
    } 
   


    return 0; // Indicate successful execution
}
