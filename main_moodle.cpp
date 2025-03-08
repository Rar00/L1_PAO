#include <iostream>
#include <chrono>
#include <bitset>

using namespace std::chrono;

const int SIZE = 100*1000*1000UL;

// 3GHz = 3 billion ops
// 0.1 billion number
// 1/30 = 30ms seconds if I will process every cycle, 1 number
// 200 M * 4B = 800 MB ~ 1GB

void invertnumbitsV0(uint32_t* in, uint32_t* out) {
    // assume out is zeroed
    for (int index = 0; index < SIZE; index++) {
        for (int i = 0; i < 32; i ++) {
            if (i & 1 == 0) {
                uint32_t bit_i = in[index] & (1 << i);
                bit_i = bit_i >> i;
                out[index] |= bit_i << (15 - i / 2 + 16);
            }
            else {
                uint32_t bit_i = in[index] & (1 << i);
                bit_i = bit_i >> i;
                out[index] |= bit_i << (15 - i / 2);
            }
        }
    }
// b31 b30 b29 … b1 b0 (b31 is MSB, b0 is LSB)
// b0 b2 b4 b6 b8 .. b30 b1 b3 b5 … b29 b31
}


void invertnumbits(uint32_t* in, uint32_t* out) {
    // assume out is zeroed
    for (register int index = 0; index < SIZE; index++) {
        register uint32_t resultin = in[index];
        register uint32_t resultout = 0;
        for (int i = 0; i < 32; i += 2) {
                register uint32_t bit_i = resultin & (1 << i);
                bit_i = bit_i >> i;
                resultout |= bit_i << (15 - (i >> 1) + 16);

                register uint32_t bit_i2 = resultin & (1 << (i+1));
                bit_i2 = bit_i2 >> (i+1);
                resultout |= bit_i2 << (15 - ((i+1) >> 1));
        }
        out[index] = resultout;
    }
// b31 b30 b29 … b1 b0 (b31 is MSB, b0 is LSB)
// b0 b2 b4 b6 b8 .. b30 b1 b3 b5 … b29 b31
}

// V0: 9202ms
// V1 avoid excessive branching + 2 fors: 8907ms
// V2 register variables hint 3800ms
// V3 shift instead of division 3800ms
// V4 -O3 gcc compiler optimizations 408 ms

// 4-bit lookup table: 8 look-ups in a 256 entries 4-bit tables (8 tables) => 1 KB
// 8-bit lookup table: 4 look-ups in a 64k entries 8-bit tables (4 tables) => 4*64KB = 256 KB
// 32-bit lookup table: 1 look-up in a 4G entries (1 table) => 4G * 4B = 16 GB memory

int main() {
    uint32_t* bufferin = new uint32_t[SIZE];
    uint32_t* bufferout = new uint32_t[SIZE];
    if ((bufferin != NULL) && (bufferout != NULL)) {
        bufferin[0] = 0xAAAAAAAA;
       // data setup
        auto start = std::chrono::high_resolution_clock::now();
        invertnumbits(bufferin, bufferout);
        auto stop = std::chrono::high_resolution_clock::now();
        // verification
        // result output
        std::bitset<32> numberin = bufferin[0];
        std::bitset<32> numberout = bufferout[0];

        std::cout << numberin << std::endl;
        std::cout << numberout << std::endl;

        std::cout << "Done in " << duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << std::endl;
    }
    else std::cout << "Not enough memory" << std::endl;
    if (bufferin != NULL) delete(bufferin);
    if (bufferout != NULL) delete(bufferout);
    return 0;
}