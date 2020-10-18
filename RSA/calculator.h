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

	//printf("a=%c; b=%c, res=%c; true/false=%d\n", c1, c2, res, isRemembered);
	return res;
}