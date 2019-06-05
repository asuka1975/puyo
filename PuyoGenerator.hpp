#pragma once

#ifndef _PUYO_GENERATOR_HPP
#define _PUYO_GENERATOR_HPP

enum puyocolor;

class PuyoGenerator {
public:
	static void Initialize();
	static void GetNext(int idx, puyocolor& puyo1, puyocolor& puyo2);
	static puyocolor Generate();
private:
	~PuyoGenerator();
	static puyocolor* next1;
	static puyocolor* next2;
};

#endif