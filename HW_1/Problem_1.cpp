// AERSP 424 HW 1, Problem 2
// Authors: Conor Dowdell, Gabrielle Dowdell, Chukwu Agbo

#include <stdio.h>

// Using compiler flags of a preprocessor directive
#define MAX_GROSS_WEIGHT 2950.0
#define FORWARD_CG_LIMIT 82.1
#define AFT_CG_LIMIT 84.7

int main() {
    // Defining all the variables here
    double empty_weight, empty_weight_moment;
    int front_occupants, rear_occupants;
    double front_seat_weights[2], rear_seat_weights[2];
    double front_moment_arm, rear_moment_arm;
    int usable_fuel_gallons;
    double usable_fuel_weight_per_gallon, fuel_tank_moment_arm;
    double baggage_weight, baggage_moment_arm;
    
    // What we want the user to see and input
    // Note: We chose to use the Scanf() function to collect and read user input!
    // Source: https://www.freecodecamp.org/news/using-scanf-in-c/#:~:text=The%20scanf()%20function%20in%20C%20is%20a%20powerful%20tool,%2Dpoint%20numbers%2C%20and%20strings.
    printf("Enter the aircraft empty weight (lbs): ");
    scanf("%lf", &empty_weight);
    
    printf("Enter the aircraft empty-weight moment (pounds-inches): ");
    scanf("%lf", &empty_weight_moment);
    
    printf("Enter the number of front seat occupants: ");
    scanf("%d", &front_occupants);
    
    for (int i = 0; i < front_occupants; i++) {
        printf("Enter the weight of front seat occupant %d (lbs): ", i + 1);
        scanf("%lf", &front_seat_weights[i]);
    }
    
    printf("Enter the front seat moment arm (inches): ");
    scanf("%lf", &front_moment_arm);
    
    printf("Enter the number of rear seat occupants: ");
    scanf("%d", &rear_occupants);
    
    for (int i = 0; i < rear_occupants; i++) {
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
    for (int i = 0; i < front_occupants; i++) {
        front_seat_total_weight += front_seat_weights[i];
        front_seat_moment += front_seat_weights[i] * front_moment_arm;
    }
    
    double rear_seat_total_weight = 0.0;
    double rear_seat_moment = 0.0;
    for (int i = 0; i < rear_occupants; i++) {
        rear_seat_total_weight += rear_seat_weights[i];
        rear_seat_moment += rear_seat_weights[i] * rear_moment_arm;
    }
    
    double fuel_weight = usable_fuel_gallons * usable_fuel_weight_per_gallon;
    double fuel_moment = fuel_weight * fuel_tank_moment_arm;
    
    double baggage_moment = baggage_weight * baggage_moment_arm;
    
    double gross_weight = empty_weight + front_seat_total_weight + rear_seat_total_weight + fuel_weight + baggage_weight;
    double total_moment = empty_weight_moment + front_seat_moment + rear_seat_moment + fuel_moment + baggage_moment;
    
    double cg_location = total_moment / gross_weight;
    
    // Output initial calculations
    printf("\nInitial Gross Weight: %.2lf lbs\n", gross_weight);
    printf("Initial CG Location: %.2lf inches\n", cg_location);
    
    // Check limits
    if (gross_weight > MAX_GROSS_WEIGHT || cg_location < FORWARD_CG_LIMIT || cg_location > AFT_CG_LIMIT) {
        printf("Gross weight or CG out of limits.\n");
        
        double adjustment_fuel_weight = fuel_weight;
        while ((gross_weight > MAX_GROSS_WEIGHT || cg_location < FORWARD_CG_LIMIT || cg_location > AFT_CG_LIMIT) && adjustment_fuel_weight >= 0) {
            adjustment_fuel_weight -= 0.01;  // Reduce fuel weight by 0.01 lbs
            
            fuel_weight = adjustment_fuel_weight;
            fuel_moment = fuel_weight * fuel_tank_moment_arm;
            
            gross_weight = empty_weight + front_seat_total_weight + rear_seat_total_weight + fuel_weight + baggage_weight;
            total_moment = empty_weight_moment + front_seat_moment + rear_seat_moment + fuel_moment + baggage_moment;
            cg_location = total_moment / gross_weight;
        }
        
        printf("Adjusted Gross Weight: %.2lf lbs\n", gross_weight);
        printf("Adjusted CG Location: %.2lf inches\n", cg_location);
        printf("Adjusted fuel weight: %.2lf lbs (%.2lf gallons)\n", adjustment_fuel_weight, adjustment_fuel_weight / usable_fuel_weight_per_gallon);
    } else {
        printf("Gross weight and CG are within limits.\n");
    }
    
    return 0;
}
