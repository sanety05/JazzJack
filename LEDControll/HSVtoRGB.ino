void HSVtoRGB(int h, int s, int v){

float f;

int i, p, q, t;

i = (int)floor(h / 60.0f) % 6;

f = (float)(h / 60.0f) - (float)floor(h / 60.0f);

p = (int)round(v * (1.0f - (s / 255.0f)));

q = (int)round(v * (1.0f - (s / 255.0f) * f));

t = (int)round(v * (1.0f - (s / 255.0f) * (1.0f - f)));

switch(i){

case 0 : r = v; g = t; b = p; break;

case 1 : r = q; g = v; b = p; break;

case 2 : r = p; g = v; b = t; break;

case 3 : r = p; g = q; b = v; break;

case 4 : r = t; g = p; b = v; break;

case 5 : r = v; g = p; b = q; break;

}

}
