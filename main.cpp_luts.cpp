//
// Created by Preoteasa Rares on 01/03/2025.
//
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <bitset>
#include <unordered_map>
#include <vector>
using namespace std::chrono;

const int SIZE = 100*1000000;


// b31 b30 b29 … b1 b0 (b31 is MSB, b0 is LSB)
// b0 b2 b4 b6 b8 .. b30 b1 b3 b5 … b29 b31
//1010101010101010=



//Model name:             Intel(R) Core(TM) i3-9100T CPU @ 3.10GHz
//Done in 601 ms
void changeordebits_lut_8b(uint32_t* input, uint32_t* output) {
/*
    std::unordered_map<uint8_t, uint8_t> hashmap1 ={{0,0},{170,255}};
    std::unordered_map<uint8_t, uint8_t> hashmap2 ={{0,0},{170,255}};
    std::unordered_map<uint8_t, uint8_t> hashmap3 ={{0,0},{170,0}};
    std::unordered_map<uint8_t, uint8_t> hashmap4 ={{0,0},{170,0}};
*/
    uint16_t lut1[3]={0,1,255};
    uint16_t lut2[3]={0,1,255};
    uint16_t lut3[1]={0};
    uint16_t lut4[1]={0};

    for (int index = 0; index < SIZE; index++) {
        //output[index] = (hashmap4[input[index] & 255] << 24) + (hashmap3[input[index] & 255] << 16)+ (hashmap2[input[index] & 255] << 8)+ hashmap1[input[index] & 255] ;
        output[index] = (lut4[input[index] & 0] << 24) + (lut3[input[index] & 0] << 16)+ (lut2[input[index] & 3] << 8)+ lut1[input[index] & 3] ;

    }


}

//Model name:             Intel(R) Core(TM) i3-9100T CPU @ 3.10GHz
//Done in 548 ms
void changeordebits_lut_16b(uint32_t* input, uint32_t* output) {
/*
    std::unordered_map<uint16_t, uint16_t> hashmap1 ={{0,0},{43690,65535}};
    std::unordered_map<uint16_t, uint16_t> hashmap2 ={{0,0},{43690,0}};
*/
    uint16_t lut1[3]={0,1,65535};

    uint16_t lut2[1]={0};

    for (int index = 0; index < SIZE; index++) {

        //output[index] = (hashmap2[input[index] & 65535] << 16) + hashmap1[input[index] & 65535] ;
        output[index] = (lut2[input[index] & 0] << 16) + lut1[input[index] & 3] ;

    }

}

void changeordebits_hash(uint32_t* input, uint32_t* output) {
    std::unordered_map<uint32_t, uint32_t> hashmap ={{0,0},{2863311530,65535}};
    for (int index = 0; index < SIZE; index++) {
        output[index] = hashmap[input[index]];
    }
}

void changeordebits_table(uint32_t* input, uint32_t* output) {

    std::bitset<32> table;

    for (int index = 0; index < SIZE; index++) {
        std::bitset<32> init_check=input[index];
        table[0] = init_check[31];
        table[1] = init_check[29];
        table[2] = init_check[27];
        table[3] = init_check[25];
        table[4] = init_check[23];
        table[5] = init_check[21];
        table[6] = init_check[19];
        table[7] = init_check[17];
        table[8] = init_check[15];
        table[9] = init_check[13];
        table[10] = init_check[11];
        table[11] = init_check[9];
        table[12] = init_check[7];
        table[13] = init_check[5];
        table[14] = init_check[3];
        table[15] = init_check[1];
        table[16] = init_check[30];
        table[17] = init_check[28];
        table[18] = init_check[26];
        table[19] = init_check[24];
        table[20] = init_check[22];
        table[21] = init_check[20];
        table[22] = init_check[18];
        table[23] = init_check[16];
        table[24] = init_check[14];
        table[25] = init_check[12];
        table[26] = init_check[10];
        table[27] = init_check[8];
        table[28] = init_check[6];
        table[29] = init_check[4];
        table[30] = init_check[2];
        table[31] = init_check[0];
        output[index] = (uint32_t)(table.to_ulong());
    }
}

