#ifndef MARKER_MANAGER_H_
#define MARKER_MANAGER_H_

#include <vector>
#include <string>

#include "Marker.h"
#include "MarkersParser.h"

using namespace std;

class MarkerManager
{
public:
	MarkerManager();
    ~MarkerManager();

	int numMarkers();

	bool addMarker(Marker);
    bool removeMarker(int);

    Marker getMarker(int i);

private:
	MarkersParser* parser;
    vector<Marker> markers;

    int elementsAdded = 0;
    int elementsRemoved = 0;
};

#endif // MARKER_MANAGER_H_
