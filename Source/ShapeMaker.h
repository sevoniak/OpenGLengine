#pragma once
#include "Defs.h"
#include "Shape.h"

class ShapeMaker
{
public:
	ShapeMaker(void);
	~ShapeMaker(void);

	Shape* genQuad();
	Shape* genCube();
	Shape* genCone(int numDiv);
	Shape* genPrism(int numDiv);
	Shape* genSphere(int numDiv, int numBands);
	Shape* genTorus(int circle, int loop, float trad, float crad);
};

