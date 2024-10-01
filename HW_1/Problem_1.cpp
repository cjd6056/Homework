// AERSP 424 HW 1, Problem 1
// Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo
// Code looks good. CAO 1 Oct

#include <stdio.h>
#include <math.h> // Include math library for absolute value function
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
        printf("Gross weight exceeds maximum limit.\n");

        // Calculate how much fuel can be removed
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

        printf("Final Adjusted Gross Weight: %.2lf lbs\n", gross_weight);
        printf("Adjusted CG Location: %.2lf inches\n", cg_location);
        printf("Adjusted fuel weight: %.2lf lbs (%.2lf gallons)\n", adjustment_fuel_weight, adjustment_fuel_weight / usable_fuel_weight_per_gallon);
    } 

    // Check CG after gross weight adjustment
    if (cg_location < FORWARD_CG_LIMIT || cg_location > AFT_CG_LIMIT) 
    {
        printf("CG is out of limits after adjustments. We need to adjust fuel to move the CG.\n");

        // Determine if we need to add or remove fuel to bring CG within limits
        double original_fuel_weight = fuel_weight; // Keep track of the original fuel weight
        double fuel_needed_to_move_cg = 0.0;

        if (cg_location < FORWARD_CG_LIMIT) 
        {
            // Calculate how much fuel is needed to bring CG above forward limit
            fuel_needed_to_move_cg = (FORWARD_CG_LIMIT - cg_location) * gross_weight / fuel_tank_moment_arm;
            fuel_needed_to_move_cg = fmax(0.0, fuel_needed_to_move_cg); // Ensure it's not negative
        } 
        else if (cg_location > AFT_CG_LIMIT) 
        {
            // Calculate how much fuel is needed to bring CG below aft limit
            fuel_needed_to_move_cg = (cg_location - AFT_CG_LIMIT) * gross_weight / fuel_tank_moment_arm;
            fuel_needed_to_move_cg = fmax(0.0, fuel_needed_to_move_cg); // Ensure it's not negative
        }

        printf("Fuel needed to bring CG within limits: %.2lf lbs\n", fuel_needed_to_move_cg);
        printf("This corresponds to %.2lf gallons of fuel (without capping to usable fuel).\n", fuel_needed_to_move_cg / usable_fuel_weight_per_gallon);
    } 
    else 
    {
        printf("Gross weight and CG are within limits.\n");
    }

    return 0; // Indicate successful execution
}
