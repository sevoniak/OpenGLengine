#include "ShapeMaker.h"


ShapeMaker::ShapeMaker(void)
{
}


ShapeMaker::~ShapeMaker(void)
{
}

Shape* ShapeMaker::genQuad()
{
	int numVerts = 4;
	int numInds = 6;

	Vertex* vertices = new Vertex[numVerts];
	vertices[0].position = Vector3(-0.5f, 0.5f, 0.0f); 
	vertices[0].normal = Vector3(0.0f, 0.0f, 1.0f);

	vertices[1].position = Vector3(0.5f, 0.5f, 0.0f); 
	vertices[1].normal = Vector3(0.0f, 0.0f, 1.0f);

	vertices[2].position = Vector3(0.5f, -0.5f, 0.0f); 
	vertices[2].normal = Vector3(0.0f, 0.0f, 1.0f);

	vertices[3].position = Vector3(-0.5f, -0.5f, 0.0f); 
	vertices[3].normal = Vector3(0.0f, 0.0f, 1.0f);

	unsigned int* indices = new unsigned int[numInds];
	indices[0] = 0; indices[1] = 2; indices[2] = 1;
	indices[3] = 0; indices[4] = 3; indices[5] = 2;

	Shape* shape = new Shape(vertices, indices, numVerts, numInds);
	return shape;
}

Shape* ShapeMaker::genCube()
{
	int numVerts = 24;
	int numInds = 36;

	Vertex* vertices = new vertex[numVerts];
	unsigned int* indices = new unsigned int [numInds];

	//Front face
	vertices[0].position = Vector3(-0.5, -0.5, -0.5); vertices[0].normal = Vector3(0,0,-1);
	vertices[1].position = Vector3(-0.5,  0.5, -0.5); vertices[1].normal = Vector3(0,0,-1);
	vertices[2].position = Vector3( 0.5, -0.5, -0.5); vertices[2].normal = Vector3(0,0,-1);
	vertices[3].position = Vector3( 0.5,  0.5, -0.5); vertices[3].normal = Vector3(0,0,-1);

	//Back face
	vertices[4].position = Vector3(-0.5, -0.5,  0.5); vertices[4].normal = Vector3(0,0,1);
	vertices[5].position = Vector3(-0.5,  0.5,  0.5); vertices[5].normal = Vector3(0,0,1);
	vertices[6].position = Vector3( 0.5, -0.5,  0.5); vertices[6].normal = Vector3(0,0,1);
	vertices[7].position = Vector3( 0.5,  0.5,  0.5); vertices[7].normal = Vector3(0,0,1);

	//Right face
	vertices[8].position = Vector3( 0.5,  0.5, -0.5); vertices[8].normal = Vector3(1,0,0);
	vertices[9].position = Vector3( 0.5, -0.5, -0.5); vertices[9].normal = Vector3(1,0,0);
	vertices[10].position = Vector3( 0.5,  0.5,  0.5); vertices[10].normal = Vector3(1,0,0);
	vertices[11].position = Vector3( 0.5, -0.5,  0.5); vertices[11].normal = Vector3(1,0,0);

	//Left face
	vertices[12].position = Vector3(-0.5,  0.5, -0.5); vertices[12].normal = Vector3(-1,0,0);
	vertices[13].position = Vector3(-0.5, -0.5, -0.5); vertices[13].normal = Vector3(-1,0,0);
	vertices[14].position = Vector3(-0.5,  0.5,  0.5); vertices[14].normal = Vector3(-1,0,0);
	vertices[15].position = Vector3(-0.5, -0.5,  0.5); vertices[15].normal = Vector3(-1,0,0);

	//Top face
	vertices[16].position = Vector3(-0.5,  0.5, -0.5); vertices[16].normal = Vector3(0,1,0);
	vertices[17].position = Vector3( 0.5,  0.5, -0.5); vertices[17].normal = Vector3(0,1,0);
	vertices[18].position = Vector3(-0.5,  0.5,  0.5); vertices[18].normal = Vector3(0,1,0);
	vertices[19].position = Vector3( 0.5,  0.5,  0.5); vertices[19].normal = Vector3(0,1,0);

	//Bottom face
	vertices[20].position = Vector3(-0.5, -0.5, -0.5); vertices[20].normal = Vector3(0,-1,0);
	vertices[21].position = Vector3( 0.5, -0.5, -0.5); vertices[21].normal = Vector3(0,-1,0);
	vertices[22].position = Vector3(-0.5, -0.5,  0.5); vertices[22].normal = Vector3(0,-1,0);
	vertices[23].position = Vector3( 0.5, -0.5,  0.5); vertices[23].normal = Vector3(0,-1,0);


	//Front
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 1; indices[4] = 3; indices[5] = 2;

	//Right
	indices[6] = 9; indices[7] = 8; indices[8] = 11;
	indices[9] = 8; indices[10] = 10; indices[11] = 11;

	//Left
	indices[12] = 12; indices[13] = 13; indices[14] = 15;
	indices[15] = 12; indices[16] = 15; indices[17] = 14;

	//Top
	indices[18] = 17; indices[19] = 16; indices[20] = 18;
	indices[21] = 17; indices[22] = 18; indices[23] = 19;

	//Bottom
	indices[24] = 20; indices[25] = 23; indices[26] = 22;
	indices[27] = 20; indices[28] = 21; indices[29] = 23;

	//Back
	indices[30] = 7; indices[31] = 5; indices[32] = 4;
	indices[33] = 7; indices[34] = 4; indices[35] = 6;

	Shape* shape = new Shape(vertices, indices, numVerts, numInds);
	return shape;
}

