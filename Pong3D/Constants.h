#ifndef CONSTANTS_H_
#define CONSTANTS_H_

#define PLAYER_ONE 1
#define PLAYER_TWO 2

#define PADDLE_RADIUS 1.0
#define BALL_RADIUS 1.0

const float LIGHT_POSITION[] = {0.0f, 0.0f, 1.0f, 1.0f};
const float LIGHT_DIFFUSE[] = {0.8f, 0.8f, 0.8f, 1.0f};
const float LIGHT_AMBIENT[] = {0.1f, 0.1f, 0.1f, 1.0f};
const float LIGHT_SPECULAR[] = {1.0f, 1.0f, 1.0f, 1.0f};

const float COLOR_CLEAR[] = {30.0f/255.0f, 30.0f/255.0f, 30.0f/255.0f, 1.0f};

const float MAT_SHININESS[] = {120.0f};

const float MAT_WHITE[] = {1.0f, 1.0f, 1.0f, 1.0f};
const float MAT_BLACK[] = {0.0f, 0.0f, 0.0f, 1.0f};
const float MAT_RED[] = {1.0f, 0.0f, 0.0f, 1.0f};
const float MAT_GREEN[] = {0.0f, 1.0f, 0.0f, 1.0f};
const float MAT_BLUE[] = {0.0f, 0.0f, 1.0f, 1.0f};
const float MAT_NEON_GREEN[] = {199.0f/255.0f, 221.0f/255.0f, 12.0f/255.0f, 1.0f};
const float MAT_YELLOW[] = {255.0f/255.0f, 198.0f/255.0f, 0.0f/255.0f, 1.0f};
const float MAT_ORANGE[] = {255.0f/255.0f, 132.0f/255.0f, 9.0f/255.0f, 1.0f};

const float MAT_OBJECTS[] = {216.0f/255.0f, 216.0f/255.0f, 216.0f/255.0f, 1.0f};
const float MAT_TRANSLATIONAL[] = {209.0f/255.0f, 136.0f/255.0f, 217.0f/255.0f, 1.0f};
const float MAT_ROTATIONAL[] = {255.0f/255.0f, 205.0f/255.0f, 34.0f/255.0f, 1.0f};
const float MAT_GRAVITATIONAL[] = {210.0f/255.0f, 82.0f/255.0f, 82.0f/255.0f, 1.0f};
const float MAT_ELECTRIC[] = {103.0f/255.0f, 140.0f/255.0f, 177.0f/255.0f, 1.0f};
const float MAT_MAGNETIC[] = {127.0f/255.0f, 179.0f/255.0f, 71.0f/255.0f, 1.0f};
const float MAT_ELECTRIC_ALTERNATIVE[] = {121.0f/255.0f, 171.0f/255.0f, 255.0f/255.0f, 1.0f};

const unsigned int COLOR_WHITE[] = {255, 255, 255, 255};
const unsigned int COLOR_BLACK[] = {0, 0, 0, 255};
const unsigned int COLOR_RED[] = {255, 0, 0, 255};
const unsigned int COLOR_GREEN[] = {0, 255, 0, 255};
const unsigned int COLOR_BLUE[] = {0, 0, 255, 255};
const unsigned int COLOR_NEON_GREEN[] = {199, 221, 12, 255};
const unsigned int COLOR_YELLOW[] = {255, 198, 0, 255};
const unsigned int COLOR_ORANGE[] = {255, 132, 9, 255};

const unsigned int COLOR_OBJECTS[] = {216, 216, 216, 255};
const unsigned int COLOR_TRANSLATIONAL[] = {209, 136, 217, 255};
const unsigned int COLOR_ROTATIONAL[] = {255, 205, 34, 255};
const unsigned int COLOR_GRAVITATIONAL[] = {210, 82, 82, 255};
const unsigned int COLOR_ELECTRIC[] = {103, 140, 177, 255};
const unsigned int COLOR_MAGNETIC[] = {127, 179, 71, 255};
const unsigned int COLOR_ELECTRIC_ALTERNATIVE[] = {121, 171, 255, 255};



#endif