#include "MarkerManager.h"
#include <algorithm>
#include <sstream>


MarkerManager::MarkerManager()
{
	parser = new MarkersParser();
    markers = parser->parse();
}


MarkerManager::~MarkerManager()
{
    delete parser;
}

Marker MarkerManager::getMarker(int i)
{
	stringstream stream;
    Marker marker;

    marker = markers.at(i);

    /*stream << marker.type << " - ";
	stream << "(" << marker.startPosition.x;
	stream << ", " << marker.startPosition.y;
    stream << ", " << marker.startPosition.z << ")";*/

    return marker;
}

int MarkerManager::numMarkers()
{
	return markers.size();
}


bool MarkerManager::addMarker(Marker marker)
{
    markers.push_back(marker);
    parser->save(markers);

    ++elementsAdded;

	return false;
}


bool MarkerManager::removeMarker(int i)
{
    markers.erase(markers.begin() + i); //preferred choice to use erase-remove idiom
    parser->save(markers);

    ++elementsRemoved;

	return false;
}

