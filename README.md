# Collision-Detection

Solves collision detection and response between 2D primitives and 3D frustums. I wrote this back in 2013 and should not be used on any production code, but should provide a good example of how to handle basic collision.

## Supported Shapes

* AABB (Axis-Aligned Bounding Box)
* Circle
* X-axis-aligned capsule
* Y-axis-aligned capsule
* Convex Hull
* Point

## Basic Usage

```
Collision2DShape shapeA = Collision2DAABB(2, 4);
MthVector2 positionA = MthVector2(1, 2);

Collision2DShape shapeB = Collision2DCircle(3);
MthVector2 positionB = MthVector2(2, 1);

// Detection
if (Collision2DCheck(shapeA, positionA, shapeB, positionB))
{
	// Shapes are overlapping!
}

// Response
Collision2DResult result;
if (Collision2DResponse(shapeA, positionA, shapeB, positionB, result))
{
	// A collision has occurred!
	positionA += Collision2DResult.Direction;
}
```
