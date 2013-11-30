int ltoi(unsigned char letter) {
	if (letter == 65 || letter == 97 || letter == 56) {
		/*A or a or 8*/
		return 0;
	}
	else if (letter == 66 || letter == 98 || letter == 55) {
		/*B or b or 7*/
		return 1;
	}
	else if (letter == 67 || letter == 99 || letter == 54) {
		/*C or c or 6*/
		return 2;
	}
	else if (letter == 68 || letter == 100 || letter == 53) {
		/*D or d or 5*/
		return 3;
	}
	else if (letter == 69 || letter == 101 || letter == 52) {
		/*E or e or 4*/
		return 4;
	}
	else if (letter == 70 || letter == 102 || letter == 51) {
		/*F or f or 3*/
		return 5;
	}
	else if (letter == 71 || letter == 103 || letter == 50) {
		/*G or g or 2*/
		return 6;
	}
	else if (letter == 72 || letter == 104 || letter == 49) {
		/*H or h or 1*/
		return 7;
	}
	else {
		/*return a number > 7 so the program will ask for new input*/
		return 42;
	}
}
