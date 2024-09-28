#include <cub3D.h>

#define DEGREE_TO_RAD (PI / 180.0)
#define INCREMENT 0.1
#define NUM_DEGREES (3600) // 360 degrees with 0.1 degree increments

// Lookup tables for sine and cosine
float sin_table[NUM_DEGREES];
float cos_table[NUM_DEGREES];

// Function to precompute the sine and cosine values
void init_trig_tables() {
    for (int i = 0; i < NUM_DEGREES; i++) {
        float radians = i * INCREMENT * DEGREE_TO_RAD; // Convert to radians
        sin_table[i] = sin(radians);
        cos_table[i] = cos(radians);
    }
}

// Function to get sine from the lookup table
float lookup_sin(float angle) {
    int index = (int)(angle / INCREMENT) % NUM_DEGREES; // Convert to table index
    return sin_table[index];
}

// Function to get cosine from the lookup table
float lookup_cos(float angle) {
    int index = (int)(angle / INCREMENT) % NUM_DEGREES; // Convert to table index
    return cos_table[index];
}