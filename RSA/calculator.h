/*****************************************************************//**
 * \file   calculator.h
 * \brief  Basic calculations
 * 
 * \author dqthebt
 * \date   October 2020
 *********************************************************************/
#pragma once
char add(char c1, char c2, bool& isRemembered)
{
	bool isNeedRemember = false;
	char res = '0';
	if (c1 == '0') {
		res = c2;
	} else if (c2 == '0') {
		res = '1';
	} else {
		res = '0';
		isNeedRemember = true;
	}

	if (res == '1') {
		res = isRemembered ? '0' : '1';
	} else {
		res = isRemembered ? '1' : '0';
		isRemembered = isNeedRemember;
	}

	return res;
}

char sub(char c1, char c2, bool& isRemembered)
{
	char res = '0';
	bool isNeedRemember = false;
	if (c1 == '0') {
		res = c2;
		isNeedRemember = (c2 == '1');
	} else if (c2 == '0') {
		res = '1';
	} else {
		res = '0';
	}

	if (res == '1') { // isNeedRemember = false or true
		res = isRemembered ? '0' : '1';
		isRemembered = isNeedRemember;
	} else { // isNeedRemember = false
		res = isRemembered ? '1' : '0';
	}

	return res;
}

char AND(char c1, char c2)
{
	if (c1 == '1' && c2 == '1') {
		return '1';
	}
	return '0';
}

char XOR(char c1, char c2)
{
	if (c1 == c2) {
		return '0';
	}
	return '1';
}