Shape* ShapeMaker::genCone(int numDiv)
{
	//keep number of faces in a reasonable range
	if(numDiv < 3) numDiv = 3;
	if(numDiv > 36) numDiv = 36;
	
	//changing the sign of angle will affect whether the inside or outside of the prism
	//is visible
	float angle = 360.0f / numDiv; //slice angle of each face

 	Vector3* bottomVertices = new Vector3[numDiv + 1];

    Vector3 v0bottom(0.5f, -0.5f, 0);

    Vector3 topCenter(0, 0.5f, 0);
    Vector3 bottomCenter(0, -0.5f, 0);

    bottomVertices[0] = v0bottom;
    bottomVertices[numDiv] = v0bottom;

    //define the vertices around the top and bottom of prism

    Quaternion rotation;
	Vector3 yaxis(0,1,0);
    for (int i = 1; i < numDiv; i++)
    {
		rotation.fromAxisAngle(yaxis, angle * i);
		Matrix4 rotationMatrix = rotation.toMatrix4();
	    bottomVertices[i] = v0bottom * rotationMatrix;
    }

	int numVerts = numDiv * 6;
	int numInds = numVerts;

	Vertex* vertices = new vertex[numVerts];
	unsigned int* indices = new unsigned int [numInds];

	//define the triangle pairs that make up each face
    for (int i = 0, j = 0; i < numDiv; i++, j++)
    {
        //face vertices in counterclockwise render order																	   
		vertices[6*i+0].position = bottomVertices[i];    vertices[6*i+0].normal = Vector3(vertices[6*i+0].position.x,0,vertices[6*i+0].position.z);	
	    vertices[6*i+2].position = topCenter;			 vertices[6*i+2].normal = Vector3(vertices[6*i+2].position.x,0,vertices[6*i+2].position.z);
	    vertices[6*i+1].position = bottomVertices[i+1];  vertices[6*i+1].normal = Vector3(vertices[6*i+1].position.x,0,vertices[6*i+1].position.z);

		//bottom slice triangle
		vertices[6*i+3].position = bottomCenter;		 vertices[6*i+3].normal = Vector3(0,-1,0);	
	    vertices[6*i+5].position = bottomVertices[i];    vertices[6*i+5].normal = Vector3(0,-1,0);
	    vertices[6*i+4].position = bottomVertices[i+1];  vertices[6*i+4].normal = Vector3(0,-1,0);
     }

	delete [] bottomVertices;

	// Load the index array with data.
	// Two triangles per face.
	for(int i = 0; i < numInds; i++)
	     indices[i] = i; 

	Shape* shape = new Shape(vertices, indices, numVerts, numInds);
	return shape;
}

