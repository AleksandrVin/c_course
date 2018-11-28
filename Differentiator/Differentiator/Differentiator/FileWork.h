#pragma once
#include "pch.h"


bool ReadFormulaFromFile(Node * formula, const char * file_to_read);

bool SaveFormulaToFile(Node * formula, const char * file_to_save);