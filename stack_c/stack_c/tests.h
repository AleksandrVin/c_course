#pragma once

#include "config.h"

#include "unittest.h"
#include "Stack.h"

static size_t passed = 0; // need for DEBUGING
static size_t total_passed = 9;  // need for DEBUGING

bool Test43_42(Stack* stack);

bool TestPushPop10(Stack* stack, int elem_to_push);

bool TestTestDump(Stack* stack);

bool TestTryPopEmpty(Stack* stack);

bool TestTryGetLast(Stack* stack);

bool TestPushAndPopLarge(Stack* stack);