Shape* ShapeMaker::genPrism(int numDiv)
{
	//keep number of faces in a reasonable range
	if(numDiv < 3) numDiv = 3;
	if(numDiv > 36) numDiv = 36;
	
	//changing the sign of angle will affect whether the inside or outside of the prism
	//is visible
	float angle = 360.0f / numDiv; //slice angle of each face

 	Vector3* topVertices = new Vector3[numDiv + 1];
 	Vector3* bottomVertices = new Vector3[numDiv + 1];

    Vector3 v0top(0.5f, 0.5f, 0); 
    Vector3 v0bottom(0.5f, -0.5f, 0);

    Vector3 topCenter(0, 0.5f, 0);
    Vector3 bottomCenter(0, -0.5f, 0);

    topVertices[0] = v0top;
    topVertices[numDiv] = v0top;
    bottomVertices[0] = v0bottom;
    bottomVertices[numDiv] = v0bottom;

    //define the vertices around the top and bottom of prism

    Quaternion rotation;
	Vector3 yaxis(0,1,0);
    for (int i = 1; i < numDiv; i++)
    {
		rotation.fromAxisAngle(yaxis, angle * i);
		Matrix4 rotationMatrix = rotation.toMatrix4();
	    topVertices[i] = v0top * rotationMatrix;
	    bottomVertices[i] = v0bottom * rotationMatrix;
    }

	int numVerts = numDiv * 12;
	int numInds = numVerts;

	Vertex* vertices = new vertex[numVerts];
	unsigned int* indices = new unsigned int [numInds];

	//define the triangle pairs that make up each face
    for (int i = 0, j = 0; i < numDiv; i++, j++)
    {
        //face vertices in counterclockwise render order
		vertices[12*i+0].position = topVertices[i];		  vertices[12*i+0].normal = Vector3(vertices[12*i+0].position.x,0,vertices[12*i+0].position.z);	
	    vertices[12*i+2].position = topVertices[i+1];	  vertices[12*i+2].normal = Vector3(vertices[12*i+2].position.x,0,vertices[12*i+2].position.z);
	    vertices[12*i+1].position = bottomVertices[i];    vertices[12*i+1].normal = Vector3(vertices[12*i+1].position.x,0,vertices[12*i+1].position.z);
																		   
		vertices[12*i+3].position = bottomVertices[i];    vertices[12*i+3].normal = Vector3(vertices[12*i+3].position.x,0,vertices[12*i+3].position.z);	
	    vertices[12*i+5].position = topVertices[i+1];	  vertices[12*i+5].normal = Vector3(vertices[12*i+5].position.x,0,vertices[12*i+5].position.z);
	    vertices[12*i+4].position = bottomVertices[i+1];  vertices[12*i+4].normal = Vector3(vertices[12*i+4].position.x,0,vertices[12*i+4].position.z);

		//top slice triangle
		vertices[12*i+6].position = topVertices[i];		  vertices[12*i+6].normal = Vector3(0,1,0);	
	    vertices[12*i+8].position = topCenter;			  vertices[12*i+8].normal = Vector3(0,1,0);
	    vertices[12*i+7].position = topVertices[i+1];	  vertices[12*i+7].normal = Vector3(0,1,0);

		//bottom slice triangle
		vertices[12*i+9].position = bottomCenter;		  vertices[12*i+9].normal = Vector3(0,-1,0);	
	    vertices[12*i+11].position = bottomVertices[i];   vertices[12*i+11].normal = Vector3(0,-1,0);
	    vertices[12*i+10].position = bottomVertices[i+1]; vertices[12*i+10].normal = Vector3(0,-1,0);
     }

	delete [] topVertices;
	delete [] bottomVertices;

	// Load the index array with data.
	// Two triangles per face.
	for(int i = 0; i < numInds; i++)
	     indices[i] = i; 

	Shape* shape = new Shape(vertices, indices, numVerts, numInds);
	return shape;
}

