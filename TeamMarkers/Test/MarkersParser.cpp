#include "MarkersParser.h"

#include <string>
#include <sstream>
#include <iostream>

#define NUM_SAVED_MARKERS 8

const char* SAVED_MARKERS[] = {
// positionX	positionY
    "390		  250\0",
    "470          170\0",
    "600          240\0",
    "730          140\0",
    "780		  230\0",
    "789          280\0",
    "750          360\0",
    "780          460\0",
};


std::vector<Marker> MarkersParser::parse()
{
	std::vector<Marker> parsedMarkers;

	std::string str;
	for (int i = 0; i < NUM_SAVED_MARKERS; ++i)
	{
		const char* markerBuffer = SAVED_MARKERS[i];
		std::stringstream stream;
		stream << markerBuffer;

		Marker marker;

        /*int markerType;
		stream >> markerType;
        marker.type = (Marker::Type)markerType;*/

        stream >> marker.startPosition.x >> marker.startPosition.y;
		parsedMarkers.push_back(marker);
	}

	return parsedMarkers;
}


void MarkersParser::save(const std::vector<Marker>&)
{
    // Not implemented yet.
}

