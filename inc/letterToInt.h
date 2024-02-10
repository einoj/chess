int ltoi(unsigned char letter)
{
    if (letter == 'A' || letter == 'a' || letter == '8') {
        return 0;
    } else if (letter == 'B' || letter == 'b' || letter == '7') {
        return 1;
    } else if (letter == 'C' || letter == 'c' || letter == '6') {
        return 2;
    } else if (letter == 'D' || letter == 'd' || letter == '5') {
        return 3;
    } else if (letter == 'E' || letter == 'e' || letter == '4') {
        return 4;
    } else if (letter == 'F' || letter == 'f' || letter == '3') {
        return 5;
    } else if (letter == 'G' || letter == 'g' || letter == '2') {
        return 6;
    } else if (letter == 'H' || letter == 'h' || letter == '1') {
        return 7;
    }
    /*return a number > 7 so the program will ask for new input*/
    return 42;
}