void changeordebits_faster(uint32_t* input, uint32_t* output) {

    for (int index = 0; index < SIZE; index++) {

        output[index] |= ((input[index] & (1 << 0)) >> 0) << (15 - 0 / 2 + 16);

        output[index] |= ((input[index] & (1 << 1)) >>1) << (15 - 1 / 2 );

        output[index] |= ((input[index] & (1 << 2)) >> 2) << (15 - 2 / 2 + 16);

        output[index] |= ((input[index] & (1 << 3)) >>3) << (15 - 3 / 2 );

        output[index] |= ((input[index] & (1 << 4)) >> 4) << (15 - 4 / 2 + 16);

        output[index] |= ((input[index] & (1 << 5)) >>5) << (15 - 5 / 2 );

        output[index] |= ((input[index] & (1 << 6)) >> 6) << (15 - 6 / 2+16);

        output[index] |= ((input[index] & (1 << 7)) >>7) << (15 - 7 / 2 );

        output[index] |= ((input[index] & (1 << 8)) >> 8) << (15 - 8 / 2+16);

        output[index] |= ((input[index] & (1 << 9)) >>9) << (15 - 9 / 2 );

        output[index] |= ((input[index] & (1 << 10)) >> 10) << (15 - 10 / 2+16);

        output[index] |= ((input[index] & (1 << 11)) >>11) << (15 - 11 / 2 );

        output[index] |= ((input[index] & (1 << 12)) >> 12) << (15 - 12 / 2+16);

        output[index] |= ((input[index] & (1 << 13)) >>13) << (15 - 13 / 2 );

        output[index] |= ((input[index] & (1 << 14)) >> 14) << (15 - 14 / 2+16);

        output[index] |= ((input[index] & (1 << 15)) >>15) << (15 - 15 / 2 );

        output[index] |= ((input[index] & (1 << 16)) >> 16) << (15 - 16 / 2+16);

        output[index] |= ((input[index] & (1 << 17)) >>17) << (15 - 17 / 2 );

        output[index] |= ((input[index] & (1 << 18)) >> 18) << (15 - 18 / 2+16);

        output[index] |= ((input[index] & (1 << 19)) >>19) << (15 - 19 / 2 );

        output[index] |= ((input[index] & (1 << 20)) >> 20) << (15 - 20 / 2+16);

        output[index] |= ((input[index] & (1 << 21)) >>21) << (15 - 21 / 2 );

        output[index] |= ((input[index] & (1 << 22)) >> 22) << (15 - 22 / 2+16);

        output[index] |= ((input[index] & (1 << 23)) >>23) << (15 - 23 / 2 );

        output[index] |= ((input[index] & (1 << 24)) >> 24) << (15 - 24 / 2+16);

        output[index] |= ((input[index] & (1 << 25)) >>25) << (15 - 25 / 2 );

        output[index] |= ((input[index] & (1 << 26)) >> 26) << (15 - 26 / 2+16);

        output[index] |= ((input[index] & (1 << 27)) >>27) << (15 - 27 / 2 );

        output[index] |= ((input[index] & (1 << 28)) >> 28) << (15 - 28 / 2+16);

        output[index] |= ((input[index] & (1 << 29)) >>29) << (15 - 29 / 2 );

        output[index] |= ((input[index] & (1 << 30)) >> 30) << (15 - 30 / 2+16);

        output[index] |= ((input[index] & (1 << 31)) >>31) << (15 - 31 / 2 );


    }
}

void changeordebits(uint32_t* input, uint32_t* output) {
//https://stackoverflow.com/questions/46329341/how-to-rearrange-bits
    for (int index = 0; index < SIZE; index++) {
        for (int i = 0; i < 32; i ++) {
            if (i & 1 == 0) {
                uint32_t bit_i = input[index] & (1 << i);
                bit_i = bit_i >> i;
                output[index] |= bit_i << (15 - i / 2 + 16);
            }
            else {
                uint32_t bit_i = input[index] & (1 << i);
                bit_i = bit_i >> i;
                output[index] |= bit_i << (15 - i / 2);
            }
        }
    }
}


int main() {

    // data setup

    uint32_t* init_num=new uint32_t[SIZE] ;

    uint32_t* out_num=new uint32_t[SIZE] ;
    init_num[0]=0xAAAAAAAA; //for testing

    if ((init_num != NULL) && (out_num != NULL)) {
        auto start = std::chrono::high_resolution_clock::now();
        // processing
        changeordebits_lut_16b(init_num,out_num);

        auto stop = std::chrono::high_resolution_clock::now();
        std::cout << "Done in " << duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms" << std::endl;

    }
    int failed_check = 0;
    // verification
        std::bitset<32> init_check=init_num[0];
        std::bitset<32> out_check=out_num[0];
        std::cout << "ini_0= "<< init_check << std::endl;
        std::cout<< "out_0= "<<out_check<< std::endl;
    init_check=init_num[1];
    out_check=out_num[1];
        std::cout << "ini_1= "<< init_check << std::endl;
        std::cout<< "out_1= "<<out_check<< std::endl;

    // result output

    if (init_num != NULL) delete(init_num);
    if (out_num != NULL) delete(out_num);
    return 0;
}

/*
Run 1: Done in 13978 ms
ini= 10101010101010101010101010101010
out= 00000000000000001111111111111111

Run 2: in loc de bucla scriu direct liniile, in changeordebits_faster
Done in 6363 ms
ini= 10101010101010101010101010101010
out= 00000000000000001111111111111111
Aici as fi putut avea timp de rulare mai scurt, dar dupa dupa un timp total de 15 minute de scris
de mana si dupa ce am incurcat care numere trebuie sa aiba + 16 la >>
am decis sa trec mai departe

Run 3: folosesc array pt valori ca pentru editarea imaginilor, in changeordebits_table
Done in 65055 ms
ini= 10101010101010101010101010101010
out= 00000000000000001111111111111111

Run 4:folosesc unordered_map cu toate valorile deja facute
OBS: fiindca unordered_map are timp de insert si retrieval O(1) conform
https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/
o sa folosesc doar valorile pt 0 si 0xAAAAAAAA (care sunt singurele folosite in implementarea mea)
care nu ar trebui sa afecteze pozitiv rularea fata de hashmap-ul care ar trebui creat pt caz
general (cu toate valorile pt input ca key si rezultatul vrut ca valoare)
Functia este changeordebits_hash
Done in 4892 ms
ini_0= 10101010101010101010101010101010
out_0= 00000000000000001111111111111111
ini_1= 00000000000000000000000000000000
out_1= 00000000000000000000000000000000



*/

