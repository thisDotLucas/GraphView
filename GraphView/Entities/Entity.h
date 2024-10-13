#pragma once
#include "Vertex.h"
#include "Edge.cpp"
#include <variant>

using Entity = std::variant<Vertex, Edge>;