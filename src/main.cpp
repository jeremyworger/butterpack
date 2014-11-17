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

#include "include/butterpack_codec.hpp"
#include "include/butterpack.hpp"

int main(int argc, char **argv) {

    Butterpack *butterpack;
    butterpack = new Butterpack();
    butterpack->encode(640, 480, 5, "src/butterpack.cpp","out.jpg");
    delete butterpack;
    return(0);
};
