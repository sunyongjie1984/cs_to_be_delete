
#pragma once

#ifndef IFC
#define IFC(expr) do {{hr = (expr); if (FAILED(hr)) goto Cleanup;}} while(0)
#endif

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))
#endif
