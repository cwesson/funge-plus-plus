/**
 * @file FungeSemantic.h
 * Type declaration for semantics.
 * @author Conlan Wesson
 */

#pragma once

#include <functional>

namespace Funge {

typedef std::function<bool()> semantic_t;

}
