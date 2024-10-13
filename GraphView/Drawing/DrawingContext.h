#pragma once
#include "EdgeDrawingContext.h"
#include "VertexDrawingContext.h"
#include "NoneDrawingContext.h"
#include <variant>

using DrawingContext = std::variant<EdgeDrawingContext, VertexDrawingContext, NoneDrawingContext>;

