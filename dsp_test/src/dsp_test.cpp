//============================================================================
// Name        : dsp_test.cpp
// Author      : Joe Post
// Version     :
// Copyright   : Your copyright notice
// Description : Saves raw MP3 data into vector object
//============================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstddef>
#include <vector>
#include <time.h>
#include <mutex>

#include "buffer.hpp"

using namespace std;

int main() {

	BufferHandler<float> BH;

//------------RUN PSEUDO CLOCK AND FILL BUFFER ----------//
	BH.Run();
//------------END RUN PSEUDO CLOCK AND FILL BUFFER ----------//

    return 0;
}
