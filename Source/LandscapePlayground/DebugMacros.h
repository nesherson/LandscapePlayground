#pragma once

#include "DrawDebugHelpers.h"

#define DRAW_DEBUG_SPHERE(Location) if (const UWorld* World = GetWorld()) DrawDebugSphere(World, Location, 75.f, 24, FColor::Red, false, 30.f)
#define DRAW_DEBUG_LINE(StartLocation, EndLocation) if (const UWorld* World = GetWorld()) DrawDebugLine(World, StartLocation, EndLocation, FColor::Red, false, 30.f)