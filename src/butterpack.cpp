/*
This file is part of butterpack.

butterpack is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

butterpack is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with butterpack.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <fstream>
#include <iostream>

#include "opencv2/opencv.hpp"
#include "include/butterpack_codec.hpp"
#include "include/butterpack.hpp"

using namespace std;
using namespace cv;

/**
 * Encodes a buffer into multiple image files
 *
 * @param w int width of the images
 * @param h int height of the images
 * @param cells int cell size of the images
 * @param in char* input filename 
 * @param out char* output filename 
 */
void Butterpack::encode(int w, int h, int cells, char *in, char *out) {
 
    ButterpackCodec *codec = new ButterpackCodec();
    char *input_data = codec->read_data(in);
    char filename[30];

    int input_size = codec->filesize(in);
    int images = codec->images(w, h, cells, input_size);
    int bytes_per_image = codec->bytes(w, h, cells);

    char buffer[bytes_per_image]; // buffer for one image

    // foreach image convert and write image
    for(int i = 0; i < images; i++) {
        sprintf(filename, "%s%d.jpg", out, i);
        int offset = i * bytes_per_image; 
        for(int b = 0; b < bytes_per_image; b++) {
            buffer[b] = input_data[offset + b];
        }
        Mat im = codec->encode_single(w, h, cells, buffer);
        imwrite(filename, im);
    }

    delete[] buffer;
    delete[] input_data;
    delete codec;
};

/**
 * Decodes a buffer from multiple images to a file
 *
 * @param w int width of the images
 * @param cells int cell size of the images
 * @param h int height of the images
 * @param in char* input filename 
 * @param out char* output filename 
 */
void Butterpack::decode(int w, int h, int cells, char *in, char *out) {
    ButterpackCodec *codec;
    fstream fs;

    codec = new ButterpackCodec();

    char *data;
    Mat image = imread(in);
    data = codec->decode_single(image, w, h, cells);
    fs.open(out, fstream::out | fstream::binary); 
    fs << data;
    fs.close();

    delete[] data;
    delete codec;
};

