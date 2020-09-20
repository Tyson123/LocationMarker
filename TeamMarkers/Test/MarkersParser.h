#pragma once

#include <vector>

#include "Marker.h"


class MarkersParser
{
public:
	std::vector<Marker> parse();
    void save(const std::vector<Marker>&);
};
