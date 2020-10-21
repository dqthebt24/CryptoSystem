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