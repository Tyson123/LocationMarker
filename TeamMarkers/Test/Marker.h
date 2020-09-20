#pragma once

struct Position
{
	float x;
	float y;
};

struct Marker
{
	enum Type
	{
		ARROW,
		DRAWING
	} type;

	Position startPosition;
};