Shape* ShapeMaker::genSphere(int numDiv, int numBands) //horizontal divisions, vertical divisions
{
	int numVerts = numDiv * numBands;
	int numInds = 6 * numDiv * numBands;

	Vertex* vertices = new vertex[numVerts];
	unsigned int* indices = new unsigned int [numInds];

	//define the triangle pairs that make up each face
	int count = 0;
	for (int i = 0; i < numBands; i++)
	{
		float yPos = 0.5f * cos(Math::PI * i / (numBands-1));
		float rad = sqrt(0.5f*0.5f - yPos*yPos);
		for (int j = 0; j < numDiv; j++)
		{
			float angle = (float)(j * 2*Math::PI / numDiv); 
			vertices[count].position = Vector3(rad*cos(angle), yPos, rad*sin(angle));
			vertices[count].normal = Vector3(vertices[count].position.x, vertices[count].position.y, vertices[count].position.z);
			vertices[count].normal.normalize();
			count++;
		}
	}

	//define indices for the entire sphere
	count = 0;
	for (int i = 0; i < numBands; i++)
	{
		for (int j = 0; j < numDiv; j++)
		{
			indices[count++] = i*numDiv + j;
			indices[count++] = i*numDiv + (j+1)%numDiv;
			indices[count++] = (i+1)*numDiv + (j+1)%numDiv;

			indices[count++] = i*numDiv + j;
			indices[count++] = (i+1)*numDiv + (j+1)%numDiv;
			indices[count++] = (i+1)*numDiv + j;
		}
	}

	Shape* shape = new Shape(vertices, indices, numVerts, numInds);
	return shape;
}

Shape* ShapeMaker::genTorus(int circle, int loop, float trad, float crad)  //num of verts per circle, num of circles per torus, rad of torus, rad of circles
{
	int numVerts = circle * loop;
	int numInds = numVerts * 6;

	Vertex* vertices = new vertex[numVerts];
	unsigned int* indices = new unsigned int [numInds];

	for (int i = 0; i < loop; i++)
	{
		float theta = i * 2*Math::PI /loop; // large loop
		//crad = 0.3 + 0.08*sin(7*theta); // vary small circle radius, 7 lobes
		Vector3 ccen = trad * Vector3(cos(theta),sin(theta),0); // centre of this small circle

		for (int j = 0; j < circle; j++) // small circle
		{
				
			float phi = j * 2*Math::PI / circle; // from 0 to 2PI
				
			Vertex thisone;
			thisone.normal = Vector3(cos(theta)*sin(phi), sin(theta)*sin(phi), cos(phi));
			thisone.position = crad * thisone.normal + ccen; //Vector3(ccen.x+thisnor.x*crad, ccen.y+thisnor.y*crad, ccen.z+thisnor.z*crad);
			vertices[i*circle + j] = thisone; // add to vertex array
		}
	}

	int count = 0;
	for (int i = 0; i < loop; i++)
	{
		for (int j = 0; j < circle; j++)
		{
			// two triangles per quad
			
			indices[count++] = (unsigned int)((i*circle + j));	
			indices[count++] = (unsigned int)(i*circle + ((j + 1) % circle));
			indices[count++] = (unsigned int)(((i + 1) % loop)*circle + j);
		
			indices[count++] = (unsigned int)(i*circle + ((j + 1) % circle));
			indices[count++] = (unsigned int)(((i + 1) % loop)*circle + ((j + 1) % circle));
			indices[count++] = (unsigned int)(((i + 1) % loop)*circle + j);
		}
	}

	Shape* shape = new Shape(vertices, indices, numVerts, numInds);
	return shape;
}
