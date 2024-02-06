#include "pcPull.h"

pcPull::pcPull(int quan) : pcs(pull(quan)) {}

Pc& pcPull::operator[](int i) { return pcs[i]; }